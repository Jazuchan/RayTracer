#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <iostream>
#include <memory>
#include "Ray.h"
#include "Sphere.h"

///Intersect contains the values for when an intersection occurs
struct Intersect
{
	bool m_hit = false;
	float m_disToHit;  //distance till intersected
	glm::vec3 m_intersectPoint;  ///<the point where the ray hits in 3D space

};

///Geometry stores the information for if the rays have been cast and what happens when they hit
class Geometry
{

public:
	Intersect RayIntersect(std::shared_ptr<Ray> _ray, glm::vec3 _cen, float _radi);  ///<takes in a ray, vector 3 and float to calculate the intersection
};
#endif