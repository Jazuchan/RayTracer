#ifndef TRACE_H
#define	TRACE_H

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Ray.h"

class Geometry;
class Sphere;

///Allows the Ray to be drawn through the scene and finds where the intersection occurs creates the Sphere
class Tracer
{
public:
	glm::vec3 RayTracer(std::shared_ptr<Ray> _ray, int a);  ///< passes in a ray and int for the when creating the rays and number of bounces which occurs between objects in a scene
	void AddSphere(std::shared_ptr<Sphere> _sphere);  ///<  enables Spheres to be drawn to the scene

	std::vector<std::shared_ptr<Sphere>> m_sphere; ///<  creates a shared pointer to access Sphere
	std::shared_ptr<Geometry> m_geo;  ///<  creates a shared pointer to access Geometry

};
#endif

