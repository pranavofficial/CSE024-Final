#include "Point.h"

Point::Point() : x(0.0f), y(0.0f) {
}

Point::Point(float x, float y) : x(x), y(y) {
}

float Point::getX() const {
    return x;
}

float Point::getY() const {
    return y;
}

void Point::setX(float newX) {
    x = newX;
}

void Point::setY(float newY) {
    y = newY;
}

void Point::move(float dx, float dy) {
    x += dx;
    y += dy;
} 