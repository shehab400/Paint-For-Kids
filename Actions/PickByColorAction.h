#ifndef PICK_BY_COLOR_ACTION_H
#define PICK_BY_COLOR_ACTION_H


#include"Action.h"

class ApplicationManager;
class CFigure;
class Input;
class Output;

class PickByColorAction : public Action
{
private:
	Output* pOut;
	Input* pIn;
	int count;
	int random_color;
	int correct_picks;
	int wrong_picks;
	int x, y;
	CFigure* fig;
	color clr;
public:
	PickByColorAction(ApplicationManager* pApp);
	void ReadActionParameters();
	void Execute();

};


#endif
