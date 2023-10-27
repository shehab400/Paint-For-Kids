#ifndef MOVE_FIG_ACTION_H
#define MOVE_FIG_ACTION_H

#include "Action.h"

#pragma once

class ApplicationManager;
class CFigure;
class Input;
class Output;


class MoveFigureAction :public Action {
private:
	Point Old_P;
	CFigure* fig;
	Output* pOut;
	Input* pIn;
public:
	MoveFigureAction(ApplicationManager* pApp);
	void ReadActionParameters();
	void Execute();
	CFigure* GetFig();
	Point GetOldP();
};

#endif