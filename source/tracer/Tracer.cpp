#include "Tracer.h"
#include "Sphere.h"
#include "Geometry.h"

glm::vec3 Tracer::RayTracer(std::shared_ptr<Ray> _ray, int a)
{
	m_col = glm::vec3(0, 0, 0);
	glm::vec3 m_interPoint;
	float m_disToPoint = INFINITY; //
	std::shared_ptr<Sphere> m_closestSphere = nullptr;
	
				
				//std::shared_ptr<Ray> m_shadowRay = std::make_shared<Ray>();
				//m_reflectRay = 0;

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
					//_ray = m_reflectRay;
					//_ray = m_shadowRay;

				//if (m_reflect < 1)
				//{
									   
				
					


					/*m_shadowRay->m_ori = m_interPoint;
					m_shadowRay->m_dir = m_closestSphere->Shadows(m_interPoint);
					m_col += RayTracer(m_shadowRay);*/

					//m_reflect++;
				//}
				//m_col += RayTracer(m_reflectRay);
					//m_col += m_closestSphere->m_reflectionVec * m_reflect;
				//glm::vec3 m_hitCol = (m_diffuseCol + m_specularCol + m_ambient) * m_lightCol * m_col;
			}
		}
		else
		{
			m_col = glm::vec3(0, 0, 0);
		}

	}


	if (m_closestSphere != nullptr)
	{
		//m_col = m_closestSphere->Shading(_ray, *this, m_interPoint);
		m_col = m_closestSphere->Shading(_ray, *this, m_interPoint, a);
	}

	return m_col;
}

void Tracer::AddSphere(std::shared_ptr<Sphere> _sphere)
{
	m_sphere.push_back(_sphere);
}