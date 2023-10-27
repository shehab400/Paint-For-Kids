#pragma once

#ifndef CHANGE_CLR_ACTION_H
#define CHANGE_CLR_ACTION_H



#include "Action.h"

class ApplicationManager;
class CFigure;
class Input;
class Output;


class ChangeColorAction : public Action {
private:
	Output* pOut;
	Input* pIn;
	CFigure* fig;
	color clr;
	color old_clr;
	bool mode;
public:
	ChangeColorAction(ApplicationManager* pApp, bool mode); // mode is true for changing filling color and false for chnaging drawing color
	void ReadActionParameters();
	void Execute();
	color GetOldColor();
	color GetColor();
	CFigure* GetFig();
	bool GetMode();
};

#endif