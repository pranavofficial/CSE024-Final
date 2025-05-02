#include "Rectangle.h"
#include <GL/freeglut.h>

Rectangle::Rectangle(float x, float y, float width, float height, const Color& color)
    : Shape(x, y, color), width(width), height(height) {
}

void Rectangle::draw() const {
    // Draw the rectangle
    glColor3f(color.getR(), color.getG(), color.getB());
    
    glBegin(GL_QUADS);
    glVertex2f(x - width/2, y - height/2);
    glVertex2f(x + width/2, y - height/2);
    glVertex2f(x + width/2, y + height/2);
    glVertex2f(x - width/2, y + height/2);
    glEnd();
    
    // Draw selection indicator if selected
    if (selected) {
        glLineWidth(1.0f);
        glColor3f(1.0f, 0.5f, 0.0f); // Orange selection color
        
        glBegin(GL_LINE_LOOP);
        glVertex2f(x - width/2 - 0.01f, y - height/2 - 0.01f);
        glVertex2f(x + width/2 + 0.01f, y - height/2 - 0.01f);
        glVertex2f(x + width/2 + 0.01f, y + height/2 + 0.01f);
        glVertex2f(x - width/2 - 0.01f, y + height/2 + 0.01f);
        glEnd();
    }
}

bool Rectangle::contains(float px, float py) const {
    return (px >= x - width/2) && (px <= x + width/2) &&
           (py >= y - height/2) && (py <= y + height/2);
}

void Rectangle::resize(float factor) {
    width *= factor;
    height *= factor;
}

float Rectangle::getWidth() const {
    return width;
}

float Rectangle::getHeight() const {
    return height;
}

void Rectangle::setWidth(float newWidth) {
    width = newWidth;
}

void Rectangle::setHeight(float newHeight) {
    height = newHeight;
} 