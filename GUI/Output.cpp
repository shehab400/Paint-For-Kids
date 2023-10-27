#include "Output.h"
#include <cmath>

Output::Output()
{
	//Initialize user interface parameters
	UI.InterfaceMode = MODE_DRAW;
	UI.width = 1250;
	UI.height = 650;
	UI.wx = 5;
	UI.wy = 5;


	UI.StatusBarHeight = 50;
	UI.ToolBarHeight = 50;
	UI.MenuItemWidth = 47;

	UI.DrawColor = BLUE;	//Drawing color
	UI.FillColor = GREEN;	//Filling color
	UI.MsgColor = RED;		//Messages color
	UI.BkGrndColor = LIGHTGOLDENRODYELLOW;	//Background color
	UI.HighlightColor = MAGENTA;	//This color should NOT be used to draw figures. use if for highlight only
	UI.StatusBarColor = TURQUOISE;
	UI.PenWidth = 3;	//width of the figures frames


	//Create the output window
	pWind = CreateWind(UI.width, UI.height, UI.wx, UI.wy);
	//Change the title
	pWind->ChangeTitle("Paint for Kids - Programming Techniques Project");

	CreateDrawToolBar();
	CreateStatusBar();
}


Input* Output::CreateInput() const
{
	Input* pIn = new Input(pWind);
	return pIn;
}

//======================================================================================//
//								Interface Functions										//
//======================================================================================//

