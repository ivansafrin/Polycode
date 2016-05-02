#ifdef GL_ES
	precision mediump float;
#endif

attribute lowp vec4 position;
attribute lowp vec3 normal;
attribute lowp vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

varying lowp vec2 texCoordVar;
varying lowp vec3 varNormal;
varying lowp vec4 varPosition;

mat3 mat3_emu(mat4 m4) {
  return mat3(
      m4[0][0], m4[0][1], m4[0][2],
      m4[1][0], m4[1][1], m4[1][2],
      m4[2][0], m4[2][1], m4[2][2]);
}

void main()
{
	mat4 modelViewMatrix = viewMatrix * modelMatrix;
	lowp vec4 p = modelViewMatrix  * position;

	lowp mat3 rotN = mat3_emu(modelViewMatrix);
	varNormal = normalize(rotN * normal);

	varPosition = modelViewMatrix  * position;
	gl_Position = projectionMatrix * p;

	texCoordVar = texCoord;
}