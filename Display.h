#pragma once
#include "stdafx.h"
#include <SFML/Graphics.hpp>

namespace fractal {
    class Button_ {
    public:
        Button_(std::string name_, int* active_, int* type_, int x_, int y_, int width_, int height_, int butActive_, int butType_);
        std::string name = "None";
        int* active;
        int* type;
        int x, y;
        int width, height;
        int butActive, butType;
        void click();
    private:
        std::function<void(int*, int*, int, int)> func;
    };

    class Display {
    public:
        Display();
        ~Display();
        void run();
    private:
        std::vector<IGeometricFractal*> geometricFractals;
        std::vector<IAlgebraicFractal*> algebraicFractals;
        double shiftX_ = 0, shiftY_ = 0;
        double scale_ = 100.0;
        int iterations_ = 0;
        int active_ = 0, type_ = 0;
        bool isMenuOpen_ = true, doVSync_ = true;
        const int horizontalPx = sf::VideoMode::getDesktopMode().width;
        const int verticalPx = sf::VideoMode::getDesktopMode().height;
        sf::Font font_;
        std::vector<std::vector<Button_>> buttons_;
    };
    // Constructors & destructors
    Display::Display() {
        int height = sf::VideoMode::getDesktopMode().height;
        geometricFractals.push_back(new SierpinskiCarpet(height));
        geometricFractals.push_back(new KochCurve(height));
        geometricFractals.push_back(new KochSnowflake(height));

        algebraicFractals.push_back(new MandelbrotSet());
        for (IGeometricFractal* frac : geometricFractals) {
            frac->generate(0);
        }
        font_.loadFromFile("OpenSans.ttf");
        std::vector<Button_> geometricButtons;
        std::vector<Button_> algebraicButtons;
        std::vector<Button_> stochasticButtons;
        geometricButtons.push_back(Button_("Sierpinski carpet", &active_, &type_, horizontalPx / 6 - 150, 180, 300, 100, 0, 0));
        geometricButtons.push_back(Button_("Koch curve", &active_, &type_, horizontalPx / 6 - 150, 300, 300, 80, 0, 1));
        geometricButtons.push_back(Button_("Koch snowflake", &active_, &type_, horizontalPx / 6 - 150, 420, 300, 100, 0, 2));
        buttons_.push_back(geometricButtons);

        algebraicButtons.push_back(Button_("Gavno mo4a", &active_, &type_, horizontalPx / 6 + horizontalPx / 3 - 150, 180, 300, 100, 1, 0));
        algebraicButtons.push_back(Button_("Gavno mo4a", &active_, &type_, horizontalPx / 6 + horizontalPx / 3 - 150, 300, 300, 100, 1, 1));
        algebraicButtons.push_back(Button_("Gavno mo4a", &active_, &type_, horizontalPx / 6 + horizontalPx / 3 - 150, 420, 300, 100, 1, 2));
        buttons_.push_back(algebraicButtons);
        buttons_.push_back(stochasticButtons);
    }

    Display::~Display() {
        for (IGeometricFractal* frac : geometricFractals) {
            delete frac;
        }
    }

