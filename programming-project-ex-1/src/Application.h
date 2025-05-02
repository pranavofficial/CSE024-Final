#ifndef APPLICATION_H
#define APPLICATION_H

#include <bobcat_ui/all.h>
#include "Canvas.h"
#include "Toolbar.h"
#include "ColorPicker.h"
#include "ToolType.h"

class Application : public bobcat::Application_ {
    bobcat::Window* window;
    Canvas* canvas;
    Toolbar* toolbar;
    ColorPicker* colorPicker;
    
    // Mouse coordinates for shape creation
    float startX, startY;
    bool isDragging;
    bool isResizing;
    float lastMouseX, lastMouseY; // For tracking mouse movement
    float initialDistance; // For resizing
    
    // Event handlers
    void onCanvasMouseDown(bobcat::Widget* sender, float mx, float my);
    void onCanvasMouseUp(bobcat::Widget* sender, float mx, float my);
    void onCanvasDrag(bobcat::Widget* sender, float mx, float my);
    void onToolbarChange(bobcat::Widget* sender);
    void onColorPickerChange(bobcat::Widget* sender);

public:
    Application();

    friend struct::AppTest;
};


#endif