#ifdef GLES2
	precision mediump float;
#endif

uniform vec4 wireframeColor;

void main() {
	gl_FragColor = wireframeColor;
}