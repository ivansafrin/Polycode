#ifdef GLES2
	precision mediump float;
#endif

attribute vec4 position;
uniform float pointSize;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
	vec4 p = viewMatrix * modelMatrix  * position;
	gl_Position = projectionMatrix * p;
	gl_PointSize = pointSize;
}