#include "AddCircleAction.h"
#include "../ApplicationManager.h"

#include "..\Figures\CCircle.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"

//(don't forgot to inherit from figure circle)

AddCircleAction::AddCircleAction(ApplicationManager* pApp) : Action(pApp)
{}

void AddCircleAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Circle: Click at Center");

	//Read center and store in point c1
	pIn->GetPointClicked(c1.x, c1.y);

	pOut->PrintMessage("New Circle: Click a point on the circle");

	//Read point on circle and store in point c2
	pIn->GetPointClicked(c2.x, c2.y);

	circleGfxinfo.isFilled = false;	//default
	//get drawing, filling colors and pen width from the interface
	circleGfxinfo.DrawClr = pOut->getCrntDrawColor();
	circleGfxinfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}


//Execute the action
void AddCircleAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a rectangle with the parameters read from the user
	CCircle* C = new CCircle(c1, c2, circleGfxinfo, pManager->GetIDCount());// create new circle(don't forgot to inherit from figure circle)
	pManager->IncrmentIDCount();
	//Add the rectangle to the list of figures
	pManager->AddFigure(C); //Add the new circle to figurelist
	pManager->AddToUndoList(this);
}


CFigure* AddCircleAction::GetFig() {
	return fig;
}