#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <bobcat_ui/all.h>
#include "ToolType.h"

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
    
    ToolType currentTool;
    Action currentAction;
    
    void deselectAllTools();
    void visualizeSelectedTool();
    void onClick(bobcat::Widget* sender);

public:
    Toolbar(int x, int y, int w, int h);
    
    // Get current tool and action
    ToolType getTool() const;
    Action getAction() const;
    void resetAction(); // Reset action after it's been processed
};

#endif // TOOLBAR_H 