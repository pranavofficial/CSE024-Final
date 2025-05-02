#ifndef COLOR_PICKER_H
#define COLOR_PICKER_H

#include <bobcat_ui/all.h>
#include "Color.h"

class ColorPicker : public bobcat::Group {
    bobcat::Button* redButton;
    bobcat::Button* greenButton;
    bobcat::Button* blueButton;
    bobcat::Button* yellowButton;
    bobcat::Button* purpleButton;
    bobcat::Button* blackButton;
    bobcat::Button* whiteButton;
    bobcat::Canvas_* colorPreview;
    
    Color currentColor;
    
    void onClick(bobcat::Widget* sender);
    void updatePreview();

public:
    ColorPicker(int x, int y, int w, int h);
    
    // Get the current selected color
    Color getColor() const;
    
    // Update the preview display
    void render();
};

#endif // COLOR_PICKER_H 