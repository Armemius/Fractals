#include "stdafx.h"

#include <SFML/Graphics.hpp>

int main()
{
    fractal::KochSnowflake kcf(700);
    fractal::KochCurve kcv(700);
    fractal::SierpinskiCarpet srpc(700);
    int type = 0;
    double shiftX = 0, shiftY = 0;
    double scale = 100.0;
    int iterations = 0;
    const int horizontalPx = 1440;
    const int verticalPx = 900;
    sf::RenderWindow window(sf::VideoMode(horizontalPx, verticalPx), "Fractals", sf::Style::Fullscreen);
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
            // Key input handler
            if (event.type == sf::Event::KeyPressed) {
                if (event.key.code == sf::Keyboard::Q && scale < 1600) {
                    scale *= 2;
                    shiftX *= 2;
                    shiftY *= 2;
                }
                if (event.key.code == sf::Keyboard::E && scale > 12.5) {
                    scale /= 2;
                    shiftX /= 2;
                    shiftY /= 2;
                }
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code == sf::Keyboard::A)
                    shiftX += 25 * 100.0 / scale;
                if (event.key.code == sf::Keyboard::D)
                    shiftX -= 25 * 100.0 / scale;
                if (event.key.code == sf::Keyboard::W)
                    shiftY += 25 * 100.0 / scale;
                if (event.key.code == sf::Keyboard::S)
                    shiftY -= 25 * 100.0 / scale;
                if (event.key.code == sf::Keyboard::I)
                    type = 0;
                if (event.key.code == sf::Keyboard::O)
                    type = 1;
                if (event.key.code == sf::Keyboard::P)
                    type = 2;
                if (event.key.code == sf::Keyboard::K) {
                    kcf = fractal::KochSnowflake(700);
                    kcv = fractal::KochCurve(700);
                    srpc = fractal::SierpinskiCarpet(700);
                    if (iterations > 0)
                        --iterations;
                    kcf.generate(iterations);
                    kcv.generate(iterations);
                    srpc.generate(iterations);
                }
                else if (event.key.code == sf::Keyboard::L) {
                    kcf = fractal::KochSnowflake(700);
                    kcv = fractal::KochCurve(700);
                    srpc = fractal::SierpinskiCarpet(700);
                    if (iterations < 7)
                        ++iterations;
                    kcf.generate(iterations);
                    kcv.generate(iterations);
                    srpc.generate(iterations);
                }
                if (event.key.code == sf::Keyboard::Space) {
                    scale = 100.0;
                    shiftX = 0;
                    shiftY = 0;
                }
            }
        }

        window.clear(sf::Color(15, 15, 15));
        // Zero/zero point relative to window
        double zeroX = horizontalPx / 2 + shiftX * scale / 100.0,
            zeroY = verticalPx / 2 + shiftY * scale / 100.0;
        const int fieldSize = 200 * scale / 100;
        if (type == 0) {
            for (auto i : kcf.lines()) {
                sf::VertexArray line(sf::LinesStrip, 2);
                line[0].color = sf::Color::White;
                line[1].color = sf::Color::White;
                line[0].position = sf::Vector2f(zeroX + i.pos.x * scale / 100, zeroY + i.pos.y * scale / 100);
                line[1].position = sf::Vector2f(zeroX + i.getSecPos().x * scale / 100, zeroY + i.getSecPos().y * scale / 100);
                window.draw(line);
            }
        } else if (type == 1) {
            for (auto i : kcv.lines()) {
                sf::VertexArray line(sf::LinesStrip, 2);
                line[0].color = sf::Color::White;
                line[1].color = sf::Color::White;
                line[0].position = sf::Vector2f(zeroX + i.pos.x * scale / 100, zeroY + i.pos.y * scale / 100);
                line[1].position = sf::Vector2f(zeroX + i.getSecPos().x * scale / 100, zeroY + i.getSecPos().y * scale / 100);
                window.draw(line);
            }
        } else if (type == 2) {
            for (auto i : srpc.squares()) {
                sf::RectangleShape squareSFML;
                squareSFML.setFillColor(sf::Color::White);
                squareSFML.setOutlineThickness(0);
                squareSFML.setPosition(zeroX + i.center.x * scale / 100 - i.diam * scale / 200, zeroY + i.center.y * scale / 100 - i.diam * scale / 200);
                squareSFML.setSize(sf::Vector2f(i.diam * scale / 100, i.diam * scale / 100));
                window.draw(squareSFML);
            }
        }
        window.display();
    }
    return 0;
}