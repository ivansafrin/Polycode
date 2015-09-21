// FXAA shader, GLSL code adapted from:

// http://horde3d.org/wiki/index.php5?title=Shading_Technique_-_FXAA

// Whitepaper describing the technique:

// http://developer.download.nvidia.com/assets/gamedev/files/sdk/11/FXAA_WhitePaper.pdf



uniform sampler2D textureSampler;



// The inverse of the texture dimensions along X and Y


vec3 rgb2hsv(vec3 c)

{

    vec4 K = vec4(0.0, -1.0 / 3.0, 2.0 / 3.0, -1.0);

    vec4 p = mix(vec4(c.bg, K.wz), vec4(c.gb, K.xy), step(c.b, c.g));

    vec4 q = mix(vec4(p.xyw, c.r), vec4(c.r, p.yzx), step(p.x, c.r));



    float d = q.x - min(q.w, q.y);

    float e = 1.0e-10;

    return vec3(abs(q.z + (q.w - q.y) / (6.0 * d + e)), d / (q.x + e), q.x);

}



vec3 hsv2rgb(vec3 c)

{

    vec4 K = vec4(1.0, 2.0 / 3.0, 1.0 / 3.0, 3.0);

    vec3 p = abs(fract(c.xxx + K.xyz) * 6.0 - K.www);

    return c.z * mix(K.xxx, clamp(p - K.xxx, 0.0, 1.0), c.y);

}



void main() {

  // The parameters are hardcoded for now, but could be

  // made into uniforms to control fromt he program.

  float FXAA_SPAN_MAX = 8.0;

  float FXAA_REDUCE_MUL = 1.0/8.0;

  float FXAA_REDUCE_MIN = (1.0/128.0);

  vec2 texcoordOffset = vec2(0.0005, 0.0005);


  vec3 rgbNW = texture2D(textureSampler, gl_TexCoord[0].st + (vec2(-1.0, -1.0) * texcoordOffset)).xyz;

  vec3 rgbNE = texture2D(textureSampler, gl_TexCoord[0].st + (vec2(+1.0, -1.0) * texcoordOffset)).xyz;

  vec3 rgbSW = texture2D(textureSampler, gl_TexCoord[0].st + (vec2(-1.0, +1.0) * texcoordOffset)).xyz;

  vec3 rgbSE = texture2D(textureSampler, gl_TexCoord[0].st + (vec2(+1.0, +1.0) * texcoordOffset)).xyz;

  vec3 rgbM  = texture2D(textureSampler, gl_TexCoord[0].st).xyz;


  vec3 luma = vec3(0.299, 0.587, 0.114);

  float lumaNW = dot(rgbNW, luma);

  float lumaNE = dot(rgbNE, luma);

  float lumaSW = dot(rgbSW, luma);

  float lumaSE = dot(rgbSE, luma);

  float lumaM  = dot( rgbM, luma);


  float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));

  float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));


  vec2 dir;

  dir.x = -((lumaNW + lumaNE) - (lumaSW + lumaSE));

  dir.y =  ((lumaNW + lumaSW) - (lumaNE + lumaSE));


  float dirReduce = max((lumaNW + lumaNE + lumaSW + lumaSE) * (0.25 * FXAA_REDUCE_MUL), FXAA_REDUCE_MIN);

 

  float rcpDirMin = 1.0/(min(abs(dir.x), abs(dir.y)) + dirReduce);


  dir = min(vec2(FXAA_SPAN_MAX,  FXAA_SPAN_MAX), 

        max(vec2(-FXAA_SPAN_MAX, -FXAA_SPAN_MAX), dir * rcpDirMin)) * texcoordOffset;


  vec3 rgbA = (1.0/2.0) * (

              texture2D(textureSampler, gl_TexCoord[0].st + dir * (1.0/3.0 - 0.5)).xyz +

              texture2D(textureSampler, gl_TexCoord[0].st + dir * (2.0/3.0 - 0.5)).xyz);

  vec3 rgbB = rgbA * (1.0/2.0) + (1.0/4.0) * (

              texture2D(textureSampler, gl_TexCoord[0].st + dir * (0.0/3.0 - 0.5)).xyz +

              texture2D(textureSampler, gl_TexCoord[0].st + dir * (3.0/3.0 - 0.5)).xyz);

  float lumaB = dot(rgbB, luma);



  if((lumaB < lumaMin) || (lumaB > lumaMax)){

    gl_FragColor.xyz=rgbA;

  } else {

    gl_FragColor.xyz=rgbB;

  }



  vec3 hsv = rgb2hsv(gl_FragColor.xyz);

  hsv.y += 0.1 * (1.0 - hsv.y);

  gl_FragColor = vec4(hsv2rgb(hsv), texture2D(textureSampler, gl_TexCoord[0].st).a);



}