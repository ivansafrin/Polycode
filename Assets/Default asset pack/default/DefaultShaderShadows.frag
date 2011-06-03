uniform sampler2D diffuse;
uniform sampler2D shadowMap0;
uniform sampler2D shadowMap1;
varying vec3 normal;
varying vec3 vertex;
varying vec4 vertexColor;
varying vec4 ShadowCoord0;
varying vec4 ShadowCoord1;
uniform mat4 shadowMatrix0;
uniform mat4 shadowMatrix1;




float calculateAttenuation(in int i, in float dist)
{
    return(1.0 / (gl_LightSource[i].constantAttenuation +
                  gl_LightSource[i].linearAttenuation * dist +
                  gl_LightSource[i].quadraticAttenuation * dist * dist));
}

void pointLight(in int i, in vec3 N, in vec3 V, in float shininess,
                inout vec4 ambient, inout vec4 diffuse, inout vec4 specular)
{
    vec3 D = gl_LightSource[i].position.xyz - V;
    vec3 L = normalize(D);

    float dist = length(D);
    float attenuation = calculateAttenuation(i, dist);

    float nDotL = dot(N,L);

    if (nDotL > 0.0)
    {   
        vec3 E = normalize(-V);
        vec3 R = reflect(-L, N);
       
        float pf = pow(max(dot(R,E), 0.0), shininess);

        diffuse  += gl_LightSource[i].diffuse  * attenuation * nDotL;
        specular += gl_LightSource[i].specular * attenuation * pf;
    }
   
    ambient  += gl_LightSource[i].ambient * attenuation;
}

void spotLight(in int i, in vec3 N, in vec3 V, in float shininess,
               inout vec4 ambient, inout vec4 diffuse, inout vec4 specular, sampler2D shadowMap, vec4 ShadowCoord)
{
	
	vec4 shadowCoordinateWdivide = ShadowCoord / ShadowCoord.w;
	shadowCoordinateWdivide.z -= 0.000000005;
	float distanceFromLight = texture2D(shadowMap,shadowCoordinateWdivide.st).z;
	float shadow = 1.0;
	if (ShadowCoord.w > 0.0)
		shadow = distanceFromLight < shadowCoordinateWdivide.z ? 0.0 : 1.0 ;
	
    vec3 D = gl_LightSource[i].position.xyz - V;
    vec3 L = normalize(D);

    float dist = length(D);
    float attenuation = calculateAttenuation(i, dist);

    float nDotL = dot(N,L);

    if (nDotL > 0.0)
    {   
        float spotEffect = dot(normalize(gl_LightSource[i].spotDirection), -L);
       
        if (spotEffect > gl_LightSource[i].spotCosCutoff)
        {
            attenuation *=  pow(spotEffect, gl_LightSource[i].spotExponent);

            vec3 E = normalize(-V);
            vec3 R = reflect(-L, N);
       
            float pf = pow(max(dot(R,E), 0.0), shininess);

            diffuse  += gl_LightSource[i].diffuse  * attenuation * nDotL * shadow;
            specular += gl_LightSource[i].specular * attenuation * pf * shadow;
        }
    }
   
    ambient  += gl_LightSource[i].ambient * attenuation;
}

void calculateLighting(in int numLights, in vec3 N, in vec3 V, in float shininess,
                       inout vec4 ambient, inout vec4 diffuse, inout vec4 specular)
{
	int spot = 0;
    // Just loop through each light, and if its enabled add
    // its contributions to the color of the pixel.
    for (int i = 0; i < numLights; i++)
    {
		if (gl_LightSource[i].spotCutoff == 180.0)
                pointLight(i, N, V, shininess, ambient, diffuse, specular);
            else {
            	if(spot == 0) {
                 spotLight(i, N, V, shininess, ambient, diffuse, specular, shadowMap0, ShadowCoord0);            		
                 spot = 1;
            	} else {
                 spotLight(i, N, V, shininess, ambient, diffuse, specular, shadowMap1, ShadowCoord1);
            	}
            }

    }
}



void main()
{
  vec3 n = normalize(normal);
   
    vec4 ambient_c  = vec4(0.0);
    vec4 diffuse_c  = vec4(0.0);
    vec4 specular_c = vec4(0.0);

    calculateLighting(6, n, vertex, gl_FrontMaterial.shininess, ambient_c, diffuse_c, specular_c);
   
	vec4 texColor = texture2D(diffuse, gl_TexCoord[0].st);
    
    vec4 color = gl_FrontLightModelProduct.sceneColor  +
                 (ambient_c  * 1.0) +
                 (diffuse_c  * 1.0) +
                 (specular_c * 1.0);
	color.a = 1.0;				 
    color = clamp(color*texColor*vertexColor, 0.0, 1.0);
    gl_FragColor = color;

}