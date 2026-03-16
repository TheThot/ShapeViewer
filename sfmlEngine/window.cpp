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

}

MyApplication::MyApplication()
    : _myWindow(800, 600, "Viewer", Color(50, 50, 50))
{
    _init();
}

void MyApplication::_init()
{

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
    //shapeManager.drawAll(window);
    _myWindow.display();
}