#ifndef LINE_HEADER
    #define LINE_HEADER
    #include <stdbool.h>
    #include "point.h"
    #include "../utils/color.h"
    #define MAX_LINE_COUNT 5

    typedef struct Line {
        Point start;
        Point end;

        RGB rgb;
        bool is_draw;
    } Line;

    typedef struct Lines {
        Line lines[MAX_LINE_COUNT];

        int index;
        int count;
    } Lines;

    void init_lines(Lines* lines);
#endif