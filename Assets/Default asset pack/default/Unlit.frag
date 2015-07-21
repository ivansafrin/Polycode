uniform sampler2D texture;
uniform vec2 scroll;

varying vec2 texCoordVar;

void main() {
	gl_FragColor = texture2D( texture, texCoordVar + scroll);
}