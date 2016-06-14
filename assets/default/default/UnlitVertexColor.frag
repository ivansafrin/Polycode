#ifdef GL_ES
	precision mediump float;
#endif

uniform sampler2D diffuse;
uniform vec4 entityColor;
varying vec2 texCoordVar;
varying vec4 varColor;

void main() {
	gl_FragColor = texture2D(diffuse, texCoordVar) * entityColor * varColor;
}