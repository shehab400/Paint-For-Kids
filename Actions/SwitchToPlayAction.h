#ifndef SWTCH_TO_PLAY_ACTION_H
#define SWTCH_TO_PLAY_ACTION_H


#include "Action.h"

class ApplicationManager;
class Input;
class Output;


class SwitchToPlayAction : public Action
{
public:
	SwitchToPlayAction(ApplicationManager* pApp);
	virtual void Execute();
	virtual void ReadActionParameters();
private:
	Output* pOut;
	string filename;

};

#endif