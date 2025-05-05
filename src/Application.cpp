#include "Application.h"

using namespace bobcat;
using namespace std;

// Helper function to calculate distance between two points
float distance(float x1, float y1, float x2, float y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2));
}

void Application::onCanvasMouseDown(Widget* sender, float mx, float my) {
    ToolType tool = toolbar->getTool();
    
    // Store starting position
    startX = mx;
    startY = my;
    isDragging = true;
    isResizing = false;
    
    // Save mouse position for dragging
    lastMouseX = mx;
    lastMouseY = my;
    
    // Get current color from toolbar
    Color currentColor = toolbar->getCurrentColor();
    
    // Handle different tools
    if (tool == ToolType::BRUSH) {
        // Start a new scribble
        canvas->startScribble(mx, my, currentColor);
    }
    else if (tool == ToolType::SELECTOR) {
        // Try to select a shape
        if (!canvas->selectShapeAt(mx, my)) {
            // If no shape was selected, deselect current selection
            canvas->clearSelection();
        } else {
            // If a shape was selected, determine if we're resizing (shift key)
            int key_state = Fl::event_state();
            isResizing = (key_state & FL_SHIFT) != 0;
            if (isResizing) {
                cerr << "Resize mode enabled" << endl;
            }
        }
        canvas->redraw();
    }
    else if (tool == ToolType::ERASER) {
        // Try to select and delete a shape
        if (canvas->selectShapeAt(mx, my)) {
            canvas->deleteSelected();
            canvas->redraw();
        }
    }
}

void Application::onCanvasMouseUp(Widget* sender, float mx, float my) {
    ToolType tool = toolbar->getTool();
    
    // Get current color from toolbar
    Color currentColor = toolbar->getCurrentColor();
    
    if (isDragging) {
        if (tool == ToolType::BRUSH) {
            // End the current scribble
            canvas->endScribble();
        }
        else if (tool == ToolType::RECTANGLE) {
            // Create a rectangle
            float width = abs(mx - startX);
            float height = abs(my - startY);
            float centerX = (mx + startX) / 2.0f;
            float centerY = (my + startY) / 2.0f;
            canvas->addRectangle(centerX, centerY, width, height, currentColor);
            canvas->redraw();
        }
        else if (tool == ToolType::CIRCLE) {
            // Create a circle
            float radius = distance(startX, startY, mx, my) / 2.0f;
            float centerX = (mx + startX) / 2.0f;
            float centerY = (my + startY) / 2.0f;
            canvas->addCircle(centerX, centerY, radius, currentColor);
            canvas->redraw();
        }
        else if (tool == ToolType::TRIANGLE) {
            // Create a triangle
            float width = abs(mx - startX);
            float height = abs(my - startY);
            float centerX = (mx + startX) / 2.0f;
            float centerY = (my + startY) / 2.0f;
            canvas->addTriangle(centerX, centerY, width, height, currentColor);
            canvas->redraw();
        }
        else if (tool == ToolType::LINE) {
            // Create a line
            canvas->addLine(startX, startY, mx, my, currentColor);
            canvas->redraw();
        }
    }
    
    isDragging = false;
    isResizing = false;
}

void Application::onCanvasDrag(Widget* sender, float mx, float my) {
    ToolType tool = toolbar->getTool();
    
    if (isDragging) {
        if (tool == ToolType::BRUSH) {
            // Add point to the current scribble
            canvas->addPointToScribble(mx, my);
            canvas->redraw();
        }
        else if (tool == ToolType::SELECTOR) {
            if (isResizing) {
                // Calculate distance from drag start to current position
                float dx = mx - lastMouseX;
                float dy = my - lastMouseY;
                
                // Calculate a resize factor based on distance moved
                // Moving right/down increases size, left/up decreases
                float resizeFactor = 1.0f;
                if (abs(dx) > abs(dy)) {
                    // Horizontal movement dominates
                    resizeFactor = dx > 0 ? 1.01f : 0.99f;
                } else {
                    // Vertical movement dominates
                    resizeFactor = dy > 0 ? 1.01f : 0.99f;
                }
                
                // Resize the selected shape
                canvas->resizeSelected(resizeFactor);
            } else {
                // Move the selected shape
                canvas->moveSelected(mx - lastMouseX, my - lastMouseY);
            }
            canvas->redraw();
        }
    }
    
    lastMouseX = mx;
    lastMouseY = my;
}

void Application::onToolbarChange(Widget* sender) {
    Action action = toolbar->getAction();
    
    if (action == Action::BRING_TO_FRONT) {
        // Handle bring to front action
        canvas->bringSelectedToFront();
        canvas->redraw();
        
        // Reset the action so it doesn't keep firing
        toolbar->resetAction();
        
        // Log feedback
        cerr << "Bringing selected shape to front" << endl;
    }
    else if (action == Action::SEND_TO_BACK) {
        // Handle send to back action
        canvas->sendSelectedToBack();
        canvas->redraw();
        
        // Reset the action so it doesn't keep firing
        toolbar->resetAction();
        
        // Log feedback
        cerr << "Sending selected shape to back" << endl;
    }
    
    toolbar->redraw();
}

Application::Application() {
    // Set up window layout
    window = new Window(100, 100, 800, 700, "Paint Application");
    
    // Calculate dimensions
    int toolbarWidth = 100;
    int canvasWidth = 800 - toolbarWidth;
    int canvasHeight = 700;
    
    // Create UI components with proper positioning
    canvas = new Canvas(toolbarWidth, 0, canvasWidth, canvasHeight);
    toolbar = new Toolbar(0, 0, toolbarWidth, canvasHeight, canvas);
    
    // Add components to window in the correct order
    window->add(toolbar);
    window->add(canvas);
    
    // Make canvas resizable
    window->resizable(canvas);
    
    // Set up event handlers
    ON_MOUSE_DOWN(canvas, Application::onCanvasMouseDown);
    ON_MOUSE_UP(canvas, Application::onCanvasMouseUp);
    ON_DRAG(canvas, Application::onCanvasDrag);
    ON_CHANGE(toolbar, Application::onToolbarChange);
    
    // Initialize state
    isDragging = false;
    isResizing = false;
    startX = 0.0f;
    startY = 0.0f;
    lastMouseX = 0.0f;
    lastMouseY = 0.0f;
    initialDistance = 0.0f;
    
    // Show the window
    window->show();
}
