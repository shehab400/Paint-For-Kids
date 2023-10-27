#include "PickByBothAction.h"
#include "..\ApplicationManager.h"

PickByBothAction::PickByBothAction(ApplicationManager* pApp) : Action(pApp) {
}

void PickByBothAction::ReadActionParameters() {
	pOut = pManager->GetOutput();
	pIn = pManager->GetInput();
	srand((unsigned)time(NULL));
	correct_picks = 0;
	wrong_picks = 0;
	color clr;
	int color_count;

	count = 0;
	while (count == 0) {
			random_color = 1 + rand() % 7;
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
		random_type = 1 + rand() % 5;
		switch (random_type) {
		case 1:
			count = pManager->GetSquareCount(clr, true);
			break;
		case 2:
			count = pManager->GetRectangleCount(clr, true);
			break;
		case 3:
			count = pManager->GetCircleCount(clr, true);
			break;
		case 4:
			count = pManager->GetHexagonCount(clr, true);
			break;
		case 5:
			count = pManager->GetTriangleCount(clr, true);
			break;
		}
	}

	
}


void PickByBothAction::Execute() {
	ReadActionParameters();
	if (random_type == 1) {
		while (correct_picks < count) {
			pIn->GetPointClicked(x, y);
			fig = pManager->GetFigure(x, y);
			if (fig != NULL) {
				if (dynamic_cast<CSquare*>(fig) && (fig->getGfx().FillClr == clr)) {
					correct_picks++;
				}
				else {
					wrong_picks++;
				}
				fig->Delete(pOut);
			}
		}
	}
	else if (random_type == 2) {
		while (correct_picks < count) {
			pIn->GetPointClicked(x, y);
			fig = pManager->GetFigure(x, y);
			if (fig != NULL) {
				if (dynamic_cast<CRectangle*>(fig) && (fig->getGfx().FillClr == clr)) {
					correct_picks++;
				}
				else {
					wrong_picks++;
				}
				fig->Delete(pOut);
			}
		}
	}
	else if (random_type == 3) {
		while (correct_picks < count) {
			pIn->GetPointClicked(x, y);
			fig = pManager->GetFigure(x, y);
			if (fig != NULL) {
				if (dynamic_cast<CCircle*>(fig) && (fig->getGfx().FillClr == clr)) {
					correct_picks++;
				}
				else {
					wrong_picks++;
				}
				fig->Delete(pOut);
			}
		}
	}
	else if (random_type == 4) {
		while (correct_picks < count) {
			pIn->GetPointClicked(x, y);
			fig = pManager->GetFigure(x, y);
			if (fig != NULL) {
				if (dynamic_cast<CHexagon*>(fig) && (fig->getGfx().FillClr == clr)) {
					correct_picks++;
				}
				else {
					wrong_picks++;
				}
				fig->Delete(pOut);
			}
		}
	}
	else if (random_type == 5) {
		while (correct_picks < count) {
			pIn->GetPointClicked(x, y);
			fig = pManager->GetFigure(x, y);
			if (fig != NULL) {
				if (dynamic_cast<CTriangle*>(fig) && (fig->getGfx().FillClr == clr)) {
					correct_picks++;
				}
				else {
					wrong_picks++;
				}
				fig->Delete(pOut);
			}
		}
	}

	pOut->PrintMessage("number of correct picks:  " + to_string(correct_picks) + "  number of wrong picks : " + to_string(wrong_picks));
	pManager->DrawAll();
}
