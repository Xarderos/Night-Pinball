#pragma once
#include "Module.h"
#include "SDL/include/SDL_rect.h"

class ModuleFadeToBlack : public Module
{
public:
	ModuleFadeToBlack(Application* app, bool start_enabled = true);

	~ModuleFadeToBlack();

	bool Start()override;

	update_status Update() override;

	update_status PostUpdate()override;

	bool FadeToBlack(Module* toDisable, Module* toEnable, float frames = 60);

private:

	enum Fade_Step
	{
		NONE,
		TO_BLACK,
		FROM_BLACK
	}currentStep = Fade_Step::NONE;

	Uint32 frameCount = 0;
	Uint32 maxFadeFrames = 0;

	SDL_Rect screenRect;

	Module* moduleToEnable = nullptr;
	Module* moduleToDisable = nullptr;
};
