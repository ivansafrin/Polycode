uniform sampler2D screenColorBuffer;
 
void main(void)
{
   gl_FragColor = texture2D(screenColorBuffer,gl_TexCoord[0].st);
}