attribute vec4 position;
attribute vec2 texCoord;

uniform mat4 modelView;
uniform mat4 projection;
varying vec2 texCoordVar;

void main()
{
	vec4 p = modelView * position;
	gl_Position = projection * p;
	texCoordVar = texCoord;
}