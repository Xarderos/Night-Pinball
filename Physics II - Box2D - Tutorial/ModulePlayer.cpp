#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	Pedra = App->textures->Load("pinball/SpriteSheet.png");
	Bola = App->textures->Load("pinball/SpriteSheet.png");
	Ball = App->physics->CreateCircle(250, 400, 7);
	

	
	

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
	
	SDL_Rect BolaPin = { 20,703,14,14 };
	position = Ball->body->GetPosition();
	App->renderer->Blit(Bola, METERS_TO_PIXELS (position.x) -14, METERS_TO_PIXELS (position.y) -14, &BolaPin,1,50*(Ball->body->GetAngle()));

	SDL_Rect PedraPin = { 354,165,56,55 };
	App->renderer->Blit(Pedra, 94 * SCREEN_SIZE, 165 * SCREEN_SIZE, &PedraPin);

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		b2Vec2 vel = b2Vec2(0, 3 * GRAVITY_Y);
		Ball->body->SetLinearVelocity(vel);
	}



	return UPDATE_CONTINUE;
}



