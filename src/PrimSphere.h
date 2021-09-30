// Sphere Geaometrical Primitive class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "IPrim.h"
#include "ray.h"
#include <math.h>

// ================================ Sphere Primitive Class ================================
/**
 * @brief Sphere Geaometrical Primitive class
 * @ingroup modulePrimitive
 * @author Sergey G. Kosov, sergey.kosov@project-10.de
 */
class CPrimSphere : public IPrim
{
public:
	/**
	 * @brief Constructor
		 * @param origin Position of the center of the sphere
		 * @param radius Radius of the sphere
	 */
	CPrimSphere(Vec3f origin, float radius)
		: IPrim()
		, m_origin(origin)
		, m_radius(radius)
	{}
	virtual ~CPrimSphere(void) = default;

	virtual bool intersect(Ray &ray) const override
	{
		// --- PUT YOUR CODE HERE ---

		/*Vec3f L = m_origin - ray.org;

		float tb = ray.dir.x * L.x + ray.dir.y * L.y + ray.dir.z * L.z;  //rau.dir * L
		float L_value = L.x * L.x + L.y * L.y + L.z * L.z;

		float h = sqrt(L_value - tb * tb);

		if(h > m_radius)
			return false;

		float delta = sqrt(m_radius * m_radius - L_value + tb * tb);
		float tx = tb - delta;

		Vec3f x = ray.org + tx * m_origin; 


		return true;*/

		double r2 = static_cast<double>(m_radius) * static_cast<double>(m_radius);

		Vec3f L = m_origin - ray.org;

		double tb = static_cast<double>(L.dot(ray.dir));

		if(tb > -Epsilon && tb < Epsilon)
			return false;

		double h2 = static_cast<double>(L.dot(L)) - tb * tb;
		
		if(h2>r2)
			return false;

		double delta = sqrt(r2 - h2);
		double t0 = tb - delta;
		double t1 = tb + delta;


		//RT_ASSERT(t0 <= t1);

		if(t0 > ray.t) return false;

		if(t0 <= Epsilon){
			t0 = 0;
			if(t1 < Epsilon || t1 > ray.t)
				return false;
		}

		ray.t = t0 > Epsilon ? t0 : t1;
		//ray.hit = shared_from_this();
		return true;
	}
	
	
private:
	Vec3f m_origin;	///< Position of the center of the sphere
	float m_radius;	///< Radius of the sphere
};

