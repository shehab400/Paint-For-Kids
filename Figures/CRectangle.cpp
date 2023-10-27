#include "CRectangle.h"


CRectangle::CRectangle(Point P1, Point P2, GfxInfo FigureGfxInfo, int id): CFigure(FigureGfxInfo, id)
{
	Corner1 = P1;
	Corner2 = P2;
}

CRectangle::CRectangle() {}
	

void CRectangle::Draw(Output* pOut) const
{
	//Call Output::DrawRect to draw a rectangle on the screen
	if (this->CanBeDrawn(Corner1, Corner2)) {
		this->Delete(pOut);
		pOut->DrawRect(Corner1, Corner2, FigGfxInfo, Selected);
	}
	else {
		pOut->PrintMessage("Can't draw rectangle at this position");
	}
	
}

void CRectangle::Delete(Output* pOut) const {
	if (CanBeDrawn(Corner1, Corner2)) {
		GfxInfo info = { UI.BkGrndColor, UI.BkGrndColor, true, UI.PenWidth };
		pOut->DrawRect(Corner1, Corner2, info);
	}
}

void CRectangle::Save(ofstream& OutFile) const {
	string DrawColor;
	string FillColor;

	DrawColor = getColorString(FigGfxInfo.DrawClr);

	if (FigGfxInfo.isFilled) {
		FillColor = getColorString(FigGfxInfo.FillClr);
		OutFile << "RECTANGLE" << "   " << ID << "   " << Corner1.x << "   " << Corner1.y << "   " << Corner2.x << "   " << Corner2.y << "   " << DrawColor << "   " << FillColor << endl;
	}
	else {
		OutFile << "RECTANGLE" << "   " << ID << "   " << Corner1.x << "   " << Corner1.y << "   " << Corner2.x << "   " << Corner2.y << "   " << DrawColor << "   " << "NO_FILL" << endl;
	}
}

void CRectangle::Load(ifstream& InFile, Output* pOut) {
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
	Corner1.x = x1;
	Corner1.y = y1;
	Corner2.x = x2;
	Corner2.y = y2;
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

void CRectangle::Move(Output* pOut, Input* pIn, Point P) {
	int x, y;
	Point C;
	Point P1;
	Point P2;
	pt_before_move = { Corner1.x + ((Corner2.x - Corner1.x) / 2), Corner1.y + ((Corner2.y - Corner1.y) / 2) };
	if ((P.x == -1) && (P.y == -1)) {
		pOut->PrintMessage("Click on the point to move the rectangle. ");
		pIn->GetPointClicked(C.x, C.y);
	}
	else {
		C = P;
	}
	pt_after_move = C;
	P1.x = C.x - ((Corner2.x - Corner1.x) / 2);
	P1.y = C.y - ((Corner2.y - Corner1.y) / 2);
	P2.x = C.x + ((Corner2.x - Corner1.x) / 2);
	P2.y = C.y + ((Corner2.y - Corner1.y) / 2);
	if (this->CanBeDrawn(P1, P2)) {
		this->Delete(pOut);
		Corner1.x = P1.x;
		Corner1.y = P1.y;
		Corner2.x = P2.x;
		Corner2.y = P2.y;
		this->Draw(pOut);
	}
	else {
		pOut->PrintMessage("Can't move to this position");
		pIn->GetPointClicked(x, y);
	}
}

bool CRectangle::IsClicked(Point P) const {
	if (((P.x >= Corner1.x) && (P.x <= Corner2.x)) && ((P.y >= Corner1.y) && (P.y <= Corner2.y))) {
		return true;
	}
	return false;
}

void CRectangle::PrintInfo(Output* pOut) const {
	if (FigGfxInfo.isFilled) {
		pOut->PrintMessage("TYPE: RECTANGLE  ID:  " + to_string(ID) + "  X1: " + to_string(Corner1.x) + "  Y1: " + to_string(Corner1.y) + "  X2: " + to_string(Corner2.x) + "  Y1: " + to_string(Corner2.y) +  "  BORDER WIDTH: " + to_string(FigGfxInfo.BorderWdth) + "  DRAW COLOR:" + getColorString(FigGfxInfo.DrawClr) + "  FILL COLOR: " + getColorString(FigGfxInfo.FillClr));
	}
	else {
		pOut->PrintMessage("TYPE: RECTANGLE  ID:  " + to_string(ID) + "  X1: " + to_string(Corner1.x) + "  Y1: " + to_string(Corner1.y) + "  X2: " + to_string(Corner2.x) + "  Y1: " + to_string(Corner2.y) + "  BORDER WIDTH: " + to_string(FigGfxInfo.BorderWdth) + "  DRAW COLOR:" + getColorString(FigGfxInfo.DrawClr) + "  FILL COLOR: NO_FILL");

	}
}


bool CRectangle::CanBeDrawn(Point P1, Point P2) const {
	return (!((P1.y) < UI.ToolBarHeight) && !((P1.y) > (UI.height - UI.StatusBarHeight)) && !((P2.y) < UI.ToolBarHeight) && !((P2.y) > (UI.height - UI.StatusBarHeight)));
}

