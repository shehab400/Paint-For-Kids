#include "DeleteFigureAction.h"
#include "../ApplicationManager.h"

DeleteFigureAction::DeleteFigureAction(ApplicationManager* pApp) :Action(pApp) {}

void DeleteFigureAction::ReadActionParameters() {
	pOut = pManager->GetOutput();
	pIn = pManager->GetInput();

}

void DeleteFigureAction::Execute()
{
	ReadActionParameters();
	bool Fig = pManager->DeleteFig();
	if (Fig) {
		pOut->ClearDrawArea();
		pOut->PrintMessage("Figure Deleted!");
		fig = pManager->GetSelectedFig();
	}
	else
		pOut->PrintMessage("No Figure selected!");
}

CFigure* DeleteFigureAction::GetFig() {
	return fig;
}
