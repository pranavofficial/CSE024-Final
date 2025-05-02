#include "ColorPicker.h"
#include <GL/freeglut.h>

using namespace bobcat;
using namespace std;

class ColorPreviewCanvas : public Canvas_ {
    Color* colorRef;
    
public:
    ColorPreviewCanvas(int x, int y, int w, int h, Color* colorRef) 
        : Canvas_(x, y, w, h), colorRef(colorRef) {
    }
    
    void render() override {
        glColor3f(colorRef->getR(), colorRef->getG(), colorRef->getB());
        glBegin(GL_QUADS);
        glVertex2f(0.0f, 0.0f);
        glVertex2f(1.0f, 0.0f);
        glVertex2f(1.0f, 1.0f);
        glVertex2f(0.0f, 1.0f);
        glEnd();
    }
};

ColorPicker::ColorPicker(int x, int y, int w, int h) : Group(x, y, w, h) {
    // Initialize with black color
    currentColor = Color(0.0f, 0.0f, 0.0f);
    
    // Set up color buttons
    int buttonSize = 50;
    int buttonY = 0;
    
    // Create color buttons
    redButton = new Button(0, buttonY, buttonSize, buttonSize, "");
    greenButton = new Button(buttonSize, buttonY, buttonSize, buttonSize, "");
    blueButton = new Button(2*buttonSize, buttonY, buttonSize, buttonSize, "");
    yellowButton = new Button(3*buttonSize, buttonY, buttonSize, buttonSize, "");
    purpleButton = new Button(4*buttonSize, buttonY, buttonSize, buttonSize, "");
    blackButton = new Button(5*buttonSize, buttonY, buttonSize, buttonSize, "");
    whiteButton = new Button(6*buttonSize, buttonY, buttonSize, buttonSize, "");
    
    // Set button colors
    redButton->color(fl_rgb_color(255, 0, 0));
    greenButton->color(fl_rgb_color(0, 255, 0));
    blueButton->color(fl_rgb_color(0, 0, 255));
    yellowButton->color(fl_rgb_color(255, 255, 0));
    purpleButton->color(fl_rgb_color(128, 0, 128));
    blackButton->color(fl_rgb_color(0, 0, 0));
    whiteButton->color(fl_rgb_color(255, 255, 255));
    
    // Set label colors
    redButton->labelcolor(FL_WHITE);
    greenButton->labelcolor(FL_WHITE);
    blueButton->labelcolor(FL_WHITE);
    yellowButton->labelcolor(FL_BLACK);
    purpleButton->labelcolor(FL_WHITE);
    blackButton->labelcolor(FL_WHITE);
    whiteButton->labelcolor(FL_BLACK);
    
    // Create color preview (shows current selected color)
    colorPreview = new ColorPreviewCanvas(0, buttonSize, w, h - buttonSize, &currentColor);
    
    // Add components to the group
    add(redButton);
    add(greenButton);
    add(blueButton);
    add(yellowButton);
    add(purpleButton);
    add(blackButton);
    add(whiteButton);
    add(colorPreview);
    
    // Set up click handlers
    ON_CLICK(redButton, ColorPicker::onClick);
    ON_CLICK(greenButton, ColorPicker::onClick);
    ON_CLICK(blueButton, ColorPicker::onClick);
    ON_CLICK(yellowButton, ColorPicker::onClick);
    ON_CLICK(purpleButton, ColorPicker::onClick);
    ON_CLICK(blackButton, ColorPicker::onClick);
    ON_CLICK(whiteButton, ColorPicker::onClick);
    
    // Highlight the initial color (black)
    blackButton->label("✓");
}

void ColorPicker::onClick(Widget* sender) {
    // Reset all button labels
    redButton->label("");
    greenButton->label("");
    blueButton->label("");
    yellowButton->label("");
    purpleButton->label("");
    blackButton->label("");
    whiteButton->label("");
    
    // Set the current color based on which button was clicked
    if (sender == redButton) {
        currentColor.set(1.0f, 0.0f, 0.0f);
        redButton->label("✓");
    } 
    else if (sender == greenButton) {
        currentColor.set(0.0f, 1.0f, 0.0f);
        greenButton->label("✓");
    }
    else if (sender == blueButton) {
        currentColor.set(0.0f, 0.0f, 1.0f);
        blueButton->label("✓");
    }
    else if (sender == yellowButton) {
        currentColor.set(1.0f, 1.0f, 0.0f);
        yellowButton->label("✓");
    }
    else if (sender == purpleButton) {
        currentColor.set(0.5f, 0.0f, 0.5f);
        purpleButton->label("✓");
    }
    else if (sender == blackButton) {
        currentColor.set(0.0f, 0.0f, 0.0f);
        blackButton->label("✓");
    }
    else if (sender == whiteButton) {
        currentColor.set(1.0f, 1.0f, 1.0f);
        whiteButton->label("✓");
    }
    
    // Update the preview and notify listeners
    updatePreview();
    redraw();
    do_callback();  // Notify parent of color change
}

void ColorPicker::updatePreview() {
    colorPreview->redraw();
}

Color ColorPicker::getColor() const {
    return currentColor;
}

void ColorPicker::render() {
    // No additional rendering needed as child widgets handle themselves
} 