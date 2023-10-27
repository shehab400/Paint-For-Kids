#pragma once

#include "CFigure.h"

class CHexagon : public CFigure {
private:
	Point CENTER;
public:
	CHexagon(Point P, GfxInfo HexagonGfxInfo, int id);
	CHexagon();
	virtual  void Draw(Output* pOut) const;
	virtual void Delete(Output* pOut) const;
	virtual void Save(ofstream& OutFile) const;
	virtual void Load(ifstream& InFile, Output* pOut);
	virtual void Move(Output* pOut, Input* pIn, Point P = {-1,-1});
	virtual bool IsClicked(Point P) const;
	virtual void PrintInfo(Output* pOut) const;
	virtual bool CanBeDrawn(Point P) const;
	bool CheckTriangles(Point P, Point Vertex1, Point Vertex2, Point Vertex3) const; // when the hexagon is divided into triangles, this function is used
	// to check if a given point is inside of any of the triangles
};

