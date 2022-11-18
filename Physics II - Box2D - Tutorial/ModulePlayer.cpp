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

	//Textures
	Botons = App->textures->Load("pinball/SpriteSheet.png");
	Pedra = App->textures->Load("pinball/SpriteSheet.png");
	Bola = App->textures->Load("pinball/SpriteSheet.png");
	llumPedra = App->textures->Load("pinball/SpriteSheet.png");
	llumVerda = App->textures->Load("pinball/SpriteSheet.png");
	llumMap = App->textures->Load("pinball/SpriteSheet.png");
	llumGroga = App->textures->Load("pinball/SpriteSheet.png");
	suportCano = App->textures->Load("pinball/SpriteSheet.png");
	cano = App->textures->Load("pinball/SpriteSheet.png");
	Tcanoverd1 = App->textures->Load("pinball/SpriteSheet.png");
	Tcanoverd2 = App->textures->Load("pinball/SpriteSheet.png");

	//Sorolls

	pedrasound = App->audio->LoadFx("pinball/Pedra.ogg");
	botonsound = App->audio->LoadFx("pinball/Botons.ogg");

	Ball = App->physics->CreateCircle(23, 243, 7);

	//Sensors

	PedraSen = App->physics->CreateRectangleSensor(120, 193, 35, 34);
	MapSen = App->physics->CreateRectangleSensor(24, 246, 5, 7);
	MapSen2 = App->physics->CreateRectangleSensor(24, 264, 5, 7);
	MapSen3 = App->physics->CreateRectangleSensor(24, 282, 5, 7);
	CanoSen = App->physics->CreateRectangleSensor(245, 300, 20, 20);
	VermeSen = App->physics->CreateRectangleSensor(154, 132, 7, 7);
	BlauSen = App->physics->CreateRectangleSensor(107, 104, 7, 7);
	BlancSen = App->physics->CreateRectangleSensor(249, 112, 5, 4);
	CanoVerdSen1 = App->physics->CreateRectangleSensor(23, 373, 10, 10);
	CanoVerdSen2 = App->physics->CreateRectangleSensor(219, 373, 10, 10);

	llumgroga = false;
	llumgroga2 = false;
	llumgroga3 = false;
	llumblava = false;
	llumvermella = false;

	Ball->listener = this;
	MapaPin1f = { 262, 1, 256, 432 };
	Reixa = { 1,596,28,42 };
	NightRampPart = { 1,547,104,36 };
	BouncerBall = { 90,618,21,20 };

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
	delete VermeSen;
	VermeSen = nullptr;
	delete BlauSen;
	BlauSen = nullptr;
	delete BlancSen;
	BlancSen = nullptr;
	delete CanoVerdSen1;
	CanoVerdSen1 = nullptr;
	delete CanoVerdSen2;
	CanoVerdSen2 = nullptr;
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

		//RECUPERA UN CANÓ
		if (estrellagroga == false) {
			numCVerds++;
			estrellagroga = true;
		}
		
	}
	if (llumblava == true)
	{
		SDL_Rect BlauSen = { 82,731,23,19 };
		App->renderer->Blit(Bola, 96 * SCREEN_SIZE, 114 * SCREEN_SIZE, &BlauSen);
		SDL_Rect BlauSen2 = { 153,563,14,14 };
		App->renderer->Blit(Bola, 128 * SCREEN_SIZE, 337 * SCREEN_SIZE, &BlauSen2);

		//RECUPERA UN CANÓ
		if (estrellablava == false) {
			numCVerds++;
			estrellablava = true;
		}

	}

	SDL_Rect BolaPin = { 20,703,14,14 };
	position = Ball->body->GetPosition();
	App->renderer->Blit(Bola, 43 * SCREEN_SIZE, 83 * SCREEN_SIZE, &BouncerBall);
	App->renderer->Blit(Bola, 55 * SCREEN_SIZE, 65 * SCREEN_SIZE, &BouncerBall);

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

	SDL_Rect Porteta = {202,523,19,7};
	App->renderer->Blit(Bola, 237 * SCREEN_SIZE, 109 * SCREEN_SIZE, &Porteta);

	SDL_Rect PedraPin = { 354,165,56,55 };
	App->renderer->Blit(Pedra, 92 * SCREEN_SIZE, 165 * SCREEN_SIZE, &PedraPin);

	if (llumblanca == true)
	{
		SDL_Rect Boss = { 125, 563, 14, 14 };
		App->renderer->Blit(Bola, 100 * SCREEN_SIZE, 337 * SCREEN_SIZE, &Boss);
		
		//RECUPERA UN CANÓ
		if (estrellablanca == false) {
			numCVerds++;
			estrellablanca = true;
		}
	}

	if (llumblava == true && llumvermella == true && llumverda > 2 && llumgroga == true && llumgroga2 == true && llumgroga3 == true)
	{
		SDL_Rect Boss = { 216, 438, 44, 56 };
		App->renderer->Blit(Bola, 180 * SCREEN_SIZE, 45 * SCREEN_SIZE, &Boss);
	}

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

		//RECUPERA UN CANÓ
		if (estrellaverda == false) {
			numCVerds++;
			estrellaverda = true;
		}
	}
	if (llumvermella == true)
	{
		SDL_Rect VermeSen = { 122,758,9,9 };
		App->renderer->Blit(Bola, 136 * SCREEN_SIZE, 141 * SCREEN_SIZE, &VermeSen);
		SDL_Rect VermeSen2 = { 135,761,9,9 };
		App->renderer->Blit(Bola, 149 * SCREEN_SIZE, 144 * SCREEN_SIZE, &VermeSen2);
		SDL_Rect VermeSen3 = { 148,758,9,9 };
		App->renderer->Blit(Bola, 162 * SCREEN_SIZE, 141 * SCREEN_SIZE, &VermeSen3);
		SDL_Rect VermeSen4 = { 139,569,14,14 };
		App->renderer->Blit(Bola, 114 * SCREEN_SIZE, 343 * SCREEN_SIZE, &VermeSen4);

		//RECUPERA UN CANÓ
		if (estrellavermella == false) {
			numCVerds++;
			estrellavermella = true;
		}
	}


	//NO POT SALTAR QUAN HA PASSAT PEL CANÓ
	if (canjump) {
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
		{
			b2Vec2 vel = b2Vec2(0, 3 * GRAVITY_Y);
			Ball->body->SetLinearVelocity(vel);
		}
	}
	if ((METERS_TO_PIXELS(position.y)) > 1500 && lifes > 0)
	{
		Ball->body->SetTransform({ PIXEL_TO_METERS(250), PIXEL_TO_METERS(400) }, 0);
		lifes--;
		canjump = true;
	}

	//temporal
	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
	{
		b2Vec2 vel = b2Vec2(0, 3 * GRAVITY_Y);
		Ball->body->SetLinearVelocity(vel);
	}
	//temporal


	//TEXTURAS CAÑÓN
	SDL_Rect SuportCanoPin = { 494, 1009, 24, 192 };
	App->renderer->Blit(suportCano, 233 * SCREEN_SIZE, 233 * SCREEN_SIZE, &SuportCanoPin);

	SDL_Rect CanoPin;

	if (canoframe3 == 0) {

		if (dinsCano == false) {
			CanoPin = { 1, 498, 33, 34 };
		}
		else {
			CanoPin = { 33, 498, 33, 34 };
		}
	}
	else if (canoframe3 > 0) {
		CanoPin = { 69, 498, 33, 34 };
		canoframe3--;
	}
	App->renderer->Blit(cano, 224 * SCREEN_SIZE, 280 * SCREEN_SIZE, &CanoPin);

	//SALTA AL MAPA QUAN TOCA EL CANÓ
	if (SaltCano == true) {

		b2Vec2 tp = b2Vec2(PIXEL_TO_METERS(245), PIXEL_TO_METERS(300));
		Ball->body->SetTransform(tp, 0);

		dinsCano = true;

		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
		{
			b2Vec2 tp = b2Vec2(PIXEL_TO_METERS(207), PIXEL_TO_METERS(273));
			Ball->body->SetTransform(tp, 0);

			b2Vec2 vel = b2Vec2(-14, -15);
			Ball->body->SetLinearVelocity(vel);

			DrawBola = true;
			SaltCano = false;
			dinsCano = false;
			canoframe3 = 5;
			canjump = false; //Quan estiguis a dins del mapa la bola no pujarà quan li donis a DOWN
		}
		
	}
	
	if (canoverdsen1 == true) {
		b2Vec2 vel = b2Vec2(0, 2 * GRAVITY_Y);
		Ball->body->SetLinearVelocity(vel);
		canoverdsen1 = false;
	}

	if (canoverdsen2 == true) {
		b2Vec2 vel = b2Vec2(0, 2 * GRAVITY_Y);
		Ball->body->SetLinearVelocity(vel);
		canoverdsen2 = false;
	}

	//TEXTURA CANONS VERDS
	SDL_Rect CanoVerd1Pin;
	SDL_Rect CanoVerd2Pin;

	if (canoverd1 == true) {
		CanoVerd1Pin = { 52, 617, 16, 21 };
		canoverd1Anim = 1;
		
	}
	else {
		if (canoverd1Anim > 0 && canoverd1Anim <= 3) {
			CanoVerd1Pin = { 131, 617, 16, 21 };
			canoverd1Anim++;
		}
		else if (canoverd1Anim > 3 && canoverd1Anim <= 6) {
			CanoVerd1Pin = { 113, 617, 16, 21 };
			canoverd1Anim++;
		}
	}

	if (canoverd2 == true) {
		CanoVerd2Pin = { 52, 617, 16, 21 };
		canoverd2Anim = 1;

	}
	else {
		if (canoverd2Anim > 0 && canoverd2Anim <= 3) {
			CanoVerd2Pin = { 131, 617, 16, 21 };
			canoverd2Anim++;
		}
		else if (canoverd2Anim > 3 && canoverd2Anim <= 6) {
			CanoVerd2Pin = { 113, 617, 16, 21 };
			canoverd2Anim++;
		}
	}
	App->renderer->Blit(Tcanoverd1, 15 * SCREEN_SIZE, 364 * SCREEN_SIZE, &CanoVerd1Pin);
	App->renderer->Blit(Tcanoverd2, 211 * SCREEN_SIZE, 364 * SCREEN_SIZE, &CanoVerd2Pin);


	//RECUPERA CANONS VERDS QUAN GUANYA UNA ESTRELLA
	if (canoverd1 == false) {
		if (numCVerds > 0) {
			canoverd1 = true;
			numCVerds--;
		}
	}

	if (canoverd2 == false) {
		if (numCVerds > 0) {
			canoverd2 = true;
			numCVerds--;
		}
	}


	//TEMPORAL (testeo de sensores)
	if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN) {
		b2Vec2 vel = b2Vec2(PIXEL_TO_METERS(23), PIXEL_TO_METERS(350));
		Ball->body->SetTransform(vel, 0);
	}
	if (App->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN) {
		b2Vec2 vel = b2Vec2(PIXEL_TO_METERS(211), PIXEL_TO_METERS(350));
		Ball->body->SetTransform(vel, 0);
	}

	//TEMPORAL (resetear cañones verdes)
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) {
		canoverd1 = true;
		canoverd2 = true;
	}



	return UPDATE_CONTINUE;
}
void ModulePlayer::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	if (bodyB == PedraSen) {
		/*App->audio->PlayFx(pedrasound);*/
		llumverda++;
	}
	if (bodyB == MapSen && llumgroga == false) {
		/*App->audio->PlayFx(botonsound);*/
		llumgroga = true;
	}
	if (bodyB == MapSen2 && llumgroga2 == false) {
		/*App->audio->PlayFx(botonsound);*/
		llumgroga2 = true;
	}
	if (bodyB == MapSen3 && llumgroga3 == false && App->scene_intro->floornum != 3) {
		/*App->audio->PlayFx(botonsound);*/
		llumgroga3 = true;
	}
	if (bodyB == CanoSen) {
		/*App->audio->PlayFx*/
		SaltCano = true;
		DrawBola = false;
	}
	if (bodyB == VermeSen && llumvermella == false) {
		llumvermella = true;
	}
	if (bodyB == BlauSen && llumblava == false) {
		llumblava = true;
	}
	if (bodyB == BlancSen && llumblanca == false) {
		llumblanca = true;
	}
	if (bodyB == App->scene_intro->Floor3_2) {
		App->scene_intro->floornum = 1;
		App->scene_intro->mapselector = true;
	}
	if (bodyB == CanoVerdSen1 && canoverd1 == true) {
		canoverdsen1 = true;
		canoverd1 = false;
	}
	if (bodyB == CanoVerdSen2 && canoverd2 == true) {
		canoverdsen2 = true;
		canoverd2 = false;
	}
}
