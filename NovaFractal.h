#pragma once
#include "stdafx.h"

namespace fractal {
	class NovaFractal : public IAlgebraicFractal {
	public:
		sf::Color getPixelColor(cmpx::Complex<long double> pos) override;
	private:
		int iterate(cmpx::Complex<long double>& start) override;
		const int maxRad = 2;
	};

	//Functions
	sf::Color NovaFractal::getPixelColor(cmpx::Complex<long double> pos) {
		int iters = this->iterate(pos);
		if (iters == this->maxIter_)
			return sf::Color::Black;
		double k = iters * 1.0 / maxIter_;
		return sf::Color(255 * k, 255 * k, 255 * k);
	}

	int NovaFractal::iterate(cmpx::Complex<long double>& start) {
		cmpx::Complex<long double> zz(0, 0);

		double x = 0, y = 0;
		double x0 = start.nat(), y0 = start.cpx();
		cmpx::Complex<long double> old;
		int iter = 0;
		while (abs(zz) <= abs(start) && iter < maxIter_) {
			zz = zz + zz - 10;
			
			if (abs(zz - old) < 1e-7) {
				return maxIter_;
			}

			iter++;
			old = zz;
		}

		return iter;
	}
}
