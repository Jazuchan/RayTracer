#ifndef	CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <SDL2/SDL.h>
#include <vector>
#include <memory>


class Ray;

///This class contains the camera matrix for the window
class Camera
{
public:
	
	Camera();
	Camera(SDL_Renderer* _renderer, int _width, int _height);  ///< contains the matrix calculations
	//bool Update();  ///<contains the matrix update
	void SceneCol();
	std::shared_ptr<Ray> PixCood(glm::ivec2 _pair);
	
	std::shared_ptr<Ray> m_pixRay;

	glm::mat4 m_viewMatrix;
	glm::mat4 m_projectionMatrix;
	
	int m_windowW = 800;
	int m_windowH = 800;
	SDL_Renderer* m_renderer;
	SDL_Window* m_window;
	unsigned int m_lastTime = SDL_GetTicks();
	unsigned int m_curr = SDL_GetTicks();
	float m_deltaTime;
};
#endif