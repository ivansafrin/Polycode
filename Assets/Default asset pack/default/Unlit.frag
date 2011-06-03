
uniform sampler2D diffuse;
varying vec4 vertexColor;

void main()
{
	vec4 texColor = texture2D(diffuse, gl_TexCoord[0].st);
    gl_FragColor = texColor*vertexColor;
}