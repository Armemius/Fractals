#pragma once
#include "stdafx.h"

namespace fractal {
	class IAlgebraicFractal {
	public:
		virtual const sf::Color getPixelColor(cmpx::Complex<double> pos) = 0;
	protected:
		const int maxIter_ = 100;
		std::map<cmpx::Complex<double>, int> cache;
		virtual int iterate(cmpx::Complex<double>& start) = 0;
	};

}