#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::ifstream;

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <cmath>
#include <string>
#include <cstring>


#include "Vect3.h"
#include "Color.h"
#include "Eye.h"
#include "Ray.h"
#include "LightSource.h"
#include "Light.h"
#include "Object.h"
#include "Sphere.h"

using namespace std;

struct SinglePixel {
	double r;
	double g;
	double b;
};

//creates file in ppm format
void save_ppm(int width, int height, char* fname, SinglePixel *pixel) {
  FILE *fp;
  const int maxVal=255; 
  int w = width;
  int h = height;
  int k = width*height;

  printf("Saving image %s: %d x %d\n", fname,width,height);
  fp = fopen(fname,"wb");
  if (!fp) {
        printf("Unable to open file '%s'\n",fname);
        return;
  }
  fprintf(fp, "P6\n");
  fprintf(fp, "%d %d\n", width, height);
  fprintf(fp, "%d\n", maxVal);

    fclose(fp);
}
//------------------------------------------------------------------------------



//returns index of closest intersection to camera
int closestObjectIndex(vector<double> object_intersections) {
	int index_of_minimum_value;

	//if no rays hit object
	if (object_intersections.size() == 0) {
		return -1;
	}
	else if (object_intersections.size() == 1) {

		//if the intersection > 0, then minimum value
		if (object_intersections.at(0) > 0) {
			return 0;
		}
		//only intersection is negative
		else{ 
			return -1;
		}
	}
	else //more than one intersection
	{
		//find max value
		double max = 0;
			for (int i = 0; i < object_intersections.size(); i++) {
				if (max < object_intersections.at(i)) {
					max = object_intersections.at(i);
				}
			}

		//find minimum positive value
			if (max > 0) {
				// we only want positive intersections
				for (int index = 0; index < object_intersections.size(); index++) {
					if (object_intersections.at(index) > 0 && object_intersections.at(index) <= max) {
						max = object_intersections.at(index);
						index_of_minimum_value = index;
					}
				}
				
				return index_of_minimum_value;
			}
		else{ //all intersections were negative
			return -1;
		}
	}
}


