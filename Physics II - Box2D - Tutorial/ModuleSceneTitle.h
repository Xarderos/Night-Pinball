#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
//#include "Animation.h"

//struct SDL_Texture;

class ModuleSceneTitle : public Module
{
public:

	ModuleSceneTitle(Application* app, bool start_enabled=true);
	~ModuleSceneTitle();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* title;
	int TitleFont = -1;
	char TitleText[10] = { "\0" };
};
