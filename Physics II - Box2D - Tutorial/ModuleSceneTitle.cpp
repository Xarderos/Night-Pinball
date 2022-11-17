#include "Application.h"
#include "ModuleRender.h"
#include "ModuleSceneTitle.h"
#include "ModuleFadeToBlack.h"
#include "ModuleInput.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"

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
	//App->renderer->camera.x = App->renderer->camera.y = 0;
	title = App->textures->Load("pinball/sprites/title.png");

	return true;
}

update_status ModuleSceneTitle::Update()
{
	App->renderer->Blit(title, 0, 0);
	if (App->input->GetKey(SDL_SCANCODE_SPACE || SDL_SCANCODE_RETURN) == KEY_DOWN)
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