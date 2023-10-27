#ifndef PICK_BY_BOTH_ACTION_H
#define PICK_BY_BOTH_ACTION_H


#include"Action.h"

#pragma once

class ApplicationManager;
class CFigure;
class Input;
class Output;


class PickByBothAction : public Action
{
private:
	Output* pOut;
	Input* pIn;
	int count;
	int random_color;
	int random_type;
	int correct_picks;
	int wrong_picks;
	int x, y;
	CFigure* fig;
	color clr;
public:
	PickByBothAction(ApplicationManager* pApp);
	void ReadActionParameters();
	void Execute();

};

#endif