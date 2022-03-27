#ifndef COLOR_HEADER
    #define COLOR_HEADER

    typedef struct RGB {
        int r; 
        int g; 
        int b; 
    } RGB;

    typedef struct RGBA {
        RGB rgb;
        int a;
    } RGBA;

    void set_color(RGB* rgb, int r, int g, int b);
#endif