#include "Tracer.h"
#include "Sphere.h"
#include "Geometry.h"

glm::vec3 Tracer::RayTracer(std::shared_ptr<Ray> _ray, int a)
{
	m_col = glm::vec3(0, 0, 0);
	glm::vec3 m_interPoint;
	float m_disToPoint = INFINITY; //
	std::shared_ptr<Sphere> m_closestSphere = nullptr;

	for (size_t i = 0; i < m_sphere.size(); i++)
	{
		Intersect m_result = m_geo->RayIntersect(_ray, m_sphere.at(i)->GetPos(), m_sphere.at(i)->GetRadi());
		if (m_result.m_hit)
		{
			if (m_result.m_disToHit < m_disToPoint)
			{
					m_disToPoint = m_result.m_disToHit;
					m_closestSphere = m_sphere.at(i);
					m_interPoint = m_result.m_intersectPoint;
			}
		}
		else
		{
			m_col = glm::vec3(0, 0, 0);
		}
	}

	if (m_closestSphere != nullptr)
	{
		m_col = m_closestSphere->Shading(_ray, *this, m_interPoint, a);
	}

	return m_col;
}

void Tracer::AddSphere(std::shared_ptr<Sphere> _sphere)
{
	m_sphere.push_back(_sphere);
}