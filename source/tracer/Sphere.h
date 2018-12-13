#ifndef SPHERE_H
#define	SPHERE_H

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include <cmath>
#include <fstream>

#include "Ray.h"
#include "Tracer.h"

///
class Sphere
{

public:
	
	glm::vec3 Shading(std::shared_ptr<Ray> _ray, Tracer& _tracer, glm::vec3(_intersect), int a);  ///<

	void SetPos(glm::vec3 _pos); 
	void SetRadi(float _radi);
	void SetCol(glm::vec3 _col); 

	glm::vec3 GetPos();
	glm::vec3 GetCol();
	float GetRadi();

	glm::vec3 Normal(glm::vec3 _pi);
	
private:

	glm::vec3 m_pos;
	glm::vec3 m_col;
	float m_radi;

};
#endif
