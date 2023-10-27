#ifndef CLEAR_ALL_ACTION_H
#define CLEAR_ALL_ACTION_H

#pragma once

#include "Action.h"

class ApplicationManager;
class Output;
class Input;

class ClearAllAction :public Action
{
private:
	Output* pOut;
	Input* pIn;
public:
	ClearAllAction(ApplicationManager* pApp);

	virtual void ReadActionParameters();

	virtual void Execute();

};

#endif