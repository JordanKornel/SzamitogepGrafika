#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

#include <SDL2/SDL_mixer.h>

typedef struct Scene
{
    Model Maze;
	Model Cube;
	Model Star;
	Model ground;
	Model Lava;
	Model Ball;
	Model placs1;
	Model placs2;
    Material material;
	GLuint ground_texture;
	GLuint Maze_texture;
	GLuint Cube_texture;
	GLuint Star_texture;
	GLuint skybox_texture;
	GLuint Help_menu;
	GLuint lava_texture;
	double angle;
	bool Help_visible;
	bool motion_up;
} Scene;

typedef struct Audio {
    Mix_Music *Music;
} Audio;


/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene, Audio *audio);
/**
 * Initializes the Audio.
 */
void load_scene_sounds(Audio *audio);

/**
 * Set the lighting of the scene.
 */
void set_lighting();

/**
 * Set the current material.
 */
void set_material(const Material* material);

/**
 * Update the scene.
 */
void update_scene(Scene* scene, double time);

/**
 * Render the scene objects.
 */
void render_scene(const Scene* scene);

/**
 * Draw the origin of the world coordinate system.
 */
void draw_origin();

/**
 * Load the skybox.
 */
void load_skybox(Scene scene);
/**
 * Load the base map.
 */
void load_Maze(Scene scene);

/**
 * Load the star.
 */
void load_Star(Scene scene);
/**
 * Load the star.
 */
void load_ground(Scene scene);

void Help(GLuint Help_menu);

#endif /* SCENE_H */
