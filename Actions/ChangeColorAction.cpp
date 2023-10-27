#include "ChangeColorAction.h"
#include "../ApplicationManager.h"

ChangeColorAction::ChangeColorAction(ApplicationManager* pApp, bool mode): Action(pApp) {
	this->mode = mode;
}

void ChangeColorAction::ReadActionParameters() {
	int x, y;
	pOut = pManager->GetOutput();
	pIn = pManager->GetInput();
	pOut->PrintMessage("Choose a color: ");
	pIn->GetPointClicked(x, y);
	fig = pManager->GetSelectedFig();
	if (fig != NULL) {
		if (mode) {
			clr = UI.FillColor;
			old_clr = fig->getGfx().DrawClr;
		}
		else {
			clr = UI.DrawColor;
			old_clr = fig->getGfx().FillClr;
		}
	}
	

}

void ChangeColorAction::Execute() {
	ReadActionParameters();
	if (fig != NULL) {
		if (mode) {
			fig->setGfx(GfxInfo{ clr, fig->getGfx().FillClr, true, fig->getGfx().BorderWdth });
		}
		else {
			fig->setGfx(GfxInfo{ fig->getGfx().DrawClr, clr, fig->getGfx().isFilled, fig->getGfx().BorderWdth });
		}
		fig->Draw(pOut);
	}
}

color ChangeColorAction::GetOldColor() { return old_clr; }
color ChangeColorAction::GetColor() { return clr; }
CFigure* ChangeColorAction::GetFig() { return fig;}
bool ChangeColorAction::GetMode() { return mode; }
