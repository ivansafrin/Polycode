#ifdef GLES2
	precision mediump float;
#endif

attribute vec4 position;
attribute vec2 texCoord;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
varying vec2 texCoordVar;

void main()
{
	vec4 p = viewMatrix * modelMatrix  * position;
	gl_Position = projectionMatrix * p;
	texCoordVar = texCoord;
}