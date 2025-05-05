#include "Line.h"
#include <GL/freeglut.h>
#include <cmath>

Line::Line(float x1, float y1, float x2, float y2, const Color& color, float thickness)
    : Shape(x1, y1, color), x2(x2), y2(y2), thickness(thickness) {
}

void Line::draw() const {
    // Draw the line
    glColor3f(color.getR(), color.getG(), color.getB());
    glLineWidth(thickness);
    
    glBegin(GL_LINES);
    glVertex2f(x, y);
    glVertex2f(x2, y2);
    glEnd();
    
    // Draw selection indicator if selected
    if (selected) {
        glLineWidth(1.0f);
        glColor3f(1.0f, 0.5f, 0.0f); // Orange selection color
        
        // Draw small circles at endpoints
        const int segments = 12;
        float radius = 0.01f;
        
        // First endpoint
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x, y); // Center
        for (int i = 0; i <= segments; i++) {
            float angle = 2.0f * M_PI * i / segments;
            float px = x + radius * cos(angle);
            float py = y + radius * sin(angle);
            glVertex2f(px, py);
        }
        glEnd();
        
        // Second endpoint
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(x2, y2); // Center
        for (int i = 0; i <= segments; i++) {
            float angle = 2.0f * M_PI * i / segments;
            float px = x2 + radius * cos(angle);
            float py = y2 + radius * sin(angle);
            glVertex2f(px, py);
        }
        glEnd();
    }
}

bool Line::contains(float px, float py) const {
    // Calculate distance from point to line segment
    float lineLength = getLength();
    
    if (lineLength < 0.0001f) {
        // Line is too short, just check distance to endpoints
        float dist1 = sqrt(pow(px - x, 2) + pow(py - y, 2));
        float dist2 = sqrt(pow(px - x2, 2) + pow(py - y2, 2));
        return std::min(dist1, dist2) < thickness * 0.01f;
    }
    
    // Calculate projection and distance to line
    float t = ((px - x) * (x2 - x) + (py - y) * (y2 - y)) / (lineLength * lineLength);
    t = std::max(0.0f, std::min(1.0f, t)); // Clamp to [0, 1]
    
    float nearestX = x + t * (x2 - x);
    float nearestY = y + t * (y2 - y);
    
    float distance = sqrt(pow(px - nearestX, 2) + pow(py - nearestY, 2));
    
    // Distance should be less than half the line thickness (adjusted for coordinate system)
    return distance <= thickness * 0.005f;
}

void Line::move(float dx, float dy) {
    // Move both endpoints
    Shape::move(dx, dy);
    x2 += dx;
    y2 += dy;
}

void Line::resize(float factor) {
    // Calculate center of line
    float centerX = (x + x2) / 2.0f;
    float centerY = (y + y2) / 2.0f;
    
    // Resize around center
    float dx = x - centerX;
    float dy = y - centerY;
    float dx2 = x2 - centerX;
    float dy2 = y2 - centerY;
    
    x = centerX + dx * factor;
    y = centerY + dy * factor;
    x2 = centerX + dx2 * factor;
    y2 = centerY + dy2 * factor;
}

float Line::getX2() const {
    return x2;
}

float Line::getY2() const {
    return y2;
}

float Line::getThickness() const {
    return thickness;
}

void Line::setX2(float newX2) {
    x2 = newX2;
}

void Line::setY2(float newY2) {
    y2 = newY2;
}

void Line::setThickness(float newThickness) {
    thickness = newThickness;
}

float Line::getLength() const {
    return sqrt(pow(x2 - x, 2) + pow(y2 - y, 2));
} 