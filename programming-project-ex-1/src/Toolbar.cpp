#include "Toolbar.h"

using namespace bobcat;
using namespace std;

Toolbar::Toolbar(int x, int y, int w, int h) : Group(x, y, w, h) {
    int buttonHeight = h / 10;
    
    // Create tool buttons
    brushButton = new Button(0, 0 * buttonHeight, w, buttonHeight, "Brush");
    eraserButton = new Button(0, 1 * buttonHeight, w, buttonHeight, "Eraser");
    clearButton = new Button(0, 2 * buttonHeight, w, buttonHeight, "Clear");
    selectorButton = new Button(0, 3 * buttonHeight, w, buttonHeight, "Select");
    rectangleButton = new Button(0, 4 * buttonHeight, w, buttonHeight, "Rectangle");
    circleButton = new Button(0, 5 * buttonHeight, w, buttonHeight, "Circle");
    triangleButton = new Button(0, 6 * buttonHeight, w, buttonHeight, "Triangle");
    lineButton = new Button(0, 7 * buttonHeight, w, buttonHeight, "Line");
    bringToFrontButton = new Button(0, 8 * buttonHeight, w, buttonHeight, "Bring to Front");
    sendToBackButton = new Button(0, 9 * buttonHeight, w, buttonHeight, "Send to Back");
    
    // Add buttons to the toolbar
    add(brushButton);
    add(eraserButton);
    add(clearButton);
    add(selectorButton);
    add(rectangleButton);
    add(circleButton);
    add(triangleButton);
    add(lineButton);
    add(bringToFrontButton);
    add(sendToBackButton);
    
    // Set up button colors
    brushButton->color(FL_BACKGROUND_COLOR);
    eraserButton->color(FL_BACKGROUND_COLOR);
    clearButton->color(FL_BACKGROUND_COLOR);
    selectorButton->color(FL_BACKGROUND_COLOR);
    rectangleButton->color(FL_BACKGROUND_COLOR);
    circleButton->color(FL_BACKGROUND_COLOR);
    triangleButton->color(FL_BACKGROUND_COLOR);
    lineButton->color(FL_BACKGROUND_COLOR);
    bringToFrontButton->color(FL_BACKGROUND_COLOR);
    sendToBackButton->color(FL_BACKGROUND_COLOR);
    
    // Set up click handlers
    ON_CLICK(brushButton, Toolbar::onClick);
    ON_CLICK(eraserButton, Toolbar::onClick);
    ON_CLICK(clearButton, Toolbar::onClick);
    ON_CLICK(selectorButton, Toolbar::onClick);
    ON_CLICK(rectangleButton, Toolbar::onClick);
    ON_CLICK(circleButton, Toolbar::onClick);
    ON_CLICK(triangleButton, Toolbar::onClick);
    ON_CLICK(lineButton, Toolbar::onClick);
    ON_CLICK(bringToFrontButton, Toolbar::onClick);
    ON_CLICK(sendToBackButton, Toolbar::onClick);
    
    // Default to brush tool
    currentTool = ToolType::BRUSH;
    currentAction = Action::NONE;
    brushButton->color(FL_WHITE); // Highlight the default tool
}

void Toolbar::onClick(Widget* sender) {
    deselectAllTools();
    currentAction = Action::NONE;
    
    if (sender == brushButton) {
        currentTool = ToolType::BRUSH;
        brushButton->color(FL_WHITE);
    } 
    else if (sender == eraserButton) {
        currentTool = ToolType::ERASER;
        eraserButton->color(FL_WHITE);
    }
    else if (sender == clearButton) {
        currentTool = ToolType::CLEAR;
        clearButton->color(FL_WHITE);
    }
    else if (sender == selectorButton) {
        currentTool = ToolType::SELECTOR;
        selectorButton->color(FL_WHITE);
    }
    else if (sender == rectangleButton) {
        currentTool = ToolType::RECTANGLE;
        rectangleButton->color(FL_WHITE);
    }
    else if (sender == circleButton) {
        currentTool = ToolType::CIRCLE;
        circleButton->color(FL_WHITE);
    }
    else if (sender == triangleButton) {
        currentTool = ToolType::TRIANGLE;
        triangleButton->color(FL_WHITE);
    }
    else if (sender == lineButton) {
        currentTool = ToolType::LINE;
        lineButton->color(FL_WHITE);
    }
    else if (sender == bringToFrontButton) {
        currentAction = Action::BRING_TO_FRONT;
        // Don't color this button as selected (it's a one-time action)
        cerr << "Bring to front clicked" << endl;
    }
    else if (sender == sendToBackButton) {
        currentAction = Action::SEND_TO_BACK;
        // Don't color this button as selected (it's a one-time action)
        cerr << "Send to back clicked" << endl;
    }
    
    redraw(); // Redraw to show changes
    do_callback(); // Notify parent of changes
}

void Toolbar::deselectAllTools() {
    brushButton->color(FL_BACKGROUND_COLOR);
    eraserButton->color(FL_BACKGROUND_COLOR);
    clearButton->color(FL_BACKGROUND_COLOR);
    selectorButton->color(FL_BACKGROUND_COLOR);
    rectangleButton->color(FL_BACKGROUND_COLOR);
    circleButton->color(FL_BACKGROUND_COLOR);
    triangleButton->color(FL_BACKGROUND_COLOR);
    lineButton->color(FL_BACKGROUND_COLOR);
    bringToFrontButton->color(FL_BACKGROUND_COLOR);
    sendToBackButton->color(FL_BACKGROUND_COLOR);
}

ToolType Toolbar::getTool() const {
    return currentTool;
}

Action Toolbar::getAction() const {
    return currentAction;
}

void Toolbar::resetAction() {
    if (currentAction != Action::NONE) {
        cerr << "Resetting toolbar action" << endl;
        currentAction = Action::NONE;
    }
}

void Toolbar::visualizeSelectedTool() {
    switch (currentTool) {
        case ToolType::BRUSH:
            brushButton->color(FL_WHITE);
            break;
        case ToolType::ERASER:
            eraserButton->color(FL_WHITE);
            break;
        case ToolType::CLEAR:
            clearButton->color(FL_WHITE);
            break;
        case ToolType::SELECTOR:
            selectorButton->color(FL_WHITE);
            break;
        case ToolType::RECTANGLE:
            rectangleButton->color(FL_WHITE);
            break;
        case ToolType::CIRCLE:
            circleButton->color(FL_WHITE);
            break;
        case ToolType::TRIANGLE:
            triangleButton->color(FL_WHITE);
            break;
        case ToolType::LINE:
            lineButton->color(FL_WHITE);
            break;
    }
} 