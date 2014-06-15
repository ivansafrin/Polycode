uniform samplerCube lightCube;
varying vec4 vertexColor;
varying vec3 normal;
uniform vec4 ambient_color;
varying vec3 worldNormal;

void main()
{
    vec4 texColor = textureCube(lightCube, worldNormal * -1.0);

    vec4 color = vec4(1.0,1.0,1.0,1.0) + ambient_color; 	           
    color = clamp((color*vertexColor*texColor), 0.0, 1.0);  

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