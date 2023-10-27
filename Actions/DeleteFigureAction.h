#ifndef DLT_FIG_ACTION_H
#define DLT_FIG_ACTION_H

#pragma once

#include"Action.h"


class ApplicationManager;
class CFigure;
class Input;
class Output;

class DeleteFigureAction :public Action
{
private:
	CFigure* fig;
	Output* pOut;
	Input* pIn;
public:
	DeleteFigureAction(ApplicationManager* pApp);
	virtual void ReadActionParameters();
	virtual void Execute();
	CFigure* GetFig();
};

#endif