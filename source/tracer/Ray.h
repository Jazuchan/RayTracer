#ifndef RAY_H
#define RAY_H

#include <glm/glm.hpp>


///This class contains the vectors for the ray tracer
class Ray
{
public:

	glm::vec3 m_ori; ///<origin of the ray
	glm::vec3 m_dir;  ///<direction of the ray
};

#endif