#ifndef __GRAPHICSDISPLAY_H__
#define __GRAPHICSDISPLAY_H__
#include <cstddef>
#include "observer.h"


class Xwindow;

class GraphicsDisplay : public Observer {
	Xwindow* window;
	int squareSize; // size of each square

  public:
	explicit GraphicsDisplay(size_t dimension);
	~GraphicsDisplay();
	
	// whenever textdisplay is updated so is the window
	virtual void notify(Subject& whoNotified) override;
	virtual void notify() override;

};

#endif
