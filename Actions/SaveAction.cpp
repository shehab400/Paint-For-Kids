#include "SaveAction.h"
#include "..\ApplicationManager.h"

SaveAction::SaveAction(ApplicationManager* p) :Action(p)
{

}
void SaveAction::ReadActionParameters()
{
	pOut = pManager->GetOutput();
	pIn = pManager->GetInput();
	pOut->PrintMessage("Enter File Name");
	filename = pIn->GetSrting(pOut);

}
void SaveAction::Execute()
{
	CFigure* c = NULL;
	ReadActionParameters();
	filename = pIn->GetSrting(pOut);
	file.open(filename, ios::out);
	file << c->getColorString((pOut->getCrntDrawColor())) << "   ";
	file << c->getColorString((pOut->getCrntFillColor())) << endl;
	pManager->SaveAll(file);
	pOut->ClearStatusBar();
	pOut->PrintMessage("file saved");
}