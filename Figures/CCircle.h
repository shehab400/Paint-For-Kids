#ifndef CCIRC_H
#define CCIRC_H

#include "CFigure.h"

class CCircle : public CFigure {
private:
	Point CENTER;
	Point P;
	double radius;
public:
	CCircle(Point C, Point P, GfxInfo CircleGfxInfo, int id);
	CCircle();
	double getRadius();
	virtual  void Draw(Output* pOut) const;
	virtual void Delete(Output* pOut) const;
	virtual void Save(ofstream& OutFile) const;
	virtual void Load(ifstream& InFile, Output* pOut);
	virtual void Move(Output* pOut, Input* pIn, Point P = {-1,-1});
	virtual bool IsClicked(Point P) const;
	virtual void PrintInfo(Output* pOut) const;
	virtual bool CanBeDrawn(Point X, Point Y) const;
};

#endif