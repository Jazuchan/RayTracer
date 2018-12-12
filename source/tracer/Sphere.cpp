#include "Sphere.h"


glm::vec3 Sphere::Shading(std::shared_ptr<Ray> _ray, Tracer& _tracer, glm::vec3(_intersect), int a)
{
	glm::vec3 m_col = GetCol();
	glm::vec3 m_lightDir = { -1.0f, -1.0f, 1.0f };
	glm::vec3 m_lightCol = { 1.0f, 1.0f, 1.0f };
	//glm::vec4 m_specCol = { 1.0f, 1.0f, 1.0f, 1.0f };
	


	float m_specIntense = 1.0f;

	//ambient
	float m_ambistrength = 0.1f;
	glm::vec3 m_ambient = m_ambistrength * m_col;

	//diffues
	m_lightDir = glm::normalize(m_lightDir);
	glm::vec3 m_surfNormal = glm::normalize(_intersect - m_pos);
	//m_surfNormal1 = m_surfNormal;
	float m_diffuseCol = glm::max(glm::dot(m_lightDir, m_surfNormal), 0.0f);

	//specular
	glm::vec3 m_reflect = glm::reflect( -m_lightDir, m_surfNormal );
	glm::vec3 m_camView = glm::normalize(-_ray->m_dir);
	float m_specularCol = glm::pow(glm::max( glm::dot(m_camView, glm::normalize(m_reflect)), 0.0f), 50 );
	m_specularCol *= m_specIntense;
	
	glm::vec3 reflecCol;
	if (a > 0)
	{
		std::shared_ptr<Ray> m_reflectRay = std::make_shared<Ray>();
		m_reflectRay->m_dir = glm::reflect(-_ray->m_dir, m_surfNormal);

		m_reflectRay->m_ori = _intersect + m_reflectRay->m_dir * 0.001f;

		reflecCol = 0.5f * _tracer.RayTracer(m_reflectRay, a - 1);

		//reflecCol = Reflection(_tracer, _intersect, a - 1);

	}

	glm::vec3 m_hitCol = (m_diffuseCol + m_specularCol + m_ambient ) * m_lightCol * m_col + reflecCol * m_col;  //casts light to the scene

	return glm::clamp(m_hitCol, glm::vec3(0), glm::vec3(1));
}

glm::vec3 Sphere::Shadows(std::shared_ptr<Ray> _ray, glm::vec3(_intersect))
{
//	//glm::vec3 m_lightDir = { -1.0f, 0.0f, 1.0f };
//
//	glm::vec3 m_surfNorm = (_intersect - m_pos);
//
////	m_rayDirect = m_lightDir - _intersect;
//
//	//m_shadowVec = m_rayDirect;
//
//	return m_rayDirect;
	return glm::vec3();
}

glm::vec3 Sphere::Reflection(Tracer& _tracer, glm::vec3(_intersect), int a)
{
	/*
	std::shared_ptr<Ray> m_reflectRay = std::make_shared<Ray>(); 
	
	glm::vec3 m_surfNorm = glm::normalize(_intersect - m_pos);


	m_reflectRay->m_dir = glm::reflect(m_rayDirect, m_surfNorm);

	m_reflectRay->m_ori = _intersect + m_reflectRay->m_dir * 0.001f;

	 = glm::normalize(m_lightDir - _intersect);
	//glm::normalize(m_reflectionVec);
	reflecCol = _tracer.RayTracer(m_reflectRay, a);

	  return reflecCol;
	  */
	return glm::vec3();
}

//glm::vec3 Sphere::Reflection(Tracer& _tracer, glm::vec3(_intersect))
//{
//	std::shared_ptr<Ray> m_reflectRay = std::make_shared<Ray>();
//
//	glm::vec3 m_surfNorm = (_intersect - m_pos);
//
//	m_reflectRay->m_ori = _intersect;
//
//	m_reflectRay->m_dir = glm::reflect(m_rayDirect, m_surfNorm);
//
//	//m_rayDirect = glm::normalize(m_lightDir - _intersect);
//	//glm::normalize(m_reflectionVec);
//	reflecCol = _tracer.RayTracer(m_reflectRay);
//
//	return reflecCol;
//}

void Sphere::SetPos(glm::vec3 _pos)
{
	m_pos = _pos;
}

void Sphere::SetCol(glm::vec3 _col)
{
	m_col = _col;
}

void Sphere::SetRadi(float _radi)
{
	m_radi = _radi;
}

glm::vec3 Sphere::GetPos()
{
	return m_pos;
}

glm::vec3 Sphere::GetCol()
{
	return m_col;
}

float Sphere::GetRadi()
{
	return m_radi;
}

glm::vec3 Sphere::Normal(glm::vec3 _pi)
{
	return (_pi - m_pos / m_radi);
}

//http://www.opengl-tutorial.org/beginners-tutorials/tutorial-8-basic-shading/
//https://www.scratchapixel.com/lessons/3d-basic-rendering/phong-shader-BRDF
//https://www.scratchapixel.com/code.php?id=32&origin=/lessons/3d-basic-rendering/phong-shader-BRDF
//https://www.tomdalling.com/blog/modern-opengl/07-more-lighting-ambient-specular-attenuation-gamma/
//http://www.rastertek.com/dx11tut10.html