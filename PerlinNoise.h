#pragma once
#include "stdafx.h"

namespace fractal {
	class vec {
	public:
		double x = 0, y = 0;
	};
	class PerlinNoise {
	public:
		PerlinNoise(int width, int height);
	private:
		
		int width_ = 0, height_ = 0;
		std::vector<std::vector<double>> display;
	};

	// Constructors & destructors
	PerlinNoise::PerlinNoise(int width, int height) :
		width_(width), 
		height_(height) {}

	// Functions
}