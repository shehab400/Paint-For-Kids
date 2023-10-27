#pragma once

#include "CFigure.h"

class CTriangle : public CFigure {
private:
	Point Vertex1;
	Point Vertex2;
	Point Vertex3;
public:
	CTriangle(Point P1, Point P2, Point P3, GfxInfo TriangleGfxInfo, int id);
	CTriangle();
	virtual void Draw(Output* pOut) const;
	virtual void Delete(Output* pOut) const;
	virtual void Save(ofstream& OutFile) const;
	virtual void Load(ifstream& InFile, Output* pOut);
	virtual void Move(Output* pOut, Input* pIn, Point P = {-1,-1});
	virtual bool IsClicked(Point P) const;
	virtual void PrintInfo(Output* pOut) const;
	virtual bool CanBeDrawn(Point P1, Point P2, Point P3) const;
	Point GetCircumCenter(Point P1, Point P2, Point P3) const;
};

