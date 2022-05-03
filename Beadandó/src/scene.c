#include "scene.h"
#include <time.h>
#include <obj/load.h>
#include <obj/draw.h>
#include <math.h>
#include <stdlib.h> 
#include <stdio.h>

void init_scene(Scene* scene, Audio *audio)
{
    load_scene_sounds(audio);

    load_model(&(scene->Maze), "assets/models/Maze4.obj");
    scene->Maze_texture = load_texture("assets/textures/tegla.png");
    glBindTexture(GL_TEXTURE_2D, scene->Maze_texture);
	
	load_model(&(scene->Cube), "assets/models/Cube.obj");
    scene->Cube_texture = load_texture("assets/textures/cube.png");
    glBindTexture(GL_TEXTURE_2D, scene->Cube_texture);
	
	load_model(&(scene->Star), "assets/models/Star5.obj");
    scene->Star_texture = load_texture("assets/textures/star.jpg");
    glBindTexture(GL_TEXTURE_2D, scene->Star_texture);
	
	load_model(&(scene->ground), "assets/models/talaj2.obj");
	scene->ground_texture = load_texture("assets/textures/nature.jpg");
	
	scene->skybox_texture = load_texture("assets/textures/egbolt.jpg");
    glBindTexture(GL_TEXTURE_2D, scene->skybox_texture);
	
	scene->Help_menu = load_texture("assets/textures/Help_menu.jpg");
	glBindTexture(GL_TEXTURE_2D, scene->Help_menu);

    scene->lava_texture = load_texture("assets/textures/lava.jpg");
	glBindTexture(GL_TEXTURE_2D, scene->lava_texture);
	
    load_model(&(scene->Lava), "assets/models/lap.obj");

    load_model(&(scene->Ball), "assets/models/ball2.obj");
    load_model(&(scene->placs1), "assets/models/placs1.obj");
    load_model(&(scene->placs2), "assets/models/placs2.obj");

	scene->motion_up = true;
	
    scene->material.ambient.red = 1.0f;
    scene->material.ambient.green = 1.0f;
    scene->material.ambient.blue = 1.0f;

    scene->material.diffuse.red = 1.0f;
    scene->material.diffuse.green = 1.0f;
    scene->material.diffuse.blue = 1.0f;

    scene->material.specular.red = 1.0f;
    scene->material.specular.green = 1.0f;
    scene->material.specular.blue = 1.0f;
    scene->material.shininess = 1.0f;
	
	scene->angle = 0;
    scene->debris = 0;
	scene->Help_visible = false;

}

void load_scene_sounds(Audio *audio) {
    audio->Music = Mix_LoadMUS("assets/audio/music.mp3");
    if (audio->Music == NULL) {
        printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
    }
}

void set_lighting()
{
    float ambient_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float diffuse_light[] = { 1.0f, 1.0f, 1.0, 1.0f };
    float specular_light[] = { 0.0f, 0.0f, 0.0f, 1.0f };
    float position[] = { 0.0f, 0.0f, 10.0f, 1.0f };

    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
    glLightfv(GL_LIGHT0, GL_POSITION, position);
}

void set_material(const Material* material)
{
    float ambient_material_color[] = {
        material->ambient.red,
        material->ambient.green,
        material->ambient.blue
    };

    float diffuse_material_color[] = {
        material->diffuse.red,
        material->diffuse.green,
        material->diffuse.blue
    };

    float specular_material_color[] = {
        material->specular.red,
        material->specular.green,
        material->specular.blue
    };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse_material_color);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular_material_color);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, &(material->shininess));
}


void load_skybox(Scene scene) {

    glBindTexture(GL_TEXTURE_2D, scene.skybox_texture);

    double theta, phi1, phi2;
    double x1, y1, z1;
    double x2, y2, z2;
    double u, v1, v2;
    int n_slices, n_stacks;
    double radius;
    int i, k;
    n_slices = 15;
    n_stacks = 15;
    radius = 70;

    glPushMatrix();

    glScaled(radius, radius, radius);

    glColor3f(1, 1, 1);

    glBegin(GL_TRIANGLE_STRIP);

    for (i = 0; i < n_stacks; ++i) {
        v1 = (double) i / n_stacks;
        v2 = (double) (i + 1) / n_stacks;
        phi1 = v1 * M_PI / 2.0;
        phi2 = v2 * M_PI / 2.0;
        for (k = 0; k <= n_slices; ++k) {
            u = (double) k / n_slices;
            theta = u * 2.0 * M_PI;
            x1 = cos(theta) * cos(phi1);
            y1 = sin(theta) * cos(phi1);
            z1 = sin(phi1) - 0.25;
            x2 = cos(theta) * cos(phi2);
            y2 = sin(theta) * cos(phi2);
            z2 = sin(phi2) - 0.25;
            glTexCoord2d(u, 1.0 - v1);
            glVertex3d(x1, y1, z1);
            glTexCoord2d(u, 1.0 - v2);
            glVertex3d(x2, y2, z2);
        }
    }

    glEnd();

    glPopMatrix();

}

