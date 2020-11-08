#version 150
uniform mat4 modelview, perspective, camera; 

attribute vec3 vcol; 
attribute vec3 vpos; 
attribute vec3 vnorm;
varying vec3 color; 
varying vec3 lightpos; 
varying vec3 norm; 
varying vec3 fragpos; 
void main(){ 
	gl_Position = (perspective * camera) * modelview * vec4(vpos, 1.0); 
	color = vcol;
	norm = vec3(modelview * vec4(vnorm, 1.0));
	norm = vnorm;
	fragpos = vec3(modelview * vec4(vpos, 1.0)); 
}



