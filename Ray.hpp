#pragma once

#include "utils.hpp"


class Ray{
    public:
        inline Ray(Vec3f O, Vec3f u) 
            : m_origin(O), m_direction(normalize(u)) {}

        inline ~Ray () {}
        
        inline Vec3f& origin() {return m_origin;}
        inline Vec3f& direction() {return m_direction;}

        inline const Vec3f& origin() const {return m_origin;}
        inline const Vec3f& direction() const {return m_direction;}

        // Return true if a the ray intersection the triangle [p0,p1,p2]. 
        // In this case, (u,v) are filled with barycentric coordinates (with the third one w = 1.0 - u - v) 
        // t with the distance from the origin to the intersection 
        // bool Triangle_Intersection(const Vec3f& p0,
        //                             const Vec3f& p1,
        //                             const Vec3f& p2,
        //                             float &u,
        //                             float &v,
        //                             float &t) const;

        // float EPSILON = 0.000001f;

        bool Triangle_Intersection(const Vec3f& p0,
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
            if (dot(n,m_direction) >= 0 || fabs(a) < epsilon)
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

    private:
        Vec3f m_origin;
        Vec3f m_direction;

};