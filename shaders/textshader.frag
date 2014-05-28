#version 120
uniform sampler2D myTexture;
varying vec2 vTexCoord;

void main(){
	gl_FragColor = vec4(1, 1, 1, texture2D(myTexture, vTexCoord).a);
}