#pragma once

#ifndef ADD_TRIANGLE_ACTION_H
#define ADD_TRIANGLE_ACTION_H



#include "Action.h"

class ApplicationManager;
class CFigure;
class Input;
class Output;


class AddTriangleAction :
	public Action
{
private:
	Point P1, P2, P3; //TRIANGLE Corners
	GfxInfo TriangleGfxInfo;
	CFigure* fig;
	Output* pOut;
	Input* pIn;
public:
	AddTriangleAction(ApplicationManager* pApp);

	//Reads TRIANGLE parameters
	virtual void ReadActionParameters();

	//Add TRIANGLE to the ApplicationManager
	virtual void Execute();
	CFigure* GetFig();

};

#endif