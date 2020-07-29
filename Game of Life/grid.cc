#include "grid.h"
#include "observer.h"
#include "textdisplay.h"
#include "graphicsdisplay.h"


static const size_t edge {1};


// Destructor
Grid::~Grid() {
	delete td;
	delete ob;
}


// Grid::init(n) sets up an n x n grid
void Grid::init(size_t n) {
	// if old grid exists
	if (td) delete td;
	// if old window exists
	if (ob) delete ob;
	if (cells.size() > 0) {
		for (auto& i : cells) {
			i.clear();
		}

		cells.clear();
	}

	// create new display
	td = new TextDisplay {n};

	// creates new graphic display
	ob = new GraphicsDisplay {n};

	// create new cells
	for (size_t rowCount {}; rowCount < n; ++rowCount) {
		std::vector<Cell> temp;

		for (size_t colCount {}; colCount < n; ++colCount) {
			// Cell tempCell {rowCount, colCount};
			temp.push_back(Cell {rowCount, colCount});
		}

		cells.push_back(temp);
	}

	// attach observers
	for (size_t rowCount {}; rowCount < n; ++rowCount) {
		for (size_t colCount {}; colCount < n; ++colCount) {
			size_t r {rowCount}, c {colCount};
			Cell& current {cells[r][c]};

			current.attach(td); // attach textdisplay
			current.attach(ob); // attach graphics display

			// Note: moved all "- 1" operations to the otehr side of inequality to avoid int overflow
			// check to see if neighbours exist
			if ((rowCount >= edge) && (colCount >= edge)) current.attach(&(cells[rowCount - edge][colCount - edge])); // top left
            if (rowCount >= edge) current.attach(&(cells[rowCount - edge][colCount])); // top center
            if ((rowCount >= edge) && (colCount + edge < n)) current.attach(&(cells[rowCount - edge][colCount + edge])); // top right
            if (colCount >= edge) current.attach(&(cells[rowCount][colCount - edge])); // center left
            if (colCount + edge < n) current.attach(&(cells[rowCount][colCount + edge])); // center right
            if ((rowCount + edge < n) && (colCount >= edge)) current.attach(&(cells[rowCount + edge][colCount - edge])); // bottom left
            if (rowCount + edge < n) current.attach(&(cells[rowCount + edge][colCount])); // bottom center
            if ((rowCount + edge < n) && (colCount + edge < n)) current.attach(&(cells[rowCount + edge][colCount + edge])); // bottom right
		}
	}
}


// Grid::turnOn(r, c) marks cell at row r, col c as alive
void Grid::turnOn(size_t r, size_t c) { // r is x coord c is y coord
	cells[c][r].setLiving();
	td->notify(cells[c][r]);
	ob->notify(cells[c][r]);
}


// Grid::tick() simulates the next generation of the game
void Grid::tick() {
	// reset alive neighbour count
	for (auto& i : cells) {
		for (auto& n : i) {
			n.reset();
		}
	}

	// update alive neighbour count
	for (auto& i : cells) {
		for (auto& n : i) {
			n.notify();
		}
	}
	
	// recalculate states of cells
	for (auto& i : cells) {
		for (auto& n : i) {
			n.recalculate();
		}
	}

	// update textdisplay
	for (auto& i : cells) {
		for (auto& n : i) {
			td->notify(n);
			ob->notify(n);
		}
	}
}


// operator<<(out, g) uses the TextDisplay object to output the grid information
std::ostream& operator<<(std::ostream& out, const Grid& g) {
	if (!g.td || g.cells.size() == 0) return out;

	out << *(g.td);

	return out;
}

