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
    BaseShape<CircleShape> _currShape;
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

#endif //SHAPEVIEWER_WINDOW_H