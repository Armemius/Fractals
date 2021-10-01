#pragma once
#include "stdafx.h"

namespace fractal {
	class JuliaSet : public IAlgebraicFractal {
	public:
		sf::Color getPixelColor(cmpx::Complex<long double> pos) override;
	private:
		int iterate(cmpx::Complex<long double>& start) override;
		const int maxIter_ = 1250;

	};

	//Functions
	sf::Color JuliaSet::getPixelColor(cmpx::Complex<long double> pos) {
		int iters = this->iterate(pos);
		if (iters == this->maxIter_)
			return sf::Color::Black;
		double k = iters * 1.0 / maxIter_;
		if (k < 0.15)
			return sf::Color(255 / 0.15 * k, 0, 0);
		if (k < 0.3)
			return sf::Color(255 / 0.3 * k, 0, 0);
		if (k > 0.7)
			return sf::Color(100 / 0.7 * k, 0, 0);
		return sf::Color(155 * k * 4, 0, 155 * k * 4);
	}

	int JuliaSet::iterate(cmpx::Complex<long double>& start) {
		cmpx::Complex<long double> zz = start;
		cmpx::Complex<long double> con(-0.74543, 0.11301);
		double x = 0, y = 0;
		double x0 = start.nat(), y0 = start.cpx();
		cmpx::Complex<long double> old;
		long double rad = (1.0 + std::sqrt(1.0 + 4.0 * abs(con))) / 2.0;
		int iter = 0;
		while (abs(zz) <= rad && iter < maxIter_) {
			zz = zz * zz + con;
			
			if (abs(zz - old) < 1e-7) {
				return maxIter_;
			}

			iter++;
			old = zz;
		}

		return iter;
	}
}
