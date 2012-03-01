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

void WgProgressBar_SetGeometry (sWProgressBar*, int x0_, int y0_, int width_, int heigth_);
void WgProgressBar_SetRange (sWProgressBar*, int min_, int max_, int step_);
void WgProgressBar_SetValue (sWProgressBar*, int value);
void WgProgressBar_Draw (sWProgressBar*);
void WgProgressBar_Update (sWProgressBar*);


//*****************************************************************************
//                           Analog indicator widget
typedef struct {
	int x0;
	int y0;
	int diametr;

	int min;
	int max;
	int step;
	int value;
	int oldValue;

} sWAnalogNeedle;

void WgAnalogNeedle_SetGeometry (sWAnalogNeedle*, int x0_, int y0_, int width_, int heigth_);
void WgAnalogNeedle_SetRange (sWAnalogNeedle*, int min_, int max_, int step_);
void WgAnalogNeedle_SetValue (sWAnalogNeedle*, int value_);
void WgAnalogNeedle_Draw (sWAnalogNeedle*);
void WgAnalogNeedle_Update (sWAnalogNeedle*);

#endif
