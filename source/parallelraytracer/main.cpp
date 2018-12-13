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

static const int num_threads = 3;
std::mutex multi;  ///protects shared data from being accessed by multiple threads at the same time

///Contains the loop for the multi-threads
void MultiThread(int _thread, std::shared_ptr<Tracer> _tracer, std::shared_ptr<Camera> _cam, std::shared_ptr<Ray> _ray, glm::vec3 _col, SDL_Renderer* _renderer, int _startX, int _startY, int _endX, int _endY )
{
	time_t start, finish;  ///holds seconds when the threading starts and finished

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
		std::cout << difftime(finish, start) << " seconds" << std::endl;  ///calculates the difference between two times

		std::lock_guard<std::mutex> gaurd( multi );  ///mutex wrapper which takes ownership of the mutex
}


int main()
{

	bool m_running = true;
	float windowW = 800.0f;
	float windowH = 800.0f;
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
	glm::vec3 col = glm::vec3(0, 0, 0);

	std::thread t[num_threads];  //multi-threading


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
	MultiThread( 1, tracer, cam, ray, col, renderer, 0, 0, windowW / 2, windowW / 2 );  //top left
	MultiThread( 1, tracer, cam, ray, col, renderer, windowW/ 2, windowH/ 2,  800, 800 );  //bottom right
	MultiThread( 1, tracer, cam, ray, col, renderer, windowW / 2, 0, 800, windowH / 2); //top right
	MultiThread( 1, tracer, cam, ray, col, renderer, 0, windowH / 2, windowW / 2, 800);  //bottom left
	//MultiThread( 1, tracer, cam, ray, col, renderer, 0, 0, 800, 800 );  //whole scene

	//creates a for loop for multithreading to occur within the scene
	for (int i = 0; i < num_threads; i++)
	{
		t[i] = std::thread(MultiThread, i, tracer, cam, ray, col, renderer, startX, startY, endX, endY ); ///accesses the MultiThread class and enables the function to be used within the loop
		t[i].join();  ///function return when the thread has been completed
	}
	
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