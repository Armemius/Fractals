#pragma once

#include <iostream>
#include <ios>
#include <iomanip>
#include <vector>
#include <set>

const double PI = 3.1415926535;

enum fractalTypes {
    GEOMETRIC = 0,
    ALGEBRAIC = 1,
    STOCHASTIC = 2
};

#include "Complex.h"
#include "fractals/Figures.h"
#include "fractals/geometric/IGeometricFractal.h"
#include "fractals/geometric/KochFractals.h"
#include "fractals/geometric/SierpinskiCarpet.h"
#include "Display.h"
