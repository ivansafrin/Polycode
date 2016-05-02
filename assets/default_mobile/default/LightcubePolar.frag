#ifdef GL_ES
   precision mediump float;
#endif

uniform sampler2D polarMap;
uniform sampler2D diffuse;
uniform vec4 entityColor;

varying vec3 varNormal;
varying vec3 worldNormal;
varying vec2 texCoordVar;
uniform float lightFactor;

const float PI = 3.14159265359;

vec2 sphere_map(vec3 n) {
	return vec2(atan(n.z,n.x)/(2.0 * PI), acos(-n.y) / (PI));
}

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
		rr = normalize( worldNormal +7.0*rr );
		rr = rr * sign(dot(worldNormal,rr));
		vec2 vN = sphere_map(rr);

        col += pow( texture2D( polarMap, vN).xyz, vec3(1.0) ) * dot(rr,worldNormal);
	}

	col = col / 32.0 * lightFactor;

	vec4 texColor = texture2D(diffuse, texCoordVar);
    vec4 color = mix(entityColor,texColor, texColor.a);
    color.xyz = color.xyz * col;
	color.a = 1.0;
    gl_FragColor = color;
}