#include "stdafx.h"

int main() {
	fractal::SierpinskiCarpet ff(18);
	ff.generate(3);
	for (auto i : ff.squares()) {
		std::cout << i.center.x << " " << i.center.y << " " << i.diam << "\n";
	}
}