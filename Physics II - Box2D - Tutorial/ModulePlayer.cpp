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
{

}

// Load assets
bool ModulePlayer::Start()
{

	Pedra = App->textures->Load("pinball/SpriteSheet.png");
	Bola = App->textures->Load("pinball/SpriteSheet.png");
	llumPedra = App->textures->Load("pinball/SpriteSheet.png");

	Ball = App->physics->CreateCircle(250, 380, 7);

	//Sensors

	PedraSen = App->physics->CreateRectangleSensor(122, 193, 40, 39);

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
	App->renderer->Blit(Pedra, 94 * SCREEN_SIZE, 165 * SCREEN_SIZE, &PedraPin);

	if (sensor_Pedra)
	{
		SDL_Rect PedraSen = { 82,844,16,15 };
		App->renderer->Blit(llumPedra, 96 * SCREEN_SIZE, 227 * SCREEN_SIZE,&PedraSen);
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

		if (sensor_Pedra != true) {
			sensor_Pedra = true;
		}
	}
}


