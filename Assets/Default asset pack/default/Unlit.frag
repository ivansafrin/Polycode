uniform sampler2D diffuse;
varying vec2 texCoordVar;

void main() {
	gl_FragColor = texture2D(diffuse, texCoordVar);
}