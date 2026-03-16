//
// Created by Admin on 16.03.2026.
//

#ifndef SHAPEVIEWER_BASESHAPE_H
#define SHAPEVIEWER_BASESHAPE_H

#include <memory>
#include <vector>
/*
 * предостовляет интерфейс отрисовки viewer
 */
template<typename viewer>
class ShapeInterface {
public:
    virtual ~ShapeInterface() = default;
    virtual void draw(viewer& window) = 0;
};

template<typename shape, typename viewer>
class BaseShape : public ShapeInterface<viewer>
{
protected:
    std::unique_ptr<shape> _shape;

public:
    BaseShape() = default;
    BaseShape(std::unique_ptr<shape> inShape) : _shape(std::move(inShape)) {}
    virtual ~BaseShape() = default;

    BaseShape(const BaseShape&) = delete;
    BaseShape& operator=(const BaseShape&) = delete;
    BaseShape(BaseShape&&) = default;
    BaseShape& operator=(BaseShape&&) = default;

    virtual void setShape(std::unique_ptr<shape> inShape)
    {
        _shape = std::move(inShape);
    }
    virtual const std::unique_ptr<shape>& getShape() const
    {
        return _shape;
    }
private:
    void draw(viewer& handler)
    {
        if (_shape) {
            handler.draw(*_shape);
        }
    }
};

/*
 * хранит данные о фигуре _listShapes
 * функция сохранения emplace_back данных
 * вывод всех фигур на экран drawAll
 */
template <typename viewer>
class ShapeManager
{
    using interface = ShapeInterface<viewer>;
    std::vector<std::unique_ptr<interface>> _listShapes;

public:
    ShapeManager() = default;
    virtual ~ShapeManager() = default;

    template<typename T>
    void emplace_back(std::unique_ptr<T> shape)
    {
        _listShapes.push_back(std::move(shape));
    }

    void drawAll(viewer& handler) const{
        for (auto& shape : _listShapes) {
            shape->draw(handler);
        }
    }
};
#endif //SHAPEVIEWER_BASESHAPE_H