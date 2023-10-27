#include "Input.h"
#include "Output.h"


Input::Input(window* pW)
{
	pWind = pW; //point to the passed window
}

void Input::GetPointClicked(int& x, int& y) const
{
	pWind->WaitMouseClick(x, y);	//Wait for mouse click
}

string Input::GetSrting(Output* pO) const
{
	string Label;
	char Key;
	while (1)
	{
		pWind->WaitKeyPress(Key);
		if (Key == 27)	//ESCAPE key is pressed
			return "";	//returns nothing as user has cancelled label
		if (Key == 13)	//ENTER key is pressed
			return Label;
		if ((Key == 8) && (Label.size() >= 1))	//BackSpace is pressed
			Label.resize(Label.size() - 1);
		else
			Label += Key;
		if (pO)
			pO->PrintMessage(Label);
	}
}

//This function reads the position where the user clicks to determine the desired action
ActionType Input::GetUserAction() const
{
	int x, y;
	pWind->WaitMouseClick(x, y);	//Get the coordinates of the user click

	if (UI.InterfaceMode == MODE_DRAW)	//GUI in the DRAW mode
	{
		//[1] If user clicks on the Toolbar
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);
			//Divide x coord of the point clicked by the menu item width (int division)
			//if division result is 0 ==> first item is clicked, if 1 ==> 2nd item and so on

			switch (ClickedItemOrder)
			{
			case ITM_RECT: return DRAW_RECT;
			case ITM_EXIT: return EXIT;
			case ITM_SQUARE: return DRAW_SQUARE;
			case ITM_TRIANGLE: return DRAWTRIANGLE;
			case ITM_HEXAGON: return DRAW_HEX;
			case ITM_CIRCLE: return DRAW_CIRCLE;
			case ITM_SWITCH: return TO_PLAY;
			case ITM_SELECTONE: return SELECT;
			case ITM_DRWCOLOR: return CHANGE_DRAW_COLOR;
			case ITM_FILLINGCOLOR: return CHANGE_FILL_COLOR;
			case ITM_BLACK: return CHANGE_COLOR;
			case ITM_YELLOW: return CHANGE_COLOR;
			case ITM_ORANGE: return CHANGE_COLOR;
			case ITM_RED: return CHANGE_COLOR;
			case ITM_GREEN: return CHANGE_COLOR;
			case ITM_BLUE: return CHANGE_COLOR;
			case ITM_DELETEFIGURE: return DELETE_FIGURE;
			case ITM_MOVEFIGURE: return MOVE_FIGURE;
			case ITM_UNDO: return UNDO;
			case ITM_REDO: return REDO;
			case ITM_CLEARALL: return CLEAR;
			case ITM_STARTRECORD: return STRT_REC;
			case ITM_STOPRECORD: return STP_REC;
			case ITM_PLAYRECORD: return PLAY_REC;
			case ITM_SAVEGRAPH: return SAVE;
			case ITM_LOADGRAPH: return LOAD;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}


		}

		//[2] User clicks on the drawing area
		if (y >= UI.ToolBarHeight && y < UI.height - UI.StatusBarHeight)
		{
			return DRAWING_AREA;
		}

		//[3] User clicks on the status bar
		return STATUS;
	}
	else	//GUI is in PLAY mode
	{
		if (y >= 0 && y < UI.ToolBarHeight)
		{
			//Check whick Menu item was clicked
			//==> This assumes that menu items are lined up horizontally <==
			int ClickedItemOrder = (x / UI.MenuItemWidth);

			switch (ClickedItemOrder)
			{
			case ITM_SWITCHTODRAWMODE: return TO_DRAW;
			case ITM_FIGURECOLOR: return PICK_BY_CLR;
			case ITM_FIGURETYPE: return PICK_BY_TYPE;
			case ITM_FIGURETYPEANDCOLOR: return PICK_BOTH;
			case ITM_RESTART: return RESTART;

			default: return EMPTY;	//A click on empty place in desgin toolbar
			}


		}

		return STATUS;	//just for now. This should be updated
	}


}
/////////////////////////////////

Input::~Input()
{
}
