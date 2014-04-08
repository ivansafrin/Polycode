varying vec3 normal;
varying vec3 worldNormal;
varying vec4 pos;
varying vec4 rawpos;
varying vec4 vertexColor;

uniform mat4 modelMatrix;

mat3 mat3_emu(mat4 m4) {
  return mat3(
      m4[0][0], m4[0][1], m4[0][2],
      m4[1][0], m4[1][1], m4[1][2],
      m4[2][0], m4[2][1], m4[2][2]);
}

void main() {
	normal = gl_NormalMatrix * gl_Normal;

	mat3 rotN = mat3_emu(modelMatrix);
	worldNormal = rotN * gl_Normal;
	worldNormal = normalize(worldNormal);

	gl_Position = ftransform();
	pos = gl_ModelViewMatrix * gl_Vertex;
	rawpos = gl_Vertex;
    vertexColor = gl_Color;
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
}