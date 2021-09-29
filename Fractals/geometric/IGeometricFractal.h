#pragma once
#include "stdafx.h"

namespace fractal {
	class IGeometricFractal {
	public:
		virtual void generate(int iters) = 0;
		virtual const std::vector<Line>* lines() = 0;
		virtual const std::vector<Square>* squares() = 0;
	};
}