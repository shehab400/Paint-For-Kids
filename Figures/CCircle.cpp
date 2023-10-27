#include "CCircle.h"
#include <cmath>

CCircle::CCircle(Point C, Point P, GfxInfo SquareGfxInfo, int id) : CFigure(SquareGfxInfo, id) {
	CENTER = C;
	this->P = P;
	radius = sqrtf(pow(P.x - C.x, 2) + pow(P.y - C.y, 2));
}

CCircle::CCircle() {}

void CCircle::Draw(Output* pOut) const {
	if (this->CanBeDrawn(CENTER, P)) {
		this->Delete(pOut);
		pOut->DrawCircle(CENTER, P, FigGfxInfo, Selected);
	}
	else {
		pOut->PrintMessage("Can't draw figure at this position");
	}
}

void CCircle::Delete(Output* pOut) const {
	if (CanBeDrawn(CENTER, P)) {
		GfxInfo info = { UI.BkGrndColor, UI.BkGrndColor, true, UI.PenWidth };
		pOut->DrawCircle(CENTER, P, info);
	}
}

void CCircle::Save(ofstream& OutFile) const {
	string DrawColor;
	string FillColor;

	DrawColor = getColorString(FigGfxInfo.DrawClr);

	if (FigGfxInfo.isFilled) {
		FillColor = getColorString(FigGfxInfo.FillClr);
		OutFile << "CIRCLE" << "   " << ID << "   " << CENTER.x << "   " << CENTER.y << "   " << "   " << P.x << "   " << P.y << "   " << DrawColor << "   " << FillColor << endl;
	}
	else {
		OutFile << "CIRCLE" << "   " << ID << "   " << CENTER.x << "   " << CENTER.y << "   " << "   " << P.x << "   " << P.y << "   " << DrawColor << "   " << "NO_FILL" << endl;
	}
}

void CCircle::Load(ifstream& InFile, Output* pOut) {
	string type;
	int id;
	int x1;
	int y1;
	int x2;
	int y2;
	string DrawColor;
	string FillColor;
	InFile >> type;
	InFile >> id;
	InFile >> x1;
	InFile >> y1;
	InFile >> x2;
	InFile >> y2;
	InFile >> DrawColor;
	InFile >> FillColor;

	ID = id;
	CENTER.x = x1;
	CENTER.y = y1;
	FigGfxInfo.BorderWdth = UI.PenWidth;


	FigGfxInfo.DrawClr = getColorFromString(DrawColor);
	if (FillColor == "NO_FILL") {
		FigGfxInfo.isFilled = false;
	}
	else {
		FigGfxInfo.FillClr = getColorFromString(FillColor);
		FigGfxInfo.isFilled = true;
	}
	this->Draw(pOut);
}

void CCircle::Move(Output* pOut, Input* pIn, Point P) {
	int x, y;
	Point P1;
	pt_before_move = CENTER;
	if ((P.x == -1) && (P.y == -1)) {
		pOut->PrintMessage("Click on the new point to move the circle. ");
		pIn->GetPointClicked(P1.x, P1.y);
	}
	else {
		P1 = P;
	}
	pt_after_move = P1;
	Point P2 = { P1.x + abs(P.x - CENTER.x) , P1.y + abs(P.y - CENTER.y) };
	if (this->CanBeDrawn(P1, P2)) {
		this->Delete(pOut);
		CENTER.x = P1.x;
		CENTER.y = P1.y;
		P.x = P2.x;
		P.y = P2.y;

		this->Draw(pOut);
	}
	else {
		pOut->PrintMessage("Can't move to this position");
		pIn->GetPointClicked(x, y);
	}
}

bool CCircle::IsClicked(Point P1) const {
	double distance = sqrtf(pow(P1.x - CENTER.x, 2) + pow(P1.y - CENTER.y, 2));
	if (distance <= radius) {
		return true;
	}
	return false;
}

void CCircle::PrintInfo(Output* pOut) const {
	if (FigGfxInfo.isFilled) {
		pOut->PrintMessage("TYPE: CIRCLE  ID:  " + to_string(ID) + "  X1: " + to_string(CENTER.x) + "  Y1: " + to_string(CENTER.y) + "  X2: " + to_string(P.x) + "  Y2: " + to_string(P.y)  + "   RADIUS:  " + to_string(radius) + "  BORDER WIDTH: " + to_string(FigGfxInfo.BorderWdth) + "  DRAW COLOR:" + getColorString(FigGfxInfo.DrawClr) + "  FILL COLOR: " + getColorString(FigGfxInfo.FillClr));
	}
	else {
		pOut->PrintMessage("TYPE: CIRCLE  ID:  " + to_string(ID) + "  X1: " + to_string(CENTER.x) + "  Y1: " + to_string(CENTER.y) + "  X2: " + to_string(P.x) + "  Y2: " + to_string(P.y) + "   RADIUS:  " + to_string(radius) +  "  BORDER WIDTH: " + to_string(FigGfxInfo.BorderWdth) + "  DRAW COLOR:" + getColorString(FigGfxInfo.DrawClr) + "  FILL COLOR: " + "NO_FILL");

	}
}

bool CCircle::CanBeDrawn(Point X, Point Y) const {
	double r = sqrtf(pow(Y.x - X.x, 2) + pow(Y.y - X.y, 2));
	return (!((X.y - r)  <  UI.ToolBarHeight) && !((X.y + r) > (UI.height - UI.StatusBarHeight)));
}
