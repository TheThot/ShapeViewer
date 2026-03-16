//
// Created by Admin on 16.03.2026.
//
#ifndef SHAPEVIEWER_WINDOW_H
#define SHAPEVIEWER_WINDOW_H

#include "BaseShape.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class MyWindow {
private:
    RenderWindow _window;
    Color _background;

public:
    explicit MyWindow(unsigned width = 300, unsigned height = 300,
        const std::string& title = "Viewer", sf::Color color = sf::Color::Black);

    ~MyWindow();

    MyWindow(const MyWindow&) = delete;
    MyWindow& operator=(const MyWindow&) = delete;

    MyWindow(MyWindow&& other) noexcept
        : _window(std::move(other._window))
        , _background(other._background) {}

    MyWindow& operator=(MyWindow&& other) noexcept {
        if (this != &other) {
            _window = std::move(other._window);
            _background = other._background;
        }
        return *this;
    }


    bool isOpen() const;
    auto pollEvent();
    void clear();
    void display();
    RenderWindow& getWindow();
    template<typename T>
    void draw(const T& shape);

};

class MyApplication
{
    BaseShape<CircleShape, RenderWindow> _currShape;

    ShapeManager<RenderWindow>           _worker;

public:

    MyWindow _myWindow;
    MyApplication();
    ~MyApplication() = default;

    void _init();
    void run();

private:

    void _handleEvent(const Event& event);
    void _render();
};

class ShapeFactory {
public:
    static auto createCircle(float radius, sf::Color color, sf::Vector2f pos) {
        auto circle = CircleShape(radius);
        circle.setFillColor(color);
        circle.setPosition(pos);
        return circle;
    }

    static auto createRectangle(sf::Vector2f size, sf::Color color, sf::Vector2f pos) {
        auto rect = RectangleShape(size);
        rect.setFillColor(color);
        rect.setPosition(pos);
        return rect;
    }

    static auto createTriangle(float side, sf::Color color, sf::Vector2f pos) {
        auto triangle = ConvexShape();
        triangle.setPointCount(3);
        triangle.setPoint(0, sf::Vector2f(0, 0));
        triangle.setPoint(1, sf::Vector2f(side, 0));
        triangle.setPoint(2, sf::Vector2f(side/2, side));
        triangle.setFillColor(color);
        triangle.setPosition(pos);
        return triangle;
    }
};

#endif //SHAPEVIEWER_WINDOW_H