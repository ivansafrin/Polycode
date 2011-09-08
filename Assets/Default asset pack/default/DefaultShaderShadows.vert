varying vec3 normal;
varying vec4 pos;
varying vec4 rawpos;
varying vec4 vertexColor;
varying vec4 ShadowCoord0;
varying vec4 ShadowCoord1;
uniform mat4 shadowMatrix0;
uniform mat4 shadowMatrix1;
uniform mat4 modelMatrix;

void main() {
	normal = gl_NormalMatrix * gl_Normal;
	gl_Position = ftransform();
	pos = gl_ModelViewMatrix * gl_Vertex;
	rawpos = gl_Vertex;
	
	ShadowCoord0 = shadowMatrix0 * modelMatrix * gl_Vertex;	
	ShadowCoord1 = shadowMatrix1 * modelMatrix * gl_Vertex;		
			
    vertexColor = gl_Color;
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;
}