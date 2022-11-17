#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{

}

// Load assets
bool ModulePlayer::Start()
{

	Pedra = App->textures->Load("pinball/SpriteSheet.png");
	Bola = App->textures->Load("pinball/SpriteSheet.png");
	llumPedra = App->textures->Load("pinball/SpriteSheet.png");
	llumVerda = App->textures->Load("pinball/SpriteSheet.png");
	llumMap = App->textures->Load("pinball/SpriteSheet.png");
	llumGroga = App->textures->Load("pinball/SpriteSheet.png");

	Ball = App->physics->CreateCircle(250, 380, 7);

	//Sensors

	PedraSen = App->physics->CreateRectangleSensor(120, 193, 35, 34);
	MapSen = App->physics->CreateRectangleSensor(44, 248, 21, 17);
	MapSen2 = App->physics->CreateRectangleSensor(44, 260, 21, 17);
	MapSen3 = App->physics->CreateRectangleSensor(44, 280, 21, 17);

	Ball->listener = this;


	lifes = 5;
	LOG("Loading player");
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");
	delete Ball;
	Ball = nullptr;
	delete PedraSen;
	PedraSen = nullptr;
	delete MapSen;
	MapSen = nullptr;
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	b2Vec2 position;
	
	SDL_Rect BolaPin = { 20,703,14,14 };
	position = Ball->body->GetPosition();
	App->renderer->Blit(Bola, METERS_TO_PIXELS (position.x) -14, METERS_TO_PIXELS (position.y) -14, &BolaPin,1, 50*(Ball->body->GetAngle()));

	SDL_Rect PedraPin = { 354,165,56,55 };
	App->renderer->Blit(Pedra, 92 * SCREEN_SIZE, 165 * SCREEN_SIZE, &PedraPin);
	
	if (llumverda > 0)
	{
		SDL_Rect PedraSen = { 82,844,16,15 };
		App->renderer->Blit(llumPedra, 96 * SCREEN_SIZE, 227 * SCREEN_SIZE,&PedraSen);
	}
	if (llumverda > 1)
	{
		SDL_Rect PedraSen = { 82,844,16,15 };
		App->renderer->Blit(llumPedra, 113 * SCREEN_SIZE, 231 * SCREEN_SIZE, &PedraSen);
	}
	if (llumverda > 2)
	{
		SDL_Rect PedraSen = { 82,844,16,15 };
		App->renderer->Blit(llumPedra, 130 * SCREEN_SIZE, 227 * SCREEN_SIZE, &PedraSen);
	}
	if (llumverda > 2)
	{
		SDL_Rect VerdSen = { 131,548,14,14 };
		App->renderer->Blit(llumVerda, 106 * SCREEN_SIZE, 322 * SCREEN_SIZE, &VerdSen);
	}
	if (llumgroga > 0)
	{
		SDL_Rect MapSen = { 21, 858, 19,15 };
		App->renderer->Blit(llumPedra, 35 * SCREEN_SIZE, 241 * SCREEN_SIZE, &MapSen);
	}
	if (llumgroga > 1)
	{
		SDL_Rect MapSen = { 21, 874, 19,15 };
		App->renderer->Blit(llumPedra, 35 * SCREEN_SIZE, 257 * SCREEN_SIZE, &MapSen);
	}
	if (llumgroga > 1)
	{
		SDL_Rect MapSen = { 21, 890, 19,15 };
		App->renderer->Blit(llumPedra, 35 * SCREEN_SIZE, 273 * SCREEN_SIZE, &MapSen);
	}
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		b2Vec2 vel = b2Vec2(0, 3 * GRAVITY_Y);
		Ball->body->SetLinearVelocity(vel);
	}

	if ((METERS_TO_PIXELS(position.y)) > 1500 && lifes > 0)
	{
		Ball->body->SetTransform({ PIXEL_TO_METERS(250), PIXEL_TO_METERS(400) }, 0);
		lifes--;
	}

	

	return UPDATE_CONTINUE;
}
void ModulePlayer::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyB == PedraSen) {
		/*App->audio->PlayFx*/
		llumverda++;
	}
	if (bodyB == MapSen) {
		/*App->audio->PlayFx*/
		llumgroga++;
	}
}


