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

	std::shared_ptr<Ray> PixCood(glm::ivec2 _pair);
	
	std::shared_ptr<Ray> m_pixRay;

	glm::mat4 m_viewMatrix;
	
	int m_windowW = 800;
	int m_windowH = 800;
	SDL_Renderer* m_renderer;

};
#endif