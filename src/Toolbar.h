#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <bobcat_ui/all.h>
#include "Canvas.h"
#include "ToolType.h"
#include "Color.h"

class Canvas;

class Toolbar : public bobcat::Group {
    bobcat::Button* brushButton;
    bobcat::Button* eraserButton;
    bobcat::Button* clearButton;
    bobcat::Button* selectorButton;
    bobcat::Button* rectangleButton;
    bobcat::Button* circleButton;
    bobcat::Button* triangleButton;
    bobcat::Button* lineButton;
    bobcat::Button* bringToFrontButton;
    bobcat::Button* sendToBackButton;
    
    // Color selection
    bobcat::Button* colorPickerButton;
    bobcat::Button* redButton;
    bobcat::Button* greenButton;
    bobcat::Button* blueButton;
    bobcat::Button* yellowButton;
    bobcat::Button* blackButton;
    bobcat::Button* whiteButton;
    
    ToolType currentTool;
    Action currentAction;
    Color currentColor;
    bool showColorOptions;
    
    void deselectAllTools();
    void visualizeSelectedTool();
    void onClick(bobcat::Widget* sender);
    void onColorButtonClick(bobcat::Widget* sender);
    void toggleColorOptions();
    void updateColorButtons();

public:
    Toolbar(int x, int y, int w, int h, Canvas* canvas);
    
    // Get current tool and action
    ToolType getTool() const;
    Action getAction() const;
    void resetAction(); // Reset action after it's been processed
    
    // Get current color
    Color getCurrentColor() const;

private:
    Canvas* canvas;
};

#endif // TOOLBAR_H 
