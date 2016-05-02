#ifdef GL_ES
	precision mediump float;
#endif

uniform vec4 wireframeColor;

void main() {
	gl_FragColor = wireframeColor;
}