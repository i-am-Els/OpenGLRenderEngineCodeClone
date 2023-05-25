#version 330

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 tex;
layout (location = 2) in vec3 norm; // normal to the surface

out vec4 vCol;
out vec2 TexCoord;
out vec3 Normal;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 projection;
uniform mat4 view;

void main()
{
	gl_Position = projection * view * model * vec4(pos, 1.0);
	vCol = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);

	TexCoord = tex;

	Normal = mat3(transpose(inverse(model))) * norm; // since normals dont have transformations or in the very lease, translation doesnt affect normals, we can remove the translation bit
								// of the model matrix which is the last row and since the last column doesnt really seem important to us, we can make the matrix into a 3x3 matrix
								// now scaling or rotating an object will not change the normals, the normals will be pointing in the original direction which is no longer the normal of 
								// the object. To overcome that, you invert the transform process, then transpose it.
	
	FragPos = (model * vec4(pos, 1.0)).xyz; //swizzling

}