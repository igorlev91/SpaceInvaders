#pragma once

#include <ios>
#include <string>
#include <glm/glm.hpp>

namespace Console
{
	void Print(const glm::vec3& Vector);
}

namespace Math
{
	float Clamp(const float Value, const float Min, const float Max);
	float Lerp(const float Min, const float Max, const float Ratio);
}

namespace Colors
{
	const glm::vec4 White(1.f, 1.f, 1.f, 1.f);
	const glm::vec4 Black(0.f, 0.f, 0.f, 1.f);
	const glm::vec4 Red(1.f, 0.f, 0.f, 1.f);
	const glm::vec4 Green(0.f, 1.f, 0.f, 1.f);
	const glm::vec4 LightBlack(0.14f, 0.15f, 0.15f, 1.f);
}

namespace File
{
	bool Exists(const std::string& FilePath);
	void Create(const std::string& FilePath, std::ios_base::openmode Mode);
	void WriteAll(const std::string& FilePath, const std::string& FileContent);
	std::string ReadAll(const std::string& FilePath);
}

struct Transform
{
	glm::vec3 Location;
	glm::vec3 Size;

	Transform();
	Transform(const glm::vec3& InLocation, const glm::vec3& InSize);
};

struct BoundingBox
{
	Transform mTransform;
	glm::vec2 ScaleOffset;

	BoundingBox(const Transform& InTransform);
	float Top() const;
	float Bottom() const;
	float Right() const;
	float Left() const;
};

struct CollisionResult
{
	bool bHit;
	glm::vec3 ImpactLocation;
};
