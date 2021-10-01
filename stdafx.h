#pragma once

#include <iostream>
#include <ios>
#include <iomanip>
#include <vector>
#include <functional>
#include <map>
#include <random>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

const double PI = 3.1415926535;

unsigned long xorshf96() {
    static unsigned long xx = 123456789, yy = 362436069, zz = 521288629;
    unsigned long t;
    xx ^= xx << 16;
    xx ^= xx >> 5;
    xx ^= xx << 1;

    t = xx;
    xx = yy;
    yy = zz;
    zz = t ^ xx ^ yy;

    return zz;
}

#include "Complex.h"
#include "fractals/Figures.h"

#include "fractals/geometric/IGeometricFractal.h"
#include "fractals/geometric/KochFractals.h"
#include "fractals/geometric/SierpinskiCarpet.h"

#include "fractals/algebraic/IAlebraicFractal.h"
#include "fractals/algebraic/FlamingShip.h"
#include "fractals/algebraic/JuliaSet.h"
#include "fractals/algebraic/MandelbrotSet.h"

#include "Display.h"
