#pragma once
#include "stdafx.h"

namespace fractal {
	class NewtonFractal : public IAlgebraicFractal {
	public:
		sf::Color getPixelColor(cmpx::Complex<double> pos) override;
	private:
		int iterate(cmpx::Complex<double>& start) override;
		const int maxRad = 2;
	};

	//Functions
	sf::Color NewtonFractal::getPixelColor(cmpx::Complex<double> pos) {
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

	int NewtonFractal::iterate(cmpx::Complex<double>& start) {
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
		}

		return iter;
	}
}
