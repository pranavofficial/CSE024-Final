#include "Application.h" // Test

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
    
    // Handle different tools
    if (tool == ToolType::BRUSH) {
        // Start a new scribble
        canvas->startScribble(mx, my, colorPicker->getColor());
    }
    else if (tool == ToolType::SELECTOR) {
        // Try to select a shape
        if (!canvas->selectShapeAt(mx, my)) {
            // If no shape was selected, deselect current selection
            canvas->clearSelection();
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
            canvas->addRectangle(centerX, centerY, width, height, colorPicker->getColor());
            canvas->redraw();
        }
        else if (tool == ToolType::CIRCLE) {
            // Create a circle
            float radius = distance(startX, startY, mx, my) / 2.0f;
            float centerX = (mx + startX) / 2.0f;
            float centerY = (my + startY) / 2.0f;
            canvas->addCircle(centerX, centerY, radius, colorPicker->getColor());
            canvas->redraw();
        }
        else if (tool == ToolType::TRIANGLE) {
            // Create a triangle
            float width = abs(mx - startX);
            float height = abs(my - startY);
            float centerX = (mx + startX) / 2.0f;
            float centerY = (my + startY) / 2.0f;
            canvas->addTriangle(centerX, centerY, width, height, colorPicker->getColor());
            canvas->redraw();
        }
        else if (tool == ToolType::LINE) {
            // Create a line
            canvas->addLine(startX, startY, mx, my, colorPicker->getColor());
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
            // Move the selected shape
            canvas->moveSelected(mx - lastMouseX, my - lastMouseY);
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
    else if (toolbar->getTool() == ToolType::CLEAR) {
        canvas->clear();
        canvas->redraw();
        
        // Log feedback
        cerr << "Clearing canvas" << endl;
    }
    
    // Regardless of which tool was selected, redraw the UI
    toolbar->redraw();
}

void Application::onColorPickerChange(Widget* sender) {
    // If a shape is selected, change its color
    canvas->changeSelectedColor(colorPicker->getColor());
    canvas->redraw();
}

Application::Application() {
    // Set up window layout
    window = new Window(100, 100, 800, 600, "Paint Application");
    
    // Calculate dimensions
    int toolbarWidth = 100;
    int colorPickerWidth = 150;
    int canvasWidth = 800 - toolbarWidth - colorPickerWidth;
    int canvasHeight = 600;
    
    // Create components with layout
    toolbar = new Toolbar(0, 0, toolbarWidth, canvasHeight);
    canvas = new Canvas(toolbarWidth, 0, canvasWidth, canvasHeight);
    colorPicker = new ColorPicker(toolbarWidth + canvasWidth, 0, colorPickerWidth, canvasHeight);
    
    // Add components to window
    window->add(toolbar);
    window->add(canvas);
    window->add(colorPicker);
    
    // Set up event handlers
    ON_MOUSE_DOWN(canvas, Application::onCanvasMouseDown);
    ON_MOUSE_UP(canvas, Application::onCanvasMouseUp);
    ON_DRAG(canvas, Application::onCanvasDrag);
    ON_CHANGE(toolbar, Application::onToolbarChange);
    ON_CHANGE(colorPicker, Application::onColorPickerChange);
    
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
