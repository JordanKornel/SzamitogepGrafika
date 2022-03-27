#include "cuboid.h"
#include <stdio.h>
int main(){

    struct Cuboid rectangle;

    rectangle = set_size();
    printf("\n");

    printf("a= %f, b= %f, heigh= %f\n",rectangle.a,rectangle.b,rectangle.heigh);

    calc_volume(rectangle);

    calc_surface(rectangle);

    square(rectangle);

    return 0;
}