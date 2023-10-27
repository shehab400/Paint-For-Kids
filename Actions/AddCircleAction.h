#pragma once

#ifndef ADD_CIRCLE_ACTION_H
#define ADD_CIRCLE_ACTION_H



#include "Action.h"

class ApplicationManager;
class CFigure;

class AddCircleAction :
	public Action
{
private:
	Point c1, c2;
	GfxInfo circleGfxinfo;
	CFigure* fig;
public:
	AddCircleAction(ApplicationManager* pApp);

	//Reads Circle parameters
	virtual void ReadActionParameters();

	//Add Circle the ApplicationManager
	virtual void Execute();
	CFigure* GetFig();
};

#endif