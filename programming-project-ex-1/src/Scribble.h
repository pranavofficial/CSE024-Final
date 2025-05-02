#ifndef SCRIBBLE_H
#define SCRIBBLE_H

#include <vector>
#include "Shape.h"
#include "Point.h"

class Scribble : public Shape {
    std::vector<Point> points;
    int strokeSize;

public:
    Scribble(float startX, float startY, const Color& color, int strokeSize = 3);
    ~Scribble() override = default;
    
    // Add a point to the scribble
    void addPoint(float x, float y);
    
    // Override Shape methods
    void draw() const override;
    bool contains(float px, float py) const override;
    void move(float dx, float dy) override;
    void resize(float factor) override;
    
    // Get stroke size
    int getStrokeSize() const;
    void setStrokeSize(int size);
};

#endif // SCRIBBLE_H 