#include "Scribble.h"
#include <GL/freeglut.h>
#include <cmath>

Scribble::Scribble(float startX, float startY, const Color& color, int strokeSize)
    : Shape(startX, startY, color), strokeSize(strokeSize) {
    // Add the first point
    points.push_back(Point(startX, startY));
}

void Scribble::addPoint(float x, float y) {
    points.push_back(Point(x, y));
}

void Scribble::draw() const {
    if (points.empty()) return;
    
    glLineWidth(strokeSize);
    glBegin(GL_LINE_STRIP);
    
    glColor3f(color.getR(), color.getG(), color.getB());
    
    for (const Point& point : points) {
        glVertex2f(point.getX(), point.getY());
    }
    
    glEnd();
    
    // Draw selection indicator if selected
    if (selected) {
        glLineWidth(1.0f);
        glColor3f(1.0f, 0.5f, 0.0f); // Orange selection color
        
        // Find bounding box
        float minX = points[0].getX();
        float minY = points[0].getY();
        float maxX = points[0].getX();
        float maxY = points[0].getY();
        
        for (const Point& point : points) {
            minX = std::min(minX, point.getX());
            minY = std::min(minY, point.getY());
            maxX = std::max(maxX, point.getX());
            maxY = std::max(maxY, point.getY());
        }
        
        // Draw bounding box
        glBegin(GL_LINE_LOOP);
        glVertex2f(minX - 0.01f, minY - 0.01f);
        glVertex2f(maxX + 0.01f, minY - 0.01f);
        glVertex2f(maxX + 0.01f, maxY + 0.01f);
        glVertex2f(minX - 0.01f, maxY + 0.01f);
        glEnd();
    }
}

bool Scribble::contains(float px, float py) const {
    if (points.empty()) return false;
    
    // Check if point is close to any segment of the scribble
    const float threshold = strokeSize * 0.005f; // Adjust based on your coordinate system
    
    for (size_t i = 1; i < points.size(); i++) {
        const Point& p1 = points[i-1];
        const Point& p2 = points[i];
        
        // Distance from point to line segment
        float lineLength = std::sqrt(std::pow(p2.getX() - p1.getX(), 2) + 
                                     std::pow(p2.getY() - p1.getY(), 2));
        
        if (lineLength < 0.0001f) continue; // Skip if points are too close
        
        // Calculate distance from point to line segment
        float t = ((px - p1.getX()) * (p2.getX() - p1.getX()) + 
                  (py - p1.getY()) * (p2.getY() - p1.getY())) / (lineLength * lineLength);
        
        t = std::max(0.0f, std::min(1.0f, t));
        
        float nearestX = p1.getX() + t * (p2.getX() - p1.getX());
        float nearestY = p1.getY() + t * (p2.getY() - p1.getY());
        
        float distance = std::sqrt(std::pow(px - nearestX, 2) + std::pow(py - nearestY, 2));
        
        if (distance <= threshold) {
            return true;
        }
    }
    
    return false;
}

void Scribble::move(float dx, float dy) {
    Shape::move(dx, dy);
    
    for (Point& point : points) {
        point.move(dx, dy);
    }
}

void Scribble::resize(float factor) {
    // Find centroid
    float centerX = 0.0f, centerY = 0.0f;
    for (const Point& point : points) {
        centerX += point.getX();
        centerY += point.getY();
    }
    centerX /= points.size();
    centerY /= points.size();
    
    // Resize around centroid
    for (Point& point : points) {
        float newX = centerX + (point.getX() - centerX) * factor;
        float newY = centerY + (point.getY() - centerY) * factor;
        point.setX(newX);
        point.setY(newY);
    }
    
    // Update shape's position to the new centroid
    x = centerX;
    y = centerY;
}

int Scribble::getStrokeSize() const {
    return strokeSize;
}

void Scribble::setStrokeSize(int size) {
    strokeSize = size;
} 