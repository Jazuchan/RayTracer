#include "Tracer.h"

glm::vec3 Tracer::RayTracer(std::shared_ptr<Ray> _ray)
{
	m_col = glm::vec3(0, 0, 0);
	glm::vec3 m_interPoint;
	float m_disToPoint = INFINITY; //
	std::shared_ptr<Sphere> m_closestSphere = nullptr;
	
				/*std::shared_ptr<Ray> m_reflectRay = std::make_shared<Ray>();
				std::shared_ptr<Ray> m_shadowRay = std::make_shared<Ray>();*/

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

			if (m_reflect < 1)
			{
				_ray->m_ori = m_interPoint;	
				_ray->m_dir = m_closestSphere->Reflection(m_result.m_intersectPoint);
				m_col += RayTracer(_ray);

				/*_ray->m_ori = m_interPoint;
				_ray->m_dir = m_closestSphere->Shadows(m_interPoint);
				m_col += RayTracer(_ray);*/

				m_reflect++;
			}
		}
		else
		{
			m_col = glm::vec3(0, 0, 0);
		}

	}


	if (m_closestSphere != nullptr)
	{
		m_col = m_closestSphere->Shading(_ray, m_interPoint);
	}

	return m_col;
}

void Tracer::AddSphere(std::shared_ptr<Sphere> _sphere)
{
	m_sphere.push_back(_sphere);
}