#include "Ray.hpp"

static float EPSILON = 0.000001f;

bool Ray::Triangle_Intersection(const Vec3f& p0,
                                    const Vec3f& p1,
                                    const Vec3f& p2,
                                    float &u,
                                    float &v,
                                    float &t) const {
    auto e0 = p1 - p0;
    auto e1 = p2 - p0;
    auto n = normalize(cross(e0,e1));
    auto q = cross(m_direction, e1);
    auto a = dot(e0,q);
    if (dot(n,m_direction) >= 0 || fabs(a) < EPSILON)
        return false;
    auto s = (m_origin-p0)/a;
    auto r = cross(s,e0);
    u = dot(s,q);
    v = dot(r,m_direction);
    t = dot(e1,r);
    if (u < 0.f || u > 1.f)
        return false;
    if (v >= 0.f && u + v <= 1.f && t >= 0)
        return true;
    return false;
}