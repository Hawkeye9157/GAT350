#include "Triangle.h"

bool Triangle::Hit(const ray_t& ray, raycastHit_t& raycastHit, float minDistance, float maxDistance)
{
    float t;
    if (!Raycast(ray, m_local_v1, m_local_v2, m_local_v3, minDistance, maxDistance, t)) return false;

        raycastHit.distance = t;
        raycastHit.point = ray.At(t);

        glm::vec3 edge1 = m_v2 - m_v1;
        glm::vec3 edge2 = m_v3 - m_v2;

        raycastHit.normal = glm::normalize(Cross(edge1, edge2));
        raycastHit.material = GetMaterial();
        return true;
}

bool Triangle::Raycast(const ray_t& ray, const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, float min, float max, float& t)
{
    glm::vec3 edge1 = v2 - v1;
    glm::vec3 edge2 = v3 - v2;

    glm::vec3 pvec = Cross(ray.direction, edge2);
    float det = Dot(pvec, edge1);

    if (det < 0 || approx(det, 0)) {
        return false;
    }
    float invDet = 1 / det;
    glm::vec3 tvec = ray.origin - v1;

    float u = Dot(tvec, pvec) * invDet;
    if (u < 0 || u > 1) {
        return false;
    }
    glm::vec3 qvec = Cross(tvec, edge1);
    float v = Dot(qvec, ray.direction) * invDet;
    if (v < 0 || u + v > 1) {
        return false;
    }
    t = Dot(edge2, qvec) * invDet;
    if (t >= min && t <= max) {
      
        return true;
    }

    return false;
}

void Triangle::Update()
{
    m_v1 = m_transform * glm::vec4{ m_local_v1,1 };
    m_v2 = m_transform * glm::vec4{ m_local_v2,1 };
    m_v3 = m_transform * glm::vec4{ m_local_v3,1 };
    
}
