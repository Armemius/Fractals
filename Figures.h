#pragma once
#include "stdafx.h"

namespace fractal {
	struct Pos {
		Pos();
		Pos(double _x, double _y);
		double x = 0, y = 0;
	};

	struct Square {
		Square();
		Square(Pos _center, double _diam);
		Square(double x, double y, double _diam);
		Pos center;
		double diam = 0;
	};

	struct Line {
		Line();
		Line(Pos _pos1, Pos _pos2);
		Line(double x0, double y0, double x1, double y1);
		Pos pos1, pos2;
	};

	// Pos
	Pos::Pos() = default;

	Pos::Pos(double _x, double _y) :
		x(_x), 
		y(_y) {}

	// Square
	Square::Square() = default;

	Square::Square(Pos _center, double _diam) :
		center(Pos(_center)),
		diam(_diam) {}

	Square::Square(double x, double y, double _diam) :
		center(Pos(x, y)),
		diam(_diam) {}

	// Line
	Line::Line() = default;

	Line::Line(Pos _pos1, Pos _pos2) :
		pos1(_pos1),
		pos2(_pos2) {}

	Line::Line(double x0, double y0, double x1, double y1) :
		pos1(Pos(x0, y0)),
		pos2(Pos(x1, y1)) {}
}