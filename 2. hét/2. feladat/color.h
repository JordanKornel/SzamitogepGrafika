#ifndef ColorDefine
    #define ColorDefine

    typedef struct Color {
        int r;
        int g;
        int b;

        int a;
    } Color;
    
    void setColor(Color* color, int r, int g, int b, int a);
    void randomColor(Color* color);
#endif