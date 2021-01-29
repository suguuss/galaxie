#include <stdio.h>
#include <inttypes.h>
#include "particles.h"
#include "vec.h"
#include "gfx.h"

#define WIDTH 1000
#define HEIGHT 600
#define NB_STARS 100
#define DEBUG_STAR 15
#define TROU_NOIR NB_STARS / 2

const unsigned long long int temps = 1000000000;

// Prototypes
int CreateWindow(int width, int height, particle *p);


int main()
{
	vec2 minVec = {.x = 0, .y = 0};
	vec2 maxVec = {.x = WIDTH, .y = HEIGHT};

	// Creates a list of stars
	particle *p = particle_create_random_list(minVec, maxVec, 1, 10, NB_STARS);
	
	// Set a star to be the black hole
	p[TROU_NOIR].m = 1000;
	p[TROU_NOIR].r.x = WIDTH / 2;
	p[TROU_NOIR].r.y = HEIGHT / 2;

	CreateWindow(WIDTH, HEIGHT, p);
}


// Functions

void render(struct gfx_context_t *context, particle *p)
{
	vec2 *forces = particle_compute_grav_resultant_forces(p, NB_STARS);

	for (int i = 0; i < NB_STARS; i++)
	{
		// if (i == DEBUG_STAR)
		if (0)
		{
			printf("-----------------\n");
			particle_print(p[i]);
			printf("Resultant force :\t");
			vec2_print(forces[i]);
			forces[i].x = (forces[i].x / p[i].m);
			forces[i].y = (forces[i].y / p[i].m);
			printf("Acceleration:\t\t");
			vec2_print(forces[i]);
			forces[i].x *= temps;
			forces[i].y *= temps;
			printf("Accel + tps:\t\t");
			vec2_print(forces[i]);
			forces[i].y *= -1;
			forces[i].x *= -1;
			printf("inverted :\t\t");
			vec2_print(forces[i]);
			p[i].r = vec2_add(p[i].r, forces[i]);
			printf("End particle : \n");
			particle_print(p[i]);
		}
		else
		{
			forces[i].x = (forces[i].x / p[i].m) * temps/* * (-1)*/;
			forces[i].y = (forces[i].y / p[i].m) * temps/* * (-1)*/;
			p[i].r = vec2_add(p[i].r, forces[i]);
		}
		

		
	}
	

	gfx_clear(context, COLOR_BLACK);
	for (int i = 0; i < NB_STARS; i++)
	{
		if (i == DEBUG_STAR)
		{
			gfx_putpixel(context, p[i].r.x, p[i].r.y, COLOR_RED);
		}
		else if (i == TROU_NOIR)
		{
			gfx_putpixel(context, p[i].r.x, p[i].r.y, COLOR_GREEN);
		}
		else
		{
			gfx_putpixel(context, p[i].r.x, p[i].r.y, COLOR_WHITE);
		}
		
	}
}


int CreateWindow(int width, int height, particle *p)
{
	struct gfx_context_t *ctxt = gfx_create("Example", width, height);
	if (!ctxt) {
		fprintf(stderr, "Graphics initialization failed!\n");
		return EXIT_FAILURE;
	}

	gfx_clear(ctxt, COLOR_BLACK);
		
	// for (int i = 0; i < 10; i++)
	// {
	// 	render(ctxt, p);
	// 	gfx_present(ctxt);
	// }
	

	while (gfx_keypressed() != SDLK_ESCAPE) {
		render(ctxt, p);
		gfx_present(ctxt);
	}

	gfx_destroy(ctxt);
	return EXIT_SUCCESS;
}