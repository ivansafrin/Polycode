#ifdef GLES2
	precision mediump float;
#endif

uniform vec4 entityColor;

void main() {
	gl_FragColor = entityColor;
}