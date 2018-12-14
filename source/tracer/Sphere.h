#ifndef SPHERE_H
#define	SPHERE_H

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <cmath>
#include <fstream>

#include "Ray.h"
#include "Tracer.h"

///Sphere contains the shading, lighting, refelctions and attributes of the spheres
class Sphere
{
public:
	
	glm::vec3 Shading(std::shared_ptr<Ray> _ray, Tracer& _tracer, glm::vec3(_intersect), int a);  ///<

	void SetPos(glm::vec3 _pos); ///<sets the posistion of the sphere in the scene
	void SetRadi(float _radi);  ///<sets the radius of the sphere
	void SetCol(glm::vec3 _col);  ///<sets the colour of the sphere

	glm::vec3 GetPos();  ///<returns the posistion of the sphere in the scene
	glm::vec3 GetCol();  ///<returns the radius of the sphere
	float GetRadi();  ///<returns the colour of the sphere
	
private:

	glm::vec3 m_pos;
	glm::vec3 m_col;
	float m_radi;

};
#endif
