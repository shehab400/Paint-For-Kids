#include "CTriangle.h"
#include <iostream>

using namespace std;

CTriangle::CTriangle(Point P1, Point P2, Point P3, GfxInfo TriangleGfxInfo, int id) : CFigure(TriangleGfxInfo, id) {
	Vertex1 = P1;
	Vertex2 = P2;
	Vertex3 = P3;
}

CTriangle::CTriangle() {}

void CTriangle::Draw(Output* pOut) const {
	if (this->CanBeDrawn(Vertex1, Vertex2, Vertex3)) {
		this->Delete(pOut);
		pOut->DrawTriangle(Vertex1, Vertex2, Vertex3, FigGfxInfo, this->IsSelected());
	}
	else {
		pOut->PrintMessage("Can't draw figure at this position");
	}
}

void CTriangle::Delete(Output* pOut) const {
	if (CanBeDrawn(Vertex1, Vertex2, Vertex3)) {
		GfxInfo info = { UI.BkGrndColor, UI.BkGrndColor, true, UI.PenWidth };
		pOut->DrawTriangle(Vertex1, Vertex2, Vertex3, info);
	}
}

void CTriangle::Save(ofstream& OutFile) const {
	string DrawColor;
	string FillColor;

	DrawColor = getColorString(FigGfxInfo.DrawClr);

	if (FigGfxInfo.isFilled) {
		FillColor = getColorString(FigGfxInfo.FillClr);
		OutFile << "TRIANGLE" << "   " << ID << "   " << Vertex1.x << "   " << Vertex1.y << "   " << Vertex2.x << "   " << Vertex2.y << "   " << Vertex3.x << "   " << Vertex3.y << "   " << DrawColor << "   " << FillColor << endl;
	}
	else {
		OutFile << "TRIANGLE" << "   " << ID << "   " << "   " << Vertex1.x << "   " << Vertex1.y << "   " << Vertex2.x << "   " << Vertex2.y << "   " << Vertex3.x << "   " << Vertex3.y << "   " << DrawColor << "   " << "NO_FILL" << endl;
	}
}

