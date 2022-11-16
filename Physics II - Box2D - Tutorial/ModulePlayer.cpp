#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{

	Bola = App->textures->Load("pinball/SpriteSheet.png");
	App->physics->CreateCircle(100, 100, 7);

	App->physics->CreateRectangle(10, 400, 600, 30);
	

	LOG("Loading player");
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	SDL_Rect BolaPin = { 1,703,14,14 };
	App->renderer->Blit(Bola, 1, 703, &BolaPin);


	return UPDATE_CONTINUE;
}



