#ifndef POINT_H
#define POINT_H

class Point {
    float x;
    float y;

public:
    Point();
    Point(float x, float y);
    
    float getX() const;
    float getY() const;
    
    void setX(float x);
    void setY(float y);
    
    void move(float dx, float dy);
};

#endif // POINT_H 