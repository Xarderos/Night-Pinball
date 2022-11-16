#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{

	// Initialise all the internal class variables, at least to NULL pointer

	ray_on = false;
	sensed = false;
}

ModuleSceneIntro::~ModuleSceneIntro()
{
	// You should do some memory cleaning here, if required
}

bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	// Set camera position
	App->renderer->camera.x = App->renderer->camera.y = 0;
	Mapa = App->textures->Load("pinball/SpriteSheet.png");
	map();

	// Add this module (ModuleSceneIntro) as a listener for collisions with the sensor.
	rightflipcircle = App->physics->CreateCircleStatic(155, 386, 5);
	leftflipcircle = App->physics->CreateCircleStatic(87, 386, 5);
	rightflipper = App->physics->CreateRectangle(140, 385, 20, 6);
	leftflipper = App->physics->CreateRectangle(101, 385, 20, 6);

	b2RevoluteJointDef rightFlip;
	rightFlip.bodyA = rightflipper->body;
	rightFlip.bodyB = rightflipcircle->body;
	rightFlip.localAnchorA.Set(PIXEL_TO_METERS(16), 0);
	rightFlip.localAnchorB.Set(0, 0);
	rightFlip.referenceAngle = 0 * DEGTORAD;
	rightFlip.enableLimit = true;
	rightFlip.lowerAngle = -30 * DEGTORAD;
	rightFlip.upperAngle = 23 * DEGTORAD;

	b2RevoluteJoint* rightflipjoint = (b2RevoluteJoint*)App->physics->world->CreateJoint(&rightFlip);

	b2RevoluteJointDef leftFlip;
	leftFlip.bodyA = leftflipper->body;
	leftFlip.bodyB = leftflipcircle->body;
	leftFlip.localAnchorA.Set(PIXEL_TO_METERS(-16), 0);
	leftFlip.localAnchorB.Set(0, 0);
	leftFlip.referenceAngle = 0 * DEGTORAD;
	leftFlip.enableLimit = true;
	leftFlip.lowerAngle = -23 * DEGTORAD;
	leftFlip.upperAngle = 30 * DEGTORAD;

	b2RevoluteJoint* leftflipjoint = (b2RevoluteJoint*)App->physics->world->CreateJoint(&leftFlip);
	return ret;
}

bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

update_status ModuleSceneIntro::Update()
{
	

	if ((App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT))
	{
		rightflipper->body->ApplyForceToCenter(b2Vec2(0, -200), 1);
	}

	if ((App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT))
	{
		leftflipper->body->ApplyForceToCenter(b2Vec2(0, -200), 1);
	}
	
	// The target point of the raycast is the mouse current position (will change over game time)
	iPoint mouse;
	mouse.x = App->input->GetMouseX();
	mouse.y = App->input->GetMouseY();

	// Total distance of the raycast reference segment
	int ray_hit = ray.DistanceTo(mouse);

	// Declare a vector. We will draw the normal to the hit surface (if we hit something)
	fVector normal(0.0f, 0.0f);

	// All draw functions ------------------------------------------------------

	// Circles
	p2List_item<PhysBody*>* c = circles.getFirst();

	// Raycasts -----------------
	if(ray_on == true)
	{
		// Compute the vector from the raycast origin up to the contact point (if we're hitting anything; otherwise this is the reference length)
		fVector destination(mouse.x-ray.x, mouse.y-ray.y);
		destination.Normalize();
		destination *= ray_hit;

		// Draw a line from origin to the hit point (or reference length if we are not hitting anything)
		App->renderer->DrawLine(ray.x, ray.y, ray.x + destination.x, ray.y + destination.y, 255, 255, 255);

		// If we are hitting something with the raycast, draw the normal vector to the contact point
		if(normal.x != 0.0f)
			App->renderer->DrawLine(ray.x + destination.x, ray.y + destination.y, ray.x + destination.x + normal.x * 25.0f, ray.y + destination.y + normal.y * 25.0f, 100, 255, 100);
	}

	SDL_Rect MapaPin = { 1, 1, 256, 432 };
	
	App->renderer->Blit(Mapa, 2, 2, &MapaPin);
	

	// Keep playing
	return UPDATE_CONTINUE;
}
void ModuleSceneIntro::map()
{

	int bottomLeftMap[40] = {
			93, 433,
			93, 417,
			36, 388,
			33, 388,
			33, 418,
			27, 421,
			19, 421,
			13, 418,
			13, 334,
			16, 300,
			25, 291,
			25, 287,
			19, 281,
			19, 242,
			22, 237,
			26, 237,
			28, 233,
			1, 174,
			1, 433,
			86, 433
	};
	bottomLeftMapHitbox.add(App->physics->CreateChain(0, 0, bottomLeftMap, 40));

	int bottomRightMap[50] = {
			149, 433,
			149, 418,
			206, 388,
			209, 388,
			209, 418,
			212, 421,
			225, 421,
			229, 418,
			229, 330,
			227, 307,
			224, 296,
			217, 289,
			230, 258,
			226, 253,
			236, 243,
			237, 415,
			239, 417,
			251, 417,
			253, 415,
			253, 218,
			250, 211,
			242, 211,
			257, 187,
			257, 433,
			152, 433
	};
	bottomRightMapHitbox.add(App->physics->CreateChain(0, 0, bottomRightMap, 50));

	int bottomLeftWall[20] = {
			36, 319,
			33, 323,
			33, 362,
			81, 388,
			86, 388,
			86, 381,
			45, 360,
			41, 356,
			37, 348,
			37, 324
	};
	bottomLeftWallHitbox.add(App->physics->CreateChain(0, 0, bottomLeftWall, 20));


	int bottomRightWall[18] = {
			156, 388,
			161, 388,
			204, 366,
			209, 362,
			209, 322,
			205, 319,
			205, 348,
			201, 357,
			156, 381
	
	};
	bottomRightWallHitbox.add(App->physics->CreateChain(0, 0, bottomRightWall, 18));

	int topMap[106] = {
			213, 193,
			209, 203,
			209, 207,
			216, 207,
			220, 202,
			230, 170,
			257, 172,
			257, 2,
			2, 1,
			1, 158,
			30, 188,
			33, 178,
			15, 136,
			12, 119,
			12, 99,
			16, 75,
			26, 61,
			36, 51,
			55, 43,
			79, 39,
			91, 39,
			106, 42,
			120, 49,
			133, 62,
			141, 79,
			144, 94,
			144, 111,
			141, 120,
			145, 124,
			149, 119,
			159, 118,
			165, 123,
			166, 129,
			167, 131,
			172, 131,
			171, 125,
			163, 116,
			155, 92,
			155, 72,
			158, 58,
			163, 48,
			173, 38,
			193, 30,
			211, 30,
			231, 38,
			242, 49,
			247, 58,
			250, 68,
			250, 83,
			243, 114,
			234, 133,
			233, 147,
			221, 193
	};
	topMapHitbox.add(App->physics->CreateChain(0, 0, topMap, 106));
}
void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{
	// Play Audio FX on every collision, regardless of who is colliding

	// Do something else. You can also check which bodies are colliding (sensor? ball? player?)
}
