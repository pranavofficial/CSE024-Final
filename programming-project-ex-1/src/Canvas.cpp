#include "Canvas.h"
#include <GL/freeglut.h>

Canvas::Canvas(int x, int y, int w, int h) 
    : Canvas_(x, y, w, h), 
      selectedShape(nullptr), 
      currentScribble(nullptr),
      isDragging(false),
      lastMouseX(0.0f),
      lastMouseY(0.0f) {
}

void Canvas::startScribble(float x, float y, const Color& color, int strokeSize) {
    currentScribble = std::make_shared<Scribble>(x, y, color, strokeSize);
    shapes.push_back(currentScribble);
}

void Canvas::addPointToScribble(float x, float y) {
    if (currentScribble) {
        currentScribble->addPoint(x, y);
    }
}

void Canvas::endScribble() {
    currentScribble = nullptr;
}

void Canvas::addRectangle(float x, float y, float width, float height, const Color& color) {
    auto rectangle = std::make_shared<Rectangle>(x, y, width, height, color);
    shapes.push_back(rectangle);
}

void Canvas::addCircle(float x, float y, float radius, const Color& color) {
    auto circle = std::make_shared<Circle>(x, y, radius, color);
    shapes.push_back(circle);
}

void Canvas::addTriangle(float x, float y, float width, float height, const Color& color) {
    auto triangle = std::make_shared<Triangle>(x, y, width, height, color);
    shapes.push_back(triangle);
}

void Canvas::addLine(float x1, float y1, float x2, float y2, const Color& color) {
    auto line = std::make_shared<Line>(x1, y1, x2, y2, color);
    shapes.push_back(line);
}

bool Canvas::selectShapeAt(float x, float y) {
    // Clear any previous selection
    clearSelection();
    
    // Check shapes in reverse order (top to bottom) for selection
    for (auto it = shapes.rbegin(); it != shapes.rend(); ++it) {
        if ((*it)->contains(x, y)) {
            selectedShape = *it;
            selectedShape->setSelected(true);
            return true;
        }
    }
    
    return false;
}

void Canvas::clearSelection() {
    if (selectedShape) {
        selectedShape->setSelected(false);
        selectedShape = nullptr;
    }
}

void Canvas::moveSelected(float dx, float dy) {
    if (selectedShape) {
        selectedShape->move(dx, dy);
    }
}

void Canvas::resizeSelected(float factor) {
    if (selectedShape) {
        selectedShape->resize(factor);
    }
}

void Canvas::changeSelectedColor(const Color& color) {
    if (selectedShape) {
        selectedShape->setColor(color);
    }
}

void Canvas::deleteSelected() {
    if (selectedShape) {
        for (auto it = shapes.begin(); it != shapes.end(); ++it) {
            if (*it == selectedShape) {
                shapes.erase(it);
                selectedShape = nullptr;
                break;
            }
        }
    }
}

void Canvas::bringSelectedToFront() {
    if (selectedShape && shapes.size() > 1) {
        for (auto it = shapes.begin(); it != shapes.end(); ++it) {
            if (*it == selectedShape) {
                // Move to end (top) of container
                shapes.push_back(selectedShape);
                shapes.erase(it);
                break;
            }
        }
    }
}

void Canvas::sendSelectedToBack() {
    if (selectedShape && shapes.size() > 1) {
        for (auto it = shapes.begin(); it != shapes.end(); ++it) {
            if (*it == selectedShape) {
                // Move to front (bottom) of container
                shapes.insert(shapes.begin(), selectedShape);
                shapes.erase(it + 1);  // +1 since we inserted at beginning
                break;
            }
        }
    }
}

void Canvas::clear() {
    shapes.clear();
    selectedShape = nullptr;
    currentScribble = nullptr;
}

void Canvas::render() {
    for (const auto& shape : shapes) {
        shape->draw();
    }
} 