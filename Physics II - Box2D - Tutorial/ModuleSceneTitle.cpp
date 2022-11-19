#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneTitle.h"
#include "ModuleSceneIntro.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleFont.h"

//#include <sstream>
//#include <string.h>
//using namespace std;

ModuleSceneTitle::ModuleSceneTitle(Application* app, bool start_enabled) : Module(app, start_enabled)
{

}

ModuleSceneTitle::~ModuleSceneTitle()
{
}

bool ModuleSceneTitle::Start()
{
	LOG("Loading Title assets uwu");
	char lookupTable[] = { "! @,_./0123456789$;< ?abcdefghijklmnopqrstuvwxyz" };
	TitleFont = App->font->Load("pinball/rtype_font3.png", lookupTable, 2);

	//App->renderer->camera.x = App->renderer->camera.y = 0;
	title = App->textures->Load("pinball/black.png");

	return true;
}

update_status ModuleSceneTitle::Update()
{
	App->renderer->Blit(title, 0, 0);
	App->font->BlitText(58, 248, TitleFont, TitleText);
	App->font->BlitText(300, 450, TitleFont, "p  r  e  s  s    s  p  a  c  e");
	App->font->BlitText(300, 470, TitleFont, "t  o    p  l  a  y");
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		App->fade->FadeToBlack(this, (Module*)App->scene_intro, 90);
	}
	
	return UPDATE_CONTINUE;
}

bool ModuleSceneTitle::CleanUp()
{
	LOG("Unloading title scene");
	App->textures->Unload(title);
	return true;
}