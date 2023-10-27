#include "LoadAction.h"
#include "../ApplicationManager.h"
#include "..\Figures\CCircle.h"
#include "..\Figures\CSquare.h"
#include "..\Figures\CRectangle.h"
#include "..\Figures\CTriangle.h"
#include "..\Figures\CHexagon.h"



LoadAction::LoadAction(ApplicationManager* pApp, string filename) :Action(pApp)
{
	this->filename = filename;
}

void LoadAction::ReadActionParameters()
{
	Output* pOut = pManager->GetOutput();
	Input* pIn = pManager->GetInput();
	pOut->PrintMessage("Load: Enter file name");
	if (filename == "") {
		filename = pIn->GetSrting(pOut);
	}

}


void LoadAction::Execute()
{
	Output* pOut = pManager->GetOutput();
	ReadActionParameters();

	file.open(filename, ios::in);
	string DrawClr, FillClr;


	if (file.is_open())     //Check if There is a File with this Name or Not
	{
		pOut->ClearDrawArea();
		pManager->ClearFigureList();
		CFigure* myfigure = NULL;
		//Load Drawing and Filling Color
		file >> DrawClr >> FillClr;
		UI.DrawColor = myfigure->getColorFromString(DrawClr);
		UI.FillColor = myfigure->getColorFromString(FillClr);
		string type;
		int numberoffigures;

		//Load Figures Count	
		file >> numberoffigures;

		for (int i = 0; i < numberoffigures; i++)
		{
			file >> type;
			if (type == "CIRCLE")
				myfigure = new CCircle;
			else if (type == "RECTANGLE")
				myfigure = new CRectangle;
			else if (type == "TRIANGLE")
				myfigure = new CTriangle;
			else if (type == "SQUARE")
				myfigure = new CSquare;
			else if (type == "HEXAGON")
				myfigure = new CHexagon;
			myfigure->Load(file, pOut);
			pManager->AddFigure(myfigure);
			myfigure = NULL;

		}

		file.close();
		pOut->ClearStatusBar();
		delete myfigure;
		pOut->PrintMessage("File is Loaded ");
	}

	else
		pOut->PrintMessage("Error File is Not Found!");
}