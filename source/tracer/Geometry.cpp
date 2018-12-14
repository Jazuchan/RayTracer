#include "Geometry.h"

Intersect Geometry::RayIntersect(std::shared_ptr<Ray> _ray, glm::vec3 _cen, float _radi)
{
	Intersect hit;

	//a
	glm::vec3 ori = _ray->m_ori;  //the rays origin is initialised as the origin of the ray intersection

	//n
	glm::vec3 dir = _ray->m_dir;  //the rays direction is initialised as the direction of the ray intersection

	//p-a
	glm::vec3 oriCen = _cen - _ray->m_ori;  //the centre of the origin is created by subtracting the passes in centre with the rays origin

	//((p-a).n)
	float project = glm::dot(oriCen, dir);  //the rays projection is created through the dot product of the centre of the origin and the direction

	//d
	float dis = glm::length(oriCen - (project) * dir); //calculates the distance between the centre of the origin and the projection direction

	if (dis > _radi)  //if the distance is greater than the radius
	{
		return hit;
	}
	else
	{
			float x = sqrt(pow(_radi, 2) - pow(dis, 2));  //the square root of the power of the radius and the distance

			hit.m_disToHit = project - x;  //the distance till intersection occur is x subtracted by the projection of the ray
			hit.m_intersectPoint = ori + hit.m_disToHit * dir;  //the intersection point is the origin of the ray, plus the distance till it intersects multiplied by the distance
			hit.m_hit = true;

			return hit;

	}

}
