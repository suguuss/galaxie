#include <stdio.h>
#include <inttypes.h>
#include "particles.h"
#include "vec.h"
#include "gfx.h"

#define WIDTH 1000
#define HEIGHT 600
#define NB_STARS 200
#define DEBUG_STAR 15
#define TROU_NOIR 0

const unsigned long long int temps = 100000000;

// Prototype
int CreateWindow(int width, int height, particle *p);


int main()
{
	vec2 minVec = {.x = 0, .y = 0};
	vec2 maxVec = {.x = WIDTH, .y = HEIGHT};

	particle *p = particle_create_random_list(minVec, maxVec, 1, 10, NB_STARS);
	
	p[TROU_NOIR].m = 1000;
	p[TROU_NOIR].r.x = WIDTH / 2;
	p[TROU_NOIR].r.y = HEIGHT / 2;

	printf("\n\n");
	CreateWindow(WIDTH, HEIGHT, p);
}


// Functions

void render(struct gfx_context_t *context, particle *p)
{
	vec2 *forces = particle_compute_grav_resultant_forces(p, NB_STARS);

	for (int i = 0; i < NB_STARS; i++)
	{
		

		if (DEBUG_STAR)
		{
			// printf("-----------------\n");
			// vec2_print(forces[i]);
			forces[i].x = (forces[i].x / p[i].m);
			forces[i].y = (forces[i].y / p[i].m);
			// vec2_print(forces[i]);
			forces[i].x *= temps;
			forces[i].y *= temps;
			// vec2_print(forces[i]);
			forces[i].y *= -1;
			forces[i].x *= -1;
			// vec2_print(forces[i]);
		}
		else
		{
			forces[i].x = (forces[i].x / p[i].m) * temps;
			forces[i].y = (forces[i].y / p[i].m) * temps;
		}
		

		p[i].r = vec2_add(p[i].r, forces[i]);
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