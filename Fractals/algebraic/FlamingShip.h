#pragma once
#include "stdafx.h"

namespace fractal {
	class ShipFractal : public IAlgebraicFractal {
	public:
		sf::Color getPixelColor(cmpx::Complex<long double> pos) override;
	private:
		int iterate(cmpx::Complex<long double>& start) override;
		const int maxIter_ = 200;

	};

	//Functions
	sf::Color ShipFractal::getPixelColor(cmpx::Complex<long double> pos) {
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

	int ShipFractal::iterate(cmpx::Complex<long double>& start) {
		cmpx::Complex<long double> zz(0, 0);
		double x = 0, y = 0;
		double x0 = start.nat(), y0 = start.cpx();
		cmpx::Complex<long double> old;
		long double rad = 4;
		int iter = 0;
		while (abs(zz) <= rad && iter < maxIter_) {
			zz = pow(cmpx::Complex<long double>(abs(zz.nat()), abs(zz.cpx())), 2) + start;
			if (abs(zz - old) < 1e-7) {
				return maxIter_;
			}

			iter++;
			old = zz;
		}

		return iter;
	}
}
