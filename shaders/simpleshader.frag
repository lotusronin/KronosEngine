#version 120
uniform sampler2D myTexture;
varying vec2 vTexCoord;

void main(){
	gl_FragColor = texture2D(myTexture, vTexCoord);
}

//	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);