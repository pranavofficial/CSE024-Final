#ifndef CANVAS_H
#define CANVAS_H

#include <bobcat_ui/all.h>
#include <vector>
#include <memory>
#include "Shape.h"
#include "Scribble.h"
#include "Rectangle.h"
#include "Circle.h"
#include "Triangle.h"
#include "Line.h"

// Forward declarations for other shape types we'll implement
class Triangle;
class Line;

class Canvas : public bobcat::Canvas_ {
    std::vector<std::shared_ptr<Shape>> shapes; // Single container for all shapes
    std::shared_ptr<Shape> selectedShape;
    std::shared_ptr<Scribble> currentScribble;
    bool isDragging;
    float lastMouseX, lastMouseY; // For tracking mouse movement

public:
    Canvas(int x, int y, int w, int h);
    
    // Shape creation methods
    void startScribble(float x, float y, const Color& color, int strokeSize = 3);
    void addPointToScribble(float x, float y);
    void endScribble(); // Finalizes current scribble
    
    void addRectangle(float x, float y, float width, float height, const Color& color);
    void addCircle(float x, float y, float radius, const Color& color);
    void addTriangle(float x, float y, float width, float height, const Color& color);
    void addLine(float x1, float y1, float x2, float y2, const Color& color);
    
    // Selection and manipulation
    bool selectShapeAt(float x, float y);
    void clearSelection();
    void moveSelected(float dx, float dy);
    void resizeSelected(float factor);
    void changeSelectedColor(const Color& color);
    void deleteSelected();
    
    // Layer management
    void bringSelectedToFront();
    void sendSelectedToBack();
    
    // Screen management
    void clear();
    
    // Rendering
    void render() override;
};

#endif // CANVAS_H 