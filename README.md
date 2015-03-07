# rayar

## Introduction
A basic ray tracer built from the ground up, using a custom vector class (not using the glm library). Rays are cast from the eye through pixels in an image plane and the color required for each pixel is calculated by recursively following the rays and determine with that objects they intersect with. This algorithm creates a global illumination model which makes for more realistic lighting in 3D scenes.

## Usage
In terminal:
```shell
$ make
$ ./rayar <input_file>
```
## Required format
<input_file> must be a path to a directory that consists of the following format:
```shell
NEAR <n>
LEFT <l>
RIGHT <r>
BOTTOM <b>
TOP <t>
RES <x> <y>
SPHERE <name> <position x> <position y> <position z> <scale x> <scale y> <scale z> <r> <g> <b> <Ka> <Kd> <Ks> <Kr> <n>
LIGHT <name> <position x> <position y> <position z> <Ir> <Ig> <Ib>
BACK <r> <g > <b>
AMBIENT <Ir> <Ig> <Ib>
OUTPUT <name>
```

### Example format
```shell
NEAR 1
LEFT -1
RIGHT 1
BOTTOM -1
TOP 1
RES 600 600
SPHERE s1 4 4 -10 2 2 1 0.5 0 0 0 0 1 0 100
SPHERE s2 0 0 -10 2 2 1 0 0.5 0 0 0 1 0 10
SPHERE s3 -4 2 -10 2 2 1 0 0 0.5 0 0 1 0 1000
LIGHT l1 0 -5 0 0.9 0.9 0
LIGHT l2 10 5 0 0 0.9 0
LIGHT l3 -10 5 0 0 0 0.9
BACK 0 0 0
AMBIENT .75 .75 .75
OUTPUT testSpecular.ppm
```

##Output
The program will render an image in Portable Pixmap format (.ppm)

### Example output
Using the above input file (in example format) which is located in the Tests folder, in shell we run:
```shell
$ make
$ ./rayar Tests/testSpecular.txt
```
This will create a .ppm file in the current directory and name it as the string that follows "OUTPUT" in the file (in our example it is "testSpecular.ppm"). The current implementation of the raytracer produces an image that looks like the following:
![alt tag](http://www.alekseev.io/misc/testSpecular.png)
