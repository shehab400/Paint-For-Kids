#pragma once

#ifndef ADD_SQUARE_ACTION_H
#define ADD_SQUARE_ACTION_H



#include "Action.h"

class ApplicationManager;
class CFigure;

class AddSquareAction :
	public Action
{
private:
	Point c;
	GfxInfo SquareGfxinfo;
	CFigure* fig;

public:
	AddSquareAction(ApplicationManager* pApp);

	//Reads HEXAGON parameters
	virtual void ReadActionParameters();

	//Add HEXAGON the ApplicationManager
	virtual void Execute();
	CFigure* GetFig();


};

#endif