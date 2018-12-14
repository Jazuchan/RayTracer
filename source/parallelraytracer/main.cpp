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

std::mutex multi;  ///<protects shared data from being accessed by multiple threads at the same time
std::shared_ptr<Tracer> tracer = std::make_shared<Tracer>();  ///<enables the Tracer class to be called and generate the Spheres

///Contains the loop for the multi-threads
void MultiThread( SDL_Renderer* _renderer, int _startX, int _startY, int _endX, int _endY )
{
	time_t start, finish;  //holds seconds when the threading starts and finished

	std::shared_ptr<Camera> cam = std::make_shared<Camera>(_renderer, 800.0f, 800.0f);

		time(&start);
		for (int x = _startX; x < _endX; x++) //generates the start and end positions on the x axis
		{
			for (int y = _startY; y < _endY; y++)  //generates the start and end positions on the y axis
			{
				std::shared_ptr<Ray> ray  = cam->PixCood(glm::ivec2(x, y));  //creates a ray and calls the pixel coordinate function from the camera and passes in the x and y of the loop
				glm::vec3 col = (tracer->RayTracer(ray, 4) * 255.0f);  //creates the color and passes in the ray tracer function from the tracer class, passing in a ray and the number of bounces multiplied by the value of colour

				multi.lock();  //locks the thread so they do not all try to draw at the same time
				SDL_SetRenderDrawColor(_renderer, col.x, col.y, col.z, 255);
				SDL_RenderDrawPoint(_renderer, x, y);
				multi.unlock();
			}
		}
		time(&finish);

		std::cout << difftime(finish, start) << " seconds" << std::endl;  //calculates the difference between two times
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
	   

	//Blue Sphere
	std::shared_ptr<Sphere> bSphere;
	bSphere = std::make_shared<Sphere>();
	bSphere->SetPos(glm::vec3(0.0f, 0.0f, 30.0f));
	bSphere->SetCol(glm::vec3(0, 0.5f, 1));
	bSphere->SetRadi(1.0f);

	//Purple Sphere
	std::shared_ptr<Sphere> pSphere;
	pSphere = std::make_shared<Sphere>();
	pSphere->SetPos(glm::vec3(3.0f, -4.0f, 20.0f));
	pSphere->SetCol(glm::vec3(0.5f, 0, 1));
	pSphere->SetRadi(1.0f);

	//Aqua Sphere
	std::shared_ptr<Sphere> aSphere;
	aSphere = std::make_shared<Sphere>();
	aSphere->SetPos(glm::vec3(-2.0f, 3.0f, 10.0f));
	aSphere->SetCol(glm::vec3(0, 1, 0.5f));
	aSphere->SetRadi(1.0f);

	//Gold Sphere
	std::shared_ptr<Sphere> gSphere;
	gSphere = std::make_shared<Sphere>();
	gSphere->SetPos(glm::vec3(0.0f, 3.0f, 20.0f));
	gSphere->SetCol(glm::vec3(1, 1, 0.5f));
	gSphere->SetRadi(1.0f);

	//Turquiose Sphere
	std::shared_ptr<Sphere> tSphere;
	tSphere = std::make_shared<Sphere>();
	tSphere->SetPos(glm::vec3(3.0f, 0.0f, 10.0f));
	tSphere->SetCol(glm::vec3(0.5f, 1, 1));
	tSphere->SetRadi(1.0f);

	//Pink Sphere
	std::shared_ptr<Sphere> piSphere;
	piSphere = std::make_shared<Sphere>();
	piSphere->SetPos(glm::vec3(-3.0f, -2.0f, 30.0f));
	piSphere->SetCol(glm::vec3(1, 0.5f, 1));
	piSphere->SetRadi(1.0f);

	//Orange Sphere
	std::shared_ptr<Sphere> oSphere;
	oSphere = std::make_shared<Sphere>();
	oSphere->SetPos(glm::vec3(-3.0f, -4.0f, 15.0f));
	oSphere->SetCol(glm::vec3(1, 0.5f, 0));
	oSphere->SetRadi(1.0f);

	//red Sphere
	std::shared_ptr<Sphere> rSphere;
	rSphere = std::make_shared<Sphere>();
	rSphere->SetPos(glm::vec3(3.0f, 4.0f, 15.0f));
	rSphere->SetCol(glm::vec3(1, 0, 0));
	rSphere->SetRadi(1.0f);

	//casts spheres to scene
	tracer->AddSphere(pSphere);
	tracer->AddSphere(bSphere);
	tracer->AddSphere(aSphere);
	tracer->AddSphere(gSphere);
	tracer->AddSphere(tSphere);
	tracer->AddSphere(piSphere);
	tracer->AddSphere(oSphere);
	tracer->AddSphere(rSphere);

	//multi-threading the scene
	//MultiThread( renderer, 0, 0, 800, 800 );  //generates the whole scene

	std::vector<std::thread> threads;  //vector of threads
	
	//runs till the scene is rendered
	for (int x = 0; x < windowW; x += windowW / 2)
	{
		for (int y = 0; y < windowH; y += windowH / 2)
		{
			threads.push_back(std::thread(MultiThread, renderer, x, y, x + (windowW / 2), y + (windowH / 2)));  //generates the threads through the loop and outputs it to the scene
		}
	}
	
	for (size_t i = 0; i < threads.size(); i++) 
	{
		threads.at(i).join(); //joins the threads together
	}
	threads.clear();  //clears the thread

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
//https://github.com/JamieAgate/BasicRayTracer/tree/master/CGG_GFX_Framework
//https://github.com/MarcusMathiassen/BasicRaytracer30min/blob/master/basic_raytracer.cpp?fbclid=IwAR2va6GSQ1BCW6CxhfhfjNqrdIjrtiGJs34cCBxTbRF2HcZVXBUVEZbDXck
//https://www.youtube.com/watch?v=RIgc5J_ZGu8&list=PLAqGIYgEAxrUO6ODA0pnLkM2UOijerFPv
//https://www.youtube.com/watch?v=ARn_yhgk7aE
//https://github.com/Hillsoft/Raytracer-Tutorial/tree/master/RayTutNew
//https://github.com/TyrrellMaye-Smith/ParallelRayTracing/tree/master/src
//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-8-basic-shading/
//https://www.scratchapixel.com/lessons/3d-basic-rendering/phong-shader-BRDF
//https://www.scratchapixel.com/code.php?id=32&origin=/lessons/3d-basic-rendering/phong-shader-BRDF
//https://www.tomdalling.com/blog/modern-opengl/07-more-lighting-ambient-specular-attenuation-gamma/
//http://www.rastertek.com/dx11tut10.ht