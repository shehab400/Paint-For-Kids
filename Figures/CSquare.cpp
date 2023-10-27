#include "CSquare.h"


CSquare::CSquare(Point P, GfxInfo SquareGfxInfo, int id): CFigure(SquareGfxInfo, id) {
	
	CENTER = P;
}

CSquare::CSquare() {}

void CSquare::Draw(Output* pOut) const {
	if (this->CanBeDrawn(CENTER)) {
		this->Delete(pOut);
		pOut->DrawSqu(CENTER, FigGfxInfo, Selected);
	}
	else {
		pOut->PrintMessage("Can't draw figure at this position");
	}
}

void CSquare::Delete(Output* pOut) const {
	if (CanBeDrawn(CENTER)) {
		GfxInfo info = { UI.BkGrndColor, UI.BkGrndColor, true, UI.PenWidth };
		pOut->DrawSqu(CENTER, info);
	}
}

void CSquare::Save(ofstream& OutFile) const{
	string DrawColor;
	string FillColor;

	DrawColor = getColorString(FigGfxInfo.DrawClr);

	if (FigGfxInfo.isFilled) {
		FillColor = getColorString(FigGfxInfo.FillClr);
		OutFile << "SQUARE" << "   " << ID << "   " << CENTER.x << "   " << CENTER.y << "   " << DrawColor << "   " << FillColor << endl;
	}
	else {
		OutFile << "SQUARE" << "   " << ID << "   " << CENTER.x << "   " << CENTER.y << "   " << DrawColor << "   " << "NO_FILL" << endl;
	}
}

void CSquare::Load(ifstream& InFile,Output* pOut) {
	string type;
	int id;
	int x1;
	int y1;
	string DrawColor;
	string FillColor;
	InFile >> type;
	InFile >> id;
	InFile >> x1;
	InFile >> y1;
	InFile >> DrawColor;
	InFile >> FillColor;

	ID = id;
	CENTER.x = x1;
	CENTER.y = y1;
	FigGfxInfo.BorderWdth = UI.PenWidth;

	
	FigGfxInfo.DrawClr = getColorFromString(DrawColor);
	if (FillColor == "NO_FILL") {
		FigGfxInfo.isFilled = false;
	}else {
		FigGfxInfo.FillClr = getColorFromString(FillColor);
		FigGfxInfo.isFilled = true;
	}
	this->Draw(pOut);
}

void CSquare::Move(Output* pOut, Input* pIn, Point P) {
	int x, y;
	Point P1;
	pt_before_move = CENTER;
	if ((P.x == -1) && (P.y == -1)) {
		pOut->PrintMessage("Click on the new point to move the square. ");
		pIn->GetPointClicked(P1.x, P1.y);
	}
	else {
		P1 = P;
	}
	pt_after_move = P1;
	if (this->CanBeDrawn(P1)) {
		this->Delete(pOut);
		CENTER.x = P.x;
		CENTER.y = P.y;
		this->Draw(pOut);
	}
	else {
		pOut->PrintMessage("Can't move to this position");
		pIn->GetPointClicked(x, y);
	}
}

bool CSquare::IsClicked(Point P) const {
	if (((P.x <= CENTER.x + 50) && (P.x >= CENTER.x - 50)) && ((P.y <= CENTER.y + 50) && (P.y >= CENTER.y - 50))) {
		return true;
	}
	return false;
}

void CSquare::PrintInfo(Output* pOut) const {
	if (FigGfxInfo.isFilled) {
		pOut->PrintMessage("TYPE: SQUARE  ID:  " + to_string(ID) + "  X1: " + to_string(CENTER.x) + "  Y1: " + to_string(CENTER.y) + "  BORDER WIDTH: " + to_string(FigGfxInfo.BorderWdth) + "  DRAW COLOR:" + getColorString(FigGfxInfo.DrawClr) + "  FILL COLOR: " + getColorString(FigGfxInfo.FillClr));
	}
	else {
		pOut->PrintMessage("TYPE: SQUARE  ID:  " + to_string(ID) + "  X1: " + to_string(CENTER.x) + "  Y1: " + to_string(CENTER.y) + "  BORDER WIDTH: " + to_string(FigGfxInfo.BorderWdth) + "  DRAW COLOR:" + getColorString(FigGfxInfo.DrawClr) + "  FILL COLOR: NO_FILL");

	}
}

bool CSquare::CanBeDrawn(Point P) const{
	return (!((P.y - 50) < UI.ToolBarHeight) && !((P.y + 50) > (UI.height - UI.StatusBarHeight)));
}
