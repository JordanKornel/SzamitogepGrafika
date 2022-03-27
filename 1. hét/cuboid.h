#ifndef CUBOID_H
#define CUBOID_H

struct Cuboid{
    float a;
    float b;
    float heigh;
	
}Cuboid;
struct Cuboid set_size();
void calc_volume(struct Cuboid rectangle);
void calc_surface(struct Cuboid rectangle);
void square(struct Cuboid rectangle);

#endif