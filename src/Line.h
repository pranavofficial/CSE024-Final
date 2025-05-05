#ifndef LINE_H
#define LINE_H

#include "Shape.h"

class Line : public Shape {
    float x2;
    float y2;
    float thickness;
    
public:
    Line(float x1, float y1, float x2, float y2, const Color& color, float thickness = 2.0f);
    ~Line() override = default;
    
    // Override Shape methods
    void draw() const override;
    bool contains(float px, float py) const override;
    void move(float dx, float dy) override;
    void resize(float factor) override;
    
    // Getters and setters
    float getX2() const;
    float getY2() const;
    float getThickness() const;
    void setX2(float x2);
    void setY2(float y2);
    void setThickness(float thickness);
    
    // Get length
    float getLength() const;
};

#endif // LINE_H 