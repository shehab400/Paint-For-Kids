#pragma once
#include "CFigure.h"

class CRectangle : public CFigure
{
private:
	Point Corner1;	// upper left
	Point Corner2;  // lower right
public:
	CRectangle(Point , Point, GfxInfo FigureGfxInfo, int id );
	CRectangle();
	virtual void Draw(Output* pOut) const;
	virtual void Delete(Output* pOut) const;
	virtual void Save(ofstream& OutFile) const;
	virtual void Load(ifstream& InFile, Output* pOut);
	virtual void Move(Output* pOut, Input* pIn, Point P = {-1,-1});
	virtual bool IsClicked(Point P) const;
	virtual void PrintInfo(Output* pOut) const;
	virtual bool CanBeDrawn(Point P1, Point P2) const;
};

