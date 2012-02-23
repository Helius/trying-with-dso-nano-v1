#ifndef _WIDGETS_H_
#define _WIDGETS_H_

#define _W_FRAME_COLOR WHITE
#define _W_BACKGND_COLOR RGB(20,10,20)


typedef struct {
	int x0;
	int y0;
	int width;
	int heigth;

	int min;
	int max;
	int step;

	int value;
	int oldPos;

} sWProgressBar;

void WgProgressBar_SetGeometry (sWProgressBar * this, int x0_, int y0_, int width_, int heigth_);
void WgProgressBar_SetRange (sWProgressBar * this, int min_, int max_, int step_);
void WgProgressBar_SetValue (sWProgressBar * this, int value);
void WgProgressBar_Update (sWProgressBar * this);
void WgProgressBar_Draw (sWProgressBar * );

#endif
