#pragma once

#include "..\defs.h"
#include "..\GUI\Output.h"
#include "..\GUI\UI_Info.h"
#include <fstream>
#include <string>


//Base class for all figures
class CFigure
{
protected:
	int ID;		//Each figure has a unique ID (not necessarily sequential)
	bool Selected;	//true if the figure is selected.
	GfxInfo FigGfxInfo;	//Figure graphis info
	Point pt_before_move;
	Point pt_after_move;
	
	/// Add more parameters if needed.

public:
	CFigure(GfxInfo FigureGfxInfo, int id);
	CFigure();
	void SetSelected(bool s);	//select/unselect the figure
	bool IsSelected() const;	//check whether fig is selected
	virtual void setGfx(GfxInfo info);
	virtual GfxInfo getGfx();
	string getColorString(color clr) const;
	color getColorFromString(string clr) const;
	int getID();

	virtual void Draw(Output* pOut) const  = 0 ;		//Draw the figure
	
	void ChngDrawClr(color Dclr);	//changes the figure's drawing color
	void ChngFillClr(color Fclr);	//changes the figure's filling color
	Point GetPtBeforeMove();
	Point GetPtAfterMove();
	///The following functions should be supported by the figure class
	///It should be overridden by each inherited figure

	///Decide the parameters that you should pass to each function	


	virtual void Save(ofstream &OutFile) const = 0;	//Save the figure parameters to the file
	virtual void Load(ifstream &Infile, Output* pOut) = 0;	//Load the figure parameters to the file
	//ADDED
	virtual void Delete(Output* pOut) const = 0;
	virtual void Move(Output* pOut, Input* pIn, Point P = {-1,-1}) = 0;
	virtual bool IsClicked(Point P) const = 0;
	//
	virtual void PrintInfo(Output* pOut) const = 0;	//print all figure info on the status bar
};
