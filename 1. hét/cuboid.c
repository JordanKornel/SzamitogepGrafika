#include "cuboid.h"
#include <stdio.h>
struct Cuboid set_size(){
    struct Cuboid rectangle;
    int ok;
    do
    {
        ok = 1;
        printf("Adja meg a Cuboid adatait: \n");
        printf("a= ");
        if(scanf("%f", &rectangle.a) != 1)
        {
            ok = 0;
            printf("Rossz input!");
        }
        printf("b= ");
        if(scanf("%f", &rectangle.b) != 1)
        {
            ok = 0;
            printf("Rossz input!");
        }
        printf("heigh= ");
        if(scanf("%f", &rectangle.heigh) != 1)
        {
            ok = 0;
            printf("Rossz input!");
        }
        
        while(getchar() != '\n');
    }
    while(!ok);
    return rectangle;
}
void calc_volume(struct Cuboid rectangle){
    printf("Terfogat= %fcm^3\n",rectangle.a * rectangle.b * rectangle.heigh);
}
void calc_surface(struct Cuboid rectangle){
    float a = 2 * (rectangle.a * rectangle.heigh + rectangle.b * rectangle.heigh + rectangle.a * rectangle.b);
    printf("Felszin= %fcm^2\n",a);
}
void square(struct Cuboid rectangle){
    if(rectangle.a == rectangle.b || rectangle.a == rectangle.heigh || rectangle.b == rectangle.heigh){
        printf("Van negyzet alaku lapja!");
    }
    else{
        printf("Nincs negyzet alaku lapja!");
    }
    
}