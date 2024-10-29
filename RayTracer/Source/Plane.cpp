#include "Plane.h"

bool Plane::Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance)
{
    float denominator = dot(ray.direction, m_normal);
    if (approx(denominator,0)) {
        return false;
    }
    float t = dot(m_center - ray.origin, m_normal);
    if (t < 0) {
        return false;
    }
    if (t <= minDistance || t >= maxDistance) return false;

    raycastHit.distance = t;
    raycastHit.normal = m_normal;
    raycastHit.point = ray.At(t);

    return true;
}
