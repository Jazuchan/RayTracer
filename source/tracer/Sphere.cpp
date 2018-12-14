#include "Sphere.h"


glm::vec3 Sphere::Shading(std::shared_ptr<Ray> _ray, Tracer& _tracer, glm::vec3(_intersect), int a)
{
	glm::vec3 col = GetCol();
	glm::vec3 lightDir = { -1.0f, -1.0f, -1.0f };  //directional light
	glm::vec3 lightPoint = glm::vec3( 0, 50, 50 ) - _intersect; //point light
	glm::vec3 lightCol = { 1.0f, 1.0f, 1.0f };
	glm::vec3 surfNormal = glm::normalize(_intersect - m_pos); //normalises the intersection subtracted by the position of the sphere

	//ambient
	glm::vec3 ambientCol = glm::vec3(1.0f, 0.0f, 0.0f);
	float ambistrength = 0.1f;
	glm::vec3 ambient = ambientCol * ambistrength;

	//diffuse
	lightDir = glm::normalize( lightDir );
	float diffuseCol = glm::max(glm::dot( lightDir, surfNormal), 0.0f);  //finds the dot product between the light direction of the surface normal

	//diffuse2
	lightPoint = glm::normalize( lightPoint );
	float diffuseCol2 = glm::max( glm::dot( lightPoint, surfNormal ), 0.0f );

	//specular
	glm::vec3 reflect = glm::reflect( -lightDir, surfNormal );  //reflects the negative light source against the surface normal
	glm::vec3 camView = glm::normalize(-_ray->m_dir);
	float specularCol = glm::pow(glm::max( glm::dot(camView, glm::normalize(reflect)), 0.0f), 50 );  //creates the dot product of the camera view and the normalised reflection and multiplies it by the power of 50 to make is shiny
	float specIntense = 1.0f;
	specularCol *= specIntense;

	//specular2
	glm::vec3 reflect2 = glm::reflect( -lightPoint, surfNormal );
	glm::vec3 camView2 = glm::normalize( -_ray->m_dir );
	float specularCol2 = glm::pow( glm::max( glm::dot( camView2, glm::normalize( reflect2 ) ), 0.0f ), 50 );
	specularCol2 *= specIntense;
	
	glm::vec3 reflecCol;
	glm::vec3 shadowCol;
	if (a > 0)  //if the bounce is greater than 0
	{
		//reflection
		std::shared_ptr<Ray> m_reflectRay = std::make_shared<Ray>();
		m_reflectRay->m_dir = glm::reflect(-_ray->m_dir, surfNormal);  //creates a reflection between the direction of the ray and the surface  normal
		m_reflectRay->m_ori = _intersect + m_reflectRay->m_dir * 0.001f; //adds the intersection to the direction of the ray and multiplies it by a float
		reflecCol = 0.5f * _tracer.RayTracer(m_reflectRay, a - 1);  //creates the colour of the reflection by multiplying a float by the Ray Tracer function within Tracer, passes in the ray and minuses the bounce by 1

	}

	glm::vec3 hitCol = (diffuseCol + diffuseCol2 + specularCol + specularCol2 + ambient) * lightCol * col + reflecCol; //casts light and reflections to the scene

	return glm::clamp(hitCol, glm::vec3(0), glm::vec3(1));  //clamps the values between 0 and 1
}


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