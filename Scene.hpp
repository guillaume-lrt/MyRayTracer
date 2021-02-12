#pragma once

// #include "utils.hpp"
#include "camera.hpp"
#include "Mesh.hpp"

using namespace std;

class Light {
	public:
		inline Light (const Vec3f &position = {2.f,2.f,2.f}, const Vec3f &color = {1.f,1.f,1.f}, const float &intensity = pow(10,5)):
			m_position(position),
			m_color(color),
			m_intensity(intensity){}

		inline ~Light(){}

		inline const Vec3f& position() const { return m_position; }
		inline Vec3f& position() { return m_position; }

		inline const Vec3f& color() const { return m_color; }
		inline Vec3f& color() { return m_color; }

		inline const float& intensity() const { return m_intensity; }
		inline float& intensity() { return m_intensity; }

	private:
		Vec3f m_position;
		Vec3f m_color;
		float m_intensity;
};

class Scene {
public:
	inline Scene () {}
	virtual ~Scene() {}

	inline const Light& light() const { return m_light; }
	inline Light& light() { return m_light; }

	inline const Camera& camera() const { return m_camera; }
	inline Camera& camera() { return m_camera; }
	
	inline const std::vector<Mesh> & meshes () const { return m_meshes;  }
	inline std::vector<Mesh> & meshes () { return m_meshes; }

private:
	Light m_light; 
	Camera m_camera;
	std::vector<Mesh> m_meshes;
};