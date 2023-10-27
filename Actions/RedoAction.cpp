#include "RedoAction.h"
#include "AddSquareAction.h"
#include "AddRectAction.h"
#include "AddTriangleAction.h"
#include "AddCircleAction.h"
#include "AddHexagonAction.h"
#include "ChangeColorAction.h"
#include "MoveFigureAction.h"
#include "DeleteFigureAction.h"
#include "..\ApplicationManager.h"


RedoAction::RedoAction(ApplicationManager* pApp) : Action(pApp) { pManager->SetLastUndoRedo(true); }

void RedoAction::ReadActionParameters() {
	pOut = pManager->GetOutput();
	action = pManager->GetLastRedo();
	if (dynamic_cast<AddSquareAction*>(action)) {
		fig = (dynamic_cast<AddSquareAction*>(action)->GetFig());
		add_figure = true;
	}
	else if (dynamic_cast<AddRectAction*>(action)) {
		fig = (dynamic_cast<AddRectAction*>(action)->GetFig());
		add_figure = true;
	}
	else if (dynamic_cast<AddHexagonAction*>(action)) {
		fig = (dynamic_cast<AddHexagonAction*>(action)->GetFig());
		add_figure = true;
	}
	else if (dynamic_cast<AddCircleAction*>(action)) {
		fig = (dynamic_cast<AddCircleAction*>(action)->GetFig());
		add_figure = true;
	}
	else if (dynamic_cast<AddTriangleAction*>(action)) {
		fig = (dynamic_cast<AddTriangleAction*>(action)->GetFig());
		add_figure = true;
	}
	else if (dynamic_cast<MoveFigureAction*>(action)) {
		fig = dynamic_cast<MoveFigureAction*>(action)->GetFig();
		P = fig->GetPtBeforeMove();
		move_figure = true;
	}
	else if (dynamic_cast<DeleteFigureAction*>(action)) {
		fig = dynamic_cast<DeleteFigureAction*>(action)->GetFig();
		delete_figure = true;
	}
	else if (dynamic_cast<ChangeColorAction*>(action)) {
		fig = dynamic_cast<ChangeColorAction*>(action)->GetFig();
		clr = dynamic_cast<ChangeColorAction*>(action)->GetColor();
		change_draw_color = dynamic_cast<ChangeColorAction*>(action)->GetMode();
		change_color = true;
	}
}

void RedoAction::Execute() {
	if (pManager->LastUndoRedo()) {
		if (delete_figure) {
			fig->Delete(pOut);
		}
		else if (add_figure) {
			pManager->AddFigure(fig);
		}
		else if (move_figure) {
			fig->Move(pOut, pManager->GetInput(), P);
		}
		else if (change_color) {
			GfxInfo info = fig->getGfx();
			if (change_draw_color) {
				info.FillClr = clr;
			}
			else {
				info.DrawClr = clr;
			}
			fig->setGfx(info);
			fig->Draw(pOut);
		}
		pManager->AddToUndoList(action);
	}
	pManager->RemoveFromRedoList();

}

