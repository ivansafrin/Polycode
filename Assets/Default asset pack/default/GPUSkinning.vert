#define MAX_JOINT_COUNT 64

uniform mat4 skeletonMatrix[MAX_JOINT_COUNT];

attribute vec4 vBoneIndices;
attribute vec4 vBoneWeights;

varying vec3 normal;
varying vec4 pos;
varying vec4 rawpos;
varying vec4 vertexColor;


mat3 m3( mat4 m )
{
	mat3 result;

	result[0][0] = m[0][0]; 
	result[0][1] = m[0][1]; 
	result[0][2] = m[0][2]; 


	result[1][0] = m[1][0]; 
	result[1][1] = m[1][1]; 
	result[1][2] = m[1][2]; 

	result[2][0] = m[2][0]; 
	result[2][1] = m[2][1]; 
	result[2][2] = m[2][2]; 

	return result;
}


void jointInfluence(in mat4 joint_matrix, in float weight, in vec4 position, inout vec4 outPosition, in vec3 normal, inout vec3 outNormal)
{
  outPosition += weight * (joint_matrix * position);

  mat3 normalMatrix = m3(joint_matrix);
  outNormal += weight * (normalMatrix * normal);
}

void main() {

	vec4 inVert = gl_Vertex;
	vec4 outVert = vec4(0.0, 0.0, 0.0, 0.0);

	vec3 inNormal = gl_Normal;
	vec3 outNormal = vec3(0.0, 0.0, 0.0);

	jointInfluence(skeletonMatrix[int(vBoneIndices.x)], vBoneWeights.x, inVert, outVert, inNormal, outNormal);
    jointInfluence(skeletonMatrix[int(vBoneIndices.y)], vBoneWeights.y, inVert, outVert, inNormal, outNormal);
    jointInfluence(skeletonMatrix[int(vBoneIndices.z)], vBoneWeights.z, inVert, outVert, inNormal, outNormal);
    jointInfluence(skeletonMatrix[int(vBoneIndices.w)], vBoneWeights.w, inVert, outVert, inNormal, outNormal);


	normal = gl_NormalMatrix * outNormal;	
	gl_Position = gl_ProjectionMatrix * gl_ModelViewMatrix * outVert;
	pos = gl_ModelViewMatrix * outVert;
	rawpos = outVert;
    vertexColor = gl_Color;
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
}