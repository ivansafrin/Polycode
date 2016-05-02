#ifdef GL_ES
	precision mediump float;
#endif

uniform vec4 entityColor;

void main() {
	gl_FragColor = entityColor;
}