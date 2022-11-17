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
	SDL_Texture* llumPedra;
	SDL_Texture* llumVerda;
	SDL_Texture* llumMap;
	SDL_Texture* llumGroga;

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

	//Sensors bools

	Animation bolapin;


	int lifes;
	int llumverda;
	int llumgroga;
};