uniform sampler2D screenColorBuffer;
uniform float exposure;
 
void main(void)
{
	float bright_threshold = 1.0;
	
	vec4 color =  texture2D(screenColorBuffer,gl_TexCoord[0].st);
	float lum = dot(vec4(0.30, 0.59, 0.11, 0.0), color);
    if (lum > bright_threshold)
        gl_FragColor = color;
    else
        gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);		
}