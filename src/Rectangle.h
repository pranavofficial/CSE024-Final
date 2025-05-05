#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "Shape.h"

class Rectangle : public Shape {
    float width;
    float height;

public:
    Rectangle(float x, float y, float width, float height, const Color& color);
    ~Rectangle() override = default;
    
    // Override Shape methods
    void draw() const override;
    bool contains(float px, float py) const override;
    void resize(float factor) override;
    
    // Getters and setters
    float getWidth() const;
    float getHeight() const;
    void setWidth(float width);
    void setHeight(float height);
};

#endif // RECTANGLE_H 