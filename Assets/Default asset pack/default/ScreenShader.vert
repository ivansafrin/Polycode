varying vec2 vTexCoord;
void main(void)
{
	gl_TexCoord[0] = gl_MultiTexCoord0;		      
//   vec2 Pos;
//   Pos = sign(); 
   gl_Position = vec4(gl_Vertex.xy, 0.0, 1.0);
}