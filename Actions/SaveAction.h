#ifndef SAVE_ACTION_H
#define SAVE_ACTION_H

#pragma once

#include "Action.h"
#include <fstream>


class ApplicationManager;
class Input;
class Output;


class SaveAction :
    public Action
{
private:
    string filename;
    ofstream file;
    Output* pOut;
    Input* pIn;
public:
    SaveAction(ApplicationManager* p);
    virtual void Execute();
    virtual void ReadActionParameters();

};

#endif