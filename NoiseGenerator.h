#pragma once
#include "stdafx.h"
#define BLACK sf::Color::Black

int fix(int n) {
	if (n < 0) return 0;
	if (n >= 255) return 255;
	return n;
}
void addRandColor(sf::Color& c, int t) {
	t /= 15;
	t *= t;
	c = sf::Color(fix(xorshf96() % t - t / 2 + c.r), fix(xorshf96() % t - t / 2 + c.g), fix(xorshf96() % t - t / 2 + c.b));
}

namespace fractal {

	class NoiseGenerator {
	public:
		static std::vector<std::vector<sf::Color>> generate(int width, int height);
	private:
		static void generateSquare(int x0, int y0, int x1, int y1, std::vector<std::vector<sf::Color>>& matrix);
		static sf::Color avgColor(const sf::Color& fst, const sf::Color& sec);
		static sf::Color randColor(int t = 255);
	};

	std::vector<std::vector<sf::Color>> NoiseGenerator::generate(int width, int height) {
		std::uniform_int_distribution<int> unifx(0, 30);
		std::random_device rand_dev;
		std::mt19937 rand_engine(rand_dev());
		for (int i = 0; i < unifx(rand_engine); ++i) {
			xorshf96();
		}
		auto matrix = std::vector<std::vector<sf::Color>>(height, std::vector<sf::Color>(width, BLACK));
		generateSquare(0, 0, height - 1, width - 1, matrix);
		return matrix;
	}

	void NoiseGenerator::generateSquare(int x0, int y0, int x1, int y1, std::vector<std::vector<sf::Color>>& matrix) {
		if (x1 - x0 < 2 && y1 - y0 < 2)
			return;
		if (matrix[x0][y0] == BLACK) {
			matrix[x0][y0] = randColor();
		}
		if (matrix[x1][y0] == BLACK) {
			matrix[x1][y0] = randColor();
		}
		if (matrix[x0][y1] == BLACK) {
			matrix[x0][y1] = randColor();
		}
		if (matrix[x1][y1] == BLACK) {
			matrix[x1][y1] = randColor();
		}
		if (matrix[(x0 + x1) / 2][y0] == BLACK) {
			matrix[(x0 + x1) / 2][y0] = avgColor(matrix[x0][y0], matrix[x1][y0]);
		}
		if (matrix[(x0 + x1) / 2][y1] == BLACK) {
			matrix[(x0 + x1) / 2][y1] = avgColor(matrix[x0][y1], matrix[x1][y1]);
		}
		if (matrix[x0][(y0 + y1) / 2] == BLACK) {
			matrix[x0][(y0 + y1) / 2] = avgColor(matrix[x0][y0], matrix[x0][y1]);
		}
		if (matrix[x1][(y0 + y1) / 2] == BLACK) {
			matrix[x1][(y0 + y1) / 2] = avgColor(matrix[x1][y0], matrix[x1][y1]);
		}
		if (matrix[(x0 + x1) / 2][(y0 + y1) / 2] == BLACK) {
			addRandColor(matrix[(x0 + x1) / 2][(y0 + y1) / 2] = avgColor(avgColor(matrix[x0][y0], matrix[x0][y1]), avgColor(matrix[x1][y0], matrix[x1][y1])), 100);
		}
		generateSquare((x0 + x1) / 2, (y0 + y1) / 2, x1, y1, matrix);
		generateSquare(x0, (y0 + y1) / 2, (x0 + x1) / 2, y1, matrix);
		generateSquare((x0 + x1) / 2, y0, x1, (y0 + y1) / 2, matrix);
		generateSquare(x0, y0, (x0 + x1) / 2, (y0 + y1) / 2, matrix);
	}

	sf::Color NoiseGenerator::avgColor(const sf::Color& fst, const sf::Color& sec) {
		return sf::Color(((int)fst.r + sec.r) / 2, ((int)fst.g + sec.g) / 2, ((int)fst.b + sec.b) / 2);
	}

	sf::Color NoiseGenerator::randColor(int t) {
		t *= t/2;
		int offset = (255 - t) / 2;
		return sf::Color(xorshf96() % t + offset, xorshf96() % t + offset, xorshf96() % t + offset);
	}
}