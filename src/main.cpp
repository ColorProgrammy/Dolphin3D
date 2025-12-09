// Ufo Mayhem: Welcome to Space  

#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <windows.h>
#include <conio.h>
#include "../include/Dolphin3D.h"

// Threads
bool colorThreadRunning = true;
bool changeColorThreadRunning = true;

DWORD WINAPI changeColor(LPVOID lpParam) {
    Box* head = static_cast<Box*>(lpParam);
    while (changeColorThreadRunning) {
        if (!changeColorThreadRunning) break;
        head->setColor(Color::Cyan());
        Sleep(2500);
        if (!changeColorThreadRunning) break;
        head->setColor(Color::Red());
        Sleep(2500);
    }
    return 0;
}

DWORD WINAPI boxColor(LPVOID lpParam) {
    Box* head = static_cast<Box*>(lpParam);
    while (changeColorThreadRunning) {
        if (!changeColorThreadRunning) break;
        head->setColor(Color::Yellow());
        Sleep(1500);
        if (!changeColorThreadRunning) break;
        head->setColor(Color::Red());
        Sleep(1500);
    }
    return 0;
}

void PlayCollisionSound() {
    Beep(1000, 20);
    Beep(1200, 30);
}

DWORD WINAPI titleSong(LPVOID lpParam) {
    Beep(500, 50);
    Beep(1000, 100);
    return 0;
}
void showCutscene() {
    const char* cutscene[] = {
		"Aliens flew with energy orbs to Mars,",
        "But because they crashed into a meteorite, their hyperdrive broke.",
        "The UFO crew was stranded on the Moon.",
        "Their only hope: collect enough",
        "scattered parts to repair the ship",
        "before oxygen runs out...",
        "",
		"Collect at least 20 parts to escape.",
		"",
        "Press any key to start..."
    };
    
    const int lines = 10;
    bool skipped = false;
    
    for(int i = 0; i < lines; i++) {
        const char* p = cutscene[i];
        while(*p && !skipped) {
            putchar(*p++);
            if(_kbhit()) {
                _getch();
                skipped = true;
                break;
            }
            Sleep(50);
        }
        if(skipped) break;
        printf("\n");
    }
    
    if(!skipped) {
        while(!_kbhit()) Sleep(100);
        _getch();
    }
    system("cls");
}

DWORD WINAPI failedSound(LPVOID lpParam) {
    Beep(500, 500);
    return 0;
}

DWORD WINAPI delayedSound(LPVOID lpParam) {
    Beep(600, 250);
    Beep(700, 200);
    return 0;
}

DWORD WINAPI successSound(LPVOID lpParam) {
    Beep(500, 50);
    Beep(1000, 100);
    return 0;
}

