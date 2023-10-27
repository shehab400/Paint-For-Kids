#include "SwitchToDrawAction.h"
#include "..\ApplicationManager.h"

SwitchToDrawAction::SwitchToDrawAction(ApplicationManager* pApp): Action(pApp)
{

}



void SwitchToDrawAction::ReadActionParameters()
{
	pOut = pManager->GetOutput();
	load_action = new LoadAction(pManager, pManager->GetPlayFile());
}

void SwitchToDrawAction::Execute()
{
	ReadActionParameters();
	pOut->ClearStatusBar();
	pOut->PrintMessage("switch to draw mode : creating draw tool bar");
	pOut->CreateDrawToolBar();
	load_action->Execute();
	delete load_action;
}