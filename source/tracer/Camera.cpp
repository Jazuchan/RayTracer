#include "Camera.h"
#include "Ray.h"


Camera::Camera(SDL_Renderer* _renderer, int _width, int _height)
{

	m_renderer = _renderer;
	m_windowW = _width;
	m_windowH = _height;
	
}

std::shared_ptr<Ray> Camera::PixCood(glm::ivec2 _pair)
{
	std::shared_ptr<Ray> m_pixRay = std::make_shared<Ray>();
	m_pixRay->m_ori.x = _pair.x;
	m_pixRay->m_ori.y = _pair.y;
	m_pixRay->m_ori.z = 0;
	m_pixRay->m_dir = glm::vec3(0, 0, -1);
			
	//perspective
	glm::vec3 nearPlane;
	glm::vec3 farPlane;

	//float nearPlane;
	//float farPlane;

	nearPlane.x = -1.0f;
	nearPlane.y = 1.0f;
	nearPlane.z = -1.0f;

	farPlane.x = -1.0f;
	farPlane.y = 1.0f;
	farPlane.z = 1.0f;

	glm::mat4 prespective = /*(float) glm::inverse*/ glm::perspective( 0.0f, 0.0f, nearPlane.z, farPlane.z );
	//m_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3));

	//m_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3));

	return m_pixRay;
}
