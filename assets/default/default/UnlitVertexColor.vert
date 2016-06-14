#ifdef GL_ES
	precision mediump float;
#endif

attribute vec4 position;
attribute vec2 texCoord;
attribute vec4 color;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
varying vec2 texCoordVar;
varying vec4 varColor;

void main()
{
	vec4 p = viewMatrix * modelMatrix  * position;
	gl_Position = projectionMatrix * p;
	varColor = color;
	texCoordVar = texCoord;
}