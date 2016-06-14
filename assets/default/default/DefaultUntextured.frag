#ifdef GL_ES
	precision mediump float;
#endif

varying vec2 texCoordVar;
varying vec3 varNormal;
varying vec4 varPosition;

uniform vec4 diffuse_color;
uniform vec4 specular_color;
uniform float shininess;

#define MAX_LIGHTS 8

struct LightInfo {
	vec3 position;
	vec3 direction;
	vec4 specular;
	vec4 diffuse;

	float spotExponent;
	float spotCosCutoff;

	float constantAttenuation;
	float linearAttenuation;	
	float quadraticAttenuation;
};

uniform LightInfo lights[MAX_LIGHTS];

float calculateAttenuation(in int i, in float dist)
{
    return(1.0 / (lights[i].constantAttenuation +
                  lights[i].linearAttenuation * dist +
                  lights[i].quadraticAttenuation * dist * dist));
}

void pointLight(in int i, in vec3 normal, in vec4 pos, inout vec4 diffuse, inout vec4 specular) {
	vec4 color = diffuse_color;
	vec4 matspec = specular_color;
	float shininess = shininess;
	vec4 lightspec = lights[i].specular;
	vec4 lpos = vec4(lights[i].position, 1.0);
	vec4 s = pos-lpos; 
	vec4 sn = -normalize(s);
	
	vec3 light = sn.xyz;
	vec3 n = normalize(normal);
	vec3 r = -reflect(light, n);
	r = normalize(r);
	vec3 v = -pos.xyz;
	v = normalize(v);

	float nDotL = dot(n, sn.xyz);
	if(nDotL > 0.0) {
		float dist = length(s);    
		float attenuation = calculateAttenuation(i, dist);

		diffuse  += color * max(0.0, nDotL) * lights[i].diffuse * attenuation;

	  if (shininess != 0.0) {
    	specular += lightspec * matspec * pow(max(0.0,dot(r, v)), shininess) * attenuation;
	  }
	}
}


void spotLight(in int i, in vec3 normal, in vec4 pos, inout vec4 diffuse, inout vec4 specular) {
	vec4 color = diffuse_color;
	vec4 matspec = specular_color;
	float shininess = shininess;
	vec4 lightspec = lights[i].specular;
	vec4 lpos = vec4(lights[i].position, 1.0);
	vec4 s = pos-lpos; 
	vec4 sn = -normalize(s);

	vec3 light = sn.xyz;
	vec3 n = normalize(normal);
	vec3 r = -reflect(light, n);
	r = normalize(r);
	vec3 v = -pos.xyz;
	v = normalize(v);

	float cos_outer_cone_angle = (1.0-lights[i].spotExponent) * lights[i].spotCosCutoff;
	float cos_cur_angle = dot(-normalize(lights[i].direction), sn.xyz);
	float cos_inner_cone_angle = lights[i].spotCosCutoff;

	float cos_inner_minus_outer_angle = cos_inner_cone_angle - cos_outer_cone_angle;
	float spot = 0.0;
	spot = clamp((cos_cur_angle - cos_outer_cone_angle) / cos_inner_minus_outer_angle, 0.0, 1.0);
	       
	float nDotL = dot(n, sn.xyz);
	if(nDotL > 0.0) {
		float dist = length(s);    
		float attenuation = calculateAttenuation(i, dist);
		diffuse  += color * max(0.0, nDotL) * lights[i].diffuse * attenuation * spot;

	  if (shininess != 0.0) {
    	specular += lightspec * matspec * pow(max(0.0,dot(r, v)), shininess) * attenuation * spot;
	  }
	}
}

void doLights(in int numLights, in vec3 normal, in vec4 pos, inout vec4 diffuse, inout vec4 specular) {
	for (int i = 0; i < numLights; i++) {
		if (lights[i].spotCosCutoff == 180.0) {
			pointLight(i, normal, pos, diffuse, specular);
		} else {
			spotLight(i, normal, pos, diffuse, specular);
		}
    }
}


void main()
{
	vec4 diffuse_val  = vec4(0.0);
	vec4 specular_val = vec4(0.0);

	doLights(MAX_LIGHTS, varNormal, varPosition, diffuse_val, specular_val);
			
    vec4 color = diffuse_val; 	           
    color = clamp((color) + specular_val, 0.0, 1.0);  

	color.a = diffuse_color.a;	
	gl_FragColor = color;

}
