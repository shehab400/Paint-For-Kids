#include "CHexagon.h"


CHexagon::CHexagon(Point P, GfxInfo HexagonInfo, int id) : CFigure(HexagonInfo, id) {
	CENTER = P;
}

CHexagon::CHexagon() {}

void CHexagon::Draw(Output* pOut) const {
	if (this->CanBeDrawn(CENTER)) {
		this->Delete(pOut);
		pOut->DrawHexagon(CENTER, FigGfxInfo, this->IsSelected());
	}
	else {
		pOut->PrintMessage("Can't draw figure at this position");
	}
}

void CHexagon::Delete(Output* pOut) const {
	if (CanBeDrawn(CENTER)) {
		GfxInfo info = { UI.BkGrndColor, UI.BkGrndColor, true, UI.PenWidth };
		pOut->DrawHexagon(CENTER, info);
	}
}

void CHexagon::Save(ofstream& OutFile) const {
	string DrawColor;
	string FillColor;

	DrawColor = getColorString(FigGfxInfo.DrawClr);

	if (FigGfxInfo.isFilled) {
		FillColor = getColorString(FigGfxInfo.FillClr);
		OutFile << "HEXAGON" << "   " << ID << "   " << CENTER.x << "   " << CENTER.y << "   " << DrawColor << "   " << FillColor << endl;
	}
	else {
		OutFile << "HEXAGON" << "   " << ID << "   " << CENTER.x << "   " << CENTER.y << "   " << DrawColor << "   " << "NO_FILL" << endl;
	}
}

void CHexagon::Load(ifstream& InFile, Output* pOut) {
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
	}
	else if (FigGfxInfo.isFilled) {
		FigGfxInfo.FillClr = getColorFromString(FillColor);
		FigGfxInfo.isFilled = true;
	}
	this->Draw(pOut);
}

void CHexagon::Move(Output* pOut, Input* pIn, Point P) {
	int x, y;
	Point P1;
	pt_before_move = CENTER;
	if ((P.x == -1) && (P.y == -1)) {
		pOut->PrintMessage("Click on the new point to move the hexagon. ");
		pIn->GetPointClicked(P1.x, P1.y);
	}
	else {
		P1 = P;
	}
	pt_after_move = P1;
	if (this->CanBeDrawn(P1)) {
		this->Delete(pOut);
		CENTER.x = P1.x;
		CENTER.y = P1.y;
		this->Draw(pOut);
	}
	else {
		pOut->PrintMessage("Can't move to this position");
		pIn->GetPointClicked(x, y);
	}
}

bool CHexagon::CheckTriangles(Point P, Point Vertex1, Point Vertex2, Point Vertex3) const{
	double Area = (0.5) * abs(((Vertex1.x) * (Vertex2.y - Vertex3.y)) + ((Vertex2.x) * (Vertex3.y - Vertex1.y)) + ((Vertex3.x) * (Vertex1.y - Vertex2.y)));
	double SubArea1 = (0.5) * abs((((P.x * (Vertex2.y - Vertex3.y)) + (Vertex2.x * (Vertex3.y - P.y)) + (Vertex3.x * (P.y - Vertex2.y)))));
	double SubArea2 = (0.5) * abs((((Vertex1.x * (P.y - Vertex3.y)) + (P.x * (Vertex3.y - Vertex1.y)) + (Vertex3.x * (Vertex1.y - P.y)))));
	double SubArea3 = (0.5) * abs((((Vertex1.x * (Vertex2.y - P.y)) + (Vertex2.x * (P.y - Vertex1.y)) + (P.x * (Vertex1.y - Vertex2.y)))));
	if (abs((Area)-(SubArea1 + SubArea2 + SubArea3)) <= 0.1) {
		return true;
	}
	return false;
}

bool CHexagon::IsClicked(Point P) const {
	int x = (float)CENTER.x;
	int y = (float)CENTER.y;
	int x_coordinates[6];
	int y_coordinates[6];
	int  a = 100;
	double angle = 3.141592654 / 3;
	for (int i = 1; i < 7; i++) {
		x_coordinates[i - 1] = x - cos(i * angle) * a;
		y_coordinates[i - 1] = y + sin(i * angle) * a;
	}
	Point P1 = {x_coordinates[0], y_coordinates[0]};
	Point P2 = {x_coordinates[1], y_coordinates[1]};
	Point P3 = { x_coordinates[2], y_coordinates[2] };
	Point P4 = { x_coordinates[3], y_coordinates[3] };
	Point P5 = { x_coordinates[4], y_coordinates[4] };
	Point P6 = { x_coordinates[5], y_coordinates[5] };
	if (CheckTriangles(P, CENTER, P1, P2) || CheckTriangles(P, CENTER, P2, P3) || CheckTriangles(P, CENTER, P3, P4) || CheckTriangles(P, CENTER, P4, P5) || CheckTriangles(P, CENTER, P5, P6)) {
		return true;
	}	
	return false;
}

void CHexagon::PrintInfo(Output* pOut) const {
	if (FigGfxInfo.isFilled) {
		pOut->PrintMessage("TYPE: HEXAGON  ID:  " + to_string(ID) + "  X1: " + to_string(CENTER.x) + "  Y1: " + to_string(CENTER.y) + "  BORDER WIDTH: " + to_string(FigGfxInfo.BorderWdth) + "  DRAW COLOR:" + getColorString(FigGfxInfo.DrawClr) + "  FILL COLOR: " + getColorString(FigGfxInfo.FillClr));
	}
	else {
		pOut->PrintMessage("TYPE: HEXAGON  ID:  " + to_string(ID) + "  X1: " + to_string(CENTER.x) + "  Y1: " + to_string(CENTER.y) + "  BORDER WIDTH: " + to_string(FigGfxInfo.BorderWdth) + "  DRAW COLOR:" + getColorString(FigGfxInfo.DrawClr) + "  FILL COLOR: NO_FILL");

	}
}

// lesa
bool CHexagon::CanBeDrawn(Point P) const {
	return (!(((float)P.y - (sqrtf(3)/2)*100) < UI.ToolBarHeight) && !(((float)P.y + (sqrtf(3) / 2) * 100) > (UI.height - UI.StatusBarHeight)));
}
