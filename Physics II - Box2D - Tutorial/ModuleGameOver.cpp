#include "Application.h"
#include "ModuleRender.h"
#include "ModuleGameOver.h"
#include "ModuleSceneIntro.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleFont.h"
#include "ModulePlayer.h"
#include "ModulePhysics.h"

#include <sstream>
#include <string.h>
using namespace std;

ModuleGameOver::ModuleGameOver(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleGameOver::~ModuleGameOver()
{
}

bool ModuleGameOver::Start()
{
	LOG("Loading Title assets uwu");
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	TitleFont = App->font->Load("pinball/rtype_font3.png", lookupTable, 2);
	App->physics->velocity = 60.0f;
	//App->renderer->camera.x = App->renderer->camera.y = 0;
	fondo = App->textures->Load("pinball/black.png");

	return true;
}

update_status ModuleGameOver::Update()
{
	App->renderer->Blit(fondo, 0, 0);
	App->font->BlitText(58, 248, TitleFont, TitleText);
	if (App->physics->Gameover==true) {
		App->font->BlitText(300, 430, TitleFont, "g  a  m  e    o  v  e  r");
		App->font->BlitText(300, 460, TitleFont, "p  r  e  s  s     r");
		App->font->BlitText(300, 490, TitleFont, "t  o    p  l  a  y");
		App->font->BlitText(300, 520, TitleFont, "a  g  a i n");

		if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
		{
			App->fade->FadeToBlack(this, (Module*)App->scene_intro, 50);
		}
	}

	string puntuacion = std::to_string(App->physics->Score);
	const char* Scorechar = puntuacion.c_str();

	if (App->physics->Win == true) {
		App->font->BlitText(300, 430, TitleFont, "l  l  e  n  g  u  a  t    l  l  e  n  g  u  a  t");
		App->font->BlitText(300, 460, TitleFont, "a    a  q  u  e  s  t    p i n  b  a  l  l");
		App->font->BlitText(300, 490, TitleFont, "h  a  s    g  u  a  n  y  a  t  A  A  A  A");
		App->font->BlitText(300, 600, TitleFont, "s  c  o  r  e");
		App->font->BlitText(300, 630, TitleFont, Scorechar);
		App->font->BlitText(300, 750, TitleFont, "p  r  e  s  s     r");
		App->font->BlitText(300, 780, TitleFont, "t  o    p  l  a  y");
		App->font->BlitText(300, 810, TitleFont, "a  g  a i n");

		if (App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)
		{
			App->fade->FadeToBlack(this, (Module*)App->scene_intro, 50);
		}
	}

	return UPDATE_CONTINUE;
}

bool ModuleGameOver::CleanUp()
{
	LOG("Unloading title scene");
	//App->textures->Unload(fondo);
	return true;
}