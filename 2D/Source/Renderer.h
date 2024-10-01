#pragma once
#include <SDL.h>
#include <iostream>

class Renderer {
public:
	int Initialize();
	int CreateWindow(int width, int height);
	SDL_Renderer* renderer = nullptr;
private:

}; 
