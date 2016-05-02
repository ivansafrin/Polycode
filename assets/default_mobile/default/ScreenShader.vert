#ifdef GL_ES
	precision mediump float;
#endif

attribute vec4 position;
attribute vec2 texCoord;
varying vec2 texCoordVar;

void main()
{
    gl_Position =  position;
    texCoordVar = texCoord;
}