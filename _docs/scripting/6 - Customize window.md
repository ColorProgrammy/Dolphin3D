# Customize window

Now it's time to customize the screen.

```c++
// Screen setup
SetConsoleTitleA("title");
system("mode con cols=120 lines=30");

setIcon(filepath);
```

Let's figure it out :3

---
Title
---

```c++
SetConsoleTitleA("title");
```

This line is responsible for the window title.

Where title is your name.

> Let me remind you that we write the name in quotes (if it is not a variable call)

----
Screen size
---

```c++
system("mode con cols=120 lines=30);
```

It looks more complicated,
but that's only at first glance.

Remember lesson 1 about variables?
So, there at the very beginning we indicated 
the length and width of the screen. 

Yes, this line of code 
is responsible for customizing the screen.

In cols we write width, and in lines we write height.

> And remember that it is not recommended to set values higher than 132 and 31. (in the next updates everything may be fixed)


---
Set icon
---

Now we have reached the icon.

```c++
setIcon(filepath);
```

This simple command sets the icon.

`filepath` - path to the icon.

You can set a `relative` path, just like with audio (previous lesson)

**It is recommended to use an icon image with the `.ico` format**

> To store files with images, audio and other things, you can place them in the assets folder (just don't forget to compile together with this folder, so there are no problems.


# That's it, now you know about screen customization!
