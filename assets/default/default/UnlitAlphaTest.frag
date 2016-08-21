#ifdef GL_ES
	precision mediump float;
#endif

uniform sampler2D diffuse;
uniform vec4 entityColor;
varying vec2 texCoordVar;

void main() {
	vec4 color = texture2D(diffuse, texCoordVar) * entityColor;
	if(color.a < 0.001) {
		discard;
	}
	gl_FragColor = color;
}