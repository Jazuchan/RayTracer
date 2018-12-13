#include "Sphere.h"


glm::vec3 Sphere::Shading(std::shared_ptr<Ray> _ray, Tracer& _tracer, glm::vec3(_intersect), int a)
{
	glm::vec3 m_col = GetCol();
	glm::vec3 m_lightDir = { -1.0f, -1.0f, -1.0f };  //directional light
	glm::vec3 m_lightPoint = glm::vec3( 0, 50, 50 ) - _intersect; //point light
	glm::vec3 m_lightCol = { 1.0f, 1.0f, 1.0f };
	glm::vec3 m_surfNormal = glm::normalize(_intersect - m_pos);

	float m_specIntense = 1.0f;

	//ambient
	glm::vec3 ambientCol = glm::vec3(1.0f, 0.0f, 0.0f);
	float m_ambistrength = 0.1f;
	glm::vec3 m_ambient = ambientCol * m_ambistrength;

	//diffuse
	m_lightDir = glm::normalize( m_lightDir );
	float m_diffuseCol = glm::max(glm::dot( m_lightDir, m_surfNormal), 0.0f);

	//diffuse2
	m_lightPoint = glm::normalize( m_lightPoint );
	float m_diffuseCol2 = glm::max( glm::dot( m_lightPoint, m_surfNormal ), 0.0f );

	//specular
	glm::vec3 m_reflect = glm::reflect( -m_lightDir, m_surfNormal );
	glm::vec3 m_camView = glm::normalize(-_ray->m_dir);
	float m_specularCol = glm::pow(glm::max( glm::dot(m_camView, glm::normalize(m_reflect)), 0.0f), 50 );
	m_specularCol *= m_specIntense;

	//specular2
	glm::vec3 m_reflect2 = glm::reflect( -m_lightPoint, m_surfNormal );
	glm::vec3 m_camView2 = glm::normalize( -_ray->m_dir );
	float m_specularCol2 = glm::pow( glm::max( glm::dot( m_camView2, glm::normalize( m_reflect2 ) ), 0.0f ), 50 );
	m_specularCol2 *= m_specIntense;
	
	glm::vec3 reflecCol;
	glm::vec3 shadowCol;
	if (a > 0)
	{
		//reflection
		std::shared_ptr<Ray> m_reflectRay = std::make_shared<Ray>();
		m_reflectRay->m_dir = glm::reflect(-_ray->m_dir, m_surfNormal);
		m_reflectRay->m_ori = _intersect + m_reflectRay->m_dir * 0.001f;
		reflecCol = 0.5f * _tracer.RayTracer(m_reflectRay, a - 1);

		//shadow
		std::shared_ptr<Ray> m_shadowRay = std::make_shared<Ray>();
		m_shadowRay->m_ori = _intersect;
		m_shadowRay->m_dir = m_lightDir - _intersect;
		shadowCol = 0.5f * _tracer.RayTracer( m_shadowRay, a );
	}



	//glm::vec3 m_hitCol = ( m_diffuseCol +  m_specularCol + m_ambient ) * m_lightCol * m_col + reflecCol + shadowCol;  //casts light to the scene
	glm::vec3 m_hitCol = (m_diffuseCol + m_diffuseCol2 + m_specularCol + m_specularCol2 + m_ambient) * m_lightCol * m_col + reflecCol;// + shadowCol;  //casts light to the scene

	return glm::clamp(m_hitCol, glm::vec3(0), glm::vec3(1));
}

//glm::vec3 Sphere::Shadows(std::shared_ptr<Ray> _ray, glm::vec3(_intersect))
//{
//	//glm::vec3 m_lightDir = { -1.0f, 0.0f, 1.0f };
//
//	glm::vec3 m_surfNorm = (_intersect - m_pos);
//
////	m_rayDirect = m_lightDir - _intersect;
//
//	//m_shadowVec = m_rayDirect;
//
//	return m_rayDirect;
//	return glm::vec3();
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