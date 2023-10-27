#include "ClearAllAction.h"
#include "../ApplicationManager.h"

ClearAllAction::ClearAllAction(ApplicationManager* pApp) :Action(pApp) {}

void ClearAllAction::ReadActionParameters() {
	pOut = pManager->GetOutput();
	pIn = pManager->GetInput();

}

void ClearAllAction::Execute()
{
	ReadActionParameters();
	pOut->ClearDrawArea();
	pOut->PrintMessage("Cleared!");
}
