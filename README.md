# 2D_GameEngine
2D Game Engine using C++ and SDL

This is an experimental game engine. The idea is that it will be used for 2D games that use procedural landmass generation and for fun experiments using Perlin noise.

After setting up the engine with a game loop and the ability to display textures using SDL, I spent the weekend getting up and running with rendering 1 dimensional perlin noise in the form of several 1 pixel square textures rendering on screen. I did this with the help of Javidx9 on Youtube and several other resources to get it working for my use case (https://www.youtube.com/c/javidx9).

![1D_perlin_noise](https://user-images.githubusercontent.com/82423961/200243773-0b9a01e5-7592-4cb4-9021-7657aef1aeda.png)

After fiddling around with the settings a bit, the following weekend I continued on getting 2 dimensional noise going from there. This was pretty simple, especially thanks to Javidx9. It's currently set up to loop through each element in the noise array and, depending on it's value, assign a specific color texture to render at those coordinates on the screen.

![2D_perlin_noise](https://user-images.githubusercontent.com/82423961/200244316-06495c58-93b3-418e-a653-b0536bfb2348.png)
