#include "lib\SortLib.h" //SortLib.h now is only in BETA!!! It has no comments!
#include "lib\Menu.h" //Menu.h version 1.0 now. Check it to see help.

//=============================================================================
//! SortGraph version 3.0
//!
//! (c) Ivan Cheremisenov (9.4.2017)
//=============================================================================

const int CMD_NONE = 0,
		  CMD_SLCT = 1,
		  CMD_BUBL = 2,
          CMD_EXIT = 3,
		  CMD_CLER = 4,
		  CMD_QSRT = 5,
		  CMD_CNSL = 6,
		  CMD_MUSC = 7;


int StartScreen(); //IDK how to name this func, but Google Translater(c) named it screensaver. Well, ok.
void Loading();
bool ExitProgram(HDC dc);

int main()
{
	txClearConsole();
	txDisableAutoPause();
	txBegin();

	txCreateWindow(1000, 1000);

	HDC background = txLoadImage("res//img//SortGraph.bmp"); //loading background resource

	Loading();

	txSelectFont("Comic Sans MS", 18);

	BUTTON buttons[] = { { CMD_QSRT, "Быстрая сортировка", "Click and see the quick sort efficiency graph"    , TX_LIGHTBLUE, },
					  { CMD_SLCT, "Сортировка выбором", "Click and see the selection sort efficiency graph", TX_MAGENTA, },
					  { CMD_BUBL, "Сортировка пузырьком", "Click and see the bubble sort efficiency graph" , TX_LIGHTGREEN, },
					  { CMD_CLER, "Очистить графики", "Clear graphs"                                       , TX_ORANGE, },
					  { CMD_EXIT, "Выход из программы", "Exit app"                                         , TX_RED, } }; //Initiating buttons.


	MENU menu(buttons, sizearr(buttons), 800, 250, 0, 140, 150, 100); //Creating menu obj.

	menu.ClearWindow = false; //Turning off window clearing.

	txSetFillColor(TX_WHITE);
	txClear();

	txBitBlt(txDC(), 0, 0, 1000, 1000, background);

	txSetColor(TX_ORANGE);

	while (true) //Main switch
	{
		switch (menu.RunMenu())
		{
		case CMD_SLCT: SortGraph(Selection, TX_MAGENTA, TX_MAGENTA);
			break;

		case CMD_BUBL: SortGraph(BubbleSort, TX_LIGHTGREEN, TX_LIGHTGREEN);
			break;

		case CMD_QSRT: QuickSortGraph(TX_LIGHTBLUE, TX_LIGHTBLUE);
			break;

		case CMD_CLER:
		{
			txClear();
			txSetColor(TX_ORANGE);
			txBitBlt(txDC(), 0, 0, 1000, 1000, background);
		}
		break;

		case CMD_EXIT:
		{
			txDeleteDC(background);
			return 0;
		}
		break;

		default: break;
		}
	}
	return 0;
}

int StartScreen()
{
	txSetColor(TX_LIGHTBLUE);

	for (int i = 0; i <= 1000; i++)
	{
		if (i % 30 == 0) txSetColor(RGB(rand() % 256, rand() % 256, rand() % 256));
		txLine(0, i, i, 0);
		txLine(1000, 1000 - i, 1000 - i, 1000);
		Sleep(2);
		if (GetAsyncKeyState(VK_SPACE)) return 0;
	}

	txSelectFont("Comic Sans MS", 50);
	txSetColor(TX_LIGHTGREEN);
	txTextOut(400, 500, "Made by Ivan(c)");

	txSetColor(TX_BLACK);
	Sleep(2000);

	for (int i = 0; i <= 1000; i++)
	{
		txLine(0, i, i, 0);
		txLine(1000, 1000 - i, 1000 - i, 1000);
		Sleep(1);
		if (GetAsyncKeyState(VK_SPACE)) return 0;
	}
	return 0;
}

void Loading()
{
	for (double x = 0; x < 200; x++)
	{
		txSetFillColor(RGB(255 - x / 200 * 255, 255 - x / 200 * 255, 255 - x / 200 * 255));
		txClear();
		txDrawText(txGetExtentX() / 2 - 100, txGetExtentY() / 2 - 75, txGetExtentX() / 2 + 100, txGetExtentY() / 2 - 50, "Loading...");

		txSetColor(RGB(x / 200 * 255, x / 200 * 255, x / 200 * 255));
		txRectangle(txGetExtentX() / 2 - 100, txGetExtentY() / 2 - 25, txGetExtentX() / 2 + 100, txGetExtentY() / 2 + 25);

		txSetFillColor(RGB(x / 200 * 255, x / 200 * 255, x / 200 * 255));
		txRectangle(txGetExtentX() / 2 - 100, txGetExtentY() / 2 - 25, txGetExtentX() / 2 - 100 + x, txGetExtentY() / 2 + 25);

		Sleep(10);
	}

	Sleep(500);
}

bool ExitProgram(HDC dc)
{
	if (!GetAsyncKeyState(VK_ESCAPE))
	{
		txDeleteDC(dc);
		return false;
	}
	else
		return true;
}

