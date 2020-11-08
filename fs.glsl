#version 150
varying vec3 color; 
varying vec3 norm; 
varying vec3 fragpos; 


void main() {

	
	vec3 lightPos = vec3(0.1, 0.0, 2.0);
	vec3 lightCol = vec3(0.0, 0.0, 1.0);
	vec3 normal = normalize(norm); 
	vec3 lightDir = normalize(lightPos - fragpos); 

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightCol;
	vec3 ambient = 0.5 * vec3(1.0, 1.0, 1.0);
	vec3 result = (ambient+ diffuse) * vec3(0.5, 0.5, 0.5);
	gl_FragColor = vec4(result, 1.0);

	return; 
} 


