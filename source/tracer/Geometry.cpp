#include "Geometry.h"

glm::vec3 Geometry::Point(std::shared_ptr<Ray> _ray, glm::vec3 _point)
{
	glm::vec3 m_ori = _ray->m_ori;

	glm::vec3 m_dir = _ray->m_dir;

	float m_project = glm::dot(_point - m_ori, m_dir);
	glm::vec3 m_x = m_ori + (m_project * m_dir);
	
	return m_x;
	//return _ray->m_ori + ((_point - _ray->m_ori) * _ray->m_dir) * _ray->m_dir;
}

//bool Geometry::RayIntersect(Ray _ray, float _trace)
//{
//	glm::vec3 m_ori = _ray.m_ori;
//
//	glm::vec3 m_dir = _ray.m_dir;
//
//	glm::vec3 m_oriCen = m_ori - m_cen;
//
//
//	double m_b = 2 * dot( m_oriCen, m_dir );
//	double m_c = dot( m_oriCen, m_oriCen ) - m_radi * m_radi;
//	double m_disc = m_b * m_b - 4 * m_c;
//	if(m_disc < 1e-4) return false;
//	m_disc = sqrt( m_disc );
//	double m_trace0 = -m_b - m_disc;
//	double m_trace1 = -m_b + m_disc;
//	_trace = ( m_trace0 < m_trace1 ) ? m_trace0 : m_trace1;
//	return true;
//}

//glm::vec3 Geometry::Normal(glm::vec3 _pi)
//{
//	return (_pi - m_sphere->GetPos()) / m_sphere->GetRadi();
//}

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


	//glm::vec3 m_x  = Point(_ray, _cen);

	if (m_dis > _radi)
	{
		return m_hit1;
	}
	else
	{
		//if (glm::length(_cen - m_x) <= _radi)
		//{
			float m_x2 = sqrt(pow(_radi, 2) - pow(m_dis, 2));

			m_hit1.m_disToHit = m_project - m_x2;
			m_hit1.m_intersectPoint = m_ori + m_hit1.m_disToHit * m_dir;
			m_hit1.m_hit = true;

			return m_hit1;
		//}
		//else
		//{
			// false;
		//}
	}


	/*if (m_d2 > m_radi) return false;
	float m_thc = sqrt(m_radi - m_d2);

	m_trace0 = m_traceCastArray - m_thc;
	m_trace1 = m_traceCastArray + m_thc;


	float m_sn = glm::max(glm::dot(glm::vec3(m_trace0, m_trace1, 0), glm::vec3(-1, -1, -1)), 0.0f);
	m_col.x = 225.0f * m_sn;

	if (m_trace0 < 0)
	{
		m_trace0 = m_trace1;
		if (m_trace0 < 0)
		{
			return false;
		}
	}

	return true;*/
}
