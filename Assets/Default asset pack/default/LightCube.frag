uniform samplerCube lightCube;
varying vec4 vertexColor;
varying vec3 normal;
uniform vec4 ambient_color;
varying vec3 worldNormal;

uniform float lightFactor;

vec3 hash3( float n )
{
    return fract(sin(vec3(n,n+1.0,n+2.0))*vec3(43758.5453123,22578.1459123,19642.3490423));
}

void main()
{
	vec3 col = vec3(0.0);
	for( int i=0; i<32; i++ )
	{			
		vec3 rr = normalize(-1.0 + 2.0*hash3(float(i)*123.5463));
		rr = normalize( worldNormal + 7.0*rr );
		rr = rr * sign(dot(worldNormal,rr));
        col += pow( textureCube( lightCube, rr ).xyz, vec3(2.2) ) * dot(rr,worldNormal);
	}

	col = col * lightFactor;

    vec4 texColor = vec4(col, 1.0);

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