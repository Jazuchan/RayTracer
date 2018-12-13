#include "Camera.h"
#include "Ray.h"

Camera::Camera(SDL_Renderer* _renderer, float _width, float _height)
{

	m_renderer = _renderer;
	m_windowW = _width;
	m_windowH = _height;
	
}

std::shared_ptr<Ray> Camera::PixCood(glm::ivec2 _pair)
{
	std::shared_ptr<Ray> pixRay = std::make_shared<Ray>();
	pixRay->m_ori.x = _pair.x;
	pixRay->m_ori.y = _pair.y;
	pixRay->m_ori.z = 0;
	pixRay->m_dir = glm::vec3(0, 0, -1);


	//perspective
	glm::vec4 nearPlane;
	glm::vec4 farPlane;
	
	nearPlane.x = (_pair.x / (800.0f / 2.0f)) - 1;
	nearPlane.y = -((_pair.y / (800.0f / 2.0f)) - 1);
	nearPlane.z = -1.0f;
	nearPlane.w = 1.0f;

	farPlane.x = (_pair.x / (800.0f / 2.0f)) - 1;
	farPlane.y = -((_pair.y / (800.0f / 2.0f)) - 1);
	farPlane.z = 1.0f;
	farPlane.w = 1.0f;


	glm::mat4 projMatrix = glm::perspective(glm::radians(45.0f), (float) m_windowW/ (float) m_windowH, nearPlane.z, farPlane.z);

	nearPlane = glm::inverse(projMatrix) * nearPlane; //multiply coordinates by inverse projection matrix
	nearPlane /= nearPlane.w;  //divide coordinates by w

	farPlane = glm::inverse(projMatrix) * farPlane;
	farPlane /= farPlane.w;

	//glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3( m_windowW,  m_windowH, 100.0f));

	//nearPlane = glm::inverse(viewMatrix) * nearPlane;  //multiply coordinates by inverse view matrix
	//farPlane = glm::inverse(viewMatrix) * farPlane;
	
	pixRay->m_ori = nearPlane;
	pixRay->m_dir = glm::normalize(-nearPlane + farPlane);


	return pixRay;
}
