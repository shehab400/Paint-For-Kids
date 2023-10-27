#pragma once

#ifndef ACTION_H
#define ACTION_H

#include "..\DefS.h"

class ApplicationManager;



//Base class for all possible actions
class Action{
protected:
	ApplicationManager* pManager;	//Actions needs AppMngr to do their job
	ActionType type;

public:

	Action(ApplicationManager* pApp);// { pManager = pApp; pManager->SetLastUndoRedo(false); }	//constructor

	//Reads parameters required for action to execute (code depends on action type)
	virtual void ReadActionParameters() =0;
	
	//Execute action (code depends on action type)
	virtual void Execute() =0;

};

#endif