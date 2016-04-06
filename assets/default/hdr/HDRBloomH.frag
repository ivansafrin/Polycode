uniform sampler2D screenTexture;
uniform float blurSize;
varying vec2 texCoordVar;

void main(void)
{
   vec4 sum = vec4(0.0);

   sum += texture2D(screenTexture, vec2(texCoordVar.x - 16.0*blurSize, texCoordVar.y)) * 0.000004;
   sum += texture2D(screenTexture, vec2(texCoordVar.x - 15.0*blurSize, texCoordVar.y)) * 0.000012;
   sum += texture2D(screenTexture, vec2(texCoordVar.x - 14.0*blurSize, texCoordVar.y)) * 0.00004;
   sum += texture2D(screenTexture, vec2(texCoordVar.x - 13.0*blurSize, texCoordVar.y)) * 0.00012;
   sum += texture2D(screenTexture, vec2(texCoordVar.x - 12.0*blurSize, texCoordVar.y)) * 0.000331;
   sum += texture2D(screenTexture, vec2(texCoordVar.x - 11.0*blurSize, texCoordVar.y)) * 0.000841;
   sum += texture2D(screenTexture, vec2(texCoordVar.x - 10.0*blurSize, texCoordVar.y)) * 0.001971;
   sum += texture2D(screenTexture, vec2(texCoordVar.x - 9.0*blurSize, texCoordVar.y)) * 0.004258;
   sum += texture2D(screenTexture, vec2(texCoordVar.x - 8.0*blurSize, texCoordVar.y)) * 0.008483;
   sum += texture2D(screenTexture, vec2(texCoordVar.x - 7.0*blurSize, texCoordVar.y)) * 0.015583;
   sum += texture2D(screenTexture, vec2(texCoordVar.x - 6.0*blurSize, texCoordVar.y)) * 0.026396;      
   sum += texture2D(screenTexture, vec2(texCoordVar.x - 5.0*blurSize, texCoordVar.y)) * 0.04123;   
   sum += texture2D(screenTexture, vec2(texCoordVar.x - 4.0*blurSize, texCoordVar.y)) * 0.059384;
   sum += texture2D(screenTexture, vec2(texCoordVar.x - 3.0*blurSize, texCoordVar.y)) * 0.07887;
   sum += texture2D(screenTexture, vec2(texCoordVar.x - 2.0*blurSize, texCoordVar.y)) * 0.096593;
   sum += texture2D(screenTexture, vec2(texCoordVar.x - 1.0*blurSize, texCoordVar.y)) * 0.109084;
   sum += texture2D(screenTexture, vec2(texCoordVar.x, texCoordVar.y)) * 0.113597;
   sum += texture2D(screenTexture, vec2(texCoordVar.x + 16.0*blurSize, texCoordVar.y)) * 0.000004;
   sum += texture2D(screenTexture, vec2(texCoordVar.x + 15.0*blurSize, texCoordVar.y)) * 0.000012;
   sum += texture2D(screenTexture, vec2(texCoordVar.x + 14.0*blurSize, texCoordVar.y)) * 0.00004;
   sum += texture2D(screenTexture, vec2(texCoordVar.x + 13.0*blurSize, texCoordVar.y)) * 0.00012;
   sum += texture2D(screenTexture, vec2(texCoordVar.x + 12.0*blurSize, texCoordVar.y)) * 0.000331;
   sum += texture2D(screenTexture, vec2(texCoordVar.x + 11.0*blurSize, texCoordVar.y)) * 0.000841;
   sum += texture2D(screenTexture, vec2(texCoordVar.x + 10.0*blurSize, texCoordVar.y)) * 0.001971;
   sum += texture2D(screenTexture, vec2(texCoordVar.x + 9.0*blurSize, texCoordVar.y)) * 0.004258;
   sum += texture2D(screenTexture, vec2(texCoordVar.x + 8.0*blurSize, texCoordVar.y)) * 0.008483;
   sum += texture2D(screenTexture, vec2(texCoordVar.x + 7.0*blurSize, texCoordVar.y)) * 0.015583;
   sum += texture2D(screenTexture, vec2(texCoordVar.x + 6.0*blurSize, texCoordVar.y)) * 0.026396;      
   sum += texture2D(screenTexture, vec2(texCoordVar.x + 5.0*blurSize, texCoordVar.y)) * 0.04123;   
   sum += texture2D(screenTexture, vec2(texCoordVar.x + 4.0*blurSize, texCoordVar.y)) * 0.059384;
   sum += texture2D(screenTexture, vec2(texCoordVar.x + 3.0*blurSize, texCoordVar.y)) * 0.07887;
   sum += texture2D(screenTexture, vec2(texCoordVar.x + 2.0*blurSize, texCoordVar.y)) * 0.096593;
   sum += texture2D(screenTexture, vec2(texCoordVar.x + 1.0*blurSize, texCoordVar.y)) * 0.109084;
   
   gl_FragColor = sum;
}

