#ifndef PICK_BY_SHAPE_ACTION_H
#define PICK_BY_SHAPE_ACTION_H

#include"Action.h"

#pragma once

class ApplicationManager;
class CFigure;
class Input;
class Output;


class PickByShapeAction : public Action
{
private:
	Output* pOut;
	Input* pIn;
	int count;
	int random_type;
	int correct_picks;
	int wrong_picks;
	int x, y;
	CFigure* fig;
public:
	PickByShapeAction(ApplicationManager* pApp);
	void ReadActionParameters();
	void Execute();
};

#endif