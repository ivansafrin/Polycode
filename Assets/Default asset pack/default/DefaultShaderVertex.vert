uniform float shininess;
uniform vec4 diffuse_color;
uniform vec4 specular_color;
uniform vec4 ambient_color;

float calculateAttenuation(in int i, in float dist)
{
    return(1.0 / (gl_LightSource[i].constantAttenuation +
                  gl_LightSource[i].linearAttenuation * dist +
                  gl_LightSource[i].quadraticAttenuation * dist * dist));
}

void pointLight(in int i, in vec3 normal, in vec4 pos, inout vec4 diffuse, inout vec4 specular) {
	vec4 color = diffuse_color;
	vec4 matspec = specular_color;
	float shininess = shininess;
	vec4 lightspec = gl_LightSource[i].specular;
	vec4 lpos = gl_LightSource[i].position;
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

		diffuse  += color * max(0.0, nDotL) * gl_LightSource[i].diffuse * attenuation;

	  if (shininess != 0.0) {
    	specular += lightspec * matspec * pow(max(0.0,dot(r, v)), shininess) * attenuation;
	  }
	}
}


void spotLight(in int i, in vec3 normal, in vec4 pos, inout vec4 diffuse, inout vec4 specular) {
	vec4 color = diffuse_color;
	vec4 matspec = specular_color;
	float shininess = shininess;
	vec4 lightspec = gl_LightSource[i].specular;
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

	float nDotL = dot(n, sn.xyz);
	if(nDotL > 0.0) {
		float dist = length(s);    
		float attenuation = calculateAttenuation(i, dist);
		diffuse  += color * max(0.0, nDotL) * gl_LightSource[i].diffuse * attenuation * spot;

	  if (shininess != 0.0) {
    	specular += lightspec * matspec * pow(max(0.0,dot(r, v)), shininess) * attenuation * spot;
	  }
	}
}

void doLights(in int numLights, in vec3 normal, in vec4 pos, inout vec4 diffuse, inout vec4 specular) {
	for (int i = 0; i < numLights; i++) {
		if (gl_LightSource[i].spotCutoff == 180.0) {
			pointLight(i, normal, pos, diffuse, specular);
		} else {
			spotLight(i, normal, pos, diffuse, specular);
		}
    }
}

varying vec4 vertexColor;
varying vec4 specularColor;

void main() {
	vec3 normal = gl_NormalMatrix * gl_Normal;
	gl_Position = ftransform();
	vec4 pos = gl_ModelViewMatrix * gl_Vertex;
	vec4 rawpos = gl_Vertex;
    vertexColor = gl_Color;
	gl_TexCoord[0] = gl_TextureMatrix[0] * gl_MultiTexCoord0;

	vec4 diffuse_val  = vec4(0.0);
	vec4 specular_val = vec4(0.0);
	doLights(6, normal, pos, diffuse_val, specular_val);
	
    vec4 color = diffuse_val +
                 ambient_color;
	
	color.a = diffuse_color.a; 
	specularColor = specular_val;
	
    vertexColor = clamp(color*vertexColor, 0.0, 1.0);  	
}