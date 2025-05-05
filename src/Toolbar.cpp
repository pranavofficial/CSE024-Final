#include "Toolbar.h"
#include "Canvas.h"

using namespace bobcat;
using namespace std;

Toolbar::Toolbar(int x, int y, int w, int h, Canvas* canvas) : Group(x, y, w, h), canvas(canvas), showColorOptions(false) {
    // Initialize the current color to black
    currentColor = Color(0.0f, 0.0f, 0.0f);
    
    // Calculate button height to fit additional buttons
    int buttonHeight = h / 12;
    
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
    
    // Create color picker buttons
    colorPickerButton = new Button(0, 10 * buttonHeight, w, buttonHeight, "Color Options");
    
    // Create color selection buttons (initially hidden)
    redButton = new Button(0, 11 * buttonHeight, w/3, buttonHeight / 2, "Red");
    redButton->color(FL_RED);
    redButton->labelcolor(FL_WHITE);
    
    greenButton = new Button(w/3, 11 * buttonHeight, w/3, buttonHeight / 2, "Green");
    greenButton->color(FL_GREEN);
    greenButton->labelcolor(FL_BLACK);
    
    blueButton = new Button(2*w/3, 11 * buttonHeight, w/3, buttonHeight / 2, "Blue");
    blueButton->color(FL_BLUE);
    blueButton->labelcolor(FL_WHITE);
    
    yellowButton = new Button(0, 11.5 * buttonHeight, w/3, buttonHeight / 2, "Yellow");
    yellowButton->color(FL_YELLOW);
    yellowButton->labelcolor(FL_BLACK);

    blackButton = new Button(w/3, 11.5 * buttonHeight, w/3, buttonHeight / 2, "Black");
    blackButton->color(FL_BLACK);
    blackButton->labelcolor(FL_WHITE);

    whiteButton = new Button(2*w/3, 11.5 * buttonHeight, w/3, buttonHeight / 2, "White");
    whiteButton->color(FL_WHITE);
    whiteButton->labelcolor(FL_BLACK);

    // Color buttons are initially hidden
    redButton->hide();
    greenButton->hide();
    blueButton->hide();
    yellowButton->hide();
    blackButton->hide();
    whiteButton->hide();
    
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
    add(colorPickerButton);
    add(redButton);
    add(greenButton);
    add(blueButton);
    add(yellowButton);
    add(blackButton);
    add(whiteButton);
    
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
    colorPickerButton->color(FL_BACKGROUND_COLOR);
    
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
    ON_CLICK(colorPickerButton, Toolbar::onClick);
    
    // Set up color button click handlers
    ON_CLICK(redButton, Toolbar::onColorButtonClick);
    ON_CLICK(greenButton, Toolbar::onColorButtonClick);
    ON_CLICK(blueButton, Toolbar::onColorButtonClick);
    ON_CLICK(yellowButton, Toolbar::onColorButtonClick);
    ON_CLICK(blackButton, Toolbar::onColorButtonClick);
    ON_CLICK(whiteButton, Toolbar::onColorButtonClick);
    
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
        // Directly Clear Canvas Here
        if(canvas)
        {
            canvas->clear();
            canvas->render(); // Force UI Refresh
        }

        currentTool = ToolType::BRUSH; // Switch back to brush tool after clearing
        brushButton->color(FL_WHITE);
        cerr << "Clear clicked" << endl;
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
        if(canvas)
        {
            canvas->bringSelectedToFront();
            canvas->redraw();
        }    
        currentAction = Action::NONE;
        // Don't color this button as selected (it's a one-time action)
        cerr << "Bring to front clicked" << endl;
    }
    else if (sender == sendToBackButton) {
        if(canvas)
        {
            canvas->sendSelectedToBack();
            canvas->redraw();
        }
        currentAction = Action::NONE;
        // Don't color this button as selected (it's a one-time action)
        cerr << "Send to back clicked" << endl;
    }
    else if (sender == colorPickerButton) {
        toggleColorOptions();
        colorPickerButton->color(FL_WHITE); // Keep the button highlighted
    }
    
    redraw(); // Redraw to show changes
    do_callback(); // Notify parent of changes
}

void Toolbar::onColorButtonClick(Widget* sender) {
    if (sender == redButton) {
        currentColor.set(1.0f, 0.0f, 0.0f);
        cerr << "Red color selected" << endl;
    }
    else if (sender == greenButton) {
        currentColor.set(0.0f, 1.0f, 0.0f);
        cerr << "Green color selected" << endl;
    }
    else if (sender == blueButton) {
        currentColor.set(0.0f, 0.0f, 1.0f);
        cerr << "Blue color selected" << endl;
    }
    else if (sender == yellowButton) {
        currentColor.set(1.0f, 1.0f, 0.0f);
        cerr << "Yellow color selected" << endl;
    }
    else if (sender == blackButton) {
        currentColor.set(0.0f, 0.0f, 0.0f);
        cerr << "Black color selected" << endl;
    }
    else if (sender == whiteButton) {
        currentColor.set(1.0f, 1.0f, 1.0f);
        cerr << "White color selected" << endl;
    }
    // If there's a selected shape, change its color
    if (canvas && currentTool == ToolType::SELECTOR) {
        canvas->changeSelectedColor(currentColor);
        canvas->redraw();
    }
    
    do_callback(); // Notify the application of color change
}

void Toolbar::toggleColorOptions() {
    showColorOptions = !showColorOptions;
    
    if (showColorOptions) {
        redButton->show();
        greenButton->show();
        blueButton->show();
        yellowButton->show();
        blackButton->show();
        whiteButton->show();
    } else {
        redButton->hide();
        greenButton->hide();
        blueButton->hide();
        yellowButton->hide();
        blackButton->hide();
        whiteButton->hide();
    }
    
    redraw();
}

void Toolbar::updateColorButtons() {
    // Update button colors if needed
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
    colorPickerButton->color(FL_BACKGROUND_COLOR);
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

Color Toolbar::getCurrentColor() const {
    return currentColor;
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
