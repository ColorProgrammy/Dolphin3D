# Objects

Finally we got to the objects.

But let's look at the code...

```c++
            // Initialization intersection
	        vec2 intersection = sphere(ro - spherePos, rd, 2);
				
	        for (int k = 0; k < 5; k++) {
                // Objects

                // Sphere
                // Change "spherePos" to your other position
		        intersection = sphere(ro - spherePos, rd, 2);
		        if (intersection.x > 0 && intersection.x < dist) {
		            dist = intersection.x;
                    vec3 itPoint = ro - spherePos + rd * dist;
                    minIt = intersection.x;
                    n = norm(itPoint);
		        }

                // Box
		        intersection = box(ro - boxPos, rd, 1,2,1, n1);
		        if (intersection.x > 0 && intersection.x < dist) {
		            dist = intersection.x;
		            n = n1;
                    vec3 itPoint = ro - boxPos + rd * dist;
                    minIt = intersection.x;
                    n = norm(itPoint);
				}
		    
                // Plane
		        intersection = plane(ro, rd, vec3(0, 0, -1), 1);
		        if (intersection.x > 0) {
		            float planeDist = intersection.x;
		            if (planeDist < minIt) {
			            minIt = planeDist;
			            n = vec3(0, 0, -1);
			            albedo = 0.5;
			        }
		        }
```

### Wow, I've piled on some code...
#### It will seem to you that it is very, very difficult, but this is only at first glance.

---
Initialization
--

**I won't comment here in particular, how is it that everything is just one line :/**

`vec2 intersection = sphere(ro - spherePos, rd, 2);`

Here we initialize intersection

**But why?**

We can't always assign `vec2` to intersection - it will give an error.

Yes, we could have done without this line, but we would have had to assign `vec2` to one object and we could have gotten confused.

This is why we initialize, so as not to get confused in the code

---
Objects
--

### Finally we got to the objects!!

But first, we must enter the cycle.
```c++
for (int k = 0; k < 5; k++) { // next is the code
```

Next we need to add objects.

### Structure

First I will show you the structure, so after you know more about the structure it will be easier for you to add objects.

The structure looks like this:
```c++
intersection = object(ro - position, rd, size, n);
if (intersection.x > 0 && intersection.x < dist) {
    n = variable;
    dist = intersection.x;
    vec3 itPoint = ro - position + rd * dist;
    minIt = intersection.x;
    n = norm(itPoint);
    albedo = 1.0; // not necessary
}
```

It looks complicated anyway, but from what is written you need to know `20%`

`object` - type of object (sphere, box, etc.)

`size` - size of the object (but it varies for different objects)

`position` - position of the object (we indicated the position variables at the beginning, see lesson 2)

`variable` - object variable (remember lesson 1)

`albedo` - "white color" of the object (see lesson 1)

And that's all you need to know, almost...

Also for other objects you need to specify a variable (remember lesson 1, where you specified `vec2 n = 0;`) and call it in the object `n = variable`. (except for some one object).

If you don't understand what I'm talking about, here's an example:
```c++
intersection = sphere(ro - spherePos, rd, 2);
if (intersection.x > 0 && intersection.x < dist) {
    n = n1;
    dist = intersection.x;
    vec3 itPoint = ro - spherePos + rd * dist;
    minIt = intersection.x;
    n = norm(itPoint);
    albedo = 1.0; // not necessary
}
```

I won't talk much about the rest of the lines of code, just say that they are responsible for lighting and display.

I've told you about the structure, but you don't know about the objects yet, let's fix that.

----
### Sphere

It looks like this:
```c++
intersection = sphere(ro - spherePos, rd, 2);
if (intersection.x > 0 && intersection.x < dist) {
    n = n1; // not necessary to specify if it will be one object without this parameter
    dist = intersection.x;
    vec3 itPoint = ro - spherePos + rd * dist;
    minIt = intersection.x;
    n = norm(itPoint);
}
```

I have already indicated it earlier, so there should be no questions.

---
### Box

And this is what it looks like:
```c++
intersection = box(ro - boxPos, rd, 1,2,1, n1);
if (intersection.x > 0 && intersection.x < dist) {
    dist = intersection.x;
    n = n1;
    vec3 itPoint = ro - boxPos + rd * dist;
    minIt = intersection.x;
    n = norm(itPoint);
}
```

It seems like there aren't any particular differences, but look at this line: 
`intersection = box(ro - boxPos, rd, 1, 2, 1, n1);`

As you can see, more parameters have appeared.

`intersection = box(ro - position, rd, x, y, z, n);`

So I think it became more understandable.

We can specify the size by 3 coordinates.
And also n (object variable) is added at the end.

Overall, there are no other differences.

----
### Plane

We've reached the very last object at the moment.

```c++
intersection = plane(ro, rd, vec3(0, 0, -1), 1);
if (intersection.x > 0) {
    float planeDist = intersection.x;
    if (planeDist < minIt) {
        minIt = planeDist;
        n = vec3(0, 0, -1);
        albedo = 0.5;
    }
}
```

The changes are immediately visible.

But, as I said before, here you need to know `20%`

Let's look at the first line: 
`intersection = plane(ro, rd, vec3(0, 0, -1), 1);`

I'll say more, nothing needs to be changed in this line except the position (`vec3(x, y, z)`), if necessary.

You may also be confused by this: 
`n = vec3(0, 0, -1);`

Here you also don't need to change anything (but perhaps if you want to change the position of the plane, then you need to change its value to the same as in the first line)

Well, the last thing we need to understand about the plane is `albedo = 0.5;`

As we may remember from lesson 1, this is the white color regulator.

Essentially, we are changing the brightness of the object.

> If you want, you can leave it as is or change it.

----
That's all! You've learned more about objects!
--
