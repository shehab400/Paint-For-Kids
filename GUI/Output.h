#ifndef OUPTUT_H
#define OUPTUT_H
#include "Input.h"

class Output	//The application manager should have a pointer to this class
{
private:
	window* pWind;	//Pointer to the Graphics Window
public:
	Output();

	window* CreateWind(int, int, int, int) const; //creates the application window
	void CreateDrawToolBar() const;	//creates Draw mode toolbar & menu  PHASE1
	void CreatePlayToolBar() const;	//creates Play mode toolbar & menu  PHASE1
	void CreateStatusBar() const;	//create the status bar             
	void cleartoolbar() const; // clears the toolbar

	Input* CreateInput() const; //creates a pointer to the Input object	
	void ClearStatusBar() const;	//Clears the status bar
	void ClearDrawArea() const;	//Clears the drawing area    

	// -- Figures Drawing functions
	void DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected = false) const;  //Draw a rectangle 

	///TODO: Make similar functions for drawing all other figure types.
	void DrawSqu(Point P1, GfxInfo SquGfxInfo, bool selected = false) const;
	void DrawCircle(Point P1, Point P2, GfxInfo CircleGfx, bool selected = false) const;
	void DrawHexagon(Point CENTER, GfxInfo HexagonGfxInfo, bool selected = false) const;  // PHASE1
	void DrawTriangle(Point P1, Point P2, Point P3, GfxInfo TriangleGfxInfo, bool selected = false) const;  // PHASE1

	void PrintMessage(string msg) const;	//Print a message on Status bar 

	color getCrntDrawColor() const;	//get current drwawing color 
	color getCrntFillColor() const;	//get current filling color   
	int getCrntPenWidth() const;		//get current pen width   


	~Output();
};

#endif