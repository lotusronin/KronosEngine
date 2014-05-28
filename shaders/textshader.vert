#version 120
attribute vec4 pos;
varying vec2 vTexCoord;

void main(){
	vTexCoord = pos.zw;
	gl_Position = vec4(pos.xy, 0, 1);
}