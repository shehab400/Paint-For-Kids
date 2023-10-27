#include "AddHexagonAction.h"
#include "../ApplicationManager.h"

#include "..\Figures\CHexagon.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
//(don't forgot to inherit from figure HEXAGON)

AddHexagonAction::AddHexagonAction(ApplicationManager* pApp) : Action(pApp)
{}

void AddHexagonAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Hexagon: Click at Center");

	//Read center and store in point c
	pIn->GetPointClicked(c.x, c.y);


	HexagonGfxinfo.isFilled = false;	//default
	//get drawing, filling colors and pen width from the interface
	HexagonGfxinfo.DrawClr = pOut->getCrntDrawColor();
	HexagonGfxinfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}


//Execute the action
void AddHexagonAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a rectangle with the parameters read from the user
	fig = new CHexagon(c, HexagonGfxinfo, pManager->GetIDCount());// create new Hexagon(don't forgot to inherit from figure hexagon
	pManager->IncrmentIDCount();
	//Add the rectangle to the list of figures
	pManager->AddFigure(fig); //Add the new Hexagon to figurelist
	pManager->AddToUndoList(this);
}

CFigure* AddHexagonAction::GetFig() {
	return fig;
}