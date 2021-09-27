#include "stdafx.h"

int main() {
	fractal::KochSnowflake kc(10);
	kc.generate(0);
	for (auto i : kc.lines()) {
		std::cout << std::fixed << i.pos.x << " " << i.pos.y << " -> " << i.getSecPos().x << " " << i.getSecPos().y << "\n\n";
	}

	return 0;
	fractal::Line line(0, 0, PI/3, 10);
	fractal::Pos pos = line.getSecPos();
	std::cout << std::fixed << pos.x << " " << pos.y;
}