int main() {
    int width = 100;
    int height = 30;

    setBuffer(width, height);
    initRender(width, height);
	setWindow(width, height, "UFO Mayhem!");
    system("cls");

	// Init
    int movePos = 0;
    int movePos1 = 12;
    int points = 0;
    const float moveSpeed = 0.4f;
    const float ufoLimit = 30.0f;

	//       :::::::: 
	//     :+:    :+: 
	//           +:+  
	//       +#++:    
	//         +#+    
	// #+#    #+#     
	// ########       

    // Menu
	const char* startTxt3 = 
							":::    ::: ::::::::::  ::::::::            ::::::::   \n"
							":+:    :+: :+:        :+:    :+:        :+:    :+:\n"
							"+:+    +:+ +:+        +:+    +:+              +:+ \n"
							"+#+    +:+ :#::+::#   +#+    +:+           +#++:   \n"
							"+#+    +#+ +#+        +#+    +#+             +#+   \n";
	const char* startText = "#+#    #+# #+#        #+#    #+#     #+#    #+#       \n"
							"########  ###         ########       ########        \n";

    const char* startTxt1 = "  ,____,  __,        /_   _   ,____, \n"
                            "_/ / / (_(_/(__(_/__/ (__(/__/ / / (_\n"
                            "               _/_                   \n"
                            "              (/                     \n";
	const char* startTxt2 = "| | | _ | _  ,_  _   |-    (`     _ _ \n"
							" \\|\\|(/_|(_()|||(/_  |_()  _)|)(|(_(/_\n"
							"                             |        \n"
							"Made by ColorProgrammy\n"
							"Version: vDev1.0\n\n";

	printf("%s", startTxt3);
	Beep(600, 100);
    printf("%s", startText);
	Beep(700, 200);
	printf("%s", startTxt1);
	Beep(800, 200);
	printf("%s", startTxt2);
	Beep(900, 200);
    Sleep(700);

    HANDLE songThread = CreateThread(NULL, 0, titleSong, NULL, 0, NULL);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN);

    printf("< Press any key to start! >\n");

    _getch();
    system("cls");


    WaitForSingleObject(songThread, INFINITE);
    CloseHandle(songThread);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);

	// Cutscene
	printf("Mission 52 - ");
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("In Progress\n\n");
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

	showCutscene(); 

	const char* goal = " d888b   .d88b.   .d8b.  db         \n"
					   "88' Y8b .8P  Y8. d8' `8b 88      db \n"
					   "88      88    88 88ooo88 88      VP \n"
					   "88  ooo 88    88 88~~~88 88         \n"
					   "88. ~8~ `8b  d8' 88   88 88booo. db \n"
					   " Y888P   `Y88P'  YP   YP Y88888P VP\n\n"; 
                          
	printf("%s", goal);
	printf("Collect ");
	Sleep(150);
	printf("as "); 
	Sleep(150);
	printf("many "); 
	Sleep(150);
	SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	printf("spare parts ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	Sleep(150);
	printf("as ");
	Sleep(150);
	printf("possible ");
	Sleep(150);
	printf("in ");
	Sleep(150);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN);
	printf("60 ");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED);
	Sleep(150);
	printf("seconds. ");
	Sleep(1200);
	system("cls");

	// Also init
    srand(static_cast<unsigned int>(time(NULL)));

	bool gameActive = true;

	DWORD startTime = GetTickCount();
    const int gameDuration = 60000;

    bool hit;
    Color currentcolor;
    vec3 normal;

    const char* gradientName = GRADIENT_0;
    size_t gradientSize = 0;

    const size_t maxGradientSize = 100;
    char gradient[maxGradientSize];

    setGradientSize(gradient, gradientSize, maxGradientSize, gradientName);

	// Objects
    vec3 spherePos = vec3(10, 0, -8);
    vec3 spherePos1 = vec3(10, 9, -1);
    vec3 boxPos = vec3(10, 0, -7);
    vec3 rayPos = vec3(10, 0, -2);
    vec3 boxPos1 = vec3(10, 0, -6);
    vec3 planePos = vec3(0, 0, -5);
    //vec3 light = vec3(0, 20, -7.0);

	std::vector<Light> lights;
    //createPointLight(lights, vec3(0, 20, -7), 30.5f, 150.0f);
	createDirectionalLight(lights, vec3(0, 20, -7), vec3(0, -1, 0.2f), 0.5f, 20.0f, 250.0f);

    std::vector<Object*> objects;
    objects.push_back(new Plane(planePos, vec3(0, 1, 0), 1.5f, Color::Grey()));

    Sphere* headUFO = new Sphere(spherePos, 2.7f, 4.5f, Color::Cyan());
    Box* target = new Box(spherePos1, vec3(2.0f, 1.0f, 2.3f), 10.0f, Color::Yellow());

    Box* rayUFO = new Box(rayPos, vec3(1.0f, 1.0f, 3.3f), 4.2f, Color::Cyan());
    Box* bodyUFO = new Box(boxPos1, vec3(4.2f, 4.2f, 0.75f), 3.5f, Color::Grey());

    objects.push_back(headUFO);
    objects.push_back(target);
    objects.push_back(rayUFO);
    objects.push_back(bodyUFO);

    // Decorations
    objects.push_back(new Box(vec3(-1, 7, 1), vec3(1.2f, 1.2f, 2.75f), 6.5f, Color::Grey()));
    objects.push_back(new Box(vec3(-2, 8, 1), vec3(1.0f, 1.2f, 2.75f), 6.5f, Color::Grey()));
	objects.push_back(new Box(vec3(50, -15, 1), vec3(14.0f, 8.2f, 6.75f), 4.5f, Color::Grey()));

	objects.push_back(new Sphere(vec3(11, 3, -3), 3.5f, 2.5f, Color::Grey()));
	objects.push_back(new Sphere(vec3(20, 11, 0), 8.5f, 2.5f, Color::Grey()));
	objects.push_back(new Sphere(vec3(23, -25, 0), 8.5f, 2.5f, Color::Grey()));
	objects.push_back(new Sphere(vec3(-4, -6, -3), 2.5f, 2.5f, Color::Grey()));
	objects.push_back(new Sphere(vec3(0, -6, -1), 1.5f, 2.5f, Color::White()));

	objects.push_back(new Sphere(vec3(50, -15, -4), 7.7f, 4.5f, Color::Cyan()));

    HANDLE colorChangeThread = CreateThread(NULL, 0, changeColor, headUFO, 0, NULL);
	HANDLE colorChangeThread1 = CreateThread(NULL, 0, boxColor, target, 0, NULL);

	// Main
    while (true) {
		target->rotateLocalZ(0.05f);
        swapBuffers(currentBuffer, displayBuffer, width, height);

        DWORD currentTime = GetTickCount();
        int elapsedSeconds = (currentTime - startTime) / 1000;
        int remainingTime = 60 - elapsedSeconds;
		float oxygenLevel = static_cast<float>(remainingTime) / 60.0f;

        if (gameActive && remainingTime <= 0) {
            gameActive = false;
        }

        if (!gameActive) {
			// Time's up
            const char* timeisup = "______                                     \n"
                                   "(  /    o           o  _                /  \n"
                                   "  /    ,  _ _ _   _ ' (     , ,  ,_    /   \n"
                                   "_/     (_/ / / / (/_  _)   (_/  _|_)  '    \n"
                                   "                                 |   o     \n"
                                   "                                 /         \n";
            system("cls");
            printf("%s\nTIME'S UP!\nPoints: %d\n---\n", timeisup, points);

			if (points <= 9) {
				Sleep(1000);
				printf("Mission 52 - ");
				PlayCollisionSound();
			    
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY);
				Sleep(1000);
				HANDLE soundThread = CreateThread(NULL, 0, failedSound, NULL, 0, NULL);
				printf("Failed\n");
			    
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				Sleep(1000);
				printf("The crew lost consciousness due to lack of air...\n\n");

				CloseHandle(soundThread);
			}
			else if (points >= 10 && points <= 19) {
				Sleep(1000);
				printf("Mission 52 - ");
				PlayCollisionSound();
			    
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				Sleep(1000);
				HANDLE soundThread = CreateThread(NULL, 0, delayedSound, NULL, 0, NULL);
				printf("Delayed\n");
			    
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				Sleep(1000);
				printf("The crew partially repaired the ship, but they won't be able to fly away on their own. \nThey called for reinforcements...\n\n");

				CloseHandle(soundThread);
			}
			else {
				Sleep(1000);
				printf("Mission 52 - ");
				PlayCollisionSound();
			    
				SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY);
				Sleep(1000);
				
				HANDLE soundThread = CreateThread(NULL, 0, successSound, NULL, 0, NULL);
				printf("Success\n");
			    
				SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
				Sleep(1000);
				printf("You managed to fix everything in a short time and you flew away.\n\n");

				CloseHandle(soundThread);
			}
			printf("Press SPACE to restart or ESC to exit");
			

            while (true) {
                if (_kbhit()) {
                    char key = _getch();
                    if (key == KEY_ESC) { // ESC
                        changeColorThreadRunning = false;
                        WaitForSingleObject(colorChangeThread, INFINITE);
                        CloseHandle(colorChangeThread);

                        freeBuffers();
                        freeObjects(objects);
                        return 0;
                    }
                    else if (key == ' ') { // SPACE
                        points = 0;
                        startTime = GetTickCount();
                        gameActive = true;
                        spherePos1 = vec3(10, 10, 0);
                        system("cls");
                        break;
                    }
                }
            }
            continue;
        }

		// Random
        float randomY = -10 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 20));
        float randomX = -2 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 14));

        float distance = length(rayPos - spherePos1);
        if (distance <= 1.0f * 3) {
            points++;
            PlayCollisionSound();
            spherePos1.x = randomX;
            spherePos1.y = randomY;
        }
		
		// Move UFO
        if (_kbhit()) {
            char key = _getch();
            if (key == 'a' || key == 'A' || key == KEY_LEFT) {
                movePos -= 1;
            }
            else if (key == 'd' || key == 'D' || key == KEY_RIGHT) {
                movePos += 1;
            }
            else if (key == 'w' || key == 'W' || key == KEY_UP) {
                movePos1 += 1;
            }
            else if (key == 's' || key == 'S' || key == KEY_DOWN) {
                movePos1 -= 1;
            }
            else if (key == KEY_ESC) {
                break;
            }

            movePos = max(min(movePos, static_cast<int>(ufoLimit)), -static_cast<int>(ufoLimit));
			movePos1 = max(min(movePos1, static_cast<int>(ufoLimit * 2)), 0);

            spherePos.y = movePos * moveSpeed;
            boxPos.y = movePos * moveSpeed;
            rayPos.y = movePos * moveSpeed;
            boxPos1.y = movePos * moveSpeed;

            spherePos.x = movePos1 * moveSpeed;
            boxPos.x = movePos1 * moveSpeed;
            rayPos.x = movePos1 * moveSpeed;
            boxPos1.x = movePos1 * moveSpeed;
        }

        headUFO->setPosition(spherePos);
        rayUFO->setPosition(rayPos);
        bodyUFO->setPosition(boxPos1);
        target->setPosition(spherePos1);

        for (int j = 0; j < height; ++j) {
            for (int i = 0; i < width; ++i) {
                float brightness = 0.2f;

                vec2 uv = createUV(i, j, width, height);
                vec3 rd = norm(vec3(1, uv));
                vec3 ro = vec3(-11, 0, -2);

                rd = rotateAroundCenterY(rd, 0.6f);
                ro = rotateAroundCenterY(ro, 0.6f);

                setObjects(objects, ro, rd, hit, currentcolor, brightness, normal, lights, 0.4f, 7.0f);
                setColors(i, j, width, gradientSize, gradient, hit, currentcolor, brightness);
            }
        }

		// UI
        char infoStr[125];
		char oxygenStr[125];

		const char* oxygenChars = ".:-!/?7ilI#%@";
		const int maxOxygenWidth = 14;
		int filledOxygen = static_cast<int>((maxOxygenWidth-2) * oxygenLevel);

		sprintf_s(oxygenStr, " Oxygen: |%.*s%*s| Temp: -271 C                                                                           ", 
			filledOxygen, 
			oxygenChars,
			(maxOxygenWidth-2 - filledOxygen), 
			"");

		sprintf_s(infoStr, " UFO Mayhem: Welcome to Space! | Time: %02d  Points: %d                                             ", 
			remainingTime, 
			points );

		int infoY = height - 4;
		int oxygenY = height - 3;

		for(int y = infoY-1; y <= oxygenY+1; y++) {
			for(int i = 0; i < width; ++i) {
				currentBuffer[i + y * width].Attributes = 0x0000;
			}
		}

		for(int i = 0; i < width; ++i) {
			currentBuffer[i + (infoY-1) * width].Char.AsciiChar = '-';
			currentBuffer[i + (infoY-1) * width].Attributes = 0x08;
		}

		for(size_t i = 0; i < strlen(infoStr) && i < static_cast<size_t>(width); ++i) {
			currentBuffer[i + infoY * width].Char.AsciiChar = infoStr[i];
			currentBuffer[i + infoY * width].Attributes = 0x0F;
		}

		for(size_t i = 0; i < strlen(oxygenStr) && i < static_cast<size_t>(width); ++i) {
			currentBuffer[i + oxygenY * width].Char.AsciiChar = oxygenStr[i];
			currentBuffer[i + oxygenY * width].Attributes = 0x0B;
			
			if(oxygenStr[i] == '|') {
				currentBuffer[i + oxygenY * width].Attributes = 0x0F;
			}
		}

		for(int i = 0; i < width; ++i) {
			currentBuffer[i + (oxygenY+1) * width].Char.AsciiChar = '-';
			currentBuffer[i + (oxygenY+1) * width].Attributes = 0x08;
		}

        render(width, height, 30);
    }

    changeColorThreadRunning = false;
    WaitForSingleObject(colorChangeThread, INFINITE);
	WaitForSingleObject(colorChangeThread1, INFINITE);
    CloseHandle(colorChangeThread);

    freeBuffers();
    freeObjects(objects);
    return 0;
}