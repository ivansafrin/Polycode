uniform sampler2D screenColorBuffer;
uniform float exposure;

void main(void)
{
	float brightMax = 1.0;
	float YD = exposure * (exposure/brightMax + 1.0) / (exposure + 1.0);
	gl_FragColor = texture2D(screenColorBuffer,gl_TexCoord[0].st) * YD;
	gl_FragColor.a = 1.0;
}