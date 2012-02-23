#include "widgets.h"
#include "Lcd.h"
#include "xprintf.h"

const int barColors [10] = {
	RGB(0,63,0),
	RGB(10,63,0),
	RGB(20,63,0),
	RGB(30,63,0),
	RGB(40,63,0),
	RGB(50,63,0),
	RGB(55,63,0),
	RGB(63,40,0),
	RGB(63,30,0),
	RGB(63,0,0),
	};

//*****************************************************************************
void WgProgressBar_SetGeometry (sWProgressBar * this, int x0_, int y0_, int width_, int heigth_)
{
	this->x0 = x0_;
	this->y0 = y0_;
	this->width = width_;
	this->heigth = heigth_;
}

//*****************************************************************************
void WgProgressBar_SetRange (sWProgressBar * this, int min_, int max_, int step_)
{
	this->min = min_;
	this->max = max_;
	this->step = step_;
	this->oldBarNmb = 0;
}

//*****************************************************************************
void WgProgressBar_SetValue (sWProgressBar * this, int value_)
{
	this->value = value_;
}

//*****************************************************************************
void WgProgressBar_Draw (sWProgressBar * this)
{
	//1. draw frame and background
	Fill_Rectangle (this->x0, this->y0, this->width, this->heigth, _W_FRAME_COLOR);
	Fill_Rectangle (this->x0+1, this->y0+1, this->width-2, this->heigth-2, _W_BACKGND_COLOR);
//	//2. draw top value
  Draw_Str (this->x0+10, this->y0 + this->heigth - 17, GRN, _W_BACKGND_COLOR, "10.3");
}

//*****************************************************************************
void WgProgressBar_Update (sWProgressBar * this)
{
	char text [8];
//	sprintf (text, "%d.%d", this->value/10, this->value%10);
	xsprintf (text, "%d.%d", this->value/10, this->value%10);
  Draw_Str (this->x0+10, this->y0 + this->heigth - 17, GRN, _W_BACKGND_COLOR, text);
	
	int barH = (this->heigth - 20) / this->step;
	int barNmb = ((this->value-this->min)*this->step)/this->max;

	if (barNmb > this->oldBarNmb) {
		// draw missing bar
		for (int i = this->oldBarNmb; i < barNmb; i++) {
			Fill_Rectangle (this->x0+3, this->y0+3 + i*(barH+1), this->width-6, barH, barColors[barNmb-1]);
			xsprintf (text, "%d", this->min+((this->max - this->min)*i)/this->step);
			Draw_Str (this->x0+14, this->y0+3 + i*(barH+1),RGB(20,20,20),barColors[barNmb-1], text);
		}
	} else if (barNmb < this->oldBarNmb) {
		// just clear waste bar
		for (int i = barNmb + 1; i < this->oldBarNmb; i++) {
			Fill_Rectangle (this->x0+3, this->y0+3 + i*(barH+1), this->width-6, barH, _W_BACKGND_COLOR);
			xsprintf (text, "%d", this->min+((this->max - this->min)*i)/this->step);
			Draw_Str (this->x0+14, this->y0+3 + i*(barH+1),RGB(20,20,20),_W_BACKGND_COLOR,text);
		}
	}
	this->oldBarNmb = barNmb;
}
