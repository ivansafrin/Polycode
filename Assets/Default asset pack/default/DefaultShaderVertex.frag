uniform sampler2D diffuse;
varying vec4 vertexColor;
varying vec4 specularColor;

void main()
{
	vec4 texColor = texture2D(diffuse, gl_TexCoord[0].st);	
    vec4 color = (texColor*vertexColor) + specularColor;    

    
    // fog
	const float LOG2 = 1.442695;
	float z = gl_FragCoord.z / gl_FragCoord.w;
	float fogFactor = exp2( -gl_Fog.density * 
				   gl_Fog.density * 
				   z * 
				   z * 
				   LOG2 );

	fogFactor = clamp(fogFactor, 0.0, 1.0);
	
	color = mix(gl_Fog.color, color, fogFactor );  
    color.a = vertexColor.a * texColor.a;	
	gl_FragColor = color;
    
}