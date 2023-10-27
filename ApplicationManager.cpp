#include "ApplicationManager.h"
#include "Actions/Action.h"


//Constructor
ApplicationManager::ApplicationManager()
{
	//Create Input and output
	pOut = new Output;
	pIn = pOut->CreateInput();

	for (int i = 0; i < 5; i++) {
		UndoList[i] = NULL;
		RedoList[i] = NULL;
	}
	
	FigCount = 0;
	undo_index = 0;
	redo_index = 0;
	id_count = 0;
	playfile = "..\playfile.txt";
	//Create an array of figure pointers and set them to NULL		
	for(int i=0; i<MaxFigCount; i++)
		FigList[i] = NULL;	
}

void ApplicationManager::SetSelectedFig(int fig_id) {
	if (fig_id == -1) {
		SelectedFig = NULL;
		return;
	}
	for (int i = FigCount - 1; i >= 0; i--) {
		if (fig_id == FigList[i]->getID()) {
			SelectedFig = FigList[i];
			break;
		}
	}
}

CFigure* ApplicationManager::GetSelectedFig() { return SelectedFig; }

//==================================================================================//
//								Actions Related Functions							//
//==================================================================================//
ActionType ApplicationManager::GetUserAction() const
{
	//Ask the input to get the action from the user.
	return pIn->GetUserAction();		
}
////////////////////////////////////////////////////////////////////////////////////
//Creates an action and executes it
void ApplicationManager::ExecuteAction(ActionType ActType)
{
	Action* pAct = NULL;

	//According to Action Type, create the corresponding action object
	switch (ActType)
	{
	case DRAW_RECT:
		pAct = new AddRectAction(this);
		break;
	case DRAW_CIRCLE:
		pAct = new AddCircleAction(this);
		break;
	case DRAWTRIANGLE:
		pAct = new AddTriangleAction(this);
		break;
	case DRAW_HEX:
		pAct = new AddHexagonAction(this);
		break;
	case DRAW_SQUARE:
		pAct = new AddSquareAction(this);
		break;
	case SAVE:
		pAct = new SaveAction(this);
		break;
	case LOAD:
		pAct = new LoadAction(this);
		break;
	case TO_DRAW:
		pAct = new SwitchToDrawAction(this);
		break;
	case TO_PLAY:
		pAct = new SwitchToPlayAction(this);
		break;
	case SELECT:
		pAct = new SelectFigureAction(this);
		break;
	case CHANGE_DRAW_COLOR:
		pAct = new ChangeColorAction(this, true);
		break;
	case CHANGE_FILL_COLOR:
		pAct = new ChangeColorAction(this, false);
		break;
	case DELETE_FIGURE:
		pAct = new DeleteFigureAction(this);
		break;
	case MOVE_FIGURE:
		pAct = new MoveFigureAction(this);
		break;
	case UNDO:
		pAct = new UndoAction(this);
		break;
	case REDO:
		pAct = new RedoAction(this);
		break;
	case CLEAR:
		pAct = new ClearAllAction(this);
		break;
	case PICK_BY_CLR:
		pAct = new PickByColorAction(this);
		break;
	case PICK_BY_TYPE:
		pAct = new PickByShapeAction(this);
		break;
	case PICK_BOTH:
		pAct = new PickByBothAction(this);
		break;
	case EXIT:
		///create ExitAction here

		break;

	case STATUS:	//a click on the status bar ==> no action
		return;
	}

	//Execute the created action
	if (pAct != NULL)
	{
		pAct->Execute();//Execute
		delete pAct;	//You may need to change this line depending to your implementation
		pAct = NULL;
	}
}


void ApplicationManager::IncrmentIDCount() {
	id_count++;
}
int ApplicationManager::GetIDCount() {
	return id_count;
}

string ApplicationManager::GetPlayFile() {
	return this->playfile;
}

void ApplicationManager::ShiftUndoList() {
	for (int i = 1; i < 5; i++) {
		UndoList[i - 1] = UndoList[i];
	}
	UndoList[4] = NULL;

}

Action* ApplicationManager::GetLastUndo() {
	for (int i = 4; i >= 0; i--) {
		if (UndoList[i] != NULL) {
			return UndoList[i];
		}
	}
}




void ApplicationManager::AddToUndoList(Action* action) {
	if ((undo_index % 4) == 0) {
		this->ShiftUndoList();
	}
	UndoList[(undo_index++)%5] = action;
}

void ApplicationManager::RemoveFromUndoList() {
	if (undo_index >= 0) {
		UndoList[(--undo_index)%5] = NULL;
	}
	else {
		undo_index = 0;
	}
}

void ApplicationManager::ShiftRedoList() {
	for (int i = 1; i < 5; i++) {
		RedoList[i - 1] = RedoList[i];
	}
	RedoList[4] = NULL;
}

bool ApplicationManager::LastUndoRedo() {
	return last_undo_redo;
}

void ApplicationManager::SetLastUndoRedo(bool last_undo_redo) {
	this->last_undo_redo = last_undo_redo;
}

void ApplicationManager::AddToRedoList(Action* action){
	if ((redo_index % 4) == 0) {
		this->ShiftRedoList();
	}
	RedoList[(redo_index++) % 5] = action;
}

void ApplicationManager::RemoveFromRedoList() {
	if (redo_index >= 0) {
		UndoList[(--redo_index) % 5] = NULL;
	}
	else {
		redo_index = 0;
	}
}

