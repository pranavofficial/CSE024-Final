#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class Triangle : public Shape {
    float width;
    float height;
    
public:
    Triangle(float x, float y, float width, float height, const Color& color);
    ~Triangle() override = default;
    
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

#endif // TRIANGLE_H 