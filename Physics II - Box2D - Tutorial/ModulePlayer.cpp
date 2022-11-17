#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModulePlayer::~ModulePlayer()
{

}

// Load assets
bool ModulePlayer::Start()
{
	Botons = App->textures->Load("pinball/SpriteSheet.png");
	Pedra = App->textures->Load("pinball/SpriteSheet.png");
	Bola = App->textures->Load("pinball/SpriteSheet.png");
	llumPedra = App->textures->Load("pinball/SpriteSheet.png");
	llumVerda = App->textures->Load("pinball/SpriteSheet.png");
	llumMap = App->textures->Load("pinball/SpriteSheet.png");
	llumGroga = App->textures->Load("pinball/SpriteSheet.png");
	suportCano = App->textures->Load("pinball/SpriteSheet.png");
	cano = App->textures->Load("pinball/SpriteSheet.png");

	Ball = App->physics->CreateCircle(250, 400, 7);

	//Sensors

	PedraSen = App->physics->CreateRectangleSensor(120, 193, 35, 34);
	MapSen = App->physics->CreateRectangleSensor(24, 246, 5, 7);
	MapSen2 = App->physics->CreateRectangleSensor(24, 264, 5, 7);
	MapSen3 = App->physics->CreateRectangleSensor(24, 282, 5, 7);
	CanoSen = App->physics->CreateRectangleSensor(245, 300, 20, 20);

	llumgroga = false;
	llumgroga2 = false;
	llumgroga3 = false;

	Ball->listener = this;
	MapaPin1f = { 262, 1, 256, 432 };
	Reixa = { 1,596,28,42 };
	NightRampPart = { 1,547,104,36 };
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
	delete MapSen2;
	MapSen2 = nullptr;
	delete MapSen3;
	MapSen3 = nullptr;
	delete CanoSen;
	CanoSen = nullptr;
	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{

	b2Vec2 position;

	if (llumgroga == false)
	{
		SDL_Rect BotonsPin = { 396, 517, 8, 13 };
		App->renderer->Blit(Botons, 22 * SCREEN_SIZE, 240 * SCREEN_SIZE, &BotonsPin);
	}
	if (llumgroga2 == false)
	{
		SDL_Rect BotonsPin2 = { 396, 517, 8, 13 };
		App->renderer->Blit(Botons, 22 * SCREEN_SIZE, 258 * SCREEN_SIZE, &BotonsPin2);
	}
	if (llumgroga3 == false)
	{
		SDL_Rect BotonsPin3 = { 396, 517, 8, 13 };
		App->renderer->Blit(Botons, 22 * SCREEN_SIZE, 276 * SCREEN_SIZE, &BotonsPin3);
	}
	if (llumgroga == true)
	{
		SDL_Rect MapSen = { 21, 858, 19,15 };
		App->renderer->Blit(llumPedra, 35 * SCREEN_SIZE, 241 * SCREEN_SIZE, &MapSen);
		SDL_Rect BotonsPin = { 409, 519, 6, 11 };
		App->renderer->Blit(Botons, 22 * SCREEN_SIZE, 240 * SCREEN_SIZE, &BotonsPin);
	}
	if (llumgroga2 == true)
	{
		SDL_Rect MapSen = { 21, 874, 19,15 };
		App->renderer->Blit(llumPedra, 35 * SCREEN_SIZE, 257 * SCREEN_SIZE, &MapSen);
		SDL_Rect BotonsPin = { 409, 519, 6, 11 };
		App->renderer->Blit(Botons, 22 * SCREEN_SIZE, 258 * SCREEN_SIZE, &BotonsPin);
	}
	if (llumgroga3 == true)
	{
		SDL_Rect MapSen = { 21, 890, 19,15 };
		App->renderer->Blit(llumPedra, 35 * SCREEN_SIZE, 273 * SCREEN_SIZE, &MapSen);
		SDL_Rect BotonsPin = { 409, 519, 6, 11 };
		App->renderer->Blit(Botons, 22 * SCREEN_SIZE, 276 * SCREEN_SIZE, &BotonsPin);
	}
	if (llumgroga == true && llumgroga2 == true && llumgroga3 == true)
	{
		SDL_Rect GrocSen = { 147, 548, 14, 14 };
		App->renderer->Blit(llumGroga, 122 * SCREEN_SIZE, 322 * SCREEN_SIZE, &GrocSen);
		
	}
	
	

	SDL_Rect BolaPin = { 20,703,14,14 };
	position = Ball->body->GetPosition();
	
	if (App->scene_intro->floornum == 2) {
		App->renderer->Blit(Bola, 2, 2, &MapaPin1f);
		App->renderer->Blit(Bola, 33 * SCREEN_SIZE, 8 * SCREEN_SIZE, &NightRampPart);
	}
	if (App->scene_intro->floornum == 3) {
		App->renderer->Blit(Bola, 2, 2, &MapaPin1f);
		App->renderer->Blit(Bola, 5 * SCREEN_SIZE, 175 * SCREEN_SIZE, &Reixa);
	}

	if (DrawBola == true) {
		App->renderer->Blit(Bola, METERS_TO_PIXELS(position.x) - 14, METERS_TO_PIXELS(position.y) - 14, &BolaPin, 1, 50 * (Ball->body->GetAngle()));
	}

	if (App->scene_intro->floornum == 1) {
		App->renderer->Blit(Bola, 2, 2, &MapaPin1f);
		App->renderer->Blit(Bola, 5 * SCREEN_SIZE, 175 * SCREEN_SIZE, &Reixa);
		App->renderer->Blit(Bola, 33 * SCREEN_SIZE, 8 * SCREEN_SIZE, &NightRampPart);
	}
	if (App->scene_intro->floornum == 2) {
		App->renderer->Blit(Bola, 5 * SCREEN_SIZE, 175 * SCREEN_SIZE, &Reixa);

	}

	if (App->scene_intro->floornum == 3) {
		App->renderer->Blit(Bola, 33 * SCREEN_SIZE, 8 * SCREEN_SIZE, &NightRampPart);
	}

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


	SDL_Rect SuportCanoPin = { 494, 1009, 24, 192 };
	App->renderer->Blit(suportCano, 233 * SCREEN_SIZE, 233 * SCREEN_SIZE, &SuportCanoPin);

	SDL_Rect CanoPin = { 1, 498, 33, 34 };
	App->renderer->Blit(cano, 224 * SCREEN_SIZE, 280 * SCREEN_SIZE, &CanoPin);

	//SALTA AL MAPA QUAN TOCA EL CANÓ
	if (SaltCano == true) {
		b2Vec2 tp = b2Vec2(PIXEL_TO_METERS(207), PIXEL_TO_METERS(273));
		Ball->body->SetTransform(tp, 0);
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			b2Vec2 vel = b2Vec2(-2, -3);
			Ball->body->SetLinearVelocity(vel);

			DrawBola = true;
			SaltCano = false;
		}
		
	}
	

	return UPDATE_CONTINUE;
}
void ModulePlayer::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyB == PedraSen) {
		/*App->audio->PlayFx*/
		llumverda++;
	}
	if (bodyB == MapSen && llumgroga == false) {
		/*App->audio->PlayFx*/
		llumgroga = true;
	}
	if (bodyB == MapSen2 && llumgroga2 == false) {
		/*App->audio->PlayFx*/
		llumgroga2 = true;
	}
	if (bodyB == MapSen3 && llumgroga3 == false) {
		/*App->audio->PlayFx*/
		llumgroga3 = true;
	}
	if (bodyB == CanoSen) {
		/*App->audio->PlayFx*/
		SaltCano = true;
		DrawBola = false;
	}
}


