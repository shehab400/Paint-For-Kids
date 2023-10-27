#ifndef SELECT_FIG_ACTION_H
#define SELECT_FIG_ACTION_H

#include "Action.h"

#pragma once

class ApplicationManager;
class CFigure;
class Input;
class Output;

class SelectFigureAction : public Action {
private:
	Output* pOut;
	Input* pIn;
	Point P;
	CFigure* selected_fig;

public:
	SelectFigureAction(ApplicationManager* pApp);

	void ReadActionParameters();
	void Execute();
};

#endif