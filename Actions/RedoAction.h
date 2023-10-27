#ifndef REDO_ACTION_H
#define REDO_ACTION_H

#include "Action.h"
#pragma once


class ApplicationManager;
class CFigure;
class AddSquareAction;
class AddRectangleAction;
class AddTriangleAction;
class AddHexagonAction;
class ChangeColorAction;
class MoveFigureAction;
class DeleteFigureAction;
class Input;
class Output;



class RedoAction : public Action {
private:
	Output* pOut;
	Action* action;
	CFigure* fig;
	color clr;
	Point P;
	bool delete_figure;
	bool add_figure;
	bool change_color;
	bool move_figure;
	bool change_draw_color;
public:
	RedoAction(ApplicationManager* pApp);
	void ReadActionParameters();
	void Execute();
};

#endif