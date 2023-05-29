#include "Entity.h"

Entity::Entity()
{

}

Entity::Entity(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale, Mesh mesh, Material* material, Texture* texture)
{
	transform = Transform(pos, rot, scale);
	this->mesh = mesh;
	this->material = material;
	this->texture = texture;
}

void Entity::addMesh(Mesh mesh)
{
	this->mesh = mesh;
}

void Entity::addMaterial(Material* material)
{
	this->material = material;
}

void Entity::addTexture(Texture* texture)
{
	this->texture = texture;
}

void Entity::setTransform(glm::vec3 pos, glm::vec3 rot, glm::vec3 scale)
{
	transform = Transform(pos, rot, scale);
}

Entity::~Entity()
{
}
