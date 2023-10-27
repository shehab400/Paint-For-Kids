#pragma once

#ifndef ADD_RECT_ACTION_H
#define ADD_RECT_ACTION_H



#include "Action.h"

class ApplicationManager;
class CFigure;

//Add Rectangle Action class
class AddRectAction: public Action
{
private:
	Point P1, P2; //Rectangle Corners
	GfxInfo RectGfxInfo;
	CFigure* fig;
public:
	AddRectAction(ApplicationManager *pApp);

	//Reads rectangle parameters
	virtual void ReadActionParameters();
	
	//Add rectangle to the ApplicationManager
	virtual void Execute() ;
	CFigure* GetFig();
	
};

#endif