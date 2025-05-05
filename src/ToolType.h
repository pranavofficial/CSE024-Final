#ifndef TOOL_TYPE_H
#define TOOL_TYPE_H

// Tool types
enum class ToolType {
    BRUSH,
    ERASER,
    CLEAR,
    SELECTOR,
    RECTANGLE,
    CIRCLE,
    TRIANGLE,
    LINE
};

// Actions for ordering
enum class Action {
    NONE,
    BRING_TO_FRONT,
    SEND_TO_BACK
};

#endif // TOOL_TYPE_H 