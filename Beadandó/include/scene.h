#ifndef SCENE_H
#define SCENE_H

#include "camera.h"
#include "texture.h"

#include <obj/model.h>

typedef struct Scene
{
    Model Maze;
	Model Cube;
	Model Star;
    Material material;
	GLuint Maze_texture;
	GLuint Cube_texture;
	GLuint Star_texture;
	GLuint skybox_texture;
	double angle;
} Scene;

/**
 * Initialize the scene by loading models.
 */
void init_scene(Scene* scene);

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



#endif /* SCENE_H */
