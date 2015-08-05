varying vec3 normal;
varying vec3 tangent;
varying vec3 binormal;
varying vec4 pos;
varying vec4 vertexColor;
uniform sampler2D diffuse;
uniform sampler2D normal_map;
uniform sampler2D specular_map;

uniform vec4 diffuse_color;
uniform vec4 specular_color;
uniform vec4 ambient_color;
uniform float shininess;


float calculateAttenuation(in int i, in float dist)
{
    return(1.0 / (gl_LightSource[i].constantAttenuation +
                  gl_LightSource[i].linearAttenuation * dist +
                  gl_LightSource[i].quadraticAttenuation * dist * dist));
}

void pointLight(in int i, in vec3 bump, in vec3 normal, in vec3 tangent, in vec3 binormal, in vec4 pos, inout vec4 diffuse, inout vec4 specular) {
	vec4 color = diffuse_color;
	vec4 matspec = specular_color;
	float shininess = shininess;
	vec4 lightspec = gl_LightSource[i].specular;
	vec4 lpos = gl_LightSource[i].position;
	
	vec3 tmpVec = lpos.xyz - pos.xyz;	
	lpos.x = dot(tmpVec, tangent);
	lpos.y = dot(tmpVec, binormal);
	lpos.z = dot(tmpVec, normal);	
	
	float distSqr = dot(lpos.xyz, lpos.xyz);
	vec3 lVec = lpos.xyz * inversesqrt(distSqr);
	
	tmpVec = -pos.xyz;
	vec3 v;
	v.x = dot(tmpVec, tangent);
	v.y = dot(tmpVec, binormal);
	v.z = dot(tmpVec, normal);	
	
	v = normalize(v);

	float nDotL = dot(lVec, bump);
	if(nDotL > 0.0) {
		float dist = length(lpos.xyz);    
		float attenuation = calculateAttenuation(i, dist);

		diffuse  += color * max(0.0, nDotL) * gl_LightSource[i].diffuse * attenuation;

	  if (shininess != 0.0) {
    	specular += lightspec * matspec * pow(clamp(dot(reflect(-lVec, bump), v),0.0,1.0), shininess) * attenuation;
	  }
	}
}


void spotLight(in int i, in vec3 bump, in vec3 normal, in vec3 tangent, in vec3 binormal, in vec4 pos, inout vec4 diffuse, inout vec4 specular) {
	vec4 color = diffuse_color;
	vec4 matspec = specular_color;
	float shininess = shininess;
	vec4 lightspec = gl_LightSource[i].specular;
	vec4 lpos = gl_LightSource[i].position;
	
	vec3 tmpVec = lpos.xyz - pos.xyz;	
	lpos.x = dot(tmpVec, tangent);
	lpos.y = dot(tmpVec, binormal);
	lpos.z = dot(tmpVec, normal);	
	
	float distSqr = dot(lpos.xyz, lpos.xyz);
	vec3 lVec = lpos.xyz * inversesqrt(distSqr);
	
	tmpVec = -pos.xyz;
	vec3 v;
	v.x = dot(tmpVec, tangent);
	v.y = dot(tmpVec, binormal);
	v.z = dot(tmpVec, normal);	
	
	v = normalize(v);
	
	tmpVec = gl_LightSource[i].spotDirection.xyz;
	vec3 lDir;
	lDir.x = dot(tmpVec, tangent);
	lDir.y = dot(tmpVec, binormal);
	lDir.z = dot(tmpVec, normal);	
	
	lDir = normalize(lDir);

	
	float cos_outer_cone_angle = (1.0-gl_LightSource[i].spotExponent) * gl_LightSource[i].spotCosCutoff;
	float cos_cur_angle = dot(-lDir, lVec);
	float cos_inner_cone_angle = gl_LightSource[i].spotCosCutoff;

	float cos_inner_minus_outer_angle = cos_inner_cone_angle - cos_outer_cone_angle;
	float spot = clamp((cos_cur_angle - cos_outer_cone_angle) / cos_inner_minus_outer_angle, 0.0, 1.0);
	       	

	float nDotL = dot(lVec, bump);
	if(nDotL > 0.0) {
		float dist = length(lpos.xyz);    
		float attenuation = calculateAttenuation(i, dist);

		diffuse  += color * max(0.0, nDotL) * gl_LightSource[i].diffuse * attenuation * spot;

	  if (shininess != 0.0) {
    	specular += lightspec * matspec * pow(clamp(dot(reflect(-lVec, bump), v),0.0,1.0), shininess) * attenuation * spot;
	  }
	}}

void doLights(in int numLights, in vec3 bump, in vec3 normal, in vec3 tangent, in vec3 binormal, in vec4 pos, inout vec4 diffuse, inout vec4 specular) {
	for (int i = 0; i < numLights; i++) {
		if (gl_LightSource[i].spotCutoff == 180.0) {
			pointLight(i, bump, normal, tangent, binormal, pos, diffuse, specular);
		} else {
			spotLight(i, bump, normal, tangent, binormal, pos, diffuse, specular);
		}
    }
}


void main()
{
	vec4 diffuse_val  = vec4(0.0);
	vec4 specular_val = vec4(0.0);
	
	vec3 bump = normalize( texture2D(normal_map, gl_TexCoord[0].st).xyz * 2.0 - 1.0);
		
	doLights(6, bump, normal, tangent, binormal, pos, diffuse_val, specular_val);
	
	specular_val.xyz *= texture2D(specular_map, gl_TexCoord[0].st).xyz * gl_FrontMaterial.specular.a;
	
	diffuse_val.a = 1.0;
	specular_val.a = 1.0;
		
	vec4 texColor = texture2D(diffuse, gl_TexCoord[0].st);		
		
    vec4 color = (diffuse_val  * texColor * vertexColor) +
                 (specular_val * 1.0)+
                 (ambient_color * texColor * vertexColor);


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
    color.a = diffuse_color.a * texColor.a;	
	gl_FragColor = color;
}
