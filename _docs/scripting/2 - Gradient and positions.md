# Gradient and positions

### Here's what we'll look at:
```c++
int main() {

  // Gradient
  char gradient[] = " .,:!/rH$#@";
  int gradientSize = strlen(gradient) - 1;

  char* screen = new char[width * height + 1];
  screen[width * height] = '\0';

  for (int t = 0; t < 10000000000000; ++t) {
    
      // Positions
      vec3 light = norm(vec3(-0.5, 0.5, -1.0));
    
      vec3 spherePos = vec3(0, 0, 0);
      vec3 boxPos = vec3(0, 0, -4);
  }

```
Again I dumped a bunch of code...

Let's take it in order.

---
Gradient
---

This is where the gradient is stored as symbols.
In this case we have 

### " .,:!/rH$#@"

> You can change the gradient to your liking.

```c++
int gradientSize = strlen(gradient) - 1;
```
This line is responsible for the numbering of symbols in the gradient.

**It is better not to touch it.**

---
Positions
---
**We missed a small piece of code, but we don't need it.**

```c++
for (int t = 0; t < 10000000000000; ++t)
```
We've entered the animation cycle, by the way.

```c++
// Positions
vec3 light = norm(vec3(-0.5, 0.5, -1.0));
    
vec3 spherePos = vec3(0, 0, 0);
vec3 boxPos = vec3(0, 0, -4);
```

You will have a question: **"What is vec3?"**

### Vector3 is the position of the object in 3D space.

So, we have `c++ vec3<name> = vec(x, y, z);`
We kind of place the object on the stage.

> For light we also need to use the normalization function, but otherwise it's no different. `c++ vec3 light = norm(vec3(-0.5, 0.5, -1.0));`

**You can specify any names for the positions.**

> To raise an object up, you need to change the z coordinate to a NEGATIVE number.

### Here we learn a little more about gradient and position.
