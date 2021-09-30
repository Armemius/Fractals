#pragma once
#include "stdafx.h"

namespace fractal {
	class MandelbrotSet : public IAlgebraicFractal {
	public:
		const sf::Color getPixelColor(cmpx::Complex<double> pos) override;
	private:
		int iterate(cmpx::Complex<double>& start) override;
		const int maxRad = 2;
	};

	//Functions
	const sf::Color MandelbrotSet::getPixelColor(cmpx::Complex<double> pos) {
		int iters = 0;
		if (cache.count(pos)) {
			iters = cache[pos];
		} else {
			iters = this->iterate(pos);
			cache.insert({pos, iters});
		}
		if (iters == maxIter_)
			return sf::Color::Black;
		return sf::Color::White;
	}

	int MandelbrotSet::iterate(cmpx::Complex<double>& start) {
		cmpx::Complex<double> comp(0, 0);

		double x2 = 0, y2 = 0;
		double x = comp.nat(), y = comp.cpx();
		double x0 = start.nat(), y0 = start.cpx();
		double xold = 0, yold = 0, period = 0;

		int iter = 0;
		while (x2 + y2 <= 4 && iter < maxIter_) {
			y = (x + x) * y + y0;
			x = x2 - y2 + x0;
			x2 = x * x;
			y2 = y * y;
			iter++;

			if (std::abs(x - xold) < 1e-5 and std::abs(y - yold) < 1e-5) {
				iter = maxIter_;
				break;
			}
			period = period + 1;
			if (period > 20) {
				period = 0;
				xold = x;
				yold = y;
			}
		}

		return iter;
	}
}