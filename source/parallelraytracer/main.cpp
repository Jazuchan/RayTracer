#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <fstream>

#include "tracer/Camera.h"
#include "tracer/Geometry.h"
#include "tracer/Ray.h"
#include "tracer/Sphere.h"
#include "tracer/Tracer.h"


int main()
{
	
	int windowW = 800;
	int windowH = 800;
	SDL_Window* window;
	SDL_Renderer* renderer;

	window = SDL_CreateWindow("Parallel Ray Tracer",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		windowW, windowH, SDL_WINDOW_RESIZABLE);

	renderer = SDL_CreateRenderer(window, -1, 0);

	std::shared_ptr<Camera> cam;
	cam = std::make_shared<Camera>(renderer, windowW, windowH);

	std::shared_ptr<Tracer> tracer;
	tracer = std::make_shared<Tracer>();

	std::shared_ptr<Ray> ray;
	glm::vec3 col;

	//blue
	std::shared_ptr<Sphere> bSphere;
	bSphere = std::make_shared<Sphere>();
	bSphere->SetPos(glm::vec3(windowW / 4, windowH / 4, -1.0f));  //edit values
	bSphere->SetCol(glm::vec3(0, 0.5f, 1));
	bSphere->SetRadi(100.0f);

	//purple
	std::shared_ptr<Sphere> pSphere;
	pSphere = std::make_shared<Sphere>();
	pSphere->SetPos(glm::vec3(windowW / 2, windowH / 4, -1.0f));
	pSphere->SetCol(glm::vec3(0.5f, 0, 1));
	pSphere->SetRadi(100.0f);

	//aqua
	std::shared_ptr<Sphere> aSphere;
	aSphere = std::make_shared<Sphere>();
	aSphere->SetPos( glm::vec3( windowW / 2, windowH / 2, -1.0f ) );
	aSphere->SetCol( glm::vec3( 0, 1, 0.5f ) );
	aSphere->SetRadi( 100.0f );

	tracer->AddSphere(bSphere);
	tracer->AddSphere(pSphere);
	tracer->AddSphere(aSphere);

	while (cam->Update())
	{
		for (int x = 0; x < windowW; x++)
		{
			for (int y = 0; y < windowH; y++)
			{
				ray = cam->PixCood(glm::ivec2(x, y));
				col = (tracer->RayTracer(ray, 2) * 255.0f);

				SDL_SetRenderDrawColor(renderer, col.x, col.y, col.z, 255);
				SDL_RenderDrawPoint(renderer, x, y);
			}
		}
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();

	return 0;
}

