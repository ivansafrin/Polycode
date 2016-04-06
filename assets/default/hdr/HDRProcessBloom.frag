uniform sampler2D baseTexture;
uniform sampler2D bloomTexture;
uniform float exposure;
uniform float bloomFactor;
varying vec2 texCoordVar;

void main(void)
{
	float brightMax = 1.0;
	
	vec4 colorBloom = texture2D(bloomTexture, texCoordVar);
	vec4 color = texture2D(baseTexture, texCoordVar);

	float YD = exposure * (exposure/brightMax + 1.0) / (exposure + 1.0);
	color *= YD;
	
	color += colorBloom * bloomFactor;
	
	gl_FragColor = color;
	gl_FragColor.a = 1.0;
}