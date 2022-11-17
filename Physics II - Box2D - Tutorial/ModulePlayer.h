#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;


class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);
	

public:

	

	//Textures
	SDL_Texture* Bola;
	SDL_Texture* Pedra;
	SDL_Texture* Botons;
	SDL_Texture* llumPedra;
	SDL_Texture* llumVerda;
	SDL_Texture* llumMap;
	SDL_Texture* llumGroga;
	SDL_Texture* suportCano;
	SDL_Texture* cano;

	SDL_Rect BolaPin;
	SDL_Rect MapaPin1f;
	SDL_Rect Reixa;
	SDL_Rect NightRampPart;

	//PhysBodies
	PhysBody* Ball;
	PhysBody* Rectangle;
	PhysBody* PedraSen;
	PhysBody* MapSen;
	PhysBody* MapSen2;
	PhysBody* MapSen3;
	PhysBody* CanoSen;
	PhysBody* VermeSen;
	PhysBody* BlauSen;
	PhysBody* BlancSen;
	//Sensors bools

	Animation bolapin;
	Animation CanoAnim;

	int botonsound;
	int pedrasound;
	int lifes;
	int llumverda;
	bool llumblanca;
	bool llumvermella;
	bool llumblava;
	bool llumgroga;
	bool llumgroga2;
	bool llumgroga3;
	bool DrawBola = true;
	bool SaltCano = false;
	bool dinsCano = false;
	int canoframe3 = 0;
	bool canjump = true;
};