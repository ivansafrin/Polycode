varying vec3 normal;
varying vec3 vertex;
varying vec4 vertexColor;
void main()
{
    normal = normalize(gl_NormalMatrix * gl_Normal);   
    vertex = vec3(gl_ModelViewMatrix * gl_Vertex);     
   vertexColor = gl_Color;
    gl_Position = ftransform();
}