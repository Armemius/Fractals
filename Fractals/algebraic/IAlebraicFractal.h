#pragma once
#include "stdafx.h"

namespace fractal {
	class IAlgebraicFractal {
	public:
		virtual sf::Color getPixelColor(cmpx::Complex<double> pos) = 0;
	protected:
		const int maxIter_ = 200;
		virtual int iterate(cmpx::Complex<double>& start) = 0;
	};

}