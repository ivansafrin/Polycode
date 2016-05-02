#ifdef GL_ES
	precision mediump float;
#endif

uniform sampler2D screenColorBuffer;
varying vec2 texCoordVar;
void main()
{
    gl_FragColor = vec4(1.0-texture2D( screenColorBuffer, texCoordVar).xyz, 1.0);
}