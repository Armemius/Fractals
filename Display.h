#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>

namespace fractal {
	class Display {
	public:
        Display();
        ~Display();
		void run();
	private:
        std::vector<IGeometricFractal*> geometricFractals;
        double shiftX_ = 0, shiftY_ = 0;
        double scale_ = 100.0;
        int iterations_ = 0;
        int type_ = 0;
	};
    // Constructors & destructors
    Display::Display() {
        int height = sf::VideoMode::getDesktopMode().height;
        geometricFractals.push_back(new SierpinskiCarpet(height));
        geometricFractals.push_back(new KochCurve(height));
        geometricFractals.push_back(new KochSnowflake(height));
        for (IGeometricFractal* frac : geometricFractals) {
            frac->generate(0);
        }
    }

    Display::~Display() {
        for (IGeometricFractal* frac : geometricFractals) {
            delete frac;
        }
    }

    // Functions
	void Display::run() {
        const int horizontalPx = sf::VideoMode::getDesktopMode().width;
        const int verticalPx = sf::VideoMode::getDesktopMode().height;
        sf::RenderWindow window(sf::VideoMode(horizontalPx, verticalPx), "Fractals", sf::Style::Fullscreen);
        while (window.isOpen()) {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close();
                // Key input handler
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Q && scale_ < 1600) {
                        scale_ *= 2;
                        shiftX_ *= horizontalPx * 1. / verticalPx;
                        shiftY_ *= horizontalPx * 1. / verticalPx;
                    }
                    if (event.key.code == sf::Keyboard::E && scale_ > 12.5) {
                        scale_ /= 2;
                        shiftX_ /= horizontalPx * 1. / verticalPx;
                        shiftY_ /= horizontalPx * 1. / verticalPx;
                    }
                    if (event.key.code == sf::Keyboard::Escape)
                        window.close();
                    if (event.key.code == sf::Keyboard::A)
                        shiftX_ += 25 * 100.0 / scale_;
                    if (event.key.code == sf::Keyboard::D)
                        shiftX_ -= 25 * 100.0 / scale_;
                    if (event.key.code == sf::Keyboard::W)
                        shiftY_ += 25 * 100.0 / scale_;
                    if (event.key.code == sf::Keyboard::S)
                        shiftY_ -= 25 * 100.0 / scale_;
                    if (event.key.code == sf::Keyboard::I)
                        type_ = 0;
                    if (event.key.code == sf::Keyboard::O)
                        type_ = 1;
                    if (event.key.code == sf::Keyboard::P)
                        type_ = 2;
                    if (event.key.code == sf::Keyboard::K) {
                        if (iterations_ > 0)
                            --iterations_;
                        geometricFractals.at(type_)->generate(iterations_);
                    }
                    else if (event.key.code == sf::Keyboard::L) {
                        if (iterations_ < 8)
                            ++iterations_;
                        geometricFractals.at(type_)->generate(iterations_);
                    }
                    if (event.key.code == sf::Keyboard::Space) {
                        scale_ = 100.0;
                        shiftX_ = 0;
                        shiftY_ = 0;
                    }
                }
            }

            window.clear(sf::Color(15, 15, 15));
            // Zero/zero point relative to window
            double zeroX = horizontalPx / 2 + shiftX_ * scale_ / 100.0,
                zeroY = verticalPx / 2 + shiftY_ * scale_ / 100.0;
            const int fieldSize = 200 * scale_ / 100;
            // Geometric fractals
            if (geometricFractals.at(type_)->lines() != NULL) {
                for (auto i : *geometricFractals.at(type_)->lines()) {
                    sf::VertexArray line(sf::LinesStrip, 2);
                    line[0].color = sf::Color::White;
                    line[1].color = sf::Color::White;
                    line[0].position = sf::Vector2f(zeroX + i.pos.x * scale_ / 100, zeroY + i.pos.y * scale_ / 100);
                    line[1].position = sf::Vector2f(zeroX + i.getSecPos().x * scale_ / 100, zeroY + i.getSecPos().y * scale_ / 100);
                    window.draw(line);
                }
            }
            if (geometricFractals.at(type_)->squares() != NULL) {
                for (auto i : *geometricFractals.at(type_)->squares()) {
                    sf::RectangleShape squareSFML;
                    squareSFML.setFillColor(sf::Color::White);
                    squareSFML.setOutlineThickness(0);
                    squareSFML.setPosition(zeroX + i.center.x * scale_ / 100 - i.diam * scale_ / 200, zeroY + i.center.y * scale_ / 100 - i.diam * scale_ / 200);
                    squareSFML.setSize(sf::Vector2f(i.diam * scale_ / 100, i.diam * scale_ / 100));
                    window.draw(squareSFML);
                }
            }

            window.display();
        }
	}
}