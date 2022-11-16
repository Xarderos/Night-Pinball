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
	Ball = App->physics->CreateCircle(240, 400, 7);
		

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
	b2Vec2 position;
	
	SDL_Rect BolaPin = { 1,703,14,14 };
	position = Ball->body->GetPosition();
	App->renderer->Blit(Bola, METERS_TO_PIXELS (position.x) - 7, METERS_TO_PIXELS (position.y) - 7, &BolaPin);

	return UPDATE_CONTINUE;
}