window* Output::CreateWind(int w, int h, int x, int y) const
{
	window* pW = new window(w, h, x, y);
	pW->SetBrush(UI.BkGrndColor);
	pW->SetPen(UI.BkGrndColor, 1);
	pW->DrawRectangle(0, UI.ToolBarHeight, w, h);
	return pW;
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateStatusBar() const
{
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::ClearStatusBar() const
{
	//Clear Status bar by drawing a filled white rectangle
	pWind->SetPen(UI.StatusBarColor, 1);
	pWind->SetBrush(UI.StatusBarColor);
	pWind->DrawRectangle(0, UI.height - UI.StatusBarHeight, UI.width, UI.height);
}
//////////////////////////////////////////////////////////////////////////////////////////
void Output::CreateDrawToolBar() const
{
	UI.InterfaceMode = MODE_DRAW;

	//You can draw the tool bar icons in any way you want.
	//Below is one possible way

	//First prepare List of images for each menu item
	//To control the order of these images in the menu, 
	//reoder them in UI_Info.h ==> enum DrawMenuItem
	string MenuItemImages[DRAW_ITM_COUNT];
	MenuItemImages[ITM_RECT] = "images\\MenuItems\\Menu_Rect.jpg";

	MenuItemImages[ITM_SQUARE] = "images\\MenuItems\\Menu_square.jpg";
	MenuItemImages[ITM_TRIANGLE] = "images\\MenuItems\\Menu_triangle.jpg";
	MenuItemImages[ITM_HEXAGON] = "images\\MenuItems\\Menu_hexagon.jpg";
	MenuItemImages[ITM_CIRCLE] = "images\\MenuItems\\Menu_Circ.jpg";
	MenuItemImages[ITM_SELECTONE] = "images\\MenuItems\\Menu_select.jpg";
	MenuItemImages[ITM_DRWCOLOR] = "images\\MenuItems\\Menu_drawcolor.jpg";
	MenuItemImages[ITM_FILLINGCOLOR] = "images\\MenuItems\\Menu_fillcolor.jpg";
	MenuItemImages[ITM_BLACK] = "images\\MenuItems\\Menu_black.jpg";
	MenuItemImages[ITM_YELLOW] = "images\\MenuItems\\Menu_yellow.jpg";
	MenuItemImages[ITM_ORANGE] = "images\\MenuItems\\Menu_orange.jpg";
	MenuItemImages[ITM_RED] = "images\\MenuItems\\Menu_red.jpg";
	MenuItemImages[ITM_GREEN] = "images\\MenuItems\\Menu_green.jpg";
	MenuItemImages[ITM_BLUE] = "images\\MenuItems\\Menu_blue.jpg";
	MenuItemImages[ITM_DELETEFIGURE] = "images\\MenuItems\\Menu_delete.jpg";
	MenuItemImages[ITM_MOVEFIGURE] = "images\\MenuItems\\Menu_move.jpg";
	MenuItemImages[ITM_UNDO] = "images\\MenuItems\\Menu_undo.jpg";
	MenuItemImages[ITM_REDO] = "images\\MenuItems\\Menu_redo.jpg";
	MenuItemImages[ITM_CLEARALL] = "images\\MenuItems\\Menu_clearall.jpg";
	MenuItemImages[ITM_STARTRECORD] = "images\\MenuItems\\Menu_start.jpg";
	MenuItemImages[ITM_STOPRECORD] = "images\\MenuItems\\Menu_stop.jpg";
	MenuItemImages[ITM_PLAYRECORD] = "images\\MenuItems\\Menu_play.jpg";
	MenuItemImages[ITM_SAVEGRAPH] = "images\\MenuItems\\Menu_save.jpg";
	MenuItemImages[ITM_LOADGRAPH] = "images\\MenuItems\\Menu_load.jpg";
	MenuItemImages[ITM_SWITCH] = "images\\MenuItems\\Menu_switch.jpg";
	MenuItemImages[ITM_EXIT] = "images\\MenuItems\\Menu_Exit.jpg";
	//TODO: Prepare images for each menu item and add it to the list

	//Draw menu item one image at a time
	for (int i = 0; i < DRAW_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);



	//Draw a line under the toolbar
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);




}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::cleartoolbar() const
{
	Point p1;
	p1.x = 0;
	p1.y = 0;
	Point p2;
	p2.x = (UI.MenuItemWidth) * DRAW_ITM_COUNT;
	p2.y = UI.ToolBarHeight;
	GfxInfo x;
	x.FillClr = SNOW;
	x.DrawClr = SNOW;
	x.BorderWdth = 3;
	x.isFilled = TRUE;

	DrawRect(p1, p2, x);
}


void Output::CreatePlayToolBar() const
{
	UI.InterfaceMode = MODE_PLAY;
	string MenuItemImages[PLAY_ITM_COUNT];
	MenuItemImages[ITM_FIGURETYPE] = "images\\MenuItems\\Menu_select.jpg";
	MenuItemImages[ITM_FIGURECOLOR] = "images\\MenuItems\\Menu_fillcolor.jpg";
	MenuItemImages[ITM_FIGURETYPEANDCOLOR] = "images\\MenuItems\\Menu_drawcolor.jpg";
	MenuItemImages[ITM_SWITCHTODRAWMODE] = "images\\MenuItems\\Menu_switch.jpg";
	MenuItemImages[ITM_RESTART] = "images\\MenuItems\\Menu_restart.jpg";

	cleartoolbar();
	for (int i = 0; i < PLAY_ITM_COUNT; i++)
		pWind->DrawImage(MenuItemImages[i], i * UI.MenuItemWidth, 0, UI.MenuItemWidth, UI.ToolBarHeight);
	pWind->SetPen(RED, 3);
	pWind->DrawLine(0, UI.ToolBarHeight, UI.width, UI.ToolBarHeight);


}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::ClearDrawArea() const
{
	pWind->SetPen(UI.BkGrndColor, 1);
	pWind->SetBrush(UI.BkGrndColor);
	pWind->DrawRectangle(0, UI.ToolBarHeight, UI.width, UI.height - UI.StatusBarHeight);

}
//////////////////////////////////////////////////////////////////////////////////////////

void Output::PrintMessage(string msg) const	//Prints a message on status bar
{
	ClearStatusBar();	//First clear the status bar

	pWind->SetPen(UI.MsgColor, 50);
	pWind->SetFont(20, BOLD, BY_NAME, "Arial");
	pWind->DrawString(10, UI.height - (int)(UI.StatusBarHeight / 1.5), msg);
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntDrawColor() const	//get current drawing color
{
	return UI.DrawColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

color Output::getCrntFillColor() const	//get current filling color
{
	return UI.FillColor;
}
//////////////////////////////////////////////////////////////////////////////////////////

int Output::getCrntPenWidth() const		//get current pen width
{
	return UI.PenWidth;
}

//======================================================================================//
//								Figures Drawing Functions								//
//======================================================================================//

void Output::DrawRect(Point P1, Point P2, GfxInfo RectGfxInfo, bool selected) const
{
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	else
		DrawingClr = RectGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (RectGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(RectGfxInfo.FillClr);
	}
	else
		style = FRAME;


	pWind->DrawRectangle(P1.x, P1.y, P2.x, P2.y, style);

}

void Output::DrawSqu(Point P1, GfxInfo SquGfxInfo, bool selected) const {
	const int length = 50; //Size of the Square
	color DrawingClr;
	if (selected)
		DrawingClr = UI.HighlightColor;
	else
		DrawingClr = SquGfxInfo.DrawClr;

	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (SquGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(SquGfxInfo.FillClr);
	}
	else
		style = FRAME;

	int x1 = P1.x + 50;
	int y1 = P1.y + 50;
	int x2 = P1.x - 50;
	int y2 = P1.y - 50;
	pWind->DrawRectangle(x1, y1, x2, y2, style);

}
void Output::DrawCircle(Point P1, Point P2, GfxInfo CircleGfx, bool selected) const {
	color DrawingClr;
	if (selected) {
		DrawingClr = UI.HighlightColor; //Figure should be drawn highlighted
	}
	else {
		DrawingClr = CircleGfx.DrawClr;
	}
	pWind->SetPen(DrawingClr, 1);
	drawstyle style;
	if (CircleGfx.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(CircleGfx.FillClr);
	}
	else {
		style = FRAME;
	}
	float r = sqrtf(pow((P1.x - P2.x), 2) + pow((P1.y - P2.y), 2));
	pWind->DrawCircle(P1.x, P1.y, r, style);
}

void Output::DrawHexagon(Point CENTER, GfxInfo HexagonGfxInfo, bool selected) const {
	color DrawingClr;
	drawstyle style;
	pWind->SetPen(HexagonGfxInfo.DrawClr, HexagonGfxInfo.BorderWdth);
	if (selected) {
		DrawingClr = UI.HighlightColor;
	}
	else {
		DrawingClr = HexagonGfxInfo.DrawClr;
	}
	if (HexagonGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(HexagonGfxInfo.FillClr);
	}
	else {
		style = FRAME;
	}
	int x = (float)CENTER.x;
	int y = (float)CENTER.y;
	int x_coordinates[6];
	int y_coordinates[6];
	int  a = 100;
	double angle = 3.141592654 / 3;
	for (int i = 1; i < 7; i++) {
		x_coordinates[i - 1] = x - cos(i * angle) * a;
		y_coordinates[i - 1] = y + sin(i * angle) * a;
	}
	pWind->DrawPolygon(x_coordinates, y_coordinates, 6, style);
}

void Output::DrawTriangle(Point P1, Point P2, Point P3, GfxInfo TriangleGfxInfo, bool selected) const {
	color DrawingClr;
	drawstyle style;
	pWind->SetPen(TriangleGfxInfo.DrawClr, TriangleGfxInfo.BorderWdth);
	if (selected) {
		DrawingClr = UI.HighlightColor;
	}
	else {
		DrawingClr = TriangleGfxInfo.DrawClr;
	}
	if (TriangleGfxInfo.isFilled)
	{
		style = FILLED;
		pWind->SetBrush(TriangleGfxInfo.FillClr);
	}
	else {
		style = FRAME;
	}
	pWind->DrawTriangle(P1.x, P1.y, P2.x, P2.y, P3.x, P3.y, style);
}



//////////////////////////////////////////////////////////////////////////////////////////
Output::~Output()
{
	delete pWind;
}

