#ifndef DEFS_H
#define DEFS_H

#include "CMUgraphicsLib\CMUgraphics.h"

//This file contains some global constants and definitions to be used in the project.
enum ActionType //The actions supported (you can add more if needed)
{
	DRAW_RECT,		//Draw Rectangle
	EXIT,			//Exit
	TO_DRAW,		//Switch interface to Draw mode
	TO_PLAY,		//Switch interface to Play mode
	EMPTY,			//A click on empty place in the toolbar
	DRAWING_AREA,	//A click on the drawing area
	STATUS,			//A click on the status bar
	DRAW_SQUARE,
	DRAWTRIANGLE,
	DRAW_HEX,
	DRAW_CIRCLE,
	SELECT,
	CHANGE_DRAW_COLOR,
	CHANGE_FILL_COLOR,
	CHANGE_COLOR,
	DELETE_FIGURE,
	MOVE_FIGURE,
	UNDO,
	REDO,
	CLEAR,
	SAVE,
	LOAD,
	STRT_REC,
	STP_REC,
	PLAY_REC,
	PICK_BY_CLR,
	PICK_BY_TYPE,
	PICK_BOTH,
	RESTART,
	ACTION_COUNT
};

struct Point	//To be used for figures points
{
	int x, y;
};

struct GfxInfo	//Graphical info of each figure (you may add more members)
{
	color DrawClr;	//Draw color of the figure
	color FillClr = GREEN;	//Fill color of the figure
	bool isFilled;	//Figure Filled or not
	int BorderWdth;	//Width of figure borders

};

#endif