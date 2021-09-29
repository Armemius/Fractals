#pragma once
#include "stdafx.h"

namespace fractal {
	class Pos {
	public:
		Pos();
		Pos(double _x, double _y);
		double x = 0, y = 0;
	};

	class Square {
	public:
		Square();
		Square(Pos _center, double _diam);
		Square(double x, double y, double _diam);
		Pos center;
		double diam = 0;
	};

	class Line {
	public:
		Line();
		Line(Pos _pos1, double _angle, double _rad);
		Line(double x0, double y0, double _angle, double _rad);
		const Pos getSecPos();
		Pos pos;

		void setAngle(double angle);
		void setRad(double rad);
		double angle();
		double rad();
	private:
		double angle_ = 0, rad_ = 0;
		void fixAngle();
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
	// Constructors & Destructors
	Line::Line() = default;

	Line::Line(Pos _pos, double angle, double rad) :
		pos(_pos),
		angle_(angle),
		rad_(rad) {
		this->fixAngle();
	}

	Line::Line(double x0, double y0, double angle, double rad) :
		pos(Pos(x0, y0)),
		angle_(angle),
		rad_(rad) {
		this->fixAngle();
	}

	// Getters & setters
	double Line::angle() {
		return this->angle_;
	}

	double Line::rad() {
		return this->rad_;
	}

	void Line::setAngle(double angle) {
		this->angle_ = angle;
		this->fixAngle();
	}

	void Line::setRad(double rad) {
		this->rad_ = rad;
	}

	// Functions
	const Pos Line::getSecPos() {
		return Pos(this->pos.x + std::cos(angle_) * this->rad_, this->pos.y + std::sin(angle_) * this->rad_);
	}

	void Line::fixAngle() {
		if (this->angle_ > 2 * PI) {
			while (this->angle_ > 2 * PI) {
				this->angle_ -= 2 * PI;
			}
		} else if (this->angle_ < 0) {
			while (this->angle_ < 0) {
				this->angle_ += 2 * PI;
			}
		}
	}
}