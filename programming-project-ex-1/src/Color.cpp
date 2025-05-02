#include "Color.h"

Color::Color() : r(0.0f), g(0.0f), b(0.0f) {
}

Color::Color(float r, float g, float b) : r(r), g(g), b(b) {
}

float Color::getR() const {
    return r;
}

float Color::getG() const {
    return g;
}

float Color::getB() const {
    return b;
}

void Color::setR(float newR) {
    r = newR;
}

void Color::setG(float newG) {
    g = newG;
}

void Color::setB(float newB) {
    b = newB;
}

void Color::set(float newR, float newG, float newB) {
    r = newR;
    g = newG;
    b = newB;
} 