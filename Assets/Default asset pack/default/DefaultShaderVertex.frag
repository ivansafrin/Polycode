uniform sampler2D diffuse;
varying vec4 vertexColor;

void main()
{
	vec4 texColor = texture2D(diffuse, gl_TexCoord[0].st);	
    vec4 color = texColor*vertexColor;    
    
    // fog
	const float LOG2 = 1.442695;
	float z = gl_FragCoord.z / gl_FragCoord.w;
	float fogFactor = exp2( -gl_Fog.density * 
				   gl_Fog.density * 
				   z * 
				   z * 
				   LOG2 );

	fogFactor = clamp(fogFactor, 0.0, 1.0);
	gl_FragColor = mix(gl_Fog.color, color, fogFactor );        
    
}