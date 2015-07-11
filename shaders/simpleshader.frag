#version 120
uniform sampler2D myTexture;
uniform vec2 animationCoords;
varying vec2 vTexCoord;

void main(){
    vec2 newTexCoord = vTexCoord;
    newTexCoord.x = (newTexCoord.x/animationCoords.y) + ((animationCoords.x-1)/animationCoords.y);
	gl_FragColor = texture2D(myTexture, newTexCoord);
}

//	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0);
