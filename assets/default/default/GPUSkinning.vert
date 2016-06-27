#ifdef GL_ES
	precision mediump float;
#endif

#define MAX_JOINT_COUNT 64

attribute vec4 position;
attribute vec3 normal;
attribute vec2 texCoord;
attribute vec4 boneIndices;
attribute vec4 boneWeights;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform mat4 skeletonMatrix[MAX_JOINT_COUNT];

varying vec2 texCoordVar;
varying vec3 varNormal;
varying vec4 varPosition;

mat3 mat3_emu(mat4 m4) {
  return mat3(
      m4[0][0], m4[0][1], m4[0][2],
      m4[1][0], m4[1][1], m4[1][2],
      m4[2][0], m4[2][1], m4[2][2]);
}

void jointInfluence(in mat4 joint_matrix, in float weight, in vec4 position, inout vec4 outPosition, in vec3 normal, inout vec3 outNormal)
{
  outPosition += weight * (joint_matrix * position);

  mat3 normalMatrix = mat3_emu(joint_matrix);
  outNormal += weight * (normalMatrix * normal);
}

void main() {

	vec4 outVert = vec4(0.0, 0.0, 0.0, 0.0);
	vec3 outNormal = vec3(0.0, 0.0, 0.0);

	jointInfluence(skeletonMatrix[int(boneIndices.x)], boneWeights.x, position, outVert, normal, outNormal);
    jointInfluence(skeletonMatrix[int(boneIndices.y)], boneWeights.y, position, outVert, normal, outNormal);
    jointInfluence(skeletonMatrix[int(boneIndices.z)], boneWeights.z, position, outVert, normal, outNormal);
    jointInfluence(skeletonMatrix[int(boneIndices.w)], boneWeights.w, position, outVert, normal, outNormal);

	outVert.w = 1.0;

	mat4 modelViewMatrix = viewMatrix * modelMatrix;
	vec4 p = modelViewMatrix  * outVert;

	mat3 rotN = mat3_emu(modelViewMatrix);
	varNormal = normalize(rotN * normalize(outNormal));

	varPosition = modelViewMatrix  * outVert;
	gl_Position = projectionMatrix * p;

	texCoordVar = texCoord;
}