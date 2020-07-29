#include "graphicsdisplay.h"
#include "info.h"
#include "window.h"
#include "subject.h"


static const size_t windowSize {500};


// constructor
GraphicsDisplay::GraphicsDisplay(size_t dimension) :
	window {new Xwindow},
	squareSize {windowSize / dimension}
{
// if remainder > 0 then maybe draw a line to show the end of the grid?
}


// destructor
GraphicsDisplay::~GraphicsDisplay() {
	delete window;
}


// GraphicsDisplay::notify(whoNotified) updates the graphics window based on the state of the subject cell
void GraphicsDisplay::notify(Subject& whoNotified) {
	Info info {whoNotified.getInfo()};
	const size_t r {info.row}, c {info.col};

	if (info.state == State::Alive) {
		window->fillRectangle(c * squareSize, r * squareSize, squareSize, squareSize, Xwindow::Black);
	} else {
		window->fillRectangle(c * squareSize, r * squareSize, squareSize, squareSize, Xwindow::White);
	}
}


// GraphicsDisplay::notify() does nothing
void GraphicsDisplay::notify() {}