void CTriangle::Load(ifstream& InFile, Output* pOut) {
	string type;
	int id;
	int x1;
	int y1;
	int x2;
	int y2;
	int x3;
	int y3;
	string DrawColor;
	string FillColor;
	InFile >> type;
	InFile >> id;
	InFile >> x1;
	InFile >> y1;
	InFile >> x2;
	InFile >> y2;
	InFile >> x3;
	InFile >> y3;
	InFile >> DrawColor;
	InFile >> FillColor;

	ID = id;
	Vertex1.x = x1;
	Vertex1.y = y1;
	Vertex2.x = x2;
	Vertex2.y = y2;
	Vertex3.x = x3;
	Vertex3.y = y3;
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

Point CTriangle::GetCircumCenter(Point P1, Point P2, Point P3) const {
	double x1 = (double)P1.x, x2 = (double)P2.x, x3 = (double)P3.x;
	double y1 = (double)P1.y, y2 = (double)P2.y, y3 = (double)P3.y;
	double x = ((x1 * x1) * (y2 - y3) + (x2 * x2) * (y3 - y1) + (x3 * x3) * (y1 - y2) - (y1 - y2) * (y2 - y3) * (y3 - y1)) / (2 * (x1 * (y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)));
	double y = ((y1 * y1) * (x3 - x2) + (y2 * y2) * (x1 - x3) + (y3 * y3) * (x2 - x1) - (x3 - x2) * (x2 - x1) * (x1 - x3)) / (2 * (y1 * (x3 - x2) + y2 * (x1 - x3) + y3 * (x2 - x1)));
	Point CR = { x,y };
	return CR;
}

void CTriangle::Move(Output* pOut, Input* pIn, Point P) {
	int x, y;
	Point P0;
	Point CR = GetCircumCenter(Vertex1, Vertex2, Vertex3);
	pt_before_move = CR;
	if ((P.x == -1) && (P.y == -1)) {
		pOut->PrintMessage("Click on the new point to move the triangle. ");
		pIn->GetPointClicked(P0.x, P0.y);
	}
	else {
		P0 = P;
	}
	pt_after_move = P0;
	Point P1 = { Vertex1.x + (P0.x - CR.x) ,Vertex1.y + (P0.y - CR.y) };
	Point P2 = { Vertex2.x + (P0.x - CR.x) ,Vertex2.y + (P0.y - CR.y) };
	Point P3 = { Vertex3.x + (P0.x - CR.x) ,Vertex3.y + (P0.y - CR.y) };
	if (this->CanBeDrawn(P1, P2, P3)) {
		this->Delete(pOut);
		Vertex1.x = P1.x;
		Vertex1.y = P1.y;
		Vertex2.x = P2.x;
		Vertex2.y = P2.y;
		Vertex3.x = P3.x;
		Vertex3.y = P3.y;
		this->Draw(pOut);
	}
	else {
		pOut->PrintMessage("Can't move to this position");
		pIn->GetPointClicked(x, y);
	}
}

bool CTriangle::IsClicked(Point P) const {
	cout << Vertex1.x << " " << Vertex1.y << endl;
	cout << Vertex2.x << " " << Vertex2.y << endl;
	cout << Vertex3.x << " " << Vertex3.y << endl;
	cout << P.x << " " << P.y << endl;
	double Area = (0.5) * abs( ((Vertex1.x)*(Vertex2.y - Vertex3.y) )  + ((Vertex2.x) * (Vertex3.y - Vertex1.y)) + ((Vertex3.x) * (Vertex1.y - Vertex2.y) ) );
	double SubArea1 = (0.5) * abs((((P.x * (Vertex2.y - Vertex3.y)) + (Vertex2.x * (Vertex3.y - P.y)) + (Vertex3.x * (P.y - Vertex2.y)))));
	double SubArea2 = (0.5) * abs((((Vertex1.x * (P.y - Vertex3.y)) + (P.x * (Vertex3.y - Vertex1.y)) + (Vertex3.x * (Vertex1.y - P.y)))));
	double SubArea3 = (0.5) * abs((((Vertex1.x * (Vertex2.y - P.y)) + (Vertex2.x * (P.y - Vertex1.y)) + (P.x * (Vertex1.y - Vertex2.y)))));
	if (abs((Area) - (SubArea1 + SubArea2 + SubArea3)) <= 0.1 ) {
		cout << "Inside triangle " << endl;
		cout << SubArea1 << " " << SubArea2 << " " << SubArea3 << " " << Area << endl;
		return true;
	}
	cout << "Outside triangle " << endl;
	return false;
}

void CTriangle::PrintInfo(Output* pOut) const {
	if (FigGfxInfo.isFilled) {
		pOut->PrintMessage("TYPE: TRIANGLE  ID:  " + to_string(ID) + "  X1: " + to_string(Vertex1.x) + "  Y1: " + to_string(Vertex1.y) + "  X2: " + to_string(Vertex2.x) + "  Y2: " + to_string(Vertex2.y) + "  X3: " + to_string(Vertex3.x) + "  Y3: " + to_string(Vertex3.y) + "  BORDER WIDTH: " + to_string(FigGfxInfo.BorderWdth) + "  DRAW COLOR:" + getColorString(FigGfxInfo.DrawClr) + "  FILL COLOR: " + getColorString(FigGfxInfo.FillClr));
	}
	else {
		pOut->PrintMessage("TYPE: TRIANGLE  ID:  " + to_string(ID) + "  X1: " + to_string(Vertex1.x) + "  Y1: " + to_string(Vertex1.y) + "  X2: " + to_string(Vertex2.x) + "  Y2: " + to_string(Vertex2.y) + "  X3: " + to_string(Vertex3.x) + "  Y3: " + to_string(Vertex3.y) + "  BORDER WIDTH: " + to_string(FigGfxInfo.BorderWdth) + "  DRAW COLOR:" + getColorString(FigGfxInfo.DrawClr) + "  FILL COLOR: NO_FILL");

	}
}

bool CTriangle::CanBeDrawn(Point P1, Point P2, Point P3) const {
	return (!(P1.y < UI.ToolBarHeight) && !(P1.y > (UI.height - UI.StatusBarHeight)) && !(P2.y < UI.ToolBarHeight) && !(P2.y > (UI.height - UI.StatusBarHeight)) && !(P3.y < UI.ToolBarHeight) && !(P3.y > (UI.height - UI.StatusBarHeight)));
}