void load_Star(Scene scene) {


    glPushMatrix();
	glScaled(0.8, 0.8, 0.8);
    glTranslated(2.25, 0, 0.5);
    glBindTexture(GL_TEXTURE_2D, scene.Star_texture);
    
    glTranslated(2.25, 0, 0.5);
    glBindTexture(GL_TEXTURE_2D, scene.Star_texture);
	glTranslated(0, 0, 0.2);
	double time_taken;
	clock_t start;
	start = clock();
	time_taken = ((double) (start)) / CLOCKS_PER_SEC;
	int ok=0;
	//printf("%lf,%lf \n",time_taken,fmod(time_taken, 10.0));
	if(fmod(time_taken, 14.4) < 0.0){
		ok = 0;
	}else if(fmod(time_taken, 14.4) > 7.2){
		ok = 1;
	}
	if(ok==0){
		glRotatef(scene.angle,0,0,1);
	}else{
		glRotatef(-scene.angle,0,0,1);
	}
	
    draw_model(&(scene.Star));
	

    glPopMatrix();
}
void load_ground(Scene scene) {
	
    glPushMatrix();
	glTranslated(-1, -1, -1.7);
    glBindTexture(GL_TEXTURE_2D, scene.ground_texture);
	glTranslated(-1, -1, -1.7);
    draw_model(&(scene.ground));
    glPopMatrix();
}


void load_lava(Scene scene){
    glPushMatrix();
    glTranslatef(0,0,-1.3);
    glBindTexture(GL_TEXTURE_2D, scene.lava_texture);
    glTranslatef(0,0,-1.3);
    draw_model(&(scene.Lava));
    glPopMatrix();
    glDisable(GL_BLEND);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
}

void load_ground2(Scene scene){
    glBlendFunc(GL_ONE_MINUS_CONSTANT_ALPHA, GL_SRC_ALPHA);
    glEnable(GL_BLEND);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_TEXTURE_2D);

    glPushMatrix();

    

    glBegin(GL_QUADS);
    
    glColor4f(0.0, 0.0, 0.0, 10.0);
    glNormal3f(1.0, 1.0, 1.0);

    glVertex3f(5.0, -2.0, 0.0);
    glVertex3f(5.0, 16.0, 0.0);
    glVertex3f(-10.0, 16.0, 0.0);
    glVertex3f(-10.0, -2.0, 0.0);

    glEnd();

    glPopMatrix();

    glDisable(GL_BLEND);
    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_TEXTURE_2D);
}

void Help(GLuint Help_menu) {
        glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_COLOR_MATERIAL);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(1, 1, 1);
    glBindTexture(GL_TEXTURE_2D, Help_menu);

    glBegin(GL_QUADS);
    glTexCoord2f(0, 0);
    glVertex3d(-2, 1.5, -3);
    glTexCoord2f(1, 0);
    glVertex3d(2, 1.5, -3);
    glTexCoord2f(1, 1);
    glVertex3d(2, -1.5, -3);
    glTexCoord2f(0, 1);
    glVertex3d(-2, -1.5, -3);
    glEnd();


    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);
}


void load_debris(Scene scene){
    srand(time(0));    
    for(int i=1; i<250; i++){
        int random_number = rand() % 60 + -30;
        int random_number2 = rand() % 60 + -30;
        glPushMatrix();
        glTranslatef(random_number,random_number2,-3.4);
        glTranslated(fmod(scene.debris * 1, 1),fmod(scene.debris * 1, 1),0);
        glRotatef(scene.debris*14,0,0,1);
        draw_model(&(scene.Ball));
        draw_model(&(scene.placs1));
        draw_model(&(scene.placs2));
        glPopMatrix();
        glDisable(GL_BLEND);
        glDisable(GL_COLOR_MATERIAL);
        glEnable(GL_TEXTURE_2D);
    }
    
}



void update_scene(Scene* scene, double time)
{
	scene->angle += 50 * time;
    scene->debris += 0.8 * time;
}

void render_scene(const Scene* scene)
{
    set_material(&(scene->material));
    set_lighting();
    draw_origin();
    load_Star(*scene);
	glBindTexture(GL_TEXTURE_2D, scene->Maze_texture);
    draw_model(&(scene->Maze));
	glBindTexture(GL_TEXTURE_2D, scene->Cube_texture);
	draw_model(&(scene->Cube));
	glBindTexture(GL_TEXTURE_2D, scene->Star_texture);
    load_lava(*scene);
	glBindTexture(GL_TEXTURE_2D, scene->skybox_texture);
	load_skybox(*scene);
    load_debris(*scene);
    load_ground2(*scene);
}

void draw_origin()
{
    glBegin(GL_LINES);

    glColor3f(1, 0, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(1, 0, 0);

    glColor3f(0, 1, 0);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 1, 0);

    glColor3f(0, 0, 1);
    glVertex3f(0, 0, 0);
    glVertex3f(0, 0, 1);

    glEnd();
}


