# `%.rt` file:
- There can only be 1 of each element with capital identifier
- All of the elements with a capital identifier must be present, as well as atleast one light, and one shape
- Each type of information from an element must be separated by one or more spaces
- Each type of element can be separated by one or more line breaks
- Each type of element can be set in any order in the file
## Ambient light
- identifier: `A`
- ratio: `[0.0,1.0]`
- RGB color: `[0,255]`,`[0,255]`,`[0,255]`
## Camera
- identifier: `C`
- 3D position vector: `ℝ`,`ℝ`,`ℝ`
- 3D orientation vector: `[-1.0,1.0]`,`[-1.0,1.0]`,`[-1.0,1.0]`
- Horizontal FOV: `[0,180]`
## Light
- identifier: `l`
- 3D position vector: `ℝ`,`ℝ`,`ℝ`
- brightness: `[0.0,1.0]`
- RGB color: `[0,255]`,`[0,255]`,`[0,255]`
## Sphere
- identifier: `sp`
- 3D position vector: `ℝ`,`ℝ`,`ℝ`
- diameter: `ℝ+`
- RGB color: `[0,255]`,`[0,255]`,`[0,255]`
- texture file: `%.xpm` or `n`
- bump map texture file: `%.xpm` or `n`
## Plane
- identifier: `pl`
- 3D position vector: `ℝ`,`ℝ`,`ℝ`
- 3D normal vector: `[-1.0,1.0]`,`[-1.0,1.0]`,`[-1.0,1.0]`
- RGB color: `[0,255]`,`[0,255]`,`[0,255]`
- texture file: `%.xpm` or `n`
- bump map texture file: `%.xpm` or `n`
## Cylinder
- identifier: `cy`
- 3D position vector: `ℝ`,`ℝ`,`ℝ`
- 3D axis vector: `[-1.0,1.0]`,`[-1.0,1.0]`,`[-1.0,1.0]`
- diameter: `ℝ+`
- height: `ℝ+`
- RGB color: `[0,255]`,`[0,255]`,`[0,255]`
- texture file: `%.xpm` or `n`
- bump map texture file: `%.xpm` or `n`
## Cone
- identifier: `co`
- 3D position vector: `ℝ`,`ℝ`,`ℝ`
- 3D axis vector: `[-1.0,1.0]`,`[-1.0,1.0]`,`[-1.0,1.0]`
- diameter: `ℝ+`
- height: `ℝ+`
- RGB color: `[0,255]`,`[0,255]`,`[0,255]`
- texture file: `%.xpm` or `n`
- bump map texture file: `%.xpm` or `n`
