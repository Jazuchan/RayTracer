#ifndef TRACE_H
#define	TRACE_H

#include <vector>
#include <memory>
#include <glm/glm.hpp>
#include "Ray.h"

class Geometry;
class Sphere;

class Tracer
{
public:
	glm::vec3 RayTracer(std::shared_ptr<Ray> _ray, int a);
	void AddSphere(std::shared_ptr<Sphere> _sphere);

	std::vector<std::shared_ptr<Sphere>> m_sphere;
	std::shared_ptr<Geometry> m_geo;


	glm::vec3 m_col;
	float m_reflect;
};
#endif

//https://github.com/JamieAgate/BasicRayTracer/tree/master/CGG_GFX_Framework
//https://github.com/MarcusMathiassen/BasicRaytracer30min/blob/master/basic_raytracer.cpp?fbclid=IwAR2va6GSQ1BCW6CxhfhfjNqrdIjrtiGJs34cCBxTbRF2HcZVXBUVEZbDXck
//https://www.youtube.com/watch?v=RIgc5J_ZGu8&list=PLAqGIYgEAxrUO6ODA0pnLkM2UOijerFPv
//https://www.youtube.com/watch?v=ARn_yhgk7aE
//https://github.com/Hillsoft/Raytracer-Tutorial/tree/master/RayTutNew
//https://github.com/TyrrellMaye-Smith/ParallelRayTracing/tree/master/src