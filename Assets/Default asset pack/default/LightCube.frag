uniform samplerCube lightCube;
varying vec4 vertexColor;
varying vec3 normal;

void main()
{
    vec4 texColor = textureCube(lightCube, normal);
    gl_FragColor = texColor*vertexColor;
}