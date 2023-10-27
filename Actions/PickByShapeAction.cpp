#include "PickByShapeAction.h"
#include "..\ApplicationManager.h"
#include <cstdlib>
#include <ctime>

PickByShapeAction::PickByShapeAction(ApplicationManager* pApp) : Action(pApp)
{}



void PickByShapeAction::ReadActionParameters()
{
	pOut = pManager->GetOutput();
	pIn = pManager->GetInput();
	srand((unsigned)time(NULL));
	correct_picks = 0;
	wrong_picks = 0;
	count = 0;
	while (count == 0) {
		random_type = 1 + rand() % 5;
		switch (random_type) {
		case 1:
			count = pManager->GetSquareCount();
			break;
		case 2:
			count = pManager->GetRectangleCount();
			break;
		case 3:
			count = pManager->GetCircleCount();
			break;
		case 4:
			count = pManager->GetHexagonCount();
			break;
		case 5:
			count = pManager->GetTriangleCount();
			break;
		}
	}
}

void PickByShapeAction::Execute()
{
	ReadActionParameters();
	if (random_type == 1) {
		while (correct_picks < count) {
			pIn->GetPointClicked(x, y);
			fig = pManager->GetFigure(x, y);
			if (fig != NULL) {
				if (dynamic_cast<CSquare*>(fig)) {
					correct_picks++;
				}
				else {
					wrong_picks++;
				}
				fig->Delete(pOut);
			}
		}
	}else if (random_type == 2) {
		while (correct_picks < count) {
			pIn->GetPointClicked(x, y);
			fig = pManager->GetFigure(x, y);
			if (fig != NULL) {
				if (dynamic_cast<CRectangle*>(fig)) {
					correct_picks++;
				}
				else {
					wrong_picks++;
				}
				fig->Delete(pOut);
			}
		}
	}else if (random_type == 3) {
		while (correct_picks < count) {
			pIn->GetPointClicked(x, y);
			fig = pManager->GetFigure(x, y);
			if (fig != NULL) {
				if (dynamic_cast<CCircle*>(fig)) {
					correct_picks++;
				}
				else {
					wrong_picks++;
				}
				fig->Delete(pOut);
			}
		}
	}else if (random_type == 4) {
		while (correct_picks < count) {
			pIn->GetPointClicked(x, y);
			fig = pManager->GetFigure(x, y);
			if (fig != NULL) {
				if (dynamic_cast<CHexagon*>(fig)) {
					correct_picks++;
				}
				else {
					wrong_picks++;
				}
				fig->Delete(pOut);
			}
		}
	}else if (random_type == 5) {
		while (correct_picks < count) {
			pIn->GetPointClicked(x, y);
			fig = pManager->GetFigure(x, y);
			if (fig != NULL) {
				if (dynamic_cast<CTriangle*>(fig)) {
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