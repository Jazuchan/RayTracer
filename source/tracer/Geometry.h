#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <vector>
#include <iostream>
#include <memory>
#include "Ray.h"
#include "Sphere.h"

//class Ray;

struct Intersect
{
	bool m_hit = false;
	float m_disToHit;
	glm::vec3 m_intersectPoint;

	//std::shared_ptr<Ray> m_ray;
	//glm::vec3 m_cen;  //sphere centre
	//float m_radi;   //sphere radius
};

class Geometry
{

public:

	glm::vec3 Point(std::shared_ptr<Ray> _ray, glm::vec3 _point);
	Intersect RayIntersect(std::shared_ptr<Ray> _ray, glm::vec3 _cen, float _radi);
	//bool RayIntersect(Ray _ray, float _trace);
	//glm::vec3 Normal(glm::vec3 _pi);
	glm::vec3 GetRayInter(float _a, float _b, glm::vec3 _c);

	//std::shared_ptr<Sphere> m_sphere;
	

	//int GetRadi() { return m_radi; }
	//glm::vec3 GetCen() { return m_cen; }


private:


	glm::vec3 m_lightOri;  //lights origin
	glm::vec3 m_lightDir;  //lights direction

};
#endif