#ifndef SWITCH_TO_DRAW_ACTION_H
#define SWITCH_TO_DRAW_ACTION_H

#pragma once

#include "Action.h"

class ApplicationManager;
class Input;
class Output;

class SwitchToDrawAction : public Action
{
public:
	SwitchToDrawAction(ApplicationManager* pApp);
	virtual void Execute();
	virtual void ReadActionParameters();
private:
	Output* pOut;
	Action* load_action;

};

#endif