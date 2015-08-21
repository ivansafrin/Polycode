#ifdef GLES2
	precision mediump float;
#endif

attribute vec4 position;
attribute vec3 normal;
attribute vec2 texCoord;

varying vec3 varNormal;
varying vec3 worldNormal;
varying vec4 pos;
varying vec4 rawpos;
varying vec4 vertexColor;
varying vec2 texCoordVar;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;


mat3 mat3_emu(mat4 m4) {
  return mat3(
      m4[0][0], m4[0][1], m4[0][2],
      m4[1][0], m4[1][1], m4[1][2],
      m4[2][0], m4[2][1], m4[2][2]);
}

void main() {
	varNormal = normal;

	mat3 rotN = mat3_emu(modelMatrix);
	worldNormal = rotN * normal;
	worldNormal = normalize(worldNormal);

	vec4 p = viewMatrix * modelMatrix  * position;
	gl_Position = projectionMatrix * p;

	pos = viewMatrix * modelMatrix * position;
	rawpos = position;

	texCoordVar = texCoord;

}