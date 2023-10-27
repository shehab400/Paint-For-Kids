#include "MoveFigureAction.h"
#include "..\ApplicationManager.h"

MoveFigureAction::MoveFigureAction(ApplicationManager* pApp) : Action(pApp) {
}

void MoveFigureAction::ReadActionParameters() {
	pOut = pManager->GetOutput();
	pIn = pManager->GetInput();
	
}

void MoveFigureAction::Execute() {
	ReadActionParameters();
	fig = pManager->GetSelectedFig();
	if (fig != NULL) {
		fig->Move(pOut, pIn);
		Old_P = fig->GetPtBeforeMove();
		pOut->ClearStatusBar();
	}
}

CFigure* MoveFigureAction::GetFig() { return this->fig; }
Point MoveFigureAction::GetOldP() { return Old_P; }
