#include "SwitchToPlayAction.h"
#include "..\ApplicationManager.h"

SwitchToPlayAction::SwitchToPlayAction(ApplicationManager* pApp) : Action(pApp)
{

}

void SwitchToPlayAction::ReadActionParameters()
{
	pOut = pManager->GetOutput();
	filename = pManager->GetPlayFile();
}

void SwitchToPlayAction::Execute()
{
	ofstream file(filename, ios::out);
	pManager->SaveAll(file);
	ReadActionParameters();
	pOut->ClearStatusBar();
	pOut->PrintMessage("switch to play mode : creating play tool bar");
	pOut->CreatePlayToolBar();
	file.close();
}


