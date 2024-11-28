#include <iostream>
#include <cstring>
#include <cmath>
#include "include/Vector2.h"
#include "include/Vector3.h"
#include "include/functions.h"
#include <windows.h>
#include "include/audio.h"
#include "include/icon.h"



int main() {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	int width = 80;
	int height = 30;
	float aspect = (float)width / height;
	float pixelAspect = 8.0f / 16.0f;

	SetConsoleTitleA("UFO");
	system("mode con cols=80 lines=30");

	const char* startText = ":::    ::: ::::::::::  ::::::::  \n"
                            ":+:    :+: :+:        :+:    :+: \n"
							"+:+    +:+ +:+        +:+    +:+ \n"
							"+#+    +:+ :#::+::#   +#+    +:+ \n"
							"+#+    +#+ +#+        +#+    +#+ \n"
							"#+#    #+# #+#        #+#    #+# \n"
							"########  ###         ########   \n\n"
							" _____\n"                          
							"|     \ .-----..--------..-----.\n"
							"|  --  ||  -__||        ||  _  |\n"
							"|_____/ |_____||__|__|__||_____|\n\n\n"
							"Made by ColorProgrammy\n"
							"Version: v1.0\n\n"
							"Starting...";
                                



	printf("%s", startText);
	setIcon("assets\\ufo.ico");
	
	playSoundAsync("assets\\sound.wav");

	Sleep(1000);
	system("clr");


    SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN);


	char gradient[] = " .:,!/rH$#@";
    int gradientSize = strlen(gradient) - 1;

    char* screen = new char[width * height + 1];
    screen[width * height] = '\0';

    for (int t = 0; t < 10000000000000; ++t) {

		vec3 light = norm(vec3(-0.5, 0.5, -2.0));
        vec3 spherePos = vec3(0, 0, -3);
		vec3 boxPos = vec3(0, 0, -2);
		vec3 boxPos1 = vec3(0, 0, -2);


        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {

                vec2 uv = (vec2(i, j) / vec2(width, height)) * 2.0f - 1.0f;
                uv.x *= aspect * pixelAspect;
				vec3 ro = vec3(-11, 0, -2);
                vec3 rd = norm(vec3(1, uv));

				rd = rotateY(rd, 0.5);
				ro = rotateY(ro, 0.5);

				rd = rotateZ(rd, t * 0.005);
				ro = rotateZ(ro, t * 0.005);

				float brightness = 0.9;

				vec2 intersection = sphere(ro - spherePos, rd, 2);
				for (int k = 0; k < 5; k++) {
					float dist = 1e9;
					float minIt = 99999;

					float albedo = 1.3;

					vec3 n = 0;
					intersection = sphere(ro - spherePos, rd, 3);
					if (intersection.x > 0 && intersection.x < dist) {
						dist = intersection.x;
                        vec3 itPoint = ro - spherePos + rd * dist;
                        minIt = intersection.x;
                        n = norm(itPoint);

					}
					
					vec3 n1 = 0;
					intersection = box(ro - boxPos, rd, 4, 4, 0.7, n1);
					if (intersection.x > 0 && intersection.x < dist) {
						n = n1;
						dist = intersection.x;
						vec3 itPoint = ro - boxPos + rd * dist;
						minIt = intersection.x;
						n = norm(itPoint);
					}

					vec3 n2 = 0;
					intersection = box(ro - boxPos1, rd, 4.2, 4.2, 0.35, n1);
					if (intersection.x > 0 && intersection.x < dist) {
						n = n2;
						dist = intersection.x;
						vec3 itPoint = ro - boxPos1 + rd * dist;
						minIt = intersection.x;
						n = norm(itPoint);
					}




					intersection = plane(ro, rd, vec3(0, 0, -1), 1);
					if (intersection.x > 0) {
						float planeDist = intersection.x;
						if (planeDist < minIt) {
							minIt = planeDist;
							n = vec3(0, 0, -1);
							albedo = 0.5;
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
        }
		printf("%s", screen);
    }
	getchar();
    delete[] screen;
    return 0;
}

