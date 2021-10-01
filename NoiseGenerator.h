#pragma once
#include "stdafx.h"

namespace fractal {
	class NoiseGenerator {
	public:
		static std::vector<std::vector<int>> generate(int width, int height);
	};

	std::vector<std::vector<int>> NoiseGenerator::generate(int width, int height) {
		std::vector<std::vector<int>> matrix;
		width += 2;
		height += 2;
		for (int i = 0; i < width; i++) {
			matrix.push_back(std::vector<int>());
			for (int j = 0; j < height; j++) {
				if (i > 0 && j > 0) {
					matrix[i].push_back((xorshf96() % 255 + matrix[i - 1][j] + matrix[i][j - 1]) / 3);
				} else {
					matrix[i].push_back(xorshf96() % 255);
				}
			}
		}

		for (int it = 0; it < 15; ++it) {
			for (int i = 0; i < width; i++) {
				matrix.push_back(std::vector<int>());
				for (int j = 0; j < height; j++) {
					if (i > 0 && j > 0 && i < width - 1 && j < height - 1) {
						matrix[i][j] = (matrix[i + 1][j] + matrix[i - 1][j] + matrix[i][j + 1] + matrix[i][j - 1]) / 4;
					}
				}
			}
		}
		

		return matrix;
	}
}