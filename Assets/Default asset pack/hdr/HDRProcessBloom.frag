uniform sampler2D baseTexture;
uniform sampler2D bloomTexture;
uniform float exposure;
uniform float bloomFactor;

void main(void)
{
	float brightMax = 1.0;
	
	vec4 colorBloom = texture2D(bloomTexture, gl_TexCoord[0].st);
	vec4 color = texture2D(baseTexture,gl_TexCoord[0].st);
	
	color += colorBloom * bloomFactor;
//	color = colorBloom * bloomFactor;
	
	float YD = exposure * (exposure/brightMax + 1.0) / (exposure + 1.0);
	gl_FragColor = color * YD;
	gl_FragColor.a = 1.0;
}