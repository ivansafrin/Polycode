uniform sampler2D screenColorBuffer;
uniform float brightThreshold;
varying vec2 texCoordVar;

void main(void)
{	
	vec4 color =  texture2D(screenColorBuffer, texCoordVar);
	float lum = dot(vec4(0.30, 0.59, 0.11, 0.0), color);

    if (lum > brightThreshold)
        gl_FragColor = color;
    else
        gl_FragColor = vec4(0.0, 0.0, 0.0, 1.0);		


}