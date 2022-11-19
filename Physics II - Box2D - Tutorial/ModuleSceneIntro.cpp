#include "Globals.h"
#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneIntro.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModulePhysics.h"
#include "ModulePlayer.h"
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
	

	// Add this module (ModuleSceneIntro) as a listener for collisions with the sensor.
	rightflipcircle = App->physics->CreateCircleStatic(155, 386, 5);
	rightflipcircle2 = App->physics->CreateCircleStatic(227, 257, 5);
	leftflipcircle = App->physics->CreateCircleStatic(87, 386, 5);
	rightflipper = App->physics->CreateRectangle(140, 385, 20, 6);
	rightflipper2 = App->physics->CreateRectangle(212, 256, 20, 6);
	leftflipper = App->physics->CreateRectangle(101, 385, 20, 6);
	NightsensorF1_1 = App->physics->CreateRectangleSensor(23,210,30,10);
	NightsensorF1_2 = App->physics->CreateRectangleSensor(201, 100, 35, 10);
	NightsensorF1_3 = App->physics->CreateRectangleSensor(225, 215, 30, 10);

	gameover = App->physics->CreateRectangleSensor(87, 430, 66, 10);

	NightsensorF2_1 = App->physics->CreateRectangleSensor(14, 186, 25, 5);
	NightsensorF2_2 = App->physics->CreateRectangleSensor(198, 66, 15, 5);
	NightsensorF2_3 = App->physics->CreateRectangleSensor(233, 198, 25, 5);

	Floor3_1 = App->physics->CreateRectangleSensor(43, 327, 25, 5);
	Floor3_2 = App->physics->CreateRectangleSensor(77, 145, 25, 5);
	Floor3_2->listener = this;
	Floor3_ac = App->physics->CreateRectangleSensor(68, 131, 10, 7);

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

	b2RevoluteJointDef rightFlip2;
	rightFlip2.bodyA = rightflipper2->body;
	rightFlip2.bodyB = rightflipcircle2->body;
	rightFlip2.localAnchorA.Set(PIXEL_TO_METERS(16), 0);
	rightFlip2.localAnchorB.Set(0, 0);
	rightFlip2.referenceAngle = 0 * DEGTORAD;
	rightFlip2.enableLimit = true;
	rightFlip2.lowerAngle = -30 * DEGTORAD;
	rightFlip2.upperAngle = 60 * DEGTORAD;

	b2RevoluteJoint* rightflipjoint2 = (b2RevoluteJoint*)App->physics->world->CreateJoint(&rightFlip2);

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

	MapaPin = { 1, 1, 256, 432 };
	RightFlipperRect = { 235,651,60,10 };
	LeftFlipperRect = { 205,662,60,10 };
	RightBouncer = { 290, 544, 21, 40 };
	LeftBouncer = { 238, 544, 21, 40 };
	ShineRightBouncer = { 316, 544, 21, 40 };
	ShineLeftBouncer = { 264, 544, 21, 40 };
	TopBumper = {419,515,10,16};
	mapselector = true;
	floornum = 1;
	int bouncerRightSens[8] = {
	182, 1226,
	168, 1256,
	166, 1255,
	180, 1226
	};
	rBumperRight= App->physics->CreateBouncyChain(0, -910, bouncerRightSens, 8);

	int bouncerLeftSens[8] = {
		62, 1238,
		63, 1227,
		76, 1256,
		67, 1250
	};
	rBumperLeft = App->physics->CreateBouncyChain(0, -910, bouncerLeftSens, 8);
	bouncerRight = false;
	bouncerLeft = false;
	rightBtimer = 0;
	leftBtimer = 0;

	return ret;
}

bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");
	for (int i = 0; i < Map.size(); i++) {
		delete Map[i];
		Map[i] = nullptr;
	}
	Map.clear();
	delete NightsensorF1_1;
	NightsensorF1_1 = nullptr;
	delete NightsensorF1_2;
	NightsensorF1_2 = nullptr;
	delete NightsensorF1_3;
	NightsensorF1_3 = nullptr;
	delete NightsensorF2_1;
	NightsensorF2_1 = nullptr;
	delete NightsensorF2_2;
	NightsensorF2_2 = nullptr;
	delete NightsensorF2_3;
	NightsensorF2_3 = nullptr;
	delete rightflipcircle;
	rightflipcircle = nullptr;
	delete leftflipcircle;
	leftflipcircle = nullptr;
	delete rightflipper;
	rightflipper = nullptr;
	delete leftflipper;
	leftflipper = nullptr;
	delete Floor3_1;
	Floor3_1 = nullptr;
	delete Floor3_2;
	Floor3_2 = nullptr;
	delete Floor3_ac;
	Floor3_ac = nullptr;
	delete rBumperRight;
	rBumperRight = nullptr;
	delete rBumperLeft;
	rBumperLeft = nullptr;
	delete rightflipcircle2;
	rightflipcircle2 = nullptr;
	delete rightflipper2;
	rightflipper2 = nullptr;
	delete gameover;
	gameover = nullptr;
	return true;
}