Color getColorAt(Vect3 intersection_position, Vect3 intersection_ray_direction, vector<Object*> scene_objects, int index_of_closest_object, vector <LightSource*> light_sources , double accuracy, double ambientLight, Color ambientColor, double diffuseLight, double specularLight, double reflectiveLight)
{
	Color closest_object_color = scene_objects.at(index_of_closest_object) -> getColor();
	Vect3 closest_object_normal = scene_objects.at(index_of_closest_object) -> getNormalAt(intersection_position);
	
	//adding ambient color
	Color final_color = closest_object_color.colorMultiply(ambientColor);

	//check what ray intersects with first
	//ray intersects and reflects with another object, and return back to first
if (closest_object_color.getAlpha() > 0 && closest_object_color.getAlpha() <=1 && reflectiveLight > 0 && reflectiveLight <=1)
{ //check for specular value and reflect
	double dot1 = closest_object_normal.dotProd(intersection_ray_direction.negative());
	Vect3 scalar1 = closest_object_normal.vect3Mult(dot1);
	Vect3 add1 = scalar1.vect3Add(intersection_ray_direction);
	Vect3 scalar2 = add1.vect3Mult(2);
	Vect3 add2 = intersection_ray_direction.negative().vect3Add(scalar2);
	Vect3 reflection_direction = add2.normalize();

//create reflection ray
	Ray reflection_ray (intersection_position, reflection_direction);
	//determine what ray intersects with firstly
	vector<double> reflection_intersections;

	for (int reflection_index = 0; reflection_index < scene_objects.size(); reflection_index++)
	{
		reflection_intersections.push_back(scene_objects.at(reflection_index)->findIntersection(reflection_ray));
	}

//check for other intersections along path
		int index_of_closest_object_with_reflection = closestObjectIndex(reflection_intersections);

		if (index_of_closest_object_with_reflection != -1) {

		//reflection ray miss everything else
			if (reflection_intersections.at(index_of_closest_object_with_reflection) > accuracy) {

			//determine position and direction at point of intersection with reflection ray
			//ray affects color if reflected

			Vect3 reflection_intersection_position = intersection_position.vect3Add(reflection_direction.vect3Mult(reflection_intersections.at(index_of_closest_object_with_reflection)));
				Vect3 reflection_intersection_ray_direction = reflection_direction;
			//Recursive call to get color
				Color reflection_intersection_color = getColorAt(reflection_intersection_position, reflection_intersection_ray_direction, scene_objects, index_of_closest_object_with_reflection, light_sources, accuracy, ambientLight, ambientColor, diffuseLight, specularLight, reflectiveLight);

				final_color = final_color.colorAdd(reflection_intersection_color.colorScalar(closest_object_color.getAlpha()));

		}
	}

}



//loop through all light sources
	for (int light_index = 0; light_index < light_sources.size(); light_index++)
	{
		Vect3 light_direction = light_sources.at(light_index)->getLightPosition().vect3Add(intersection_position.negative()).normalize();

		float cosine_angle = closest_object_normal.dotProd(light_direction);

		if (cosine_angle > 0)
		{
			//test for shadows 
			//find distance from intersection point to light source
			bool shadowed = false;
			Vect3 distance_to_light = light_sources.at(light_index)-> getLightPosition().vect3Add(intersection_position.negative());

			float distance_to_light_magnitude = distance_to_light.magnitude();
			//create ray from intersection to light source
			Ray shadow_ray (intersection_position, light_sources.at(light_index)->getLightPosition().vect3Add(intersection_position.negative()).normalize());
			vector<double>secondary_intersections;

			for (int object_index = 0; object_index< scene_objects.size() && shadowed == false; object_index++)
			{
				secondary_intersections.push_back(scene_objects.at(object_index)->findIntersection(shadow_ray));
			}

//loop through secondary intersections, and if it is less than distance to light source, then shadow
			for (int c = 0; c<secondary_intersections.size(); c++)
			{
				if (secondary_intersections.at(c) > accuracy)
				{
					if (secondary_intersections.at(c) <= distance_to_light_magnitude)
					{
						shadowed = true;
					}
						break;
				}
			
			}
			//no need for shadow
			if (shadowed == false)
			{
				final_color = final_color.colorAdd(closest_object_color.colorMultiply(light_sources.at(light_index)->getColor()).colorScalar(cosine_angle));

				if (closest_object_color.getAlpha() > 0 && closest_object_color.getAlpha()<=1)
				{
					double dot1 = closest_object_normal.dotProd(intersection_ray_direction.negative());
					Vect3 scalar1 = closest_object_normal.vect3Mult(dot1);
					Vect3 add1 = scalar1.vect3Add(intersection_ray_direction);
					Vect3 scalar2 = add1.vect3Mult(2);
					Vect3 add2 = intersection_ray_direction.negative().vect3Add(scalar2);
					Vect3 reflection_direction = add2.normalize();
						//glm::vec4 spec (0,0,0,1);
					double specular = reflection_direction.dotProd(light_direction);
					if (specular > 0)
					{
						specular = pow(specular, 10);
						final_color = final_color.colorAdd(light_sources.at(light_index)->getColor().colorScalar(specular*specularLight*closest_object_color.getAlpha()));
					}
				}
			}

		}
	}
//NEED TO CLIP
return final_color;
}









//Constant Declarations
const int MAX_CHARS_PER_LINE = 512;
const int MAX_TOKENS_PER_LINE = 20;
const int MAX_SPHERES = 14;
const int MAX_LIGHTS = 9;
const char* const DELIMITER = " ";
const char* const DELIMITER2 = "\t";
//Variable Declarations
int line_cnt = 0;
int token_cnt = 0;
int sphere_cnt = 0;
int light_cnt = 0;

int near,left,right,bottom,top;
//resolution
int nRows, nColumns;
//background
double bgRed, bgGreen, bgBlue;
//ambient color
double ambRed, ambGreen, ambBlue;
Color ambientColor = Color();
char outputFile[50];

//Spheres
//std::vector<Sphere> v;
string *sphere_name = new string[MAX_SPHERES];
char sph_name[MAX_SPHERES][20];
int sph_posX[MAX_SPHERES], sph_posY[MAX_SPHERES], sph_posZ[MAX_SPHERES];
double sph_sclX[MAX_SPHERES], sph_sclY[MAX_SPHERES], sph_sclZ[MAX_SPHERES];
double sph_red[MAX_SPHERES], sph_green[MAX_SPHERES], sph_blue[MAX_SPHERES];
double sph_K_amb[MAX_SPHERES], sph_K_diff[MAX_SPHERES], sph_K_spec[MAX_SPHERES], sph_K_refl[MAX_SPHERES], sph_n[MAX_SPHERES];

