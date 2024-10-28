#include "Plane.h"

bool Plane::Hit(const ray_t& ray)
{
    float denominator = dot(ray.direction, m_normal);
    if (denominator == 0) {
        return false;
    }
    float t = dot(m_center - ray.origin, m_normal);
    if (t < 0) {
        return false;
    }
    return true;
}
