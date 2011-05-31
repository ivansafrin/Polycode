varying vec3 normal;
varying vec3 vertex;
varying vec4 vertexColor;
varying vec4 ShadowCoord0;
varying vec4 ShadowCoord1;
uniform mat4 shadowMatrix0;
uniform mat4 shadowMatrix1;

void main()
{
    gl_TexCoord[0] = gl_MultiTexCoord0;		
    normal = normalize(gl_NormalMatrix * gl_Normal);   
    vec4 v = gl_ModelViewMatrix * gl_Vertex;
    vertex = vec3(v);     
    
	ShadowCoord0 = shadowMatrix0 * gl_Vertex;	
	ShadowCoord1 = shadowMatrix1 * gl_Vertex;	
		    
    
    vertexColor = gl_Color;
    gl_Position = ftransform();
}