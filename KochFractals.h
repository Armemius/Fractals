#pragma once
#include "stdafx.h"

namespace fractal {
	class KochCurve {
	public:
		KochCurve();
		KochCurve(int size);

		const std::vector<Line>& lines();
		void generate(int iters);
	protected:
		double size_ = 100;
		std::vector<Line> lines_;
	private:
		std::vector<Line> tmp;
	};

	class KochSnowflake : public KochCurve {
	public:
		KochSnowflake();
		KochSnowflake(int size);
	};

	// Koch curve
	// Constructors & destructors
	KochCurve::KochCurve() {
		lines_ = std::vector<Line>();
		lines_.push_back(Line(-size_ / 2, 0, 0, size_));
	}

	KochCurve::KochCurve(int size) :
		size_(size) {
		lines_ = std::vector<Line>();
		lines_.push_back(Line(-size_ / 2, 0, 0, size_));
	}

	// Getters & setters
	const std::vector<Line>& KochCurve::lines() {
		return this->lines_;
	}

	// Functions
	void KochCurve::generate(int iters) {
		if (iters < 0)
			throw std::exception("Iteration count must be zero or greater");
		if (iters == 0)
			return;
		tmp = std::vector<Line>();
		for (Line& i : this->lines_) {
			Pos pos = i.pos;
			double angle = i.angle(), rad = i.rad();
			Line line1 = Line(pos, angle, rad / 3),
				 line2 = Line(line1.getSecPos(), angle + PI / 3, rad / 3),
				 line3 = Line(line2.getSecPos(), angle - PI / 3, rad / 3),
				 line4 = Line(line3.getSecPos(), angle, rad / 3);
			tmp.push_back(line1);
			tmp.push_back(line2);
			tmp.push_back(line3);
			tmp.push_back(line4);
		}
		lines_ = tmp;
		this->generate(iters - 1);
	}

	// Koch snowflake
	KochSnowflake::KochSnowflake() {
		lines_ = std::vector<Line>();
		Line line1(-size_ / 2, 0, 0, size_),
			line2(line1.getSecPos(), -PI / 3, size_),
			line3(line2.getSecPos(), -PI * 2 / 3, size_);
		lines_.push_back(line1);
		lines_.push_back(line2);
		lines_.push_back(line3);
	}

	KochSnowflake::KochSnowflake(int size) {
		this->size_ = size;
		lines_ = std::vector<Line>();
		Line line1(-size_ / 2, 0, 0, size_),
			 line2(line1.getSecPos(), -PI * 2 / 3, size_),
			 line3(line2.getSecPos(), -PI * 4 / 3, size_);
		lines_.push_back(line1);
		lines_.push_back(line2);
		lines_.push_back(line3);
	}
}
