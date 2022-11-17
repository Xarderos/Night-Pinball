#pragma once
#include "Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "Globals.h"
#include <vector>
class PhysBody;

class ModuleSceneIntro : public Module
{
public:

	// Constructors & Destructors
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	// Main module steps
	bool Start();
	update_status Update();
	bool CleanUp();
	void map();
	void OnCollision(PhysBody* bodyA, PhysBody* bodyB);

public:

	//Vector is good, vector is good, Pol Rius 
	std::vector<PhysBody*> Map;



	// Lower ground sensor (will kill all objects passig through it)
	PhysBody* lower_ground_sensor;
	PhysBody* rightflipcircle;
	PhysBody* leftflipcircle;
	PhysBody* rightflipper;
	PhysBody* leftflipper;
	PhysBody* NightsensorF1_1;
	PhysBody* NightsensorF1_2;
	PhysBody* NightsensorF1_3;

	PhysBody* NightsensorF2_1;
	PhysBody* NightsensorF2_2;
	PhysBody* NightsensorF2_3;

	bool sensed;

	// Textures

	SDL_Texture* Mapa;

	SDL_Rect MapaPin;
	SDL_Rect RightFlipperRect;
	SDL_Rect LeftFlipperRect;


	// FX
	uint bonus_fx;

	// Raycast
	p2Point<int> ray;
	bool ray_on;

	bool mapselector;
	int floornum;
};
