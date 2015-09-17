uniform vec4 entityColor;
varying vec2 texCoordVar;
varying vec3 varNormal;
varying vec4 varPosition;

uniform mat4 viewMatrix;

mat3 mat3_emu(mat4 m4) {
  return mat3(
      m4[0][0], m4[0][1], m4[0][2],
      m4[1][0], m4[1][1], m4[1][2],
      m4[2][0], m4[2][1], m4[2][2]);
}

void main()
{

	mat3 rotN = mat3_emu(viewMatrix);
	vec3 viewNormal = normalize(rotN * varNormal);

	if(dot((viewMatrix * varPosition).xyz * -1.0, viewNormal) < 0.0) {
		gl_FragColor = vec4(0.0 ,0.0, 0.0, 0.2);
	} else {
		gl_FragColor = entityColor;
	}	
    
}