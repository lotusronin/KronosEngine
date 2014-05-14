#version 120
attribute vec2 pos;
attribute vec2 texCoord;
varying vec2 vTexCoord;
uniform mat4 transformation;

//glOrtho(0, width, height, 0, 1, -1);

// left = 0;
// right = 640;
// bottom = 480;
// top = 0;
// near = 1;
// far = -1;

mat4 ortho = mat4(
	2/(640), 0, 0, 0,
	0, 2/(-480), 0, 0,
	0, 0, -2/(-2), 0,
	-1, 1, 0, 1
	);

void main(){
	vTexCoord = texCoord;
	gl_Position = gl_ProjectionMatrix*gl_ModelViewMatrix*transformation*vec4(pos, 0.0, 1.0);
}