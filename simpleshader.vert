#version 120
attribute vec2 pos;
attribute vec2 texCoord;
varying vec2 vTexCoord;

void main(){
	vTexCoord = texCoord;
	gl_Position = vec4(pos, 0.0, 1.0);
}