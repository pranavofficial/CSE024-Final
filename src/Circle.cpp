#include "Circle.h"
#include <GL/freeglut.h>
#include <cmath>

Circle::Circle(float x, float y, float radius, const Color& color)
    : Shape(x, y, color), radius(radius) {
}

void Circle::draw() const {
    const int numSegments = 100;
    const float angleIncrement = 2.0f * M_PI / numSegments;
    
    // Set the color
    glColor4f(color.getR(), color.getG(), color.getB(), 1.0f); // Using 1.0f for alpha
    
    // Draw the circle
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(x, y); // Center point
    
    for (int i = 0; i <= numSegments; i++) {
        float angle = i * angleIncrement;
        float px = x + radius * cos(angle);
        float py = y + radius * sin(angle);
        glVertex2f(px, py);
    }
    glEnd();
    
    // If selected, draw a highlight
    if (isSelected()) {
        glColor4f(1.0f, 1.0f, 0.0f, 0.5f);
        glLineWidth(2.0f);
        
        glBegin(GL_LINE_LOOP);
        for (int i = 0; i < numSegments; i++) {
            float angle = i * angleIncrement;
            float px = x + radius * cos(angle);
            float py = y + radius * sin(angle);
            glVertex2f(px, py);
        }
        glEnd();
        
        glLineWidth(1.0f);
    }
}

bool Circle::contains(float px, float py) const {
    float dx = px - x;
    float dy = py - y;
    float distanceSquared = dx * dx + dy * dy;
    
    return distanceSquared <= radius * radius;
}

void Circle::resize(float factor) {
    radius *= factor;
}

float Circle::getRadius() const {
    return radius;
}

void Circle::setRadius(float r) {
    radius = r;
} 