    // Functions
    void Display::run() {
        sf::RenderWindow window(sf::VideoMode(horizontalPx, verticalPx), "Fractals", sf::Style::Fullscreen);
        window.setVerticalSyncEnabled(doVSync_);
        sf::Clock clock;
        while (window.isOpen()) {
            sf::Time elapsed = clock.restart();
            // Mouse click handler
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                for (int i = 0; i < buttons_.size(); ++i) {
                    for (int j = 0; j < buttons_.at(i).size(); ++j) {
                        if (pos.x >= buttons_.at(i).at(j).x && pos.x <= buttons_.at(i).at(j).x + buttons_.at(i).at(j).width) {
                            if (pos.y >= buttons_.at(i).at(j).y && pos.y <= buttons_.at(i).at(j).y + buttons_.at(i).at(j).height) {
                                buttons_.at(i).at(j).click();
                                if (i == 0)
                                    geometricFractals.at(j)->generate(iterations_);
                            }
                        }
                    }
                }
            }
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    window.close(); 
                if (event.type == sf::Event::MouseWheelScrolled && !isMenuOpen_)
                {
                    if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel) {
                        if (event.mouseWheelScroll.delta == 1) {
                            scale_ *= 1.2;
                        } else if (event.mouseWheelScroll.delta == -1) {
                            scale_ /= 1.2;
                        }
                    }
                }
                // Key input handler
                if (event.type == sf::Event::KeyPressed) {
                    if (event.key.code == sf::Keyboard::Escape) {
                        if (!isMenuOpen_)
                            window.close();
                        else
                            isMenuOpen_ = false;
                    }
                    if (event.key.code == sf::Keyboard::M)
                        isMenuOpen_ = !isMenuOpen_;
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
            // Geometric fractals display
            if (active_ == 0) {
                if (geometricFractals.at(type_)->lines() != NULL) {
                    for (Line i : *geometricFractals.at(type_)->lines()) {
                        sf::VertexArray line(sf::LinesStrip, 2);
                        line[0].color = sf::Color::White;
                        line[1].color = sf::Color::White;
                        line[0].position = sf::Vector2f(zeroX + i.pos.x * scale_ / 100, zeroY + i.pos.y * scale_ / 100);
                        line[1].position = sf::Vector2f(zeroX + i.getSecPos().x * scale_ / 100, zeroY + i.getSecPos().y * scale_ / 100);
                        window.draw(line);
                    }
                }
                if (geometricFractals.at(type_)->squares() != NULL) {
                    for (Square i : *geometricFractals.at(type_)->squares()) {
                        sf::RectangleShape squareSFML;
                        squareSFML.setFillColor(sf::Color::White);
                        squareSFML.setOutlineThickness(0);
                        squareSFML.setPosition(zeroX + i.center.x * scale_ / 100 - i.diam * scale_ / 200, zeroY + i.center.y * scale_ / 100 - i.diam * scale_ / 200);
                        squareSFML.setSize(sf::Vector2f(i.diam * scale_ / 100, i.diam * scale_ / 100));
                        window.draw(squareSFML);
                    }
                }
            // Algebraic fractals display
            } else if (active_ == 1) {
                for (int i = 0; i < horizontalPx; ++i) {
                    for (int j = 0; j < verticalPx; ++j) {
                        sf::VertexArray point(sf::LinesStrip, 2);
                        point[0].position = sf::Vector2f(i, j);
                        point[1].position = sf::Vector2f(i, j);
                        sf::Color color = algebraicFractals.at(0)->getPixelColor(cmpx::Complex<double>(i, j));
                        point[]
                    }
                }
            // Stochactic fractals display
            } else {

            }

            // Menu display
            if (isMenuOpen_) {
                sf::RectangleShape menuBG;
                menuBG.setPosition(sf::Vector2f(0, 0));
                menuBG.setFillColor(sf::Color(31, 30, 28, 200));
                menuBG.setSize(sf::Vector2f(horizontalPx, verticalPx));
                menuBG.setOutlineThickness(0);
                window.draw(menuBG);

                sf::Text header;
                header.setFont(font_);
                header.setString("Fractals viewer");
                header.setCharacterSize(50);
                header.setPosition(sf::Vector2f(horizontalPx / 2, 50));
                sf::FloatRect headerRect = header.getLocalBounds();
                header.setOrigin(sf::Vector2f(headerRect.left + headerRect.width / 2.0,
                    headerRect.top + headerRect.height / 2.0));
                window.draw(header);

                std::vector<std::string> names{"Geometric", "Algebraic", "Stochastic"};
                for (int i = 0; i < 3; i++) {
                    sf::Text headerFractal;
                    headerFractal.setFont(font_);
                    headerFractal.setString(names.at(i));
                    headerFractal.setCharacterSize(30);
                    double horizontalPos = horizontalPx / 3 * i + horizontalPx / 6;
                    headerFractal.setPosition(sf::Vector2f(horizontalPos, 130));
                    sf::FloatRect geometricRect = headerFractal.getLocalBounds();
                    headerFractal.setOrigin(sf::Vector2f(geometricRect.left + geometricRect.width / 2.0,
                        geometricRect.top + geometricRect.height / 2.0));
                    window.draw(headerFractal);

                    for (int j = 0; j < this->buttons_.at(i).size(); j++) {
                        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
                        sf::RectangleShape button;
                        button.setPosition(sf::Vector2f(horizontalPos - 150, 180 + 120 * j));
                        sf::Color butColor = (active_ == i && type_ == j ? sf::Color(74, 58, 139, 135) : sf::Color(29, 27, 46, 135));
                        sf::Event event1;
                        
                        sf::FloatRect butRect = button.getLocalBounds();
                        button.setSize(sf::Vector2f(300, 80));
                        button.setOutlineThickness(2);
                        button.setOutlineColor(sf::Color(200, 220, 200));
                        button.setFillColor(butColor);
                        window.draw(button);

                        sf::Text buttonLabel;
                        buttonLabel.setFont(font_);
                        buttonLabel.setString(buttons_.at(i).at(j).name);
                        buttonLabel.setPosition(sf::Vector2f(horizontalPos, 220 + 120 * j));
                        sf::FloatRect buttonRect = buttonLabel.getLocalBounds();
                        buttonLabel.setOrigin(sf::Vector2f(buttonRect.left + buttonRect.width / 2.0,
                            buttonRect.top + buttonRect.height / 2.0));
                        buttonLabel.setCharacterSize(30);
                        window.draw(buttonLabel);
                    }
                }
            }
            // Movement handler
            if (!isMenuOpen_) {
                int renderTime = elapsed.asMilliseconds();
                sf::Vector2i pos = sf::Mouse::getPosition(window);
                if (pos.x < 100) {
                    shiftX_ += 100.0 / scale_ * renderTime;
                }
                if (pos.x > horizontalPx - 100) {
                    shiftX_ -= 100.0 / scale_ * renderTime;
                }
                if (pos.y < 100) {
                    shiftY_ += 100.0 / scale_ * renderTime;
                }
                if (pos.y > verticalPx - 100) {
                    shiftY_ -= 100.0 / scale_ * renderTime;
                }
            }
            window.display();
        }
    }
    
    // Button
    Button_::Button_(std::string name_, int* active_, int* type_, int x_, int y_, int width_, int height_, int butActive_, int butType_) :
        name(name_),
        active(active_),
        type(type_), 
        x(x_), 
        y(y_),
        width(width_), 
        height(height_), 
        butActive(butActive_), 
        butType(butType_) {
        func = [](int* active, int* type, int setActive, int setType) {*active = setActive; *type = setType; };
    }

    void Button_::click() {
        this->func(active, type, butActive, butType);
    }
}
