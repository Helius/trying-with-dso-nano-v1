#ifndef _WIDGETS_H_
#define _WIDGETS_H_

#define _W_FRAME_COLOR WHITE
#define _W_BACKGND_COLOR RGB(20,10,20)

//*****************************************************************************
//                         Progress bar widget

#define _W_PGB_TOP_MARGIN   20 // gap for top value text
#define _W_PGB_LEFT_MAGRIN  22 // gap for left legend marks
#define _W_PGB_BAR_GAP      2  // horisontale gap beetwen bars

typedef struct {
	int x0;
	int y0;
	int width;
	int heigth;

	int min;
	int max;
	int step;
	int barHeight;

	int value;
	int oldPos;

} sWProgressBar;

void WgProgressBar_SetGeometry (sWProgressBar * this, int x0_, int y0_, int width_, int heigth_);
void WgProgressBar_SetRange (sWProgressBar * this, int min_, int max_, int step_);
void WgProgressBar_SetValue (sWProgressBar * this, int value);
void WgProgressBar_Update (sWProgressBar * this);
void WgProgressBar_Draw (sWProgressBar * );

//*****************************************************************************
//                           Analog indicator widget
typedef struct {
	int ry;
	int rx;
	int Rad;

	int min;
	int max;
	int step;
	int value;
	int oldValue;

} sWAnalogNeedle;

void WgAnalogNeedle_Draw (/*sWAnalogNeedle * */);
void WgAnalogNeedle_SetGeometry (sWAnalogNeedle * this, int x0_, int y0_, int diametr_);
void WgAnalogNeedle_SetRange (sWAnalogNeedle * this, int min_, int max_, int step_);
void WgAnalogNeedle_SetValue (sWAnalogNeedle * this, int value);
void WgAnalogNeedle_Update (sWAnalogNeedle * this);
void WgAnalogNeedle_Draw (sWAnalogNeedle * );

#endif
