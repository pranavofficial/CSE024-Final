#include "Triangle.h"
#include <GL/freeglut.h>
#include <cmath>

Triangle::Triangle(float x, float y, float width, float height, const Color& color)
    : Shape(x, y, color), width(width), height(height) {
}

void Triangle::draw() const {
    // Draw the triangle
    glColor3f(color.getR(), color.getG(), color.getB());
    
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y + height/2); // Top point
    glVertex2f(x - width/2, y - height/2); // Bottom left
    glVertex2f(x + width/2, y - height/2); // Bottom right
    glEnd();
    
    // Draw selection indicator if selected
    if (selected) {
        glLineWidth(1.0f);
        glColor3f(1.0f, 0.5f, 0.0f); // Orange selection color
        
        glBegin(GL_LINE_LOOP);
        glVertex2f(x, y + height/2 + 0.01f); // Top point
        glVertex2f(x - width/2 - 0.01f, y - height/2 - 0.01f); // Bottom left
        glVertex2f(x + width/2 + 0.01f, y - height/2 - 0.01f); // Bottom right
        glEnd();
    }
}

bool Triangle::contains(float px, float py) const {
    // Barycentric coordinate method to check if a point is inside a triangle
    float x0 = x - width/2;
    float y0 = y - height/2;
    float x1 = x + width/2;
    float y1 = y - height/2;
    float x2 = x;
    float y2 = y + height/2;
    
    // Calculate area of the full triangle
    float areaTotal = 0.5f * abs((x1 - x0) * (y2 - y0) - (x2 - x0) * (y1 - y0));
    
    // Calculate the three sub-areas using the point
    float area0 = 0.5f * abs((x1 - px) * (y2 - py) - (x2 - px) * (y1 - py));
    float area1 = 0.5f * abs((px - x0) * (y2 - y0) - (x2 - x0) * (py - y0));
    float area2 = 0.5f * abs((x1 - x0) * (py - y0) - (px - x0) * (y1 - y0));
    
    // Point is inside if the three sub-areas sum up to the total area
    return abs(areaTotal - (area0 + area1 + area2)) < 0.0001f;
}

void Triangle::resize(float factor) {
    width *= factor;
    height *= factor;
}

float Triangle::getWidth() const {
    return width;
}

float Triangle::getHeight() const {
    return height;
}

void Triangle::setWidth(float newWidth) {
    width = newWidth;
}

void Triangle::setHeight(float newHeight) {
    height = newHeight;
} 