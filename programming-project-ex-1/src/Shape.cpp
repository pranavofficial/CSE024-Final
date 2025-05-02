#include "Shape.h"

Shape::Shape(float x, float y, const Color& color) 
    : x(x), y(y), color(color), selected(false) {
}

void Shape::move(float dx, float dy) {
    x += dx;
    y += dy;
}

void Shape::setColor(const Color& newColor) {
    color = newColor;
}

bool Shape::isSelected() const {
    return selected;
}

void Shape::setSelected(bool isSelected) {
    selected = isSelected;
}

float Shape::getX() const {
    return x;
}

float Shape::getY() const {
    return y;
}

Color Shape::getColor() const {
    return color;
} 