#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <thread>

#include "tracer/Camera.h"
#include "tracer/Geometry.h"
#include "tracer/Ray.h"
#include "tracer/Sphere.h"
#include "tracer/Tracer.h"

void MultiThread(int _thread, std::shared_ptr<Tracer> _tracer, std::shared_ptr<Camera> _cam, std::shared_ptr<Ray> _ray, glm::vec3 _col, SDL_Renderer* _renderer, int _startX, int _startY, int _endX, int _endY )
{
	time_t start, finish;  //time then the threading starts and finished

		time(&start);
		for (int x = _startX; x < _endX; x++)
		{
			for (int y = _startY; y < _endY; y++)
			{
				_ray = _cam->PixCood(glm::ivec2(x, y));
				_col = (_tracer->RayTracer(_ray, 2) * 255.0f);

				SDL_SetRenderDrawColor(_renderer, _col.x, _col.y, _col.z, 255);
				SDL_RenderDrawPoint(_renderer, x, y);
			}
		}
	
		time(&finish);
		std::cout << difftime(finish, start) << " seconds" << std::endl;
}

static const int num_threads = 3;

int main()
{

	bool m_running = true;
	int windowW = 800;
	int windowH = 800;
	int startX, startY, endX, endY = 0;
	SDL_Window* window;
	SDL_Renderer* renderer;

	window = SDL_CreateWindow("Parallel Ray Tracer",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		windowW, windowH, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, 0);

	std::shared_ptr<Camera> cam = std::make_shared<Camera>(renderer, windowW, windowH);

	std::shared_ptr<Tracer> tracer = std::make_shared<Tracer>();

	std::shared_ptr<Ray> ray;
	glm::vec3 col = glm::vec3(0, 0, 0) ;

	std::thread t[num_threads];  //multi-threading


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
	aSphere->SetPos(glm::vec3(windowW / 2, windowH / 2, -1.0f));
	aSphere->SetCol(glm::vec3(0, 1, 0.5f));
	aSphere->SetRadi(100.0f);

	tracer->AddSphere(bSphere);
	tracer->AddSphere(pSphere);
	tracer->AddSphere(aSphere);

	//multi-threading
	MultiThread( 1, tracer, cam, ray, col, renderer, 0, 0, windowW / 2, windowW / 2 );
	MultiThread( 1, tracer, cam, ray, col, renderer, windowW/ 2, windowH/ 2,  800, 800 );
	MultiThread( 1, tracer, cam, ray, col, renderer, 800, 800, windowW / 2, windowW / 2 );
	MultiThread( 1, tracer, cam, ray, col, renderer, 0, 0, 800, 800 );

	for (int i = 0; i < num_threads; i++)
	{
		t[i] = std::thread(MultiThread, i, tracer, cam, ray, col, renderer, startX, startY, endX, endY );
		t[i].join();
	}
	
	while (m_running)
	{
		SDL_Event m_event = { 0 };

		while (SDL_PollEvent(&m_event))
		{
			if (m_event.type == SDL_QUIT)
			{
				m_running = false;
			}

		}
		SDL_RenderPresent(renderer);
	}

	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();


	return 0;
}
//https://solarianprogrammer.com/2011/12/16/cpp-11-thread-tutorial/
