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
	/*_pair.x = -1.0f;
	_pair.y = 1.0f;*/

	std::shared_ptr<Ray> m_pixRay = std::make_shared<Ray>();
	m_pixRay->m_ori.x = _pair.x;
	m_pixRay->m_ori.y = _pair.y;
	m_pixRay->m_ori.z = 0;
	m_pixRay->m_dir = glm::vec3(0, 0, -1);
		

	//perspective
	glm::vec4 nearPlane;
	glm::vec4 farPlane;
	
	nearPlane.x = -1.0f;
	nearPlane.y = 1.0f;
	nearPlane.z = -1.0f;
	nearPlane.w = 1.0f;

	farPlane.x = - 1.0f;;
	farPlane.y = 1.0f;;
	farPlane.z = 1.0f;
	farPlane.w = 1.0f;


	glm::mat4 projMatrix = glm::perspective(glm::radians(45.0f), (float) m_windowW/ (float) m_windowH, nearPlane.z, farPlane.z);
	//glm::mat4 projMatrix = glm::perspective(glm::radians(45.0f), (float)m_windowW / (float)m_windowH, 0.1f, 100.0f);

	nearPlane = glm::inverse(projMatrix) * nearPlane; //multiply coordinates by inverse projection matrix
	nearPlane /= nearPlane.w;  //divide coordinates by w

	farPlane = glm::inverse(projMatrix) * farPlane;
	farPlane /= farPlane.w;

	glm::mat4 viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3((float) m_windowW, (float) m_windowH, -10.0f));

	nearPlane = glm::inverse(viewMatrix) * nearPlane;  //multiply coordinates by inverse view matrix
	farPlane = glm::inverse(viewMatrix) * farPlane;




	return m_pixRay;
}
