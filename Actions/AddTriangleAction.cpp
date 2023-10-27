#include "AddTriangleAction.h"
#include "../ApplicationManager.h"

#include "..\Figures\CTriangle.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
#include <iostream>

using namespace std;

AddTriangleAction::AddTriangleAction(ApplicationManager* pApp) :Action(pApp)
{}

void AddTriangleAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	pOut = pManager->GetOutput();
	pIn = pManager->GetInput();

	pOut->PrintMessage("New Triangle: Click at first corner");

	//Read 1st corner and store in point P1
	pIn->GetPointClicked(P1.x, P1.y);

	pOut->PrintMessage("New Triangle: Click at second corner");

	//Read 2nd corner and store in point P2
	pIn->GetPointClicked(P2.x, P2.y);

	pOut->PrintMessage("New Triangle: Click at third corner");
	//Read 3nd corner and store in point P3
	pIn->GetPointClicked(P3.x, P3.y);

	TriangleGfxInfo.isFilled = false;	//default
	//get drawing, filling colors and pen width from the interface
	TriangleGfxInfo.DrawClr = pOut->getCrntDrawColor();
	TriangleGfxInfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

//Execute the action
void AddTriangleAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a Triangle with the parameters read from the user
	fig = new CTriangle(P1, P2, P3, TriangleGfxInfo, pManager->GetIDCount());// create new Triangle(don't forgot to inherit from figure triangle)
	pManager->IncrmentIDCount();
	//Add the Triangle to the list of figures
	pManager->AddFigure(fig);
	pManager->AddToUndoList(this);
}

CFigure* AddTriangleAction::GetFig(){
	return fig;
}