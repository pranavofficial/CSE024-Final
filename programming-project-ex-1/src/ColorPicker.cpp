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
        
        // Draw border around preview
        glColor3f(0.3f, 0.3f, 0.3f);
        glLineWidth(2.0f);
        glBegin(GL_LINE_LOOP);
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
    
    // Title
    add(new Button(10, 10, w-20, 30, "Color Picker"));
    
    // Set up color buttons
    int buttonSize = min(w-20, 40);  // Button size based on width
    int spacing = 10;  // Space between buttons
    int startY = 50;   // Start position for buttons
    
    // Create color preview (shows current selected color)
    colorPreview = new ColorPreviewCanvas(10, startY, w-20, buttonSize*1.5, &currentColor);
    add(colorPreview);
    
    startY += buttonSize*1.5 + spacing*2;
    
    // Create color buttons in a vertical arrangement
    // Row 1
    redButton = new Button(10, startY, buttonSize, buttonSize, "");
    add(redButton);
    
    greenButton = new Button((w-buttonSize)/2, startY, buttonSize, buttonSize, "");
    add(greenButton);
    
    blueButton = new Button(w-buttonSize-10, startY, buttonSize, buttonSize, "");
    add(blueButton);
    
    // Row 2
    startY += buttonSize + spacing;
    yellowButton = new Button(10, startY, buttonSize, buttonSize, "");
    add(yellowButton);
    
    purpleButton = new Button((w-buttonSize)/2, startY, buttonSize, buttonSize, "");
    add(purpleButton);
    
    whiteButton = new Button(w-buttonSize-10, startY, buttonSize, buttonSize, "");
    add(whiteButton);
    
    // Row 3
    startY += buttonSize + spacing;
    blackButton = new Button((w-buttonSize)/2, startY, buttonSize, buttonSize, "");
    add(blackButton);
    
    // Add labels
    add(new Button(10, startY + buttonSize + spacing, w-20, 20, "Current Color:"));
    
    // Set button colors with clear labels
    redButton->color(fl_rgb_color(255, 0, 0));
    redButton->labelcolor(FL_WHITE);
    redButton->label("R");
    
    greenButton->color(fl_rgb_color(0, 255, 0));
    greenButton->labelcolor(FL_BLACK);
    greenButton->label("G");
    
    blueButton->color(fl_rgb_color(0, 0, 255));
    blueButton->labelcolor(FL_WHITE);
    blueButton->label("B");
    
    yellowButton->color(fl_rgb_color(255, 255, 0));
    yellowButton->labelcolor(FL_BLACK);
    yellowButton->label("Y");
    
    purpleButton->color(fl_rgb_color(128, 0, 128));
    purpleButton->labelcolor(FL_WHITE);
    purpleButton->label("P");
    
    whiteButton->color(fl_rgb_color(255, 255, 255));
    whiteButton->labelcolor(FL_BLACK);
    whiteButton->label("W");
    
    blackButton->color(fl_rgb_color(0, 0, 0));
    blackButton->labelcolor(FL_WHITE);
    blackButton->label("K");
    
    // Set up click handlers
    ON_CLICK(redButton, ColorPicker::onClick);
    ON_CLICK(greenButton, ColorPicker::onClick);
    ON_CLICK(blueButton, ColorPicker::onClick);
    ON_CLICK(yellowButton, ColorPicker::onClick);
    ON_CLICK(purpleButton, ColorPicker::onClick);
    ON_CLICK(blackButton, ColorPicker::onClick);
    ON_CLICK(whiteButton, ColorPicker::onClick);
    
    // Highlight the initial color (black) - use a check mark for selection
    blackButton->label("K ✓");
}

void ColorPicker::onClick(Widget* sender) {
    // Reset all button labels (keeping the letter label)
    redButton->label("R");
    greenButton->label("G");
    blueButton->label("B");
    yellowButton->label("Y");
    purpleButton->label("P");
    blackButton->label("K");
    whiteButton->label("W");
    
    // Set the current color based on which button was clicked
    if (sender == redButton) {
        currentColor.set(1.0f, 0.0f, 0.0f);
        redButton->label("R ✓");
    } 
    else if (sender == greenButton) {
        currentColor.set(0.0f, 1.0f, 0.0f);
        greenButton->label("G ✓");
    }
    else if (sender == blueButton) {
        currentColor.set(0.0f, 0.0f, 1.0f);
        blueButton->label("B ✓");
    }
    else if (sender == yellowButton) {
        currentColor.set(1.0f, 1.0f, 0.0f);
        yellowButton->label("Y ✓");
    }
    else if (sender == purpleButton) {
        currentColor.set(0.5f, 0.0f, 0.5f);
        purpleButton->label("P ✓");
    }
    else if (sender == blackButton) {
        currentColor.set(0.0f, 0.0f, 0.0f);
        blackButton->label("K ✓");
    }
    else if (sender == whiteButton) {
        currentColor.set(1.0f, 1.0f, 1.0f);
        whiteButton->label("W ✓");
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