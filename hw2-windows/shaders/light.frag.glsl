# version 330 core
// Do not use any version older than 330!

/* This is the fragment shader for reading in a scene description, including 
   lighting.  Uniform lights are specified from the main program, and used in 
   the shader.  As well as the material parameters of the object.  */

// Inputs to the fragment shader are the outputs of the same name of the vertex shader.
// Note that the default output, gl_Position, is inaccessible!
in vec3 mynormal; 
in vec4 myvertex; 

// You will certainly need this matrix for your lighting calculations
uniform mat4 modelview;

// This first defined output of type vec4 will be the fragment color
out vec4 fragColor;

uniform vec3 color;

const int numLights = 10; 
uniform bool enablelighting; // are we lighting at all (global).
uniform vec4 lightposn[numLights]; // positions of lights 
uniform vec4 lightcolor[numLights]; // colors of lights
uniform int numused;               // number of lights used

// Now, set the material parameters.
// I use ambient, diffuse, specular, shininess. 
// But, the ambient is just additive and doesn't multiply the lights.  

uniform vec4 ambient; 
uniform vec4 diffuse; 
uniform vec4 specular; 
uniform vec4 emission; 
uniform float shininess; 

vec4 ComputeLight (const in vec3 direction, const in vec4 lightcolor, const in vec3 normal, const in vec3 halfvec, const in vec4 mydiffuse, const in vec4 myspecular, const in float myshininess) {

        float nDotL = dot(normal, direction)  ;         
        vec4 lambert = mydiffuse * lightcolor * max (nDotL, 0.0) ;  

        float nDotH = dot(normal, halfvec) ; 
        vec4 phong = myspecular * lightcolor * pow (max(nDotH, 0.0), myshininess) ; 

        vec4 retval = lambert + phong ; 
        return retval ;            
}    

void main (void) 
{       
    if (enablelighting) {       
        vec4 finalcolor = ambient; 

		const vec3 eyepos = vec3(0,0,0) ; 
        vec3 mypos = myvertex.xyz / myvertex.w ; // Dehomogenize current location 
        vec3 eyedirn = normalize(eyepos - mypos) ; 

        // Compute normal, needed for shading. 
        vec3 normal = normalize(mynormal) ; 

        // YOUR CODE FOR HW 2 HERE
        // A key part is implementation of the fragment shader

		for(int i = 0; i < numLights; i++) {
			vec4 color;
			if(lightposn[i][3]==0.0) {
				//directional
				vec3 lightdiren = normalize(vec3(lightposn[i][0], lightposn[i][1], lightposn[i][2]));
				vec3 lighthalfangle = normalize(lightdiren + eyedirn);
				vec4 currlightcolor = vec4(lightcolor[i][0], lightcolor[i][1], lightcolor[i][2], lightcolor[i][3]);
				color = ComputeLight(lightdiren, currlightcolor, normal, lighthalfangle, diffuse, specular, shininess);
			} else {
				//point
				vec3 position = lightposn[i].xyz / lightposn[i].w;
				vec3 direction = normalize(position - mypos);
				vec3 lighthalf = normalize(direction + eyedirn);
				vec4 currlightcolor = vec4(lightcolor[i][0], lightcolor[i][1], lightcolor[i][2], lightcolor[i][3]);
				color = ComputeLight(direction, currlightcolor, normal, lighthalf, diffuse, specular, shininess);
			} finalcolor += color;
		}

        fragColor = finalcolor; 
    } else {
        fragColor = vec4(color, 1.0f); 
    }
}
