# Audio

Now we've reached audio.

I wrote a library for this to make it easier for you to embed audio into your application.

Well, let's get started.

---

### There are two types of audio:

```c++
playSoundSync(filename);
// and
playSoundAsync(filename);
```

But how are they different?

----

Let's look at the first one.

`playSoundSync(filename);`

Here we enter the relative path (or full path) to the audio.

`playSoundSync(filename);` plays audio, but it kind of pauses the program until the audio finishes.

---

`playSoundAsync(filename);`

It also plays the sound, but does not pause other actions, unlike `playSoundSync(filename);`


That's all, you learned about audio in detail.
--
