varying vec3 normal;
varying vec3 tangent;
varying vec3 binormal;
varying vec4 pos;
varying vec4 rawpos;
varying vec4 vertexColor;
attribute vec3 vTangent;

void main() {
	normal = normalize(gl_NormalMatrix * gl_Normal);
	tangent = normalize(gl_NormalMatrix * vTangent); 
	binormal = normalize(cross(normal, tangent));
	gl_Position = ftransform();
	pos = gl_ModelViewMatrix * gl_Vertex;
	rawpos = gl_Vertex;
    vertexColor = gl_Color;
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
}