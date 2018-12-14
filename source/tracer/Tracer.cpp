#include "Tracer.h"
#include "Sphere.h"
#include "Geometry.h"

glm::vec3 Tracer::RayTracer(std::shared_ptr<Ray> _ray, int a)
{
	glm::vec3 col = glm::vec3(0, 0, 0);
	glm::vec3 interPoint;
	float disToPoint = INFINITY; //returns the positive infinity value of a given float
	std::shared_ptr<Sphere> closestSphere;  //creates a shared pointer to access Sphere

	for (size_t i = 0; i < m_sphere.size(); i++)
	{
		Intersect m_result = m_geo->RayIntersect(_ray, m_sphere.at(i)->GetPos(), m_sphere.at(i)->GetRadi()); //the geometrys ray intersect is called and the ray at the point of the sphere position and it radius is passed in
		if (m_result.m_hit) //if the ray hits
		{
			if (m_result.m_disToHit < disToPoint)  //if the distance till it hits is less than the ditance to the point
			{
					disToPoint = m_result.m_disToHit;  //initialises the distance to the point to the results intersects distance till it hits
					closestSphere = m_sphere.at(i);  //initialses the closes sphere to the sphere at point i
					interPoint = m_result.m_intersectPoint; //initialises the intersection point to the results intersection point
			}
		}
		else
		{
			col = glm::vec3(0, 0, 0);  //colours scene black
		}
	}

	if (closestSphere)
	{
		col = closestSphere->Shading(_ray, *this, interPoint, a);   //calls the shading function for sphere
	}

	return col;
}

void Tracer::AddSphere(std::shared_ptr<Sphere> _sphere)
{
	m_sphere.push_back(_sphere);  
}