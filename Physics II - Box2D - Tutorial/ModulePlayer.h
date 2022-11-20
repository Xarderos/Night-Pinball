#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"
#include "Animation.h"

struct SDL_Texture;


class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled);
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
	SDL_Texture* Tcanoverd1;
	SDL_Texture* Tcanoverd2;
	SDL_Texture* Black;

	//SDL_Rect
	SDL_Rect BolaPin;
	SDL_Rect MapaPin1f;
	SDL_Rect Reixa;
	SDL_Rect NightRampPart;
	SDL_Rect BouncerBall;
	SDL_Rect Boss2;
	SDL_Rect Chip;
	SDL_Rect FleGroc;
	SDL_Rect BotonsPin;
	SDL_Rect BotonsPin2;
	SDL_Rect BotonsPin3;
	SDL_Rect MapSen_;
	SDL_Rect GrocSen;
	SDL_Rect BlauSen_;
	SDL_Rect BlauSen2;
	SDL_Rect Llumlila;
	SDL_Rect Boss;
	SDL_Rect Lilatriangle;
	SDL_Rect Llumrectangle;
	SDL_Rect Lilatriangle2;
	SDL_Rect PedraSen_;
	SDL_Rect VerdSen;
	SDL_Rect VermeSen_;
	SDL_Rect VermeSen2;
	SDL_Rect VermeSen3;
	SDL_Rect VermeSen4;
	SDL_Rect Porteta;
	SDL_Rect PedraPin;
	SDL_Rect LlumBoss;
	SDL_Rect SuportCanoPin;
	SDL_Rect CanoPin;
	SDL_Rect animaciocano;
	SDL_Rect rampataronja1;
	SDL_Rect rampataronja2;
	SDL_Rect CanoVerd1Pin;
	SDL_Rect CanoVerd2Pin;
	SDL_Rect Portablanca;
	SDL_Rect RightFlipperRect;
	SDL_Rect LeftFlipperRect;
	SDL_Rect BossPart;
	SDL_Rect BossVida;
	SDL_Rect BossVida2;
	SDL_Rect BossVida3;
	SDL_Rect BossVida4;
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
	PhysBody* PortaSen;
	PhysBody* TriangleLilaSen;
	PhysBody* LlumRectangle;
	PhysBody* CanoVerdSen1;
	PhysBody* CanoVerdSen2;
	PhysBody* RampaT1;
	PhysBody* RampaT2;
	PhysBody* BossHitbox;

	//Animations
	Animation bolapin;
	Animation CanoAnim;
	Animation BossAnim;
	Animation ChipAnim;
	Animation FleGrocAnim;
	Animation CanoVerdAnim;
	Animation CanoVerdAnim2;
	Animation PortaBlanca;
	Animation BossDeathAnim;


	//FX
	uint silencio;
	uint canonshot;
	uint fire_ball;
	uint flipper;

	//Definitions
	int botonsound;
	int pedrasound;
	int lifes;
	int llumverda;
	int bossvida;
	bool portablanca;
	bool lilatriangle;
	bool llumrectangle;
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
	bool canoverdsen1;
	bool canoverdsen2;
	bool canoverd1 = true;
	bool canoverd2 = true;
	bool changegrav;
	int canoverd1Anim = 0;
	int canoverd2Anim = 0;
	float gravity;
	int numCVerds = 0;

	bool estrellablanca = false;
	bool estrellablava = false;
	bool estrellagroga = false;
	bool estrellaverda = false;
	bool estrellavermella = false;

	bool GameOver = false;
	bool boss;
	bool WIN;
	// Font score index
	int score;
	int scoreFont = -1; //SCORE ELIMINAR AIXÒ
	char scoreText[10] = { "\0" };
};