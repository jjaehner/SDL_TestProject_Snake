#ifndef _TEST_INCLUDES_H
//#include <windows.h>
#include <sdl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <time.h>
#include "GameTimer.h"
#include "SnakeObject.h"
#define _TEST_INCLUDES_H

int main(int argc, char** argv)
{
	srand(time(0));

	SDL_Window* _windowPtr = nullptr;
	SDL_Renderer* _rendererPtr = nullptr;

	GameTimer gameTimer;

	SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_JOYSTICK | SDL_INIT_GAMECONTROLLER);
	IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP);
	TTF_Init();

	_windowPtr = SDL_CreateWindow("SDL Window", 100, 100, 660, 660, 0);
	_rendererPtr = SDL_CreateRenderer(_windowPtr, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	SDL_Surface* _bunnyImgPtr = IMG_Load("fuzzy_bunny.jpg");
	SDL_Texture* _bunnyTexturePtr = SDL_CreateTextureFromSurface(_rendererPtr, _bunnyImgPtr);
	//SDL_SetWindowSize(_windowPtr, _bunnyImgPtr->w, _bunnyImgPtr->h);
	SDL_Rect _bunnyRect = { 0, 0, _bunnyImgPtr->w, _bunnyImgPtr->h };

	//TTF_Font* _arial = TTF_OpenFont("arial.ttf", 24);
	//SDL_Color _ttfColor = { 255, 0, 0 };
	//SDL_Surface* _ttfSurfacePtr = TTF_RenderText_Solid(_arial, "Hello World!", _ttfColor);
	//SDL_Texture* _ttfTexturePtr = SDL_CreateTextureFromSurface(_rendererPtr, _ttfSurfacePtr);
	SDL_Rect _ttfRect = { 0, 0, 0, 0 };

	SnakeObject* snakeObj = new SnakeObject(_rendererPtr);

	int frameCount = 0;
	int currentTicks = 0;

	char fpsChars[20];

	while (true)
	{
		gameTimer.update();

		SDL_Event evt;
		SDL_PollEvent(&evt);

		snakeObj->update(gameTimer.getDeltaTimeInSeconds());

		if (evt.type == SDL_KEYDOWN)
		{
			switch (evt.key.keysym.sym)
			{
			case SDLK_w:
				snakeObj->changeDirection(NORTH);
				break;
			case SDLK_a:
				snakeObj->changeDirection(WEST);
				break;
			case SDLK_s:
				snakeObj->changeDirection(SOUTH);
				break;
			case SDLK_d:
				snakeObj->changeDirection(EAST);
				break;
			default:
				break;
			}
		}

		if (evt.type == SDL_QUIT) {
			break;
		}

		SDL_SetRenderDrawColor(_rendererPtr, 100, 149, 237, 255);
		SDL_RenderClear(_rendererPtr);
		snakeObj->render();
		//SDL_RenderCopy(_rendererPtr, _bunnyTexturePtr, &_bunnyRect, nullptr);
		//SDL_RenderCopy(_rendererPtr, _ttfTexturePtr, nullptr, nullptr);
		SDL_RenderPresent(_rendererPtr);
		sprintf(fpsChars, "%f", gameTimer.getFps());
		SDL_SetWindowTitle(_windowPtr, fpsChars);
	}
	
	delete snakeObj;

	SDL_DestroyTexture(_bunnyTexturePtr);
	SDL_DestroyRenderer(_rendererPtr);
	_rendererPtr = nullptr;
	SDL_DestroyWindow(_windowPtr);
	_windowPtr = nullptr;

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return 0;
}

#endif