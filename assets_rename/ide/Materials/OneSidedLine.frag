varying vec4 vertexColor;
varying vec3 normal;
varying vec4 pos;

void main()
{
	if(dot(pos.xyz * -1.0, normal) < 0.0) {
		discard;
	}

    gl_FragColor = vertexColor;
}