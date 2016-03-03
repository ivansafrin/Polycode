uniform sampler2D screenColorBuffer;
uniform float exposure;
varying vec2 texCoordVar;

void main(void)
{
	float brightMax = 1.0;
	float YD = exposure * (exposure/brightMax + 1.0) / (exposure + 1.0);
	gl_FragColor = texture2D(screenColorBuffer, texCoordVar) * YD;
	gl_FragColor.a = 1.0;
}