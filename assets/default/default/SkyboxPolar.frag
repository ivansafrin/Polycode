#ifdef GLES2
	precision mediump float;
#endif

uniform sampler2D polarMap;
varying vec4 vertexColor;
varying vec3 normal;
uniform vec4 ambient_color;
varying vec3 worldNormal;

const float PI = 3.14159265359;

vec2 sphere_map(vec3 n) {
	return vec2(atan(n.z,n.x)/(2.0 * PI), acos(-n.y) / (PI));
}

void main()
{
	
	vec2 vN = sphere_map(worldNormal);

    vec4 texColor = texture2D(polarMap, vN);

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