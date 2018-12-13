#include "Geometry.h"

glm::vec3 Geometry::Point(std::shared_ptr<Ray> _ray, glm::vec3 _point)
{
	glm::vec3 m_ori = _ray->m_ori;

	glm::vec3 m_dir = _ray->m_dir;

	float m_project = glm::dot(_point - m_ori, m_dir);
	glm::vec3 m_x = m_ori + (m_project * m_dir);
	
	return m_x;
}

glm::vec3 Geometry::GetRayInter(float _a, float _b, glm::vec3 _c)
{
	return (_c - _a) / (_b - _a);
}

Intersect Geometry::RayIntersect(std::shared_ptr<Ray> _ray, glm::vec3 _cen, float _radi)
{
	Intersect m_hit1;

	//a
	glm::vec3 m_ori = _ray->m_ori;

	//n
	glm::vec3 m_dir = _ray->m_dir;

	//p-a
	glm::vec3 m_oriCen = _cen - _ray->m_ori;


	//((p-a).n)
	float m_project = glm::dot(m_oriCen, m_dir);

	//d
	float m_dis = glm::length(m_oriCen - (m_project) * m_dir);

	if (m_dis > _radi)
	{
		return m_hit1;
	}
	else
	{
			float m_x2 = sqrt(pow(_radi, 2) - pow(m_dis, 2));

			m_hit1.m_disToHit = m_project - m_x2;
			m_hit1.m_intersectPoint = m_ori + m_hit1.m_disToHit * m_dir;
			m_hit1.m_hit = true;

			return m_hit1;

	}

}
