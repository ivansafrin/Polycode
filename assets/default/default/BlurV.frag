uniform sampler2D screenTexture;
uniform float blurSize;
varying vec2 texCoordVar;

void main(void)
{
   vec4 sum = vec4(0.0);
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y - 4.0*blurSize)) * 0.05;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y - 3.0*blurSize)) * 0.09;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y - 2.0*blurSize)) * 0.12;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y - blurSize)) * 0.15;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y)) * 0.16;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y + blurSize)) * 0.15;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y + 2.0*blurSize)) * 0.12;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y + 3.0*blurSize)) * 0.09;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y + 4.0*blurSize)) * 0.05;
   
   gl_FragColor = sum;

}