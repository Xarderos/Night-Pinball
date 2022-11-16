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
	Ball = App->physics->CreateCircle(260, 150, 7);
		
	bolapin.PushBack({ 1,703,14,14 });
	bolapin.PushBack({ 20,703,14,14 });
	bolapin.PushBack({ 39,703,14,14 });
	bolapin.PushBack({ 58,703,14,14 });
	bolapin.loop = true;
	bolapin.speed = 0.11f;


	

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
	App->renderer->Blit(Bola, METERS_TO_PIXELS (position.x) -14, METERS_TO_PIXELS (position.y) -14, &BolaPin);
	bolapin.Update();


	return UPDATE_CONTINUE;
}



