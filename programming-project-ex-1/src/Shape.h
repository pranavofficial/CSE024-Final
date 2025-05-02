#ifndef SHAPE_H
#define SHAPE_H

#include <vector>
#include "Color.h"

class Shape {
protected:
    float x;
    float y;
    Color color;
    bool selected;
    
public:
    Shape(float x, float y, const Color& color);
    virtual ~Shape() = default;
    
    // Required methods for all shapes
    virtual void draw() const = 0;
    virtual bool contains(float px, float py) const = 0;
    virtual void move(float dx, float dy);
    virtual void resize(float factor) = 0;
    virtual void setColor(const Color& color);
    
    // Selection methods
    bool isSelected() const;
    void setSelected(bool selected);
    
    // Position getters
    float getX() const;
    float getY() const;
    Color getColor() const;
};

#endif // SHAPE_H 