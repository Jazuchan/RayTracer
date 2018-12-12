#include "Camera.h"
#include "Ray.h"

Camera::Camera()
{

}

Camera::Camera(SDL_Renderer* _renderer, int _width, int _height)
{
	//m_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3));
	//m_projectionMatrix = glm::perspective(45.0f, 1.0f, 0.1f, 10000.0f);

	//m_viewMatrix = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, -3));

	m_renderer = _renderer;
	m_windowW = _width;
	m_windowH = _height;

}

bool Camera::Update()
{
	SceneCol();//0, 255, 200);

	SDL_Event m_event = { 0 };

	while (SDL_PollEvent(&m_event))
	{
		if (m_event.type == SDL_QUIT)
		{
			m_running = false;
		}

	}

	m_deltaTime = (float)(m_curr - m_lastTime) / 1000.0f;
	m_lastTime = m_curr;
		
	return m_running;
}

void Camera::SceneCol()//int _red, int _green, int _blue)
{
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);
}

std::shared_ptr<Ray> Camera::PixCood(glm::ivec2 _pair)
{
	m_pixRay = std::make_shared<Ray>();

	m_pixRay->m_ori.x = _pair.x;
	m_pixRay->m_ori.y = _pair.y;
	m_pixRay->m_ori.z = 0;
	//m_pixRay->m_ori = glm::vec3(_pair.x, _pair.y, 0);
	m_pixRay->m_dir = glm::vec3(0, 0, -1);
			 
	/*m_pixRay->m_dir = glm::vec3(glm::perspective(45.0f, 1.0f, 0.1f, 1.0f) * glm::vec4(m_pixRay->m_dir, 1));
	m_pixRay->m_ori = glm::vec3(glm::perspective(45.0f, 1.0f, 0.1f, 1.0f) * glm::vec4(m_pixRay->m_ori, 1));
*/
	return m_pixRay; //std::make_shared<Ray>();
}

//void Camera::PixCood(glm::ivec2 _pair)
//{
//	SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255);
//	SDL_RenderDrawPoint(m_renderer, _pair.x, _pair.y);
//}