//
// Created by Admin on 16.03.2026.
//
#include "window.h"
#include <iostream>

MyWindow::MyWindow(unsigned width, unsigned height,
        const std::string& title, sf::Color color)
        : _window(sf::VideoMode({width, height}), title)
        , _background(color)
{
    _window.setFramerateLimit(60);
}

// RAII interface
MyWindow::~MyWindow()
{
    if (_window.isOpen()) {
        _window.close();
    }
}

auto MyWindow::pollEvent() {
    return _window.pollEvent();
}

void MyWindow::clear() {
    _window.clear(_background);
}

void MyWindow::display() {
    _window.display();
}

RenderWindow& MyWindow::getWindow() {
    return _window;
}

bool MyWindow::isOpen() const
{
    return _window.isOpen();
}

// рисование объектов разных форм
template<typename T>
void MyWindow::draw(const T& shape)
{
    _window.draw(*shape.getShape());
}

MyApplication::MyApplication()
    : _myWindow(800, 600, "Viewer", Color(50, 50, 50))
{
    _init();
}

// наполнение примитивами
void MyApplication::_init()
{
    auto shp1 = std::make_unique<BaseShape<CircleShape, RenderWindow>>(
        std::make_unique<CircleShape>(ShapeFactory::createCircle(80, Color::Blue, Vector2f{300, 250}))
    );
    auto shp2 = std::make_unique<BaseShape<RectangleShape, RenderWindow>>(
        std::make_unique<RectangleShape>(ShapeFactory::createRectangle(Vector2f{90, 90}, Color::Green, Vector2f{100, 250}))
        );
    auto shp3 = std::make_unique<BaseShape<ConvexShape, RenderWindow>>(
        std::make_unique<ConvexShape>(ShapeFactory::createTriangle(95, Color::Red, Vector2f{500, 250}))
    );
    _worker.emplace_back(std::move(shp1));
    _worker.emplace_back(std::move(shp2));
    _worker.emplace_back(std::move(shp3));
}

void MyApplication::run()
{
    std::cout << "[run]\n";

    while (_myWindow.isOpen()) {
        std::optional<Event> event;
        while ( ( event = _myWindow.pollEvent() ) != std::nullopt) {
            _handleEvent(event.value());
        }
        _render();
    }

    std::cout << "[finish]\n";
}

void MyApplication::_handleEvent(const Event& event)
{
    if (event.is<Event::Closed>()) {
        std::cout << "[close]\n";
        _myWindow.getWindow().close();
    }
}

void MyApplication::_render() {
    _myWindow.clear();
    // передаю менеджеру задание нарисовать пул shapes
    _worker.drawAll(_myWindow.getWindow());
    _myWindow.display();
}