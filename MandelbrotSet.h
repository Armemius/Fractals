#pragma once
#include "stdafx.h"

namespace fractal {
	class MandelbrotSet : public IAlgebraicFractal {
	public:
		sf::Color getPixelColor(cmpx::Complex<long double> pos) override;
	private:
		int iterate(cmpx::Complex<long double>& start) override;
		const int maxRad = 2;
	};
	
	//Functions
	sf::Color MandelbrotSet::getPixelColor(cmpx::Complex<long double> pos) {
		int iters = this->iterate(pos);
		if (iters == this->maxIter_)
			return sf::Color::Black;
		double k = iters * 1.0 / maxIter_;
		if (k > 0.75)
			return sf::Color(75 * k, 0, 0);
		if (k > 0.5)
			return sf::Color(100 * k, 0, 100 * k);
		if (k > 0.25)
			return sf::Color(255, 0, 255 * k);
		return sf::Color(1000 * k, 0, 1000 * k);
	}
	
	int MandelbrotSet::iterate(cmpx::Complex<long double>& start) {
		cmpx::Complex<long double> complex(0, 0);

		cmpx::Complex<long double> recurent(0, 0);
		double x = 0, y = 0;
		double x0 = start.nat(), y0 = start.cpx();
		cmpx::Complex<long double> old;

		int iter = 0;
		while (abs(complex) <= 4 && iter < maxIter_) {
			complex = (complex * complex) + start;
			
			if (abs(complex - old) < 1e-7) {
				return maxIter_;
			}
			iter++;
			old = complex;
		}

		return iter;
	}
}