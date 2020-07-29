#include "textdisplay.h"
#include "observer.h"
#include "subject.h"


// constructor
TextDisplay::TextDisplay(size_t n) {
	for (size_t rowCounter {}; rowCounter < n; ++rowCounter) {
		std::vector<char> temp;

		for (size_t colCounter {}; colCounter < n; ++colCounter) {
			temp.push_back('_');
		}

		theDisplay.push_back(temp);
	}
}


// TextDisplay::notify(whoNotified) updates the textdisplay depending on the aliveness of the subject cell
void TextDisplay::notify(Subject& whoNotified) {
	Info info {whoNotified.getInfo()};
	const size_t r {info.row}, c {info.col};

	if (info.state == State::Alive) {
		theDisplay[r][c] = 'X';
	} else {
		theDisplay[r][c] = '_';
	}
}


// TextDisplay::notify() does nothing
void TextDisplay::notify() {}


// operator<<(out, td) prints the game grid
std::ostream& operator<<(std::ostream& out, const TextDisplay& td) {
	for (auto& i : td.theDisplay) {
		for (auto& n : i) {
			out << n;
		}

		out << std::endl;
	}

	return out;
}
