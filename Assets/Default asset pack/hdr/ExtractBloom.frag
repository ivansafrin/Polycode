uniform sampler2D screenColorBuffer;
uniform float brightThreshold;
 
void main(void)
{	
	vec4 color =  texture2D(screenColorBuffer,gl_TexCoord[0].st);
	float lum = dot(vec4(0.30, 0.59, 0.11, 0.0), color);
    if (lum > brightThreshold)
        gl_FragColor = color;
    else
        gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);		
}