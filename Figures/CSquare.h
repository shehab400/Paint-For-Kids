#pragma once

#include "CFigure.h"

class CSquare : public CFigure {
private:
	Point CENTER;
public:
	CSquare(Point P, GfxInfo SquareGfxInfo, int id);
	CSquare();
	virtual  void Draw(Output* pOut) const;
	virtual void Delete(Output* pOut) const;
	virtual void Save(ofstream &OutFile) const;
	virtual void Load(ifstream& InFile, Output* pOut);
	virtual void Move(Output* pOut, Input* pIn, Point P = {-1,-1});
	virtual bool IsClicked(Point P) const;
	virtual void PrintInfo(Output* pOut) const;
	virtual bool CanBeDrawn(Point P) const;

};

