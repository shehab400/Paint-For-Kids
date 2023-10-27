#include "AddSquareAction.h"
#include "../ApplicationManager.h"

#include "..\Figures\CSquare.h"

#include "..\GUI\input.h"
#include "..\GUI\Output.h"
//(don't forgot to inherit from figure Square

AddSquareAction::AddSquareAction(ApplicationManager* pApp) :Action(pApp)
{}

void AddSquareAction::ReadActionParameters()
{
	//Get a Pointer to the Input / Output Interfaces
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();

	pOut->PrintMessage("New Square: Click at Center");

	//Read center and store in point c
	pIn->GetPointClicked(c.x, c.y);


	SquareGfxinfo.isFilled = false;	//default
	//get drawing, filling colors and pen width from the interface
	SquareGfxinfo.DrawClr = pOut->getCrntDrawColor();
	SquareGfxinfo.FillClr = pOut->getCrntFillColor();

	pOut->ClearStatusBar();

}

CFigure* AddSquareAction::GetFig() { return fig; }

//Execute the action
void AddSquareAction::Execute()
{
	//This action needs to read some parameters first
	ReadActionParameters();

	//Create a rectangle with the parameters read from the user
	fig = new CSquare(c, SquareGfxinfo, pManager->GetIDCount());// create new Square(don't forgot to inherit from figure Square
	pManager->IncrmentIDCount();
	//Add the rectangle to the list of figures
	pManager->AddFigure(fig); //Add the new Square to figurelist
	pManager->AddToUndoList(this);
}

