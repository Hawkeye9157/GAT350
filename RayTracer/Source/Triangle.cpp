#include "Triangle.h"

bool Triangle::Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance)
{
    glm::vec3 edge1 = m_v2 - m_v1;
    glm::vec3 edge2 = m_v3 - m_v2;

    glm::vec3 pvec = Cross(ray.direction, edge2);
    float det = Dot(pvec, edge1);

    if (det < 0 || approx(det, 0)) {
        return false;
    }
    float invDet = 1 / det;
    glm::vec3 tvec = ray.origin - m_v1;

    float u = Dot(tvec, pvec) * invDet;
    if (u < 0 || u > 1) {
        return false;
    }
    glm::vec3 qvec = Cross(tvec, edge1);
    float v = Dot(qvec, ray.direction) * invDet;
    if (v < 0 || u + v > 1) {
        return false;
    }
    float t = Dot(edge2, qvec) * invDet;
    if (t >= minDistance && t <= maxDistance) {
        raycastHit.distance = t;
        raycastHit.point = ray.At(t);
        raycastHit.normal = glm::normalize(Cross(edge1, edge2));
        raycastHit.material = GetMaterial();
        return true;
    }

    return false;
}
