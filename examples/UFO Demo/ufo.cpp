#include <iostream>
#include <cstring>
#include <cmath>
#include <vector>
#include <windows.h>
#include <conio.h>
#include "../include/Dolphin3D.h"

DWORD WINAPI changeColor(LPVOID lpParam) {
    Box* head = static_cast<Box*>(lpParam);
    while (true) {
        head->setColor(Color::Green());
        Sleep(1000);
        head->setColor(Color::Yellow());
        Sleep(1000);
        head->setColor(Color::Cyan());
        Sleep(1000);
        head->setColor(Color::White());
        Sleep(1000);
        head->setColor(Color::Blue());
        Sleep(1000);
    }
    return 0;
}

void PlayCollisionSound() {
    Beep(1000, 30);
	Beep(1200, 40);
}

int main() {
    Config cfg;
    if (!setConfig(folderName, configPath, cfg)) {
        return 1;
    }
    system("cls");

    int movePos = 0;
    int movePos1 = 10;
    int points = 0;
    const float moveSpeed = 0.4f;
    const float ufoLimit = 18.0f;
    bool gameActive = true;
    DWORD startTime = GetTickCount();
    const int gameDuration = 60000;

    const char* startText = ":::    ::: ::::::::::  ::::::::  \n"
                            ":+:    :+: :+:        :+:    :+: \n"
                            "+:+    +:+ +:+        +:+    +:+ \n"
                            "+#+    +:+ :#::+::#   +#+    +:+ \n"
                            "+#+    +#+ +#+        +#+    +#+ \n"
                            "#+#    #+# #+#        #+#    #+# \n"
                            "########  ###         ########   \n"
							"  ,____,  __,        /_   _   ,____, \n"
							"_/ / / (_(_/(__(_/__/ (__(/__/ / / (_\n"
							"               _/_                   \n"
							"              (/                     \n\n"
                            "Made by ColorProgrammy\n"
                            "Version: v1.0\n\n"
                            "Starting...";

    printf("%s", startText);
    Sleep(1000);
    system("cls");
	//playSoundAsync("assets\\nature.wav");

    srand(static_cast<unsigned int>(time(NULL)));
	SetConsoleTextAttribute(hConsole, FOREGROUND_BLUE | FOREGROUND_GREEN);

    bool hit;
    Color currentcolor;
    vec3 normal;

    int width = cfg.width;
    int height = cfg.height;

    setBuffer(width, height);
    initRender(width, height);
    setWindow(width, height, cfg.title);
    setIcon(cfg, folderName);

    const char* gradientName = GRADIENT_0;
    size_t gradientSize = 0;

    const size_t maxGradientSize = 100;
    char gradient[maxGradientSize];

    strncpy(gradient, gradientName, maxGradientSize);
    gradient[maxGradientSize-1] = '\0';
    setGradientSize(gradient, gradientSize);

    vec3 spherePos = vec3(10, 0, -8);
    vec3 spherePos1 = vec3(10, 10, -1);
    vec3 boxPos = vec3(10, 0, -7);
    vec3 rayPos = vec3(10, 0, -2);
    vec3 boxPos1 = vec3(10, 0, -6);
    vec3 planePos = vec3(0, 0, -5);
    vec3 light = vec3(0, 20, -7.0);

    std::vector<Object*> objects;
    objects.push_back(new Plane(planePos, vec3(0, 1, 0), 1.5f, Color::Green()));

    Sphere* headUFO = new Sphere(spherePos, 2.7f, 4.5f, Color::Cyan());
    Sphere* target = new Sphere(spherePos1, 3.0f, 10.0f, Color::Yellow());
	
    Box* rayUFO = new Box(rayPos, vec3(1.0f, 1.0f, 3.0f), 4.2f, Color::Cyan());
    Box* bodyUFO = new Box(boxPos1, vec3(4.2f, 4.2f, 0.75f), 3.5f, Color::Grey());

	objects.push_back(headUFO);
    objects.push_back(target);
    objects.push_back(rayUFO);
    objects.push_back(bodyUFO);

	//// Decorations
	// Bushes
	objects.push_back(new Sphere(vec3(15, 25, -3), 9.0f, 2.0f, Color::Green()));
	objects.push_back(new Sphere(vec3(15, 20, -3), 7.0f, 2.0f, Color::Green()));
	objects.push_back(new Sphere(vec3(15, 14, -3), 5.0f, 2.0f, Color::Green()));
	objects.push_back(new Sphere(vec3(15, 10, -3), 7.0f, 2.0f, Color::Green()));
	objects.push_back(new Sphere(vec3(15, 6, -3), 6.0f, 2.0f, Color::Green()));
	objects.push_back(new Sphere(vec3(15, 4, -3), 3.0f, 2.0f, Color::Green()));
	objects.push_back(new Sphere(vec3(15, 0, -3), 8.0f, 2.0f, Color::Green()));
	objects.push_back(new Sphere(vec3(15, -2, -3), 7.0f, 2.0f, Color::Green()));
	objects.push_back(new Sphere(vec3(15, -7, -3), 5.0f, 2.0f, Color::Green()));
	objects.push_back(new Sphere(vec3(15, -10, -3), 6.0f, 2.0f, Color::Green()));
	objects.push_back(new Sphere(vec3(15, -14, -3), 3.0f, 2.0f, Color::Green()));
	objects.push_back(new Sphere(vec3(15, -17, -3), 8.0f, 2.0f, Color::Green()));
	objects.push_back(new Sphere(vec3(15, -25, -3), 10.0f, 2.0f, Color::Green()));

	// Lake
	objects.push_back(new Sphere(vec3(-2, -10, 2), 4.0f, 3.0f, Color::Blue()));
	objects.push_back(new Sphere(vec3(-3, -9, 2), 3.0f, 3.0f, Color::Blue()));

	// Stones
	objects.push_back(new Box(vec3(-1, 7, 1), vec3(1.2f, 1.2f, 2.75f), 6.5f, Color::Grey()));
	objects.push_back(new Box(vec3(-2, 8, 1), vec3(1.0f, 1.2f, 2.75f), 6.5f, Color::Grey()));

	////

	HANDLE colorChangeThread = CreateThread(NULL, 0, changeColor, headUFO, 0, NULL);

    while (true) {
        swapBuffers(currentBuffer, displayBuffer, width, height);

        DWORD currentTime = GetTickCount();
        int elapsedSeconds = (currentTime - startTime) / 1000;
        int remainingTime = 60 - elapsedSeconds;

        if (gameActive && remainingTime <= 0) {
            gameActive = false;
        }

        if (!gameActive) {
			const char* timeisup = "______                                     \n"
								   "(  /    o           o  _                /  \n"
								   "  /    ,  _ _ _   _ ' (     , ,  ,_    /   \n"
								   "_/     (_/ / / / (/_  _)   (_/  _|_)  '    \n"
								   "                                 |   o     \n"
                                   "                                 /         \n";  
            system("cls");
            printf("%s\nTIME'S UP!\n\nPoints: %d\nPress SPACE to restart or ESC to exit", timeisup, points);
            
            while (true) {
                if (_kbhit()) {
                    char key = _getch();
                    if (key == KEY_ESC) { // ESC
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

        float randomY = -10 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 20));
		float randomX = -2 + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 14));



        float distance = length(rayPos - spherePos1);
        if (distance <= 1.5f * 3) {
            points++;
            PlayCollisionSound();
            spherePos1.x = randomX;
            spherePos1.y = randomY;
        }

        if (_kbhit()) {
            char key = _getch();
            if (key == 'a' || key == 'A' || key == 75) {
                movePos -= 1;
            }
            else if (key == 'd' || key == 'D' || key == 77) {
                movePos += 1;
            }
            else if (key == 'w' || key == 'W' || key == 72) {
                movePos1 += 1;
            }
            else if (key == 's' || key == 'S' || key == 80) {
                movePos1 -= 1;
            }
            else if (key == KEY_ESC) {
                break;
            }

            movePos = max(min(movePos, static_cast<int>(ufoLimit)), -static_cast<int>(ufoLimit));
            movePos1 = max(min(movePos1, static_cast<int>(ufoLimit * 2)), 3);

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

                renderObjects(objects, ro, rd, hit, currentcolor, brightness, normal, light, 0.9f, 2);
                renderColor(i, j, width, gradientSize, gradient, hit, currentcolor, brightness);
            }
        }

        char infoStr[64];
        sprintf_s(infoStr, " UFO Mayhem! | Time: %02d  Points: %d ", remainingTime, points);

        int infoY = height - 2;
        for (size_t i = 0; i < strlen(infoStr) && i < static_cast<size_t>(width); ++i) {
            currentBuffer[i + infoY * width].Char.AsciiChar = infoStr[i];
            currentBuffer[i + infoY * width].Attributes = 0x0F;
        }

        for (int i = 0; i < width; ++i) {
            currentBuffer[i + (infoY - 1) * width].Char.AsciiChar = '-';
            currentBuffer[i + (infoY - 1) * width].Attributes = 0x08;
        }

        render(width, height, 30);
    }

	CloseHandle(colorChangeThread);
	WaitForSingleObject(colorChangeThread, INFINITE);

    freeBuffers();
    freeObjects(objects);
    return 0;
}
