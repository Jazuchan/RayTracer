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
	
	Camera(SDL_Renderer* _renderer, float _width, float _height);  ///< contains the matrix calculations

	std::shared_ptr<Ray> PixCood(glm::ivec2 _pair);  ///<  takes in the pixel coordinates for the Ray
		
	int m_windowW = 800.0f;
	int m_windowH = 800.0f;
	SDL_Renderer* m_renderer;

};
#endif