//Lights
char lt_name[9][20];
int lt_posX[9], lt_posY[9], lt_posZ[9];
double lt_red[9], lt_green[9], lt_blue[9];
int curr_pixel; //index value that changes -- to determine x and y coords of individual pixel










int main (int argc, char *argv[])
{

//save_ppm(width, height, outputFile, pixelppm); //output to ppm

//-------------START PARSER
  // create a file-reading object
  ifstream fin;
  fin.open(argv[1]); // open a file
  if (!fin.good()) 
    return 1; // exit if file not found
  
  // read each line of the file
  while (!fin.eof())
  {
    // read an entire line into memory
    char buf[MAX_CHARS_PER_LINE];
    fin.getline(buf, MAX_CHARS_PER_LINE);
    
    // parse the line into blank-delimited tokens
    int n = 0; // a for-loop index
    
    // array to store memory addresses of the tokens in buf
    const char* token[MAX_TOKENS_PER_LINE] = {}; // initialize to 0
    
    // parse the line
    token[0] = strtok(buf, DELIMITER); // first token
    if (token[0]) // zero if line is blank
    {
      for (n = 1; n < MAX_TOKENS_PER_LINE; n++)
      {
        token[n] = strtok(0, DELIMITER); // subsequent tokens
        token_cnt = n;
        if (!token[n]) break; // no more tokens
      }
    }

//-------------------------------------------------------
//check and validate file
//NEAR
if ((!strcmp(token[0],"NEAR")) && (token_cnt == 2)) 
{
	printf("Correct!! line#: %d, tokens#: %d \n", line_cnt, token_cnt);
}
//LEFT
else if ((!strcmp(token[0],"LEFT")) && (token_cnt == 2)) 
{
	printf("Correct!! line#: %d, tokens#: %d \n", line_cnt, token_cnt);
}
//RIGHT
else if ((!strcmp(token[0],"RIGHT")) && (token_cnt == 2)) 
{
	printf("Correct!! line#: %d, tokens#: %d \n", line_cnt, token_cnt);
}
//BOTTOM
else if ((!strcmp(token[0],"BOTTOM")) && (token_cnt == 2)) 
{
	printf("Correct!! line#: %d, tokens#: %d \n", line_cnt, token_cnt);
}
//TOP
else if ((!strcmp(token[0],"TOP")) && (token_cnt == 2)) 
{
	printf("Correct!! line#: %d, tokens#: %d \n", line_cnt, token_cnt);
}
//RESOLUTION
else if ((!strcmp(token[0],"RES")) && (token_cnt == 3)) 
{
	nRows = atoi(token[1]);
	nColumns = atoi(token[2]);

	printf("Correct!! line#: %d, tokens#: %d \n", line_cnt, token_cnt);
}

//########## fix from here down to count how many spheres
//SPHERE --> up to 14
else if ((!strcmp(token[0],"SPHERE")) && (token_cnt == 16)) 
{
	printf("Correct!! line#: %d, tokens#: %d \n", line_cnt, token_cnt);
	
	if ((!strcmp(token[0],"SPHERE")))
	{
		sphere_cnt++;
		printf("IS A SPHERE --- %d\n",sphere_cnt);

		//<name>
		strncpy(sph_name[sphere_cnt],token[1],20);
		printf("%s\n",sph_name[sphere_cnt]);

		//<pos>
		sph_posX[sphere_cnt] = atoi(token[2]);
		sph_posY[sphere_cnt] = atoi(token[3]);
		sph_posZ[sphere_cnt] = atoi(token[4]);
		//<scale>
		sph_sclX[sphere_cnt] = strtod(token[5],NULL);
		sph_sclY[sphere_cnt] = strtod(token[6],NULL);
		sph_sclZ[sphere_cnt] = strtod(token[7],NULL);
		//<color>
		sph_red[sphere_cnt] = strtod(token[8],NULL);
		sph_green[sphere_cnt] = strtod(token[9],NULL);
		sph_blue[sphere_cnt] = strtod(token[10],NULL);

		//<k-values>
		sph_K_amb[sphere_cnt] = strtod(token[11],NULL);
		sph_K_diff[sphere_cnt] = strtod(token[12],NULL);
		sph_K_spec[sphere_cnt] = strtod(token[13],NULL);
		sph_K_refl[sphere_cnt] = strtod(token[14],NULL);

		//<n-value>
		sph_n[sphere_cnt] = strtod(token[15],NULL);
	}
}
//########### fix from here down to count how many lights
//LIGHT --> up to 9
else if ((!strcmp(token[0],"LIGHT")) && (token_cnt == 8)) 
{
	printf("Correct!! line#: %d, tokens#: %d \n", line_cnt, token_cnt);
	if ((!strcmp(token[0],"LIGHT")))
	{
		light_cnt++;
		printf("IS A LIGHT --- %d\n",light_cnt);

		//<name>
		strncpy(lt_name[light_cnt],token[1],20);
		printf("%s\n",lt_name[light_cnt]);

		//<pos>
		lt_posX[light_cnt] = atoi(token[2]);
		lt_posY[light_cnt] = atoi(token[3]);
		lt_posZ[light_cnt] = atoi(token[4]);

		//<color>
		lt_red[light_cnt] = strtod(token[5],NULL);
		lt_green[light_cnt] = strtod(token[6],NULL);
		lt_blue[light_cnt] = strtod(token[7],NULL);
	}
}

//BACKGROUND
else if ((!strcmp(token[0],"BACK")) && (token_cnt == 4)) 
{
	printf("Correct!! line#: %d, tokens#: %d \n", line_cnt, token_cnt);
	bgRed = strtod(token[1],NULL);
	bgGreen = strtod(token[2],NULL);
	bgBlue = strtod(token[3],NULL);

}

//AMBIENT
else if ((!strcmp(token[0],"AMBIENT")) && (token_cnt == 4)) 
{
	printf("Correct!! line#: %d, tokens#: %d \n", line_cnt, token_cnt);
	ambRed = strtod(token[1],NULL);
	ambGreen = strtod(token[2],NULL);
	ambBlue = strtod(token[3],NULL);
	ambientColor.setRed(ambRed);
	ambientColor.setGreen(ambGreen);
	ambientColor.setBlue(ambBlue);


}

//FILE OUTPUT
else if ((!strcmp(token[0],"OUTPUT")) && (token_cnt == 2)) 
{
	printf("Correct!! line#: %d, tokens#: %d \n", line_cnt, token_cnt);
strncpy(outputFile,token[1],20);
}

else if ((!strcmp(token[0]," ")) || (!strcmp(token[0],"\t")))
{
printf("BLANK\n");
}
//-------------------------------------------------------

    // process (print) the tokens
    for (int i = 0; i < n; i++) // n = #of tokens
      cout << "Token[" << i << "] = " << token[i] << endl;
    cout << endl;

    line_cnt++;
  }


//--------------END PARSER


  cout << "rendering ..." << endl;

clock_t t1, t2;
t1 = clock();

	int dpi = 72;
	int width = nRows;
	int height = nColumns;
	int n = width*height;
	SinglePixel *pixels = new SinglePixel[n];
	SinglePixel *pixelppm = new SinglePixel[n];
	double aspectratio = (double)width/(double)height;
	double accuracy = 0.000001; //when ray intersects with sphere, ensure intersection is on outside 

	Vect3 O (0,0,0);
	Vect3 X (1,0,0);
	Vect3 Y (0,1,0);
	Vect3 Z (0,0,1);
	
	Light ambientLt(O,ambientColor);
	
	//change here
	double ambientLight = 1;
	double specularLight = 1;
	double diffuseLight = 1;
	double reflectiveLight = 1;


	Vect3 campos (0+accuracy, 0, -30);
	//create direction of camera
	Vect3 look_at (0, 0, 0);
	Vect3 diff_btw (campos.getVectX() - look_at.getVectX(), campos.getVectY() - look_at.getVectY(), campos.getVectZ() - look_at.getVectZ());

	Vect3 camdir = diff_btw.negative().normalize();
	Vect3 camright = Y.crossProd(camdir).normalize();
	Vect3 camdown = camright.crossProd(camdir);
	Eye scene_cam (campos, camdir, camright, camdown); //create camera

	//pushes lights in scene into vector of light sources
	std::vector<Light*> lights;
	vector<LightSource*> light_sources;
	for (unsigned int i = 1; i <= light_cnt; i++)
	{
		Light *new_Light = new Light (Vect3(lt_posX[i],lt_posY[i],lt_posZ[i]), Color(lt_red[i], lt_green[i], lt_blue[i], 0));
		light_sources.push_back(dynamic_cast<LightSource*>(new_Light));
	}

	//create spheres
	std::vector<Sphere*> spheres;
	vector<Object*> scene_objects;
	for (unsigned int i = 1; i <= sphere_cnt; i++)
	{
		Sphere *new_Sphere = new Sphere (Vect3(sph_posX[i],sph_posY[i],sph_posZ[i]), sph_sclX[i], Color(sph_red[i],sph_green[i],sph_blue[i],0.5),sph_K_amb[i],sph_K_diff[i],sph_K_spec[i], sph_K_refl[i]);
		spheres.push_back(new_Sphere);
		scene_objects.push_back(dynamic_cast<Object*>(new_Sphere));
	}




int curr_pixel;
	double xamnt, yamnt;

//start from left to right of each pixel
	for (int x = 0; x < width; x++) {
	//start from top to bottom of each pixel
		for (int y = 0; y < height; y++) {		
	//need to return a color
			curr_pixel = y*width + x;


		//create view angle of camera
		if (width > height) {//image is wider than tall
				xamnt = ((x+0.5)/width)*aspectratio - (((width-height)/(double)height)/2);
				yamnt = ((height - y) + 0.5)/height;		
		}
		else if (height > width) 		//image is taller than wide
		{
			xamnt = (x + 0.5)/ width;
			yamnt = (((height - y) + 0.5)/height)/aspectratio - (((height - width)/(double)width)/2);
		}
		else //image is same height and width
		{
				xamnt = (x + 0.5)/width;
				yamnt = ((height - y) + 0.5)/height;
		}



		xamnt = (x + 0.5)/width;
		yamnt = ((height - y) + 0.5)/height;

		Vect3 cam_ray_origin = scene_cam.getEyePosition(); //return camera origin
		Vect3 cam_ray_direction = camdir.vect3Add(camright.vect3Mult(xamnt - 0.5).vect3Add(camdown.vect3Mult(yamnt - 0.5))).normalize();

		Ray cam_ray (cam_ray_origin, cam_ray_direction);//goes through specific x,y pixel into scene and looks for intersections with objects

		vector <double> intersections;

		//want to loop through scene and determine if ray intersects with any objects in scene
		for (int index = 0; index < scene_objects.size(); index++) {
			//loops through each object, finds intersection with camera ray, and pushes into intersections
		intersections.push_back(scene_objects.at(index)->findIntersection(cam_ray));
		}

		//returns -1, 0, or 1
		int index_of_closest_object = closestObjectIndex(intersections);
		//PRINT data of raytracer
		//cout <<  index_of_closest_object;

		//Background color
		//ray missed so paint black
		if (index_of_closest_object == -1) {

			pixels[curr_pixel].r = bgRed;
			pixels[curr_pixel].g = bgGreen;
			pixels[curr_pixel].b = bgBlue;

			pixelppm[curr_pixel].r = bgRed;
			pixelppm[curr_pixel].g = bgGreen;
			pixelppm[curr_pixel].b = bgBlue;
		}
		
		//index is an object in scene
		else
		{
			if (intersections.at(index_of_closest_object) > accuracy)
			{
				//find position and direction at point of intersection
				Vect3 intersection_position = cam_ray_origin.vect3Add(cam_ray_direction.vect3Mult(intersections.at(index_of_closest_object)));
				Vect3 intersection_ray_direction = cam_ray_direction;


				Color intersection_color = getColorAt(intersection_position, intersection_ray_direction, scene_objects, index_of_closest_object, light_sources ,accuracy, ambientLight, ambientColor, diffuseLight, specularLight, reflectiveLight);
				//need a function for specific color of intersection
				pixels[curr_pixel].r = intersection_color.getRed();
				pixels[curr_pixel].g = intersection_color.getGreen();
				pixels[curr_pixel].b = intersection_color.getBlue();

				pixelppm[curr_pixel].r = intersection_color.getRed();
				pixelppm[curr_pixel].g = intersection_color.getGreen();
				pixelppm[curr_pixel].b = intersection_color.getBlue();
			}
		}
	}
}


	return 0;
}