//
// Created by Admin on 16.03.2026.
//

#ifndef SHAPEVIEWER_BASESHAPE_H
#define SHAPEVIEWER_BASESHAPE_H

#include <memory>

template<typename shape>
class BaseShape
{
protected:
    std::unique_ptr<shape> _shape;

public:
    BaseShape() = default;
    virtual ~BaseShape() = default;

    BaseShape(const BaseShape&) = delete;
    BaseShape& operator=(const BaseShape&) = delete;
    BaseShape(BaseShape&&) = default;
    BaseShape& operator=(BaseShape&&) = default;

    virtual void setShape(std::unique_ptr<shape> shape)
    {
        _shape = std::move(shape);
    }
    virtual const std::unique_ptr<shape>& getShape() const
    {
        return _shape;
    }
};
#endif //SHAPEVIEWER_BASESHAPE_H