A. Shoot 1 ray per pixel
	1. calculate viewport position of pixel
	2. determine ray direction
	3. calculate collision
	4. store the closest intersection point (if any), including the object's color and material properties
	5. shoot ray from the position it collided in the object towards the light (or towards every light in the scene)
		- do step 3
		- if ray doesn't reach the light, render pixel with ambient light ?
		- if ray reaches the light, render pixel using the combined colors of object and lights
