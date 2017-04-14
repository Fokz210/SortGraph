#pragma once

//=========================================================================
//! This header is useful if you want to create a group of buttons (menu)
//!
//! Enjoy!
//!
//! (c) Ivan Cheremisenov (9.4.2017) Version 1.0
//==========================================================================

struct BUTTON //Button structure
{
	int command;

	const char* text;
	const char* helpText;
	COLORREF color;

	HDC dc;

	int x1, y1;
	int x2, y2;
	int status;
}; 

class MENU //Menu class
{
public:
	const int BS_NONE = 0, //Button status
			  BS_PRESSED = 1,
		      BS_MOUSEOVER = 2; 

	const int CMD_NONE = 0; //Null button command

	BUTTON buttons[10] = {}; //Group of buttons
	int size = 0; //Size of this group

    /*!parameter!*/ bool UseHint = false; //Turn on this parameter if you want to use hint!
	/*!parameter!*/ bool ClearWindow = true; //Turn off this parameter if you don't fant to clear your window!

	MENU(BUTTON menu[], unsigned int menusize, int inx0, int iny0, int intsizex, int intsizey, int inbuttonsizex, int inbuttonsizey) //You know what is it, don't you?
	{
		size = menusize;
		ButtonsInitAll(inx0, iny0, intsizex, intsizey, inbuttonsizex, inbuttonsizey);

		for (int i = 0; i < menusize; i++) //I think it is not the best(!) way 
		{
			buttons[i].command = menu[i].command;
			buttons[i].text = menu[i].text;
			buttons[i].helpText = menu[i].helpText;
			buttons[i].color = menu[i].color;
			buttons[i].dc = menu[i].dc;  
		}
	}

	int ButtonTest(BUTTON* button) //Testing one(!) button
	{
		int mx = txMouseX(), my = txMouseY();

		if (button->x1 <= mx && mx <= button->x2 &&
			button->y1 <= my && my <= button->y2)
		{
			button->status = BS_MOUSEOVER;

			if (txMouseButtons() == 1)
			{
				button->status = BS_PRESSED;
				return BS_PRESSED;
			}
		}
		else
			button->status = BS_NONE;

		return BS_NONE;
	}

	void ButtonDraw(const BUTTON* button) //Drawing one(!) button
	{
		txSetColor(TX_BLACK);
		txSetFillColor((button->status == BS_MOUSEOVER) ? TX_YELLOW : ((button->color) ? button->color : TX_ORANGE));

		int hint = (button->status == BS_MOUSEOVER) ? 0 : 0;

		txRectangle(button->x1 - hint, button->y1 - hint, button->x2 + hint, button->y2 + hint);

		if (button->dc)
			txBitBlt(txDC(), button->x1, button->y1,
				button->x2 - button->x1, button->y2 - button->y1,
				button->dc);

		txDrawText(button->x1, button->y1, button->x2, button->y2, button->text, DT_CENTER | DT_VCENTER | DT_WORDBREAK | DT_WORD_ELLIPSIS | DT_EDITCONTROL);

		if (button->status == BS_MOUSEOVER && UseHint)
		{
			txSetFillColor(TX_WHITE);
			txSetColor (TX_WHITE);

		    txRectangle(100, txGetExtentY() - 30, txGetExtentX() - 100, txGetExtentY());

		    txSetColor(TX_BLACK);

			txDrawText (100, txGetExtentY() - 30, txGetExtentX() - 100, txGetExtentY(), button->helpText);
		}
	}

	void ButtonsInitAll(int x0, int y0, int tSizeX, int tSizeY, int buttonSizeX, int buttonSizeY) //Initiating all buttons
	{
		for (int i = 0; i < size; i++)
		{
			buttons[i].x1 = x0 + i * tSizeX;
			buttons[i].y1 = y0 + i * tSizeY;
			buttons[i].x2 = x0 + i * tSizeX + buttonSizeX;
			buttons[i].y2 = y0 + i * tSizeY + buttonSizeY;
		}
	}

	void ButtonsDrawAll() //Drawing all buttons
	{
		for (int i = 0; i < size; i++)
			ButtonDraw(&buttons[i]);
	}

	int ButtonsTestAll() //Testing all buttons 
	{
		for (int i = 0; i < size; i++)
			if (ButtonTest(&buttons[i]) == BS_PRESSED) return buttons[i].command;

		return CMD_NONE;
	}

	int RunMenu() //Main class func. Returning command, which button is pressed
	{
		while (!GetAsyncKeyState(VK_ESCAPE))
		{
			txSetFillColor(TX_WHITE);

			if(ClearWindow) txClear();

			int command = ButtonsTestAll();
			if (command != CMD_NONE) return command;

			ButtonsDrawAll();

			txSleep(50);
			txClearConsole();
		}
		return CMD_NONE;
	}
};
