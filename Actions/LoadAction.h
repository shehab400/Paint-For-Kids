#ifndef LOAD_ACTION_H
#define lOAD_ACTION_H

#include "Action.h"
#include <fstream>

#pragma once

class ApplicationManager;
class CHexagon;
class CRectangle;
class CCircle;
class CSquare;
class CTriangle;

class LoadAction : public Action
{

	string filename;
	ifstream file;

public:

	LoadAction(ApplicationManager* pApp, string filename="");

	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif