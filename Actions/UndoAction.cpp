#include "UndoAction.h"
#include "AddSquareAction.h"
#include "AddRectAction.h"
#include "AddTriangleAction.h"
#include "AddCircleAction.h"
#include "AddHexagonAction.h"
#include "ChangeColorAction.h"
#include "MoveFigureAction.h"
#include "DeleteFigureAction.h"
#include "..\ApplicationManager.h"


UndoAction::UndoAction(ApplicationManager* pApp) : Action(pApp) { 
	pManager->SetLastUndoRedo(true);
	delete_figure = false;
	add_figure = false;
	move_figure = false;
	change_color = false;
}

void UndoAction::ReadActionParameters() {
	pOut = pManager->GetOutput();
	action = pManager->GetLastUndo();
	if (dynamic_cast<AddSquareAction*>(action)) {
		fig = (dynamic_cast<AddSquareAction*>(action)->GetFig());
		delete_figure = true;
	}
	else if (dynamic_cast<AddRectAction*>(action)) {
		fig = (dynamic_cast<AddRectAction*>(action)->GetFig());
		delete_figure = true;
	}
	else if (dynamic_cast<AddHexagonAction*>(action)) {
		fig = (dynamic_cast<AddHexagonAction*>(action)->GetFig());
		delete_figure = true;
	}
	else if (dynamic_cast<AddCircleAction*>(action)) {
		fig = (dynamic_cast<AddCircleAction*>(action)->GetFig());
		delete_figure = true;
	}
	else if (dynamic_cast<AddTriangleAction*>(action)) {
		fig = (dynamic_cast<AddTriangleAction*>(action)->GetFig());
		delete_figure = true;
	}
	else if (dynamic_cast<MoveFigureAction*>(action)) {
		fig = dynamic_cast<MoveFigureAction*>(action)->GetFig();
		Old_P = fig->GetPtBeforeMove();
		move_figure = true;
	}
	else if (dynamic_cast<DeleteFigureAction*>(action)) {
		fig = dynamic_cast<DeleteFigureAction*>(action)->GetFig();
		add_figure = true;
	}
	else if (dynamic_cast<ChangeColorAction*>(action)) {
		fig = dynamic_cast<ChangeColorAction*>(action)->GetFig();
		old_clr = dynamic_cast<ChangeColorAction*>(action)->GetOldColor();
		change_draw_clr = dynamic_cast<ChangeColorAction*>(action)->GetMode();
		change_color = true;
	}
}

void UndoAction::Execute() {
	ReadActionParameters();
		if (delete_figure) {
			fig->Delete(pOut);
		}
		else if (add_figure) {
			pManager->AddFigure(fig);
		}
		else if (move_figure) {
			fig->Move(pOut, pManager->GetInput() , Old_P);
		}
		else if (change_color) {
			GfxInfo info = fig->getGfx();
			if (change_draw_clr) {
				info.FillClr = old_clr;
			}
			else {
				info.DrawClr = old_clr;
			}
			fig->setGfx(info);
			fig->Draw(pOut);
		}
		pManager->RemoveFromUndoList();
		pManager->AddToRedoList(action);

}

