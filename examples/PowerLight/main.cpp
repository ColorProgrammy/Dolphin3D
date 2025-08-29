#include <iostream>
#include <cmath>
#include <vector>
#include <windows.h>
#include <conio.h>
#include "../include/Dolphin3D.h"

int main() {
    int width = 100;
    int height = 30;

    setBuffer(width, height);
    initRender(width, height);
    setWindow(width, height, "PointLight");

    system("cls");

    const char* gradientName = GRADIENT_0;
    size_t gradientSize = 0;
    char gradient[100];
    setGradientSize(gradient, gradientSize, 100, gradientName);

    std::vector<Light> lights;
    createPointLight(lights, vec3(0,5,-7), 30.5f, 150.0f);

    std::vector<Object*> objects;
    objects.push_back(new Plane(vec3(0, 0, -5), vec3(0, 1, 0), 2.0f, Color::White()));
    objects.push_back(new Sphere(vec3(0, 0, -5), 4.0f, 1.5f, Color::Yellow()));

    float lightSpeed = 0.3f;
    float cameraSpeed = 0.5f;
    float rotationSpeed = 0.05f;
    vec3 ro(-11, 0, -2);

    bool lightView = false;
    vec3 originalLightPos = lights[0].position;

    mat4 cameraRotation = mat4::identity();
    mat4 lightRotation = mat4::identity();
    
    float cameraYaw = 0.4f;
    float cameraPitch = 0.0f;
    float lightYaw = 0.0f;
    float lightPitch = 0.0f;

    while(true) {
        swapBuffers(currentBuffer, displayBuffer, width, height);

        if(GetAsyncKeyState('V') & 0x8000) {
            lightView = !lightView;
			Beep(600, 200);
            Sleep(200);
        }

        if(GetAsyncKeyState(VK_UP) & 0x8000) lightYaw -= rotationSpeed;
        if(GetAsyncKeyState(VK_DOWN) & 0x8000) lightYaw += rotationSpeed;
        if(GetAsyncKeyState(VK_LEFT) & 0x8000) lightPitch -= rotationSpeed;
        if(GetAsyncKeyState(VK_RIGHT) & 0x8000) lightPitch += rotationSpeed;

        lightPitch = max(min(lightPitch, 1.5f), -1.5f);   
        lightRotation = mat4::rotateY(lightYaw) * mat4::rotateX(lightPitch);

        vec3 lightOffset = originalLightPos - vec3(0,0,-5);
        lightOffset = lightRotation.rotateVector(lightOffset);
        lights[0].position = vec3(0,0,-5) + lightOffset;

        if(!lightView) {
            if(GetAsyncKeyState('L') & 0x8000) cameraPitch += rotationSpeed;
            if(GetAsyncKeyState('J') & 0x8000) cameraPitch -= rotationSpeed;
            if(GetAsyncKeyState('K') & 0x8000) cameraYaw -= rotationSpeed;
            if(GetAsyncKeyState('I') & 0x8000) cameraYaw += rotationSpeed;

            cameraPitch = max(min(cameraPitch, 1.5f), -1.5f);
            cameraRotation = mat4::rotateY(cameraYaw) * mat4::rotateX(cameraPitch);

            if(GetAsyncKeyState('E') & 0x8000) ro.z += cameraSpeed;
            if(GetAsyncKeyState('Q') & 0x8000) ro.z -= cameraSpeed;
            if(GetAsyncKeyState('S') & 0x8000) ro.x -= cameraSpeed;
            if(GetAsyncKeyState('W') & 0x8000) ro.x += cameraSpeed;
            if(GetAsyncKeyState('D') & 0x8000) ro.y += cameraSpeed;
            if(GetAsyncKeyState('A') & 0x8000) ro.y -= cameraSpeed;
        }

        if(GetAsyncKeyState('H') & 0x8000) originalLightPos.y += lightSpeed;
        if(GetAsyncKeyState('F') & 0x8000) originalLightPos.y -= lightSpeed;
        if(GetAsyncKeyState('G') & 0x8000) originalLightPos.x -= lightSpeed;
        if(GetAsyncKeyState('T') & 0x8000) originalLightPos.x += lightSpeed;
        if(GetAsyncKeyState('R') & 0x8000) originalLightPos.z -= lightSpeed;
        if(GetAsyncKeyState('Y') & 0x8000) originalLightPos.z += lightSpeed;

        bool hit;
        Color currentcolor;
        vec3 normal;
        
        for(int j = 0; j < height; ++j) {
            for(int i = 0; i < width; ++i) {
                float brightness = 0.2f;
                vec2 uv = createUV(i, j, width, height);
                
                vec3 rd = norm(vec3(1, uv));
                
                if(lightView) {
                    rd = lightRotation.rotateVector(rd);
                    vec3 rotated_ro = lights[0].position;
                    brightness = 0.5f;
                    
                    setObjects(objects, rotated_ro, rd, hit, currentcolor, brightness, normal, lights, 0.4f, 7.0f);
                } else {
                    rd = cameraRotation.rotateVector(rd);
                    vec3 rotated_ro = ro;
                    
                    setObjects(objects, rotated_ro, rd, hit, currentcolor, brightness, normal, lights, 0.4f, 7.0f);
                }
                
                setColors(i, j, width, gradientSize, gradient, hit, currentcolor, brightness);
            }
        }

        if(lightView) {
            const char* text = "LIGHT VIEW (Arrows: rotate, T/G: up/down, F/H: left/right, R/Y: forward/back, V: switch)               ";
            int textLength = strlen(text);
            
            for(int i = 0; i < textLength && i < width; i++) {
                int index = i;
                currentBuffer[index].Char.AsciiChar = text[i];
                currentBuffer[index].Attributes = 0x0F;
            }
        } else {
            const char* text = "CAMERA VIEW (WASD: move, QE: up/down, IJKL: rotate, T/G/F/H/R/Y: light control, V: switch)             ";
            int textLength = strlen(text);
            
            for(int i = 0; i < textLength && i < width; i++) {
                int index = i;
                currentBuffer[index].Char.AsciiChar = text[i];
                currentBuffer[index].Attributes = 0x0F;
            }
        }
        
        render(width, height, 30);

        if(_kbhit() && _getch() == KEY_ESC) break;
    }
    freeBuffers();
    freeObjects(objects);
    
    return 0;
}
