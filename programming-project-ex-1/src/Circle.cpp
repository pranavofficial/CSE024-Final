#include "Circle.h"
#include <GL/freeglut.h>
#include <cmath>

Circle::Circle(float x, float y, float radius, const Color& color)
    : Shape(x, y, color), radius(radius) {
}

void Circle::draw() const {
    // Draw the circle
    glColor3f(color.getR(), color.getG(), color.getB());
    
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center
    
    const int segments = 32;
    for (int i = 0; i <= segments; i++) {
        float angle = 2.0f * M_PI * i / segments;
        float px = x + radius * cos(angle);
        float py = y + radius * sin(angle);
        glVertex2f(px, py);
    }
    glEnd();
    
    // Draw selection indicator if selected
    if (selected) {
        glLineWidth(1.0f);
        glColor3f(1.0f, 0.5f, 0.0f); // Orange selection color
        
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < segments; i++) {
            float angle = 2.0f * M_PI * i / segments;
            float px = x + (radius + 0.01f) * cos(angle);
            float py = y + (radius + 0.01f) * sin(angle);
            glVertex2f(px, py);
        }
        glEnd();
    }
}

bool Circle::contains(float px, float py) const {
    float distance = sqrt(pow(px - x, 2) + pow(py - y, 2));
    return distance <= radius;
}

void Circle::resize(float factor) {
    radius *= factor;
}

float Circle::getRadius() const {
    return radius;
}

void Circle::setRadius(float newRadius) {
    radius = newRadius;
} 