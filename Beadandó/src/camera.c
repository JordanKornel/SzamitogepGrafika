#include "camera.h"

#include <GL/gl.h>

#include <math.h>
#define CAMERA_SPEED 1.0
int sprint = 2;
int jumped = 0;
int Collided(float x, float y)
{
	//külső falak
    if(x>4.4 || y<-0.91 || y>12.34 || (x<-6.21 && y>-1 && y<3.5) || (x<-6.21 && y>5.3 && y<12.2)){
        return 1;
    }
	//vízszintes falak
	if(y<1.09 && y>-0.91 && x>-2.7 && x<-2.1){
        return 1;
    }
	if(y<1.09 && y>-0.91 && x<2.96 && x>2.48){
        return 1;
    }
	if(y>0.98 && y<3.37 && x<-4.2 && x>-4.9){
        return 1;
    }
	if(y>0.98 && y<3.37 && x<1.08 && x>0.65){
        return 1;
    }
	if(y>3.5 && y<10.55 && x<3.1 && x>2.55){
        return 1;
    }
	if(y>3.5 && y<8.1 && x<1.1 && x>0.8){
        return 1;
    }
	if(y>3.5 && y<8.1 && x>-0.7 && x<-3.5){
        return 1;
    }
	if(y>8.2 && y<10.6 && x>-4.8 && x<-4.7){
        return 1;
    }
	//függőleges falak

	if(y<10.8 && y>9.8 && x>-4.3 && x<3){
        return 1;
    }
	
	if(y<8.2 && y>7.9 && x>-2.5 && x<-0.7){
        return 1;
    }
	if(y<6.3 && y>6 && x>-6.21 && x<-4.2){
        return 1;
    }
	
	if(y<3.5 && y>2.8 && x>-4.3 && x<3.05){
        return 1;
    }
	
	if(y<1.1 && y>0.9 && x>-2.5 && x<1.1){
        return 1;
    }
    return 0;
}

void init_camera(Camera* camera)
{
    camera->position.x = 0.0;
    camera->position.y = 0.0;
    camera->position.z = 1.0;
    camera->rotation.x = 0.0;
    camera->rotation.y = 0.0;
    camera->rotation.z = 0.0;
    camera->speed.x = 0.0;
    camera->speed.y = 0.0;
    camera->speed.z = 0.0;

    camera->is_preview_visible = false;
}

void update_camera(Camera* camera, double time)
{
    double angle;
    double side_angle;
	double distance;
	distance = time * CAMERA_SPEED*sprint;
	
    angle = degree_to_radian(camera->rotation.z);
    side_angle = degree_to_radian(camera->rotation.z + 90.0);
	if(camera->position.x += cos(angle) * camera->speed.y * time){
		angle = degree_to_radian(camera->rotation.z);
    if(!Collided(camera->position.x,camera->position.y + sin(angle)*distance )){
    camera->position.y += sin(angle) * distance;
}
    if(!Collided(camera->position.x + cos(angle) * distance ,camera->position.y)){
	camera->position.x += cos(angle) * distance;
    }
	}
    if(camera->position.y += sin(angle) * camera->speed.y * time){
		angle = degree_to_radian(camera->rotation.z);
    if(!Collided(camera->position.x,camera->position.y - sin(angle)*distance )){
    camera->position.y -= sin(angle) * distance;
}
    if(!Collided(camera->position.x - cos(angle) * distance ,camera->position.y)){
	camera->position.x -= cos(angle) * distance;
    }
	}
    if(camera->position.x += cos(side_angle) * camera->speed.x * time){
		angle = degree_to_radian(camera->rotation.z + 90.0);
    if(!Collided(camera->position.x,camera->position.y + sin(angle)*distance )){
        camera->position.y += sin(angle) * distance;
}
    if(!Collided(camera->position.x + cos(angle) * distance ,camera->position.y)){
	camera->position.x += cos(angle) * distance;
    }
	}
    if(camera->position.y += sin(side_angle) * camera->speed.x * time){
		angle = degree_to_radian(camera->rotation.z - 90.0);
    if(!Collided(camera->position.x,camera->position.y + sin(angle)*distance )){
    camera->position.y += sin(angle) * distance;
}
    if(!Collided(camera->position.x + cos(angle) * distance ,camera->position.y)){
	camera->position.x += cos(angle) * distance;
    }
	}
    
}

void set_view(const Camera* camera)
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glRotatef(-(camera->rotation.x + 90), 1.0, 0, 0);
    glRotatef(-(camera->rotation.z - 90), 0, 0, 1.0);
    glTranslatef(-camera->position.x, -camera->position.y, -camera->position.z);
}

void rotate_camera(Camera* camera, double horizontal, double vertical)
{
    camera->rotation.z += horizontal;
    camera->rotation.x += vertical;

    if (camera->rotation.z < 0) {
        camera->rotation.z += 360.0;
    }

    if (camera->rotation.z > 360.0) {
        camera->rotation.z -= 360.0;
    }

    if (camera->rotation.x < 0) {
        camera->rotation.x += 360.0;
    }

    if (camera->rotation.x > 360.0) {
        camera->rotation.x -= 360.0;
    }
}

void set_camera_speed(Camera* camera, double speed)
{
    camera->speed.y = speed;
}

void set_camera_side_speed(Camera* camera, double speed)
{
    camera->speed.x = speed;
}

void show_texture_preview()
{
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3f(-1, 1, -3);
    glTexCoord2f(1, 0);
    glVertex3f(1, 1, -3);
    glTexCoord2f(1, 1);
    glVertex3f(1, -1, -3);
    glTexCoord2f(0, 1);
    glVertex3f(-1, -1, -3);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
}
