#pragma once

#ifndef APPLICATION_MANAGER_H
#define APPLICATION_MANAGER_H


#include "Actions/Action.h"
#include "Figures\CHexagon.h"
#include "Figures\CSquare.h"
#include "Figures\CRectangle.h"
#include "Figures\CTriangle.h"
#include "Figures\CCircle.h"
#include "Actions\AddRectAction.h"
#include "Actions\AddCircleAction.h"
#include "Actions\AddSquareAction.h"
#include "Actions\AddTriangleAction.h"
#include "Actions\AddHexagonAction.h"
#include "Actions\ChangeColorAction.h"
#include "Actions\LoadAction.h"
#include "Actions\MoveFigureAction.h"
#include "Actions\PickByColorAction.h"
#include "Actions\PickByShapeAction.h"
#include "Actions\PickByBothAction.h"
#include "Actions\RedoAction.h"
#include "Actions\UndoAction.h"
#include "Actions\SelectFigureAction.h"
#include "Actions\SwitchToDrawAction.h"
#include "Actions\SwitchToPlayAction.h"
#include "Actions\ClearAllAction.h"
#include "Actions\DeleteFigureAction.h"
#include "Actions\SaveAction.h"
#include "Actions\SaveAction.h"


//Main class that manages everything in the application.
class ApplicationManager
{
	enum { MaxFigCount = 200 };	//Max no of figures

private:
	int FigCount;		//Actual number of figures
	CFigure* FigList[MaxFigCount];	//List of all figures (Array of pointers)
	Action* UndoList[5];
	Action* RedoList[5];
	int undo_index;
	int redo_index;
	bool last_undo_redo; // true if the last operation was undo/redo
	int id_count;
	string playfile; // location for saving before switching to play mode
	

	CFigure* SelectedFig; //Pointer to the selected figure

	//Pointers to Input and Output classes
	Input *pIn;
	Output *pOut;

public:
	/// <summary>
	///  TODO: add setters and getters for SelectedFig
	/// </summary>
	ApplicationManager(); 
	~ApplicationManager();
	
	// -- Action-Related Functions
	//Reads the input command from the user and returns the corresponding action type
	void IncrmentIDCount();
	int GetIDCount();
	ActionType GetUserAction() const;
	bool LastUndoRedo();
	void SetLastUndoRedo(bool last_undo_redo);
	void ExecuteAction(ActionType) ; //Creates an action and executes it  // to be implemented
	void SetSelectedFig(int fig_id);
	CFigure* GetSelectedFig();
	void ShiftUndoList();
	Action* GetLastUndo(); // shifts undo list to the left
	void AddToUndoList(Action* action);
	void RemoveFromUndoList();
	void AddToRedoList(Action* action);
	void ShiftRedoList(); // shifts redo list to the left
	void RemoveFromRedoList();
	Action* GetLastRedo();
	void ClearFigureList();
	void SaveAll(ofstream& file) const;
	void DrawAll();
	int GetSquareCount(color clr = PURPLE,bool with_color=false);
	int GetRectangleCount(color clr = PURPLE, bool with_color = false);
	int GetHexagonCount(color clr = PURPLE, bool with_color = false);
	int GetCircleCount(color clr = PURPLE, bool with_color = false);
	int GetTriangleCount(color clr = PURPLE, bool with_color = false);
	string GetPlayFile();
	bool DeleteFig();
	

	// -- Figures Management Functions
	void AddFigure(CFigure* pFig);          //Adds a new figure to the FigList  // gahez
	CFigure *GetFigure(int x, int y) const; //Search for a figure given a point inside the figure // to be implemented // this class does no logic regarding finding the figure.
		
	// -- Interface Management Functions
	Input *GetInput() const; //Return pointer to the input
	Output *GetOutput() const; //Return pointer to the output
	void UpdateInterface() const;	//Redraws all the drawing window	
};

#endif