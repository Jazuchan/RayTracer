#include <SDL2/SDL.h>
#include <iostream>
#include <cmath>
#include <fstream>
#include <thread>
#include <mutex>

#include "tracer/Camera.h"
#include "tracer/Geometry.h"
#include "tracer/Ray.h"
#include "tracer/Sphere.h"
#include "tracer/Tracer.h"

static const int num_threads = 4;
std::mutex multi;  ///protects shared data from being accessed by multiple threads at the same time

std::shared_ptr<Tracer> tracer = std::make_shared<Tracer>();

//Tracer tracer;

///Contains the loop for the multi-threads
void MultiThread( SDL_Renderer* _renderer, int _startX, int _startY, int _endX, int _endY )
{
	time_t start, finish;  ///holds seconds when the threading starts and finished

	//std::shared_ptr<Tracer> tracer;
	//tracer = std::make_shared<Tracer>();
	std::shared_ptr<Camera> cam = std::make_shared<Camera>(_renderer, 800.0f, 800.0f);


		time(&start);
		for (int x = _startX; x < _endX; x++)
		{
			for (int y = _startY; y < _endY; y++)
			{
				std::shared_ptr<Ray> ray  = cam->PixCood(glm::ivec2(x, y));
				glm::vec3 col = (tracer->RayTracer(ray, 2) * 255.0f);

				multi.lock();
				SDL_SetRenderDrawColor(_renderer, col.x, col.y, col.z, 255);
				SDL_RenderDrawPoint(_renderer, x, y);
				multi.unlock();
			}
		}
	
		time(&finish);
		std::cout << difftime(finish, start) << " seconds" << std::endl;  ///calculates the difference between two times

		//std::lock_guard<std::mutex> guard( multi );  ///mutex wrapper which takes ownership of the mutex
}


int main()
{
	bool m_running = true;
	float windowW = 800.0f;
	float windowH = 800.0f;
	
	SDL_Window* window;
	SDL_Renderer* renderer;

	window = SDL_CreateWindow("Parallel Ray Tracer",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		windowW, windowH, SDL_WINDOW_RESIZABLE);
	renderer = SDL_CreateRenderer(window, -1, 0);
	   

	std::thread t[num_threads];  //multi-threading
	//std::shared_ptr<Tracer> tracer = std::make_shared<Tracer>();

	//Blue Sphere
	std::shared_ptr<Sphere> bSphere;
	bSphere = std::make_shared<Sphere>();
	bSphere->SetPos(glm::vec3(0.0f, 0.0f, 30.0f));
	bSphere->SetCol(glm::vec3(0, 0.5f, 1));
	bSphere->SetRadi(1.0f);

	//Pink Sphere
	std::shared_ptr<Sphere> pSphere;
	pSphere = std::make_shared<Sphere>();
	pSphere->SetPos(glm::vec3(2.0f, -4.0f, 20.0f));
	pSphere->SetCol(glm::vec3(0.5f, 0, 1));
	pSphere->SetRadi(1.0f);

	//Green Sphere
	std::shared_ptr<Sphere> aSphere;
	aSphere = std::make_shared<Sphere>();
	aSphere->SetPos(glm::vec3(-2.0f, 3.0f, 10.0f));
	aSphere->SetCol(glm::vec3(0, 1, 0.5f));
	aSphere->SetRadi(1.0f);

	tracer->AddSphere(pSphere);
	tracer->AddSphere(bSphere);
	tracer->AddSphere(aSphere);

	//multi-threading the scene
	//MultiThread( renderer, 0, 0, 800, 800 );  //whole scene

	std::vector<std::thread> sickthreads;
	
	for (int x = 0; x < windowW; x += windowW / 2)
	{
		for (int y = 0; y < windowH; y += windowH / 2)
		{
			sickthreads.push_back(std::thread(MultiThread, renderer, x, y, x + (windowW / 2), y + (windowH / 2)));
		}
	}
	
	for (size_t i = 0; i < sickthreads.size(); i++) 
	{
		sickthreads.at(i).join(); 
	}
	sickthreads.clear();


	//without multithreading
		//for (int x = 0; x < 800; x++)
		//{
		//	for (int y = 0; y < 800; y++)
		//	{
		//		ray = cam->PixCood(glm::ivec2(x, y));
		//		col = (tracer->RayTracer(ray, 2) * 255.0f);

		//		SDL_SetRenderDrawColor(renderer, col.x, col.y, col.z, 255);
		//		SDL_RenderDrawPoint(renderer, x, y);
		//	}
		//}

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
//https://en.cppreference.com/w/cpp/thread/mutex
//https://en.cppreference.com/w/cpp/chrono/c/difftime