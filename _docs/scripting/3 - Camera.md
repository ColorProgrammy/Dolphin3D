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

---
Setup the camera
--
```c++
vec3 ro = vec3(-10, 0, 0);
vec3 rd = norm(vec3(1, uv));
```
### We will only analyze the first line, because the second one does not require flattery.

We specify the camera position in this line of code: `vec3 ro = vec3(-10, 0, 0)`

The closer the x coordinate is to 0, the closer it is to the center.

> You can play with the coordinates.

----
Rotate the camera
--

Now we will look at camera rotation.

Here you can specify `RotateX, RotateY, RotateZ`

```c++
ro = rotateX(ro, 0.25);
ro = rotateY(ro, 0.25);
rd = rotateY(rd, 0.25);
              
ro = rotateZ(ro, t * 0.01);
rd = rotateZ(rd, t * 0.01);
```

You can choose a one-time rotation or a continuous one.

One-time rotation:
```c++
rd = rotateY(rd, 0.25);
```

Continuous rotation:
```c++ 
ro = rotateZ(ro, t * 0.01);
```

The difference between them is that the second parameter is multiplied by the variable t (the variable needed for the loop)

#### IF YOU WANT TO ROTATE THE CAMERA AROUND THE CENTER, THEN SPECIFY BOTH ro AND rd WITH THE SAME PARAMETERS.

> I don't know if it's a bug or not, if you rotate the camera by X all the time, then at one point the camera will suddenly turn over, but then return to its original state. Try doing this, it creates a cool effect.

## Well now you know more about the camera!
