# Camera

Now we will deal with the camera and its settings.

We will provide you with the code:
```c++
// Camera
vec3 ro = vec3(-10, 0, 0);
vec3 rd = norm(vec3(1, uv));

// Rotate the camerа
ro = rotateX(ro, 0.25);
ro = rotateY(ro, 0.25);
rd = rotateY(rd, 0.25);
              
ro = rotateZ(ro, t * 0.01);
rd = rotateZ(rd, t * 0.01);
```

Okay, let's figure it out.

--
Setup the camera
--
```c++
vec3 ro = vec3(-10, 0, 0);
vec3 rd = norm(vec3(1, uv));
```
### We will only analyze the first line, because the second one does not require flattery.

