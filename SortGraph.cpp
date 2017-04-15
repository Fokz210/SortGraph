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
		  CMD_MUSC = 7,
		  CMD_ISRT = 8;


void Loading();
bool ExitProgram(HDC dc);

int main()
{
	txClearConsole();
	txDisableAutoPause();
	txBegin();

	_txWindowStyle &= ~WS_CAPTION;
	txCreateWindow(1600, 1200);

	HDC background = txLoadImage("res//img//SortGraph.bmp"); //loading background resource

	txSelectFont("Comic Sans MS", 40);

	BUTTON buttons[] = { { CMD_QSRT, "Быстрая сортировка", "Click and see the quick sort efficiency graph"  , TX_LIGHTBLUE },
					   { CMD_SLCT, "Сортировка выбором", "Click and see the selection sort efficiency graph", TX_MAGENTA },
					   { CMD_BUBL, "Сортировка пузырьком", "Click and see the bubble sort efficiency graph" , TX_LIGHTGREEN },
					   { CMD_ISRT, "Сортировка вставкой", ""                                                , TX_YELLOW },
					   { CMD_CLER, "Очистить графики", "Clear graphs"                                       , TX_ORANGE },
					   { CMD_EXIT, "Выход из программы", "Exit app"                                         , TX_RED } }; //Initiating buttons.


	MENU menu(buttons, sizearr(buttons), 1150, 50, 0, 900 / 6, 400, 900 / 6 - 20); //Creating menu obj.

	menu.ClearWindow = false; //Turning off window clearing.

	txSetFillColor(TX_BLACK);
	txClear();

	txBitBlt(txDC(), 0, 0, 1600, 1200, background);

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
			txBitBlt(txDC(), 0, 0, 1600, 1200, background);
		}
            break;

        case CMD_ISRT: SortGraph(BinaryInsertionSort, TX_YELLOW, TX_YELLOW);
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

