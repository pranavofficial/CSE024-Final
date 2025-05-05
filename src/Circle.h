#ifndef CIRCLE_H
#define CIRCLE_H

#include "Shape.h"

class Circle : public Shape {
    float radius;
    
public:
    Circle(float x, float y, float radius, const Color& color);
    ~Circle() override = default;
    
    // Override Shape methods
    void draw() const override;
    bool contains(float px, float py) const override;
    void resize(float factor) override;
    
    // Getters and setters
    float getRadius() const;
    void setRadius(float radius);
};

#endif // CIRCLE_H 