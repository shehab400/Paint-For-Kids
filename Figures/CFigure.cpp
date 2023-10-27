#include "CFigure.h"



CFigure::CFigure(GfxInfo FigureGfxInfo, int id)
{ 
	FigGfxInfo = FigureGfxInfo;	//Default status is non-filled.
	Selected = false;
	ID = id;
}

CFigure::CFigure(){}

void CFigure::SetSelected(bool s)
{	Selected = s; }

int CFigure::getID() { return this->ID; }

bool CFigure::IsSelected() const
{	return Selected; }

string CFigure::getColorString(color clr) const{
	string Color;
	if (clr == RED) {
		Color = "RED";
	}
	else if (clr == BLACK) {
		Color = "BLACK";
	}
	else if (clr == YELLOW) {
		Color = "YELLOW";
	}
	else if (clr == ORANGE) {
		Color = "ORANGE";
	}
	else if (clr == GREEN) {
		Color = "GREEN";
	}
	else if (clr == BLUE) {
		Color = "BLUE";
	}

	return Color;
}

color CFigure::getColorFromString(string clr) const{
	color Color;
	if (clr == "BLACK") {
		Color = BLACK;
	}
	else if (clr == "YELLOW") {
		Color = YELLOW;
	}
	else if (clr == "GREEN") {
		Color = GREEN;
	}
	else if (clr == "ORANGE") {
		Color = ORANGE;
	}
	else if (clr == "RED") {
		Color = RED;
	}
	else if (clr == "BLUE") {
		Color = BLUE;
	}

	return Color;
}

void CFigure::ChngDrawClr(color Dclr)
{	FigGfxInfo.DrawClr = Dclr; }

void CFigure::ChngFillClr(color Fclr)
{	
	FigGfxInfo.isFilled = true;
	FigGfxInfo.FillClr = Fclr; 
}

void CFigure::setGfx(GfxInfo info) {
	FigGfxInfo = info;
}

GfxInfo CFigure::getGfx() { return FigGfxInfo; }

Point CFigure::GetPtAfterMove() { return pt_after_move; }
Point CFigure::GetPtBeforeMove() { return pt_before_move; }