Action* ApplicationManager::GetLastRedo() {
	for (int i = 4; i >= 0; i--) {
		if (RedoList[i] != NULL) {
			return RedoList[i];
		}
	}
}





//==================================================================================//
//						Figures Management Functions								//
//==================================================================================//

//Add a figure to the list of figures
void ApplicationManager::AddFigure(CFigure* pFig)
{
	if(FigCount < MaxFigCount )
		FigList[FigCount++] = pFig;	
}

bool ApplicationManager::DeleteFig()
{
	for (int i = 0; i < FigCount; i++) {
		if (FigList[i]->IsSelected()) {
			delete FigList[i];
			int k = 0;
			for (int j = FigCount; j >= 0; j--) {
				if (j == i)
					break;
				FigList[i + k] = FigList[i + k + 1];
				k++;
			}
			FigCount--;
			return true;
		}
	}
	return false;
}

////////////////////////////////////////////////////////////////////////////////////
CFigure *ApplicationManager::GetFigure(int x, int y) const
{
	//If a figure is found return a pointer to it.
	//if this point (x,y) does not belong to any figure return NULL
	// This function will call a function in the Cfigure class pointer that check if the point x,y is inside it or on its borders


	//Add your code here to search for a figure given a point x,y	
	//Remember that ApplicationManager only calls functions do NOT implement it.

	for (int i = 0; i < FigCount; i++) {
		if (FigList[i]->IsClicked(Point{x,y})) {
			return FigList[i];
		}
	}

	return NULL;
}

int ApplicationManager::GetSquareCount(color clr, bool with_color) {
	int c = 0;
	if (with_color) {
		for (int i = 0; i < FigCount; i++) {
			if (dynamic_cast<CSquare*>(FigList[i]) && FigList[i]->getGfx().FillClr == clr) {
				c++;
			}
		}
	}
	else {
		for (int i = 0; i < FigCount; i++) {
			if (dynamic_cast<CSquare*>(FigList[i])) {
				c++;
			}
		}
	}
	return c;
}

int ApplicationManager::GetRectangleCount(color clr, bool with_color) {
	int c = 0;
	if (with_color) {
		for (int i = 0; i < FigCount; i++) {
			if (dynamic_cast<CRectangle*>(FigList[i]) && FigList[i]->getGfx().FillClr == clr) {
				c++;
			}
		}
	}
	else {
		for (int i = 0; i < FigCount; i++) {
			if (dynamic_cast<CRectangle*>(FigList[i])) {
				c++;
			}
		}
	}
	return c;
}

int ApplicationManager::GetHexagonCount(color clr, bool with_color) {
	int c = 0;
	if (with_color) {
		for (int i = 0; i < FigCount; i++) {
			if (dynamic_cast<CHexagon*>(FigList[i]) && FigList[i]->getGfx().FillClr == clr) {
				c++;
			}
		}
	}
	else {
		for (int i = 0; i < FigCount; i++) {
			if (dynamic_cast<CHexagon*>(FigList[i])) {
				c++;
			}
		}
	}
	return c;
}

int ApplicationManager::GetCircleCount(color clr, bool with_color) {
	int c = 0;
	if (with_color) {
		for (int i = 0; i < FigCount; i++) {
			if (dynamic_cast<CCircle*>(FigList[i]) && FigList[i]->getGfx().FillClr == clr) {
				c++;
			}
		}
	}
	else {
		for (int i = 0; i < FigCount; i++) {
			if (dynamic_cast<CCircle*>(FigList[i])) {
				c++;
			}
		}
	}
	return c;
}

int ApplicationManager::GetTriangleCount(color clr, bool with_color) {
	int c = 0;
	if (with_color) {
		for (int i = 0; i < FigCount; i++) {
			if (dynamic_cast<CTriangle*>(FigList[i]) && FigList[i]->getGfx().FillClr == clr) {
				c++;
			}
		}
	}
	else {
		for (int i = 0; i < FigCount; i++) {
			if (dynamic_cast<CTriangle*>(FigList[i])) {
				c++;
			}
		}
	}
	return c;
}

void ApplicationManager::ClearFigureList() {
	for (int i = 0; i < FigCount; i++) {
		delete FigList[i];
		FigList[i] = NULL;
	}
	FigCount = 0;
}

void ApplicationManager::SaveAll(ofstream& file) const  ////////Function that loops on figures and calls save of each figure
{
	file << FigCount << endl;

	for (int i = 0; i < FigCount; i++)
	{
		FigList[i]->Save(file);
	}
}

void ApplicationManager::DrawAll() {
	for (int i = 0; i < FigCount; i++) {
		FigList[i]->Draw(pOut);
	}
}

//==================================================================================//
//							Interface Management Functions							//
//==================================================================================//

//Draw all figures on the user interface
void ApplicationManager::UpdateInterface() const
{	
	pOut->ClearDrawArea();
	for(int i=0; i<FigCount; i++)
		FigList[i]->Draw(pOut);		//Call Draw function (virtual member fn)
}
////////////////////////////////////////////////////////////////////////////////////
//Return a pointer to the input
Input *ApplicationManager::GetInput() const
{	return pIn; }
//Return a pointer to the output
Output *ApplicationManager::GetOutput() const
{	return pOut; }
////////////////////////////////////////////////////////////////////////////////////
//Destructor
ApplicationManager::~ApplicationManager()
{
	for(int i=0; i<FigCount; i++)
		delete FigList[i];
	delete pIn;
	delete pOut;
	
}
