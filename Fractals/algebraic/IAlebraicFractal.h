#pragma once
#include "stdafx.h"

namespace fractal {
	class IAlgebraicFractal {
	public:
		virtual sf::Color getPixelColor(cmpx::Complex<long double> pos) = 0;
	protected:
		const int maxIter_ = 100;
		virtual int iterate(cmpx::Complex<long double>& start) = 0;
	};

}