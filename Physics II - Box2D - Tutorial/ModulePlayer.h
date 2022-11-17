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

	SDL_Rect BolaPin;

	//PhysBodies
	PhysBody* Ball;
	PhysBody* Rectangle;
	PhysBody* PedraSen;


	//Sensors bools

	bool sensor_Pedra = false;

	Animation bolapin;


	int lifes;
};