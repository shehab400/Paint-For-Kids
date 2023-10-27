#pragma once

#ifndef ADD_HEXAGON_ACTION_H
#define ADD_HEXAGON_ACTION_H



#include "Action.h"

class ApplicationManager;
class CFigure;

class AddHexagonAction :
    public Action
{
private:
	Point c;
	GfxInfo HexagonGfxinfo;
	CFigure* fig;
public:
	AddHexagonAction(ApplicationManager* pApp);
	//Reads HEXAGON parameters
	virtual void ReadActionParameters();

	//Add HEXAGON the ApplicationManager
	virtual void Execute();
	CFigure* GetFig();

};

#endif