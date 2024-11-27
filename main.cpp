#include <iostream>
#include <cstring>
#include <cmath>
#include "../include/Vectors/Vector2.h"
#include "../include/Vectors/Vector3.h"
#include "../include/functions.h"
#include <windows.h>

//////////////
//
//  Screen size
//
//  I do not recommend setting values 
//  higher than 132 and 31, 
//  as the image will not be displayed correctly.
//
//////////////

int width = 120;
int height = 30;

float aspect = (float)width / height;
float pixelAspect = 8.0f / 16.0f;

float minIt = 99999;
float dist = 1e9;

vec3 n = 0;

float albedo = 1;
float brightness = 1;

int main() {
    SetConsoleTitleA("DolphinEngine");
    system("mode con cols=120 lines=30");
    
    char gradient[] = " .:,!/rH#$@";
    int gradientSize = strlen(gradient) - 1;

    char* screen = new char[width * height + 1];
    screen[width * height] = '\0';

    for (int t = 2; t < 1; ++t) {
        vec3 light = norm(vec3(-0.5, 0.5, -1.0));
        
        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {

                vec2 uv = (vec2(i, j) / vec2(width, height)) * 2.0f - 1.0f;
                uv.x *= aspect * pixelAspect;
            
                vec3 ro = vec3(0, 0, 0);
                vec3 rd = norm(vec3(1, uv));
              
		        intersection = plane(ro, rd, vec3(0, 0, -1), 1);
		        if (intersection.x > 0) {
		            float planeDist = intersection.x;
		            if (planeDist < minIt) {
			            minIt = planeDist;
			            n = vec3(0, 0, -1);
			            albedo = 0.7;
			        }
		        }

		        if (minIt < 99999) {
                    brightness *= (dot(n, light) * 0.5 + 0.5) * albedo;
                    ro = ro + rd * (minIt - 0.01);
		        } 
					
	            if (minIt < 99998) {
		            rd = reflect(rd, n);
		        }
					
		        else break;
            }


				
            int color = (int)(brightness * 10);
            color = clamp(color, 0, gradientSize);
            char pixel = gradient[color];
            screen[i + j * width] = pixel;
        }
        printf("%s", screen);
    }
    getchar();
    delete[] screen;
    return 0;
}
