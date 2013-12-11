varying vec3 normal;
varying vec4 pos;
varying vec4 vertexColor;
uniform sampler2D diffuse;

uniform vec4 diffuse_color;
uniform vec4 ambient_color;


float calculateAttenuation(in int i, in float dist)
{
    return(1.0 / (gl_LightSource[i].constantAttenuation +
                  gl_LightSource[i].linearAttenuation * dist +
                  gl_LightSource[i].quadraticAttenuation * dist * dist));
}

void pointLight(in int i, in vec3 normal, in vec4 pos, inout vec4 diffuse) {
	vec4 color = diffuse_color;
	vec4 lpos = gl_LightSource[i].position;
	vec4 s = pos-lpos; 
	vec4 sn = -normalize(s);
	
	vec3 light = sn.xyz;
	vec3 n = normalize(normal);
	vec3 r = -reflect(light, n);
	r = normalize(r);
	vec3 v = -pos.xyz;
	v = normalize(v);

	float nDotL = 1.0;
		float dist = length(s);    
		float attenuation = calculateAttenuation(i, dist);

		diffuse  += color * max(0.0, nDotL) * gl_LightSource[i].diffuse * attenuation;
}


void spotLight(in int i, in vec3 normal, in vec4 pos, inout vec4 diffuse) {
	vec4 color = diffuse_color;
	vec4 lpos = gl_LightSource[i].position;
	vec4 s = pos-lpos; 
	vec4 sn = -normalize(s);

	vec3 light = sn.xyz;
	vec3 n = normalize(normal);
	vec3 r = -reflect(light, n);
	r = normalize(r);
	vec3 v = -pos.xyz;
	v = normalize(v);

	float cos_outer_cone_angle = (1.0-gl_LightSource[i].spotExponent) * gl_LightSource[i].spotCosCutoff;
	float cos_cur_angle = dot(-normalize(gl_LightSource[i].spotDirection), sn.xyz);
	float cos_inner_cone_angle = gl_LightSource[i].spotCosCutoff;

	float cos_inner_minus_outer_angle = cos_inner_cone_angle - cos_outer_cone_angle;
	float spot = 0.0;
	spot = clamp((cos_cur_angle - cos_outer_cone_angle) / cos_inner_minus_outer_angle, 0.0, 1.0);
	       
	float nDotL = 1.0;
		float dist = length(s);    
		float attenuation = calculateAttenuation(i, dist);
		diffuse  += color * max(0.0, nDotL) * gl_LightSource[i].diffuse * attenuation * spot;

}

void doLights(in int numLights, in vec3 normal, in vec4 pos, inout vec4 diffuse) {
	for (int i = 0; i < numLights; i++) {
		if (gl_LightSource[i].spotCutoff == 180.0) {
			pointLight(i, normal, pos, diffuse);
		} else {
			spotLight(i, normal, pos, diffuse);
		}
    }
}


void main()
{
	vec4 diffuse_val  = vec4(0.0);
	doLights(6, normal, pos, diffuse_val);
		
	vec4 texColor = texture2D(diffuse, gl_TexCoord[0].st);		
		
    vec4 color = diffuse_val + ambient_color;	
    color = clamp(color*vertexColor*texColor, 0.0, 1.0);	

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
	color.a = diffuse_color.a * texColor.a * vertexColor.a;  	
	gl_FragColor = color;

}
