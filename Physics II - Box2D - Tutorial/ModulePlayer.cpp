#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneIntro.h"
#include "ModuleFont.h"
#include "Animation.h"

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

	Bola = App->textures->Load("pinball/SpriteSheet.png");

	//Fonts

	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	scoreFont = App->font->Load("pinball/rtype_font3.png", lookupTable, 2);
	
	//Sorolls

	pedrasound = App->audio->LoadFx("pinball/Pedra.ogg");
	botonsound = App->audio->LoadFx("pinball/Botons.ogg");

	Ball = App->physics->CreateCircle(250, 400, 7);

	//Boss Animations

	BossAnim.PushBack({ 3,438,64,58 });
	BossAnim.PushBack({ 67,438,64,58 });
	BossAnim.PushBack({ 131,438,64,58 });
	BossAnim.PushBack({ 195,438,64,58 });
	BossAnim.PushBack({ 259,438,64,58 });
	BossAnim.PushBack({ 323,438,64,58 });
	BossAnim.loop = true;
	BossAnim.speed = 0.05f;

	//Animations

	ChipAnim.PushBack({ 261,731,39,77 });
	ChipAnim.PushBack({ 300,731,39,77 });
	ChipAnim.PushBack({ 339,731,39,77 });
	ChipAnim.PushBack({ 378,731,39,77 });
	ChipAnim.loop = true;
	ChipAnim.speed = 0.03f;

	FleGrocAnim.PushBack({ 279,933,37,72 });
	FleGrocAnim.PushBack({ 316,933,37,72 });
	FleGrocAnim.PushBack({ 353,933,37,72 });
	FleGrocAnim.PushBack({ 390,933,36,72 });
	FleGrocAnim.loop = true;
	FleGrocAnim.speed = 0.03f;

	CanoVerdAnim.PushBack({ 52, 617, 16, 21 });
	CanoVerdAnim.PushBack({ 113, 617, 16, 21 });
	CanoVerdAnim.PushBack({ 131, 617, 16, 21 });
	CanoVerdAnim.PushBack({ 0, 0, 0, 0 });

	CanoVerdAnim.loop = false;
	CanoVerdAnim.speed = 0.05;

	CanoVerdAnim2.PushBack({ 52, 617, 16, 21 });
	CanoVerdAnim2.PushBack({ 113, 617, 16, 21 });
	CanoVerdAnim2.PushBack({ 131, 617, 16, 21 });
	CanoVerdAnim2.PushBack({ 0, 0, 0, 0 });

	CanoVerdAnim2.loop = false;
	CanoVerdAnim2.speed = 0.05;



	//Sensors

	PedraSen = App->physics->CreateRectangleSensor(120, 193, 35, 34);
	MapSen = App->physics->CreateRectangleSensor(24, 246, 5, 7);
	MapSen2 = App->physics->CreateRectangleSensor(24, 264, 5, 7);
	MapSen3 = App->physics->CreateRectangleSensor(24, 282, 5, 7);
	CanoSen = App->physics->CreateRectangleSensor(245, 300, 20, 20);
	VermeSen = App->physics->CreateRectangleSensor(154, 132, 7, 7);
	BlauSen = App->physics->CreateRectangleSensor(107, 104, 7, 7);
	BlancSen = App->physics->CreateRectangleSensor(249, 112, 5, 4);
	CanoVerdSen1 = App->physics->CreateRectangleSensor(23, 382, 10, 10);
	CanoVerdSen2 = App->physics->CreateRectangleSensor(219, 382, 10, 10);


	int Rampa1[8] = {
			208, 1297,
			229, 1287,
			229, 1299,
			208, 1307
	};
	RampaT1=App->physics->CreateChain(0, -910, Rampa1, 8);
	
	int Rampa2[8] = {
			36, 1298,
			13, 1289,
			13, 1304,
			33, 1311
	};
	RampaT2 = App->physics->CreateChain(0, -910, Rampa2, 8);
	canoverd1 = false;
	canoverd2 = false;

	llumgroga = false;
	llumgroga2 = false;
	llumgroga3 = false;
	llumblava = false;
	llumvermella = false;

	Ball->listener = this;
	MapaPin1f = { 262, 1, 256, 432 };
	Reixa = { 1,596,28,42 };
	BouncerBall = { 90,618,21,20 };
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

	if (lifes <= 0) {
		GameOver = true;
			Black = App->textures->Load("pinball/black.png");
			App->font->BlitText(300, 500, scoreFont, "g  a  m  e    o  v  e  r");
			App->font->BlitText(300, 520, scoreFont, "p  r  e  s  s    r    t  o");
			App->font->BlitText(300, 540, scoreFont, "r  e  s  t  a  r  t");
			lifes = 5;
			score = 0;
			if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN) {
				App->textures->Unload(Black);
				App->font->UnLoad(scoreFont);
				App->player->Start();
			}	
		
	}
	
	if (llumgroga == false)
	{
		BotonsPin = { 396, 517, 8, 13 };
		App->renderer->Blit(Bola, 22 * SCREEN_SIZE, 240 * SCREEN_SIZE, &BotonsPin);
	}
	if (llumgroga2 == false)
	{
		BotonsPin2 = { 396, 517, 8, 13 };
		App->renderer->Blit(Bola, 22 * SCREEN_SIZE, 258 * SCREEN_SIZE, &BotonsPin2);
	}
	if (llumgroga3 == false)
	{
		BotonsPin3 = { 396, 517, 8, 13 };
		App->renderer->Blit(Bola, 22 * SCREEN_SIZE, 276 * SCREEN_SIZE, &BotonsPin3);
	}
	if (llumgroga == true)
	{
		MapSen_ = { 21, 858, 19,15 };
		App->renderer->Blit(Bola, 35 * SCREEN_SIZE, 241 * SCREEN_SIZE, &MapSen_);
		BotonsPin = { 409, 519, 6, 11 };
		App->renderer->Blit(Bola, 22 * SCREEN_SIZE, 240 * SCREEN_SIZE, &BotonsPin);
	}
	if (llumgroga2 == true)
	{
		MapSen_ = { 21, 874, 19,15 };
		App->renderer->Blit(Bola, 35 * SCREEN_SIZE, 257 * SCREEN_SIZE, &MapSen_);
		BotonsPin = { 409, 519, 6, 11 };
		App->renderer->Blit(Bola, 22 * SCREEN_SIZE, 258 * SCREEN_SIZE, &BotonsPin);
	}
	if (llumgroga3 == true)
	{
		MapSen_ = { 21, 890, 19,15 };
		App->renderer->Blit(Bola, 35 * SCREEN_SIZE, 273 * SCREEN_SIZE, &MapSen_);
		BotonsPin = { 409, 519, 6, 11 };
		App->renderer->Blit(Bola, 22 * SCREEN_SIZE, 276 * SCREEN_SIZE, &BotonsPin);
	}
	if (llumgroga == true && llumgroga2 == true && llumgroga3 == true)
	{
		GrocSen = { 147, 548, 14, 14 };
		App->renderer->Blit(Bola, 122 * SCREEN_SIZE, 322 * SCREEN_SIZE, &GrocSen);

		//RECUPERA UN CANÓ
		if (estrellagroga == false) {
			numCVerds++;
			estrellagroga = true;
		}
		
	}
	if (llumblava == true)
	{
		BlauSen_ = { 82,731,23,19 };
		App->renderer->Blit(Bola, 96 * SCREEN_SIZE, 114 * SCREEN_SIZE, &BlauSen_);
		BlauSen2 = { 153,563,14,14 };
		App->renderer->Blit(Bola, 128 * SCREEN_SIZE, 337 * SCREEN_SIZE, &BlauSen2);

		//RECUPERA UN CANÓ
		if (estrellablava == false) {
			numCVerds++;
			estrellablava = true;
		}

	}

	Chip = ChipAnim.GetCurrentFrame();
	App->renderer->Blit(Bola, 15 * SCREEN_SIZE, 106 * SCREEN_SIZE, &Chip);
	ChipAnim.Update();

	FleGroc = FleGrocAnim.GetCurrentFrame();
	App->renderer->Blit(Bola, 189 * SCREEN_SIZE, 118 * SCREEN_SIZE, &FleGroc);
	FleGrocAnim.Update();


	if (llumblava == true && llumvermella == true && llumverda > 2 && llumgroga == true && llumgroga2 == true && llumgroga3 == true && llumblanca == true)
	{
		Llumlila = { 173, 566, 30, 18 };
		App->renderer->Blit(Bola, 106 * SCREEN_SIZE, 362 * SCREEN_SIZE, &Llumlila);
	}
	if (llumblanca == true)
	{
		Boss = { 125, 563, 14, 14 };
		App->renderer->Blit(Bola, 100 * SCREEN_SIZE, 337 * SCREEN_SIZE, &Boss);

		//RECUPERA UN CANÓ
		if (estrellablanca == false) {
			numCVerds++;
			estrellablanca = true;
		}
	}
	if (llumverda > 0)
	{
		PedraSen_ = { 82,844,16,15 };
		App->renderer->Blit(Bola, 96 * SCREEN_SIZE, 227 * SCREEN_SIZE, &PedraSen_);
	}
	if (llumverda > 1)
	{
		PedraSen_ = { 82,844,16,15 };
		App->renderer->Blit(Bola, 113 * SCREEN_SIZE, 231 * SCREEN_SIZE, &PedraSen_);
	}
	if (llumverda > 2)
	{
		PedraSen_ = { 82,844,16,15 };
		App->renderer->Blit(Bola, 130 * SCREEN_SIZE, 227 * SCREEN_SIZE, &PedraSen_);
	}
	if (llumverda > 2)
	{
		VerdSen = { 131,548,14,14 };
		App->renderer->Blit(Bola, 106 * SCREEN_SIZE, 322 * SCREEN_SIZE, &VerdSen);

		//RECUPERA UN CANÓ
		if (estrellaverda == false) {
			numCVerds++;
			estrellaverda = true;
		}
	}
	if (llumvermella == true)
	{
		VermeSen_ = { 122,758,9,9 };
		App->renderer->Blit(Bola, 136 * SCREEN_SIZE, 141 * SCREEN_SIZE, &VermeSen_);
		VermeSen2 = { 135,761,9,9 };
		App->renderer->Blit(Bola, 149 * SCREEN_SIZE, 144 * SCREEN_SIZE, &VermeSen2);
		VermeSen3 = { 148,758,9,9 };
		App->renderer->Blit(Bola, 162 * SCREEN_SIZE, 141 * SCREEN_SIZE, &VermeSen3);
		VermeSen4 = { 139,569,14,14 };
		App->renderer->Blit(Bola, 114 * SCREEN_SIZE, 343 * SCREEN_SIZE, &VermeSen4);

		//RECUPERA UN CANÓ
		if (estrellavermella == false) {
			numCVerds++;
			estrellavermella = true;
		}
	}
	BolaPin = { 20,703,14,14 };
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

	Porteta = {202,523,19,7};
	App->renderer->Blit(Bola, 237 * SCREEN_SIZE, 109 * SCREEN_SIZE, &Porteta);

	PedraPin = { 354,165,56,55 };
	App->renderer->Blit(Bola, 92 * SCREEN_SIZE, 165 * SCREEN_SIZE, &PedraPin);

	if (llumblava == true && llumvermella == true && llumverda > 2 && llumgroga == true && llumgroga2 == true && llumgroga3 == true && llumblanca == true)
	{
		LlumBoss = { 176, 722, 9, 12 };
		App->renderer->Blit(Bola, 190 * SCREEN_SIZE, 105 * SCREEN_SIZE, &LlumBoss);
		Boss2 = BossAnim.GetCurrentFrame();
		App->renderer->Blit(Bola, 173 * SCREEN_SIZE, 37 * SCREEN_SIZE, &Boss2);
		BossAnim.Update();
	}


	//NO POT SALTAR QUAN HA PASSAT PEL CANÓ
	if (canjump) {
		if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_DOWN)
		{
			b2Vec2 vel = b2Vec2(0, 3 * GRAVITY_Y);
			Ball->body->SetLinearVelocity(vel);
		}
	}
	if ((METERS_TO_PIXELS(position.y)) > 1500)
	{
		Ball->body->SetTransform({ PIXEL_TO_METERS(250), PIXEL_TO_METERS(400) }, 0);
		//lifes--;
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
	SuportCanoPin = { 494, 1009, 24, 192 };
	App->renderer->Blit(Bola, 233 * SCREEN_SIZE, 233 * SCREEN_SIZE, &SuportCanoPin);

	CanoPin;

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
	App->renderer->Blit(Bola, 224 * SCREEN_SIZE, 280 * SCREEN_SIZE, &CanoPin);

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
	
	if (canoverd1 == true && CanoVerdSen1->body->IsActive()==true)
	{
		b2Vec2 vel = b2Vec2(0, 2.2 * GRAVITY_Y);
		Ball->body->SetLinearVelocity(vel);
		CanoVerdSen1->body->SetActive(false);
	}

	if (canoverd2 == true && CanoVerdSen2->body->IsActive() == true) {
		b2Vec2 vel = b2Vec2(0, 2.2 * GRAVITY_Y);
		Ball->body->SetLinearVelocity(vel);
		CanoVerdSen2->body->SetActive(false);
	}
	if (canoverd1 == true) {
		animaciocano;
		animaciocano = CanoVerdAnim.GetCurrentFrame();
		App->renderer->Blit(Bola, 15 * SCREEN_SIZE, 391 * SCREEN_SIZE, &animaciocano);
		CanoVerdAnim.Update();
		rampataronja1;
		rampataronja1 = { 449, 621, 20, 16 };
		App->renderer->Blit(Bola, 13 * SCREEN_SIZE, 376 * SCREEN_SIZE, &rampataronja1);

	}

	if (canoverd2 == true) {
		animaciocano;
		animaciocano = CanoVerdAnim2.GetCurrentFrame();
		App->renderer->Blit(Bola, 211 * SCREEN_SIZE, 391 * SCREEN_SIZE, &animaciocano);
		CanoVerdAnim2.Update();
		rampataronja2;
		rampataronja2 = { 420, 621, 20, 16 };
		App->renderer->Blit(Bola, 209 * SCREEN_SIZE, 376 * SCREEN_SIZE, &rampataronja2);
	}


	if (canoverd1 == false) {
		CanoVerd1Pin;
		CanoVerd1Pin = { 52, 617, 16, 21 };
		App->renderer->Blit(Bola, 15 * SCREEN_SIZE, 384 * SCREEN_SIZE, &CanoVerd1Pin);
		canoverd1Anim = 1;
		
	}
	if (canoverd2 == false) {
		CanoVerd2Pin;
		CanoVerd2Pin = { 52, 617, 16, 21 };
		App->renderer->Blit(Bola, 211 * SCREEN_SIZE, 384 * SCREEN_SIZE, &CanoVerd2Pin);
		canoverd2Anim = 1;

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




	//FONTS


	App->font->BlitText(58, 248, scoreFont, scoreText);


	App->font->BlitText(620,15, scoreFont, "s  t  a  g  e           0 1");
	App->font->BlitText(620, 200, scoreFont, "s  c  o  r  e");
	App->font->BlitText(620, 450, scoreFont, "l i v  e  s");
	App->font->BlitText(620, 700, scoreFont, "c  o  m  b  o");
	App->font->BlitText(620, 900, scoreFont, "h i g  h  s  c  o  r  e");


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
	if (bodyB == CanoVerdSen1) {
		canoverd1 = true;

	}
	if (bodyB == CanoVerdSen2) {
		canoverd2 = true;

	}
	if (bodyB == App->scene_intro->rBumperRight) {
		App->scene_intro->rightBtimer = 20;
	}
	if (bodyB == App->scene_intro->rBumperLeft) {
		App->scene_intro->leftBtimer = 20;
	}

}