update_status ModuleSceneIntro::Update()
{
	if ((App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)) {
		mapselector = true;
		floornum = 3;
	}
	if (mapselector == true) {
		map();
	}
	
	if ((App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT))
	{
		rightflipper->body->ApplyForceToCenter(b2Vec2(0, -150), 1);
		rightflipper2->body->ApplyForceToCenter(b2Vec2(0, -150), 1);
	}

	if ((App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT))
	{
		leftflipper->body->ApplyForceToCenter(b2Vec2(0, -150), 1);
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

	//Rectangles

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

	
	App->renderer->Blit(Mapa, 2, 2, &MapaPin);
	App->renderer->Blit(Mapa, 127 * SCREEN_SIZE, 380 * SCREEN_SIZE, &RightFlipperRect, 0, App->scene_intro->rightflipper->GetRotation());
	App->renderer->Blit(Mapa, 199 * SCREEN_SIZE, 250 * SCREEN_SIZE, &RightFlipperRect, 0, App->scene_intro->rightflipper2->GetRotation());

	App->renderer->Blit(Mapa, 55 * SCREEN_SIZE, 380 * SCREEN_SIZE, &LeftFlipperRect, 0, App->scene_intro->leftflipper->GetRotation());
	if (rightBtimer<=0) {
		App->renderer->Blit(Mapa, 163 * SCREEN_SIZE, 313 * SCREEN_SIZE, &RightBouncer);
		
	}
	if (leftBtimer <= 0) {
		App->renderer->Blit(Mapa, 58 * SCREEN_SIZE, 313 * SCREEN_SIZE, &LeftBouncer);
	}
	if (rightBtimer > 0) {
		App->renderer->Blit(Mapa, 163 * SCREEN_SIZE, 313 * SCREEN_SIZE, &ShineRightBouncer);

	}
	if (leftBtimer > 0) {
		App->renderer->Blit(Mapa, 58 * SCREEN_SIZE, 313 * SCREEN_SIZE, &ShineLeftBouncer);
	}
	App->renderer->Blit(Mapa, 214 * SCREEN_SIZE, 176 * SCREEN_SIZE, &TopBumper);
	App->renderer->Blit(Mapa, 218 * SCREEN_SIZE, 159 * SCREEN_SIZE, &TopBumper);
	App->renderer->Blit(Mapa, 222 * SCREEN_SIZE, 144 * SCREEN_SIZE, &TopBumper);

	rightBtimer--;
	leftBtimer--;

	// Keep playing
	return UPDATE_CONTINUE;
}
void ModuleSceneIntro::map()
{
	if (floornum == 1) {

		for (int i = 0; i < Map.size(); i++) {
			delete Map[i];
			Map[i] = nullptr;
		}

		

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
		Map.push_back(App->physics->CreateChain(0, 0, bottomLeftMap, 40));
		
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
		Map.push_back(App->physics->CreateChain(0, 0, bottomRightMap, 50));

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
		Map.push_back(App->physics->CreateChain(0, 0, bottomLeftWall, 20));


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
		Map.push_back(App->physics->CreateChain(0, 0, bottomRightWall, 18));

		int paretAdalt[32] = {
				66, 143,
				55, 154,
				52, 152,
				52, 149,
				54, 147,
				55, 143,
				57, 120,
				65, 114,
				74, 115,
				93, 132,
				88, 137,
				83, 132,
				79, 131,
				73, 125,
				61, 136,
				66, 141

		};
		Map.push_back(App->physics->CreateChain(0, 0, paretAdalt, 32));

		int topCurve1[32] = {
				32, 97,
				34, 98,
				36, 97,
				37, 90,
				40, 83,
				44, 78,
				50, 72,
				57, 67,
				63, 64,
				71, 64,
				71, 60,
				62, 60,
				52, 65,
				43, 73,
				35, 84,
				32, 94
		};
		Map.push_back(App->physics->CreateChain(0, 0, topCurve1, 32));

		int topCurve2[30] = {
				89, 62,
				90, 64,
				101, 65,
				109, 68,
				118, 77,
				122, 89,
				122, 96,
				124, 97,
				126, 95,
				126, 88,
				123, 78,
				118, 70,
				110, 64,
				98, 61,
				90, 60
		};
		Map.push_back(App->physics->CreateChain(0, 0, topCurve2, 30));

		int topBossCircle[48] = {
				191, 84,
				188, 97,
				183, 91,
				180, 83,
				180, 74,
				184, 64,
				193, 57,
				202, 55,
				211, 56,
				218, 58,
				225, 65,
				228, 74,
				228, 83,
				226, 92,
				219, 98,
				212, 102,
				211, 89,
				219, 81,
				218, 70,
				213, 64,
				203, 62,
				194, 66,
				189, 73,
				190, 80
		};
		Map.push_back(App->physics->CreateChain(0, 0, topBossCircle, 48));

		int topMap[112] = {
			213, 193,
			209, 203,
			209, 207,
			216, 207,
			220, 202,
			230, 170,
			257, 172,
			257, 2,
			2, 1,
			1, 168,
			5, 156,
			16, 151,
			29, 193,
			31, 184,
			33, 180,
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
		Map.push_back(App->physics->CreateChain(0, 0, topMap, 112));

		int bouncerRight[8] = {
			182, 1224,
			165, 1261,
			183, 1252,
			184, 1224
		};
		Map.push_back(App->physics->CreateChain(0, -910, bouncerRight, 8));

		int bouncerLeft[8] = {
			60, 1224,
			77, 1261,
			58, 1252,
			58, 1224
	
		};
		Map.push_back(App->physics->CreateChain(0, -910, bouncerLeft, 8));

		int ballBouncer1[22] = {
			50, 991,
			54, 993,
			58, 993,
			61, 997,
			62, 1005,
			58, 1010,
			51, 1011,
			44, 1009,
			42, 1004,
			42, 996,
			45, 992
		};

		Map.push_back(App->physics->CreateBouncyChain(0, -910, ballBouncer1, 22));

		int ballBouncer2[24] = {
			65, 974,
			68, 976,
			73, 975,
			75, 979,
			76, 987,
			73, 994,
			65, 994,
			58, 994,
			57, 989,
			55, 985,
			55, 980,
			59, 976
		};
		Map.push_back(App->physics->CreateBouncyChain(0, -910, ballBouncer2, 24));
	
		int bouncerleft[12] = {
			226, 1056,
			214, 1101,
			217, 1098,
			223, 1079,
			230, 1057,
			230, 1052
		};
		Map.push_back(App->physics->CreateBouncyChain(0, -910, bouncerleft, 12));


	}
	if (floornum == 2) {
		for (int i = 0; i < Map.size(); i++) {
			delete Map[i];
			Map[i] = nullptr;
		}
		int NightRamp1[62] = {
			273, 209,
			262, 173,
			258, 154,
			255, 134,
			253, 110,
			253, 89,
			255, 70,
			263, 47,
			287, 22,
			315, 10,
			347, 2,
			382, 1,
			414, 2,
			436, 4,
			459, 11,
			483, 22,
			499, 35,
			512, 54,
			515, 71,
			517, 100,
			516, 125,
			514, 148,
			510, 170,
			504, 192,
			498, 208,
			513, 196,
			524, 151,
			527, -4,
			244, -2,
			236, 186,
			264, 204
		};
		Map.push_back(App->physics->CreateChain(-261, 0, NightRamp1, 62));

		int NightRamp2[48] = {
			295, 203,
			287, 184,
			280, 159,
			276, 127,
			275, 106,
			274, 85,
			279, 66,
			287, 51,
			302, 38,
			324, 30,
			345, 25,
			368, 22,
			393, 21,
			412, 22,
			426, 27,
			437, 38,
			446, 52,
			451, 67,
			417, 31,
			340, 33,
			297, 61,
			283, 92,
			283, 126,
			294, 185
		};
		Map.push_back(App->physics->CreateChain(-261, 0, NightRamp2, 48));

		int NightRamp3[32] = {
				469, 71,
				467, 52,
				464, 44,
				458, 31,
				466, 34,
				479, 45,
				488, 56,
				495, 74,
				498, 101,
				496, 125,
				495, 140,
				486, 183,
				476, 203,
				485, 89,
				483, 80,
				476, 74
		};
		Map.push_back(App->physics->CreateChain(-261, 0, NightRamp3, 32));

	}
	if (floornum == 3) {
		for (int i = 0; i < Map.size(); i++) {
			delete Map[i];
			Map[i] = nullptr;
		}
		int Floor3[152] = {
			47, 1237,
			52, 1235,
			55, 1231,
			55, 1225,
			54, 1219,
			54, 1213,
			54, 1207,
			52, 1201,
			47, 1195,
			40, 1191,
			31, 1186,
			24, 1183,
			19, 1179,
			18, 1117,
			30, 1104,
			51, 1094,
			76, 1081,
			116, 1061,
			136, 1041,
			151, 1004,
			153, 974,
			143, 942,
			133, 934,
			120, 928,
			97, 925,
			73, 927,
			52, 937,
			37, 953,
			32, 973,
			30, 1002,
			39, 1022,
			55, 1039,
			66, 1052,
			0, 1010,
			43, 907,
			182, 934,
			103, 1183,
			48, 1250,
			-8, 1207,
			-16, 1146,
			3, 1094,
			26, 1082,
			48, 1071,
			65, 1066,
			102, 1046,
			116, 1032,
			126, 977,
			107, 954,
			80, 956,
			60, 992,
			71, 1022,
			78, 1039,
			59, 1021,
			52, 1013,
			48, 999,
			49, 977,
			52, 961,
			62, 949,
			77, 942,
			100, 942,
			122, 948,
			134, 965,
			136, 976,
			135, 1001,
			124, 1031,
			105, 1049,
			20, 1092,
			1, 1109,
			1, 1183,
			7, 1192,
			17, 1198,
			36, 1207,
			38, 1221,
			35, 1227,
			37, 1234,
			42, 1236
		};
		Map.push_back(App->physics->CreateChain(0, -910, Floor3, 152));
	}
<<<<<<< HEAD

	
	////APAREIXEN COLLIDERS DE LES RAMPES TARONJES QUAN UN DELS CANONS NO EXISTEIX
	//if (App->player->rampataronja1 == false) {

	//	//RampaTaronja1
	//	int Rampa1[10] = {
	//		34, 1302,
	//		34, 1297,
	//		10, 1283,
	//		10, 1289,
	//		34, 1302
	//	};
	//	Map.push_back(App->physics->CreateChain(0, -910, Rampa1, 10));
	//}
	//if (App->player->rampataronja2 == false) {

	//	for (int i = 0; i < Map.size(); i++) {
	//		delete Map[i];
	//		Map[i] = nullptr;
	//	}

	//	//RampaTaronja2
	//	int Rampa2[10] = {
	//		205, 1298,
	//		230, 1284,
	//		230, 1289,
	//		205, 1302,
	//		205, 1298
	//	};
	//	Map.push_back(App->physics->CreateChain(0, -910, Rampa2, 10));
	//}



=======
>>>>>>> parent of 21cecce (Canons verds baixats + textura rampa taronja)
	mapselector = false;
}
void ModuleSceneIntro::OnCollision(PhysBody* bodyA, PhysBody* bodyB)
{

	// Play Audio FX on every collision, regardless of who is colliding

	// Do something else. You can also check which bodies are colliding (sensor? ball? player?)
}
