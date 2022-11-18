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

	//Vector is good, vector is good, POL RIUS!!
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

	PhysBody* Floor3_1;
	PhysBody* Floor3_2;
	PhysBody* Floor3_ac;

	PhysBody* rBumperRight;
	PhysBody* rBumperLeft;


	bool sensed;

	// Textures

	SDL_Texture* Mapa;

	SDL_Rect MapaPin;
	SDL_Rect MapaPin1f;

	SDL_Rect RightFlipperRect;
	SDL_Rect LeftFlipperRect;
	SDL_Rect RightBouncer;
	SDL_Rect LeftBouncer;




	// FX
	uint bonus_fx;

	// Raycast
	p2Point<int> ray;
	bool ray_on;

	bool mapselector;
	int floornum;
};
