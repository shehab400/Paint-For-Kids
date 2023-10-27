#include "PickByColorAction.h"
#include "..\ApplicationManager.h"
#include <cstdlib>
#include <ctime>

PickByColorAction::PickByColorAction(ApplicationManager* pApp) : Action(pApp) 
{}

void PickByColorAction::ReadActionParameters()
{
	pOut = pManager->GetOutput();
	pIn = pManager->GetInput();
	srand((unsigned)time(NULL));
	random_color = 1 + rand() % 7;
	correct_picks = 0;
	wrong_picks = 0;
	color clr;
	switch (random_color) {
	case 1:
		clr = RED;
		break;
	case 2:
		clr = GREEN;
		break;
	case 3:
		clr = BLACK;
		break;
	case 4:
		clr = YELLOW;
		break;
	case 5:
		clr = BLUE;
		break;
	case 6:
		clr = ORANGE;
		break;
	}
	count = pManager->GetSquareCount(clr,true) + pManager->GetRectangleCount(clr, true) + pManager->GetHexagonCount(clr, true) + pManager->GetTriangleCount(clr, true) + pManager->GetCircleCount(clr, true);
	while (count == 0) {
		random_color = 1 + rand() % 7;
	}
}

void PickByColorAction::Execute()
{
	ReadActionParameters();
	while (correct_picks < count) {
		pIn->GetPointClicked(x, y);
		fig = pManager->GetFigure(x, y);
		if (fig != NULL) {
			if (fig->getGfx().FillClr == clr) {
				correct_picks++;
			}
			else {
				wrong_picks++;
			}
			fig->Delete(pOut);
		}
	}

	pOut->PrintMessage("number of correct picks:  " + to_string(correct_picks) + "  number of wrong picks : " + to_string(wrong_picks));
	pManager->DrawAll();
}