#pragma once
#include "stdafx.h"

namespace fractal {
	class SierpinskiCarpet : public IGeometricFractal {
	public:
		SierpinskiCarpet();
		SierpinskiCarpet(int size);
		~SierpinskiCarpet();

		double size();
		void setSize(double size);
		void generate(int iters) override;
		const std::vector<Line>* lines() override;
		const std::vector<Square>* squares() override;
	private:
		double size_ = 100;
		std::vector<Square> squares_;

		void generate_(int iters, double size, Pos pos);
	};
	// Constructors & destructors
	SierpinskiCarpet::SierpinskiCarpet() = default;

	SierpinskiCarpet::SierpinskiCarpet(int size) : 
		size_(size) {}

	SierpinskiCarpet::~SierpinskiCarpet() {}

	// Functions
	double SierpinskiCarpet::size() {
		return this->size_;
	}

	const std::vector<Line>* SierpinskiCarpet::lines() {
		return NULL;
	}

	const std::vector<Square>* SierpinskiCarpet::squares() {
		return &this->squares_;
	}

	void SierpinskiCarpet::setSize(double size) {
		this->size_ = size;
		return;
	}

	void SierpinskiCarpet::generate(int iters) {
		this->squares_ = std::vector<Square>();
		this->generate_(iters, this->size_, Pos(0, 0));
		return;
	}

	void SierpinskiCarpet::generate_(int iters, double size, Pos pos) {
		if (iters < 0)
			throw std::exception("Iteration count must be zero or greater");
		if (iters == 0)
			return;
		this->squares_.push_back(Square(pos, size / 3));
		iters--;
		this->generate_(iters, size / 3, Pos(pos.x + size / 3, pos.y + size / 3));
		this->generate_(iters, size / 3, Pos(pos.x - size / 3, pos.y + size / 3));
		this->generate_(iters, size / 3, Pos(pos.x + size / 3, pos.y - size / 3));
		this->generate_(iters, size / 3, Pos(pos.x - size / 3, pos.y - size / 3));
		this->generate_(iters, size / 3, Pos(pos.x + size / 3, pos.y));
		this->generate_(iters, size / 3, Pos(pos.x - size / 3, pos.y));
		this->generate_(iters, size / 3, Pos(pos.x, pos.y + size / 3));
		this->generate_(iters, size / 3, Pos(pos.x, pos.y - size / 3));
	}
}