#ifndef SWITCH_TO_PLAY_ACTION_H
#define SWITCH_TO_PLAY_ACTION_H


#include "Action.h"

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

class UndoAction : public Action {
private:
	Output* pOut;
	Action* action;
	CFigure* fig;
	color old_clr;
	Point Old_P;
	bool delete_figure;
	bool add_figure;
	bool change_color;
	bool change_draw_clr;
	bool move_figure;
public:
	UndoAction(ApplicationManager* pApp);
	void ReadActionParameters();
	void Execute();
};

#endif