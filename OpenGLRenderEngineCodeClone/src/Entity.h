#pragma once

#include "Mesh.h"
#include "Transform.h"
#include "Texture.h"
#include "Material.h"

class Entity
{
public:
	Entity();
	Entity(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, Mesh mesh, Material* material, Texture* texture);

	Transform transform;
	Mesh mesh;
	Texture* texture = nullptr;
	Material* material = nullptr;

	void addMesh(Mesh mesh);
	void addMaterial(Material* material);
	void addTexture(Texture* texture);
	void setTransform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale);

	~Entity();
};

