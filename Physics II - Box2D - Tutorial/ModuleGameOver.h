#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
//#include "Animation.h"

struct SDL_Texture;

class ModuleGameOver : public Module
{
public:

	ModuleGameOver(Application* app, bool start_enabled);
	~ModuleGameOver();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* fondo;
	int TitleFont = -1;
	char TitleText[10] = { "\0" };
};
