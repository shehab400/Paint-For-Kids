#include "SelectFigureAction.h"
#include "..\ApplicationManager.h"

SelectFigureAction::SelectFigureAction(ApplicationManager* pApp) : Action(pApp) {}

void SelectFigureAction::ReadActionParameters() {
	pOut = pManager->GetOutput();
	pIn = pManager->GetInput();
	pIn->GetPointClicked(P.x, P.y);
	selected_fig = pManager->GetFigure(P.x, P.y);
}

void SelectFigureAction::Execute() {
	ReadActionParameters();
	if (selected_fig != NULL) {
		if (selected_fig->IsSelected()) {
			selected_fig->SetSelected(false);
			pManager->SetSelectedFig(-1);
			selected_fig->Draw(pOut);
		}
		else {
			pManager->GetSelectedFig()->SetSelected(false);
			selected_fig->SetSelected(true);
			pManager->SetSelectedFig(selected_fig->getID());
			selected_fig->Draw(pOut);
			selected_fig->PrintInfo(pOut);
		}
	}
}

