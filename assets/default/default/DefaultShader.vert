#ifdef GLES2
	precision mediump float;
#endif

attribute vec4 position;
attribute vec3 normal;
attribute vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

varying vec2 texCoordVar;
varying vec3 varNormal;
varying vec4 varPosition;

mat3 mat3_emu(mat4 m4) {
  return mat3(
      m4[0][0], m4[0][1], m4[0][2],
      m4[1][0], m4[1][1], m4[1][2],
      m4[2][0], m4[2][1], m4[2][2]);
}

void main()
{
	mat4 modelViewMatrix = viewMatrix * modelMatrix;
	vec4 p = modelViewMatrix  * position;

	mat3 rotN = mat3_emu(modelMatrix);
	varNormal = normalize(rotN * normal);


	varPosition = modelMatrix  * position;
	gl_Position = projectionMatrix * p;

	texCoordVar = texCoord;
}