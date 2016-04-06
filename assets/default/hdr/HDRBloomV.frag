uniform sampler2D screenTexture;
uniform float blurSize;
varying vec2 texCoordVar;

void main(void)
{
   vec4 sum = vec4(0.0);
   
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y- 16.0*blurSize)) * 0.000004;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y- 15.0*blurSize)) * 0.000012;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y- 14.0*blurSize)) * 0.00004;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y- 13.0*blurSize)) * 0.00012;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y- 12.0*blurSize)) * 0.000331;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y- 11.0*blurSize)) * 0.000841;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y- 10.0*blurSize)) * 0.001971;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y- 9.0*blurSize)) * 0.004258;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y- 8.0*blurSize)) * 0.008483;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y- 7.0*blurSize)) * 0.015583;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y- 6.0*blurSize)) * 0.026396;      
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y- 5.0*blurSize)) * 0.04123;   
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y- 4.0*blurSize)) * 0.059384;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y- 3.0*blurSize)) * 0.07887;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y- 2.0*blurSize)) * 0.096593;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y- 1.0*blurSize)) * 0.109084;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y)) * 0.113597;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y+ 16.0*blurSize)) * 0.000004;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y+ 15.0*blurSize)) * 0.000012;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y+ 14.0*blurSize)) * 0.00004;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y+ 13.0*blurSize)) * 0.00012;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y+ 12.0*blurSize)) * 0.000331;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y+ 11.0*blurSize)) * 0.000841;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y+ 10.0*blurSize)) * 0.001971;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y+ 9.0*blurSize)) * 0.004258;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y+ 8.0*blurSize)) * 0.008483;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y+ 7.0*blurSize)) * 0.015583;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y+ 6.0*blurSize)) * 0.026396;      
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y+ 5.0*blurSize)) * 0.04123;   
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y+ 4.0*blurSize)) * 0.059384;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y+ 3.0*blurSize)) * 0.07887;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y+ 2.0*blurSize)) * 0.096593;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y+ 1.0*blurSize)) * 0.109084;

   gl_FragColor = sum;
}