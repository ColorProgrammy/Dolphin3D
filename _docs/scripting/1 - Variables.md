# Variables

Hello!
Now we'll deal with variables.

First you need to setup the DolphinEngine (see _setup.txt).

It is recommended that you know at least basic C++.
----------------------------
Well, we need to get acquainted with the code.

```c++
// Variables //

// Screen size
int width = 120;
int height = 30;

// Aspect
float aspect = (float)width / height;
float pixelAspect = 8.0f / 16.0f;

// Render
float minIt = 99999;
float dist = 1e9;

// Object variables
vec3 n = 0;
vec3 n2 = 0;
vec3 n3 = 0;
vec3 n4 = 0

// Lighting
float albedo = 1;
float brightness = 1;

/////////
```

What does this all mean?
Let's take everything in order.

-----------------
Screen Size
-----------------

These variables are responsible for the screen size (or more precisely, what resolution to render in)

If you bring the screen to maximazed or change it somehow, then, everything will fall apart.

> It is NOT RECOMMENDED to set values higher than 131 and 31, as the image will not be displayed correctly.

---
Aspect
---

There are two variables: aspect and pixelAspect.
They are responsible for the correct display of the image.

> Fun fact: the pixels in the console are not square. They are 8px by 16px. That's what pixelAspect is for, otherwise we'd have a flat image.


**It's better not to touch them.**

---
Render
---

These 2 variables are responsible for rendering.
Without them there would be a lot of bugs and shortcomings.

> Variable "Dist" is needed for the correct display of objects. Without it, the ball from the cube standing behind us would be shown as in front.

**It's better not to touch them, again...**

---
Object variables
---

In this case, 4 variables are presented.
There may be different numbers of them, depending on the number of objects.

They are needed so that objects have light and shadow.

> In the very first object (no matter which one), it is not necessary to specify a new variable. In this case, we have a variable n. In other cases, in the object code, n = <variable> is written; where <variable> is a new variable.

---
Lighting
---

This is where things get more interesting.
These two variables are responsible for light.

Brightness is responsible for all the light and its brightness.
With albedo it's a little different. It is responsible for the white color in objects. It can be applied to all, or only to one object (the line is inserted into the object code).

> You can play around with these parameters. You can change the brightness, albedo. You can even make it so that only the object is visible and the background with the plane are completely black. Your imagination plays here!

---

## Now you know what these variables represent!

