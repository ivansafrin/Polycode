uniform sampler2D screenColorBuffer;
uniform vec4 scale;
uniform vec4 bias;

varying vec2 texCoordVar;

void main(void) {	
	gl_FragColor = max(vec4(0.0), texture2D(screenColorBuffer, texCoordVar) - bias) * scale;
}