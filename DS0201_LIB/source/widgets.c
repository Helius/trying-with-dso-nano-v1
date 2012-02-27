#include "widgets.h"
#include "Lcd.h"
#include "xprintf.h"

const int barColors [10] = {
	RGB(0,0,63),
	RGB(0,63,63),
	RGB(0,63,0),
	RGB(40,63,0),
	RGB(50,63,0),
	RGB(63,63,0),
	RGB(63,0,0),
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
	this->oldPos = 0;
}

//*****************************************************************************
void WgProgressBar_SetValue (sWProgressBar * this, int value_)
{
	if (value_ < this->max)
		this->value = value_;
	else
		this->value = this->max;
}

//*****************************************************************************
void WgProgressBar_Draw (sWProgressBar * this)
{
	char text [8];
	this->barHeight = (this->heigth - _W_PGB_TOP_MARGIN) / this->step;
	//1. draw frame and background
	Fill_Rectangle (this->x0, this->y0, this->width, this->heigth, _W_FRAME_COLOR);
	Fill_Rectangle (this->x0+1, this->y0+1, this->width-2, this->heigth-2, _W_BACKGND_COLOR);
	//2. draw top value
  Draw_Str (this->x0+14, this->y0 + this->heigth - 17, GRN, _W_BACKGND_COLOR, "00.0");
	//3. draw left legend mark
	for (int i = 1; i < this->step; i++) {
		xsprintf (text, "%d", ((((this->max - this->min)/this->step)*i) + this->min)/10);
		Draw_Str (this->x0+3, this->y0-5 + i*(this->barHeight+1),RGB(63,63,63),_W_BACKGND_COLOR, text);
	}
}

//*****************************************************************************
void WgProgressBar_Update (sWProgressBar * this)
{
	char text [8];
	// draw value at top of widget
	xsprintf (text, "%d.%d", this->value/10, this->value%10);
  Draw_Str (this->x0 + 14, this->y0 + this->heigth - 17, GRN, _W_BACKGND_COLOR, text);
	
	int oldBarNmb = this->oldPos/this->barHeight;
	int barNmb = 0;
	int linePos = 0;

	if (this->value >= this->min)
		linePos = ((this->value - this->min) * (this->heigth - _W_PGB_TOP_MARGIN)) / (this->max - this->min);

	if (linePos == this->oldPos)
		return;
	// calc higher bar need to show	
	barNmb = linePos/this->barHeight;

	if (barNmb > oldBarNmb) {
		// draw missing bar
		for (int i = oldBarNmb; i < barNmb; i++) {
			Fill_Rectangle (this->x0 + _W_PGB_LEFT_MAGRIN,
											this->y0+3 + i*this->barHeight,
											this->width-3-_W_PGB_LEFT_MAGRIN,
											this->barHeight-_W_PGB_BAR_GAP,
											barColors[barNmb]);

		}
	}

	if (linePos > this->oldPos) {
		Fill_Rectangle (this->x0 + _W_PGB_LEFT_MAGRIN, 
										this->y0 + 3 + (barNmb * this->barHeight ), 
										this->width - 3 - _W_PGB_LEFT_MAGRIN, 
										linePos - (barNmb * this->barHeight), 
										barColors[barNmb+1]);
	} else {
		Fill_Rectangle (this->x0 + _W_PGB_LEFT_MAGRIN, 
										linePos + this->y0 + 3, 
										this->width - 3 - _W_PGB_LEFT_MAGRIN,
										this->oldPos - linePos,
										_W_BACKGND_COLOR);
	}

	this->oldPos = linePos;
}






//*****************************************************************************
//

void Circle(int x, int y, int r)
{
	int x1,y1,yk = 0;
	int sigma,delta,f;

	x1 = 0;
	y1 = r;
	delta = 2*(1-r);

	do
	{
		Point_SCR(x+x1,y+y1);
		Set_Pixel (WHITE);
		Point_SCR(x-x1,y+y1);
		Set_Pixel (WHITE);
		Point_SCR(x+x1,y-y1);
		Set_Pixel (WHITE);
		Point_SCR(x-x1,y-y1);
		Set_Pixel (WHITE);

		f = 0;
		if (y1 < yk)
						break;
		if (delta < 0)
		{
						sigma = 2*(delta+y1)-1;
						if (sigma <= 0)
						{
										x1++;
										delta += 2*x1+1;
										f = 1;
						}
		}
		else
		if (delta > 0)
		{
						sigma = 2*(delta-x1)-1;
						if (sigma > 0)
						{
										y1--;
										delta += 1-2*y1;
										f = 1;
						}
		}
		if (!f)
		{
						x1++;
						y1--;
						delta += 2*(x1-y1-1);
		}
	}
	while(1);
}

void WgAnalogNeedle_Draw (/*sWAnalogNeedle * this*/)
{
	Circle (50,50,25);
}
