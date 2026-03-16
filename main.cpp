//
// Created by Admin on 16.03.2026.
//
#include <iostream>
#include "window.h"

int main()
{
    try {

        MyApplication app;
        app.run();

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}