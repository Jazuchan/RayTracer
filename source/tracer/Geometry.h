#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <iostream>
#include <memory>
#include "Ray.h"
#include "Sphere.h"

///
struct Intersect
{
	bool m_hit = false;
	float m_disToHit;
	glm::vec3 m_intersectPoint;

};

///
class Geometry
{

public:

	glm::vec3 Point(std::shared_ptr<Ray> _ray, glm::vec3 _point);  ///<
	Intersect RayIntersect(std::shared_ptr<Ray> _ray, glm::vec3 _cen, float _radi);  ///<
	glm::vec3 GetRayInter(float _a, float _b, glm::vec3 _c);  ///<

};
#endif