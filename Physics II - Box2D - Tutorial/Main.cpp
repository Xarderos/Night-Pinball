#include <stdlib.h>
#include "Application.h"
#include "Globals.h"
#include "MemLeaks.h"
#include "SDL/include/SDL.h"
#pragma comment( lib, "SDL/libx86/SDL2.lib" )
#pragma comment( lib, "SDL/libx86/SDL2main.lib" )
#include <chrono>

const float targetFPS = 60.0f;
const float fixedDeltaTime = 1.0f / targetFPS;
auto lastUpdateTime = std::chrono::high_resolution_clock::now();
enum main_states
{
	MAIN_CREATION,
	MAIN_START,
	MAIN_UPDATE,
	MAIN_FINISH,
	MAIN_EXIT
};


int main(int argc, char ** argv)
{
	LOG("Starting game '%s'...", TITLE);

	int main_return = EXIT_FAILURE;
	main_states state = MAIN_CREATION;
	Application* App = NULL;

	while (state != MAIN_EXIT)
	{
		switch (state)
		{
		case MAIN_CREATION:

			LOG("-------------- Application Creation --------------");
			App = new Application();
			state = MAIN_START;
			break;

		case MAIN_START:

			LOG("-------------- Application Init --------------");
			if (App->Init() == false)
			{
				LOG("Application Init exits with ERROR");
				state = MAIN_EXIT;
			}
			else
			{
				state = MAIN_UPDATE;
				LOG("-------------- Application Update --------------");
			}

			break;

		case MAIN_UPDATE:
		{
			auto currentTime = std::chrono::high_resolution_clock::now();

			// Calcular el tiempo transcurrido desde la �ltima actualizaci�n
			auto deltaTime = std::chrono::duration<float>(currentTime - lastUpdateTime).count();
			if (deltaTime >= fixedDeltaTime)
			{
				int update_return = App->Update();

				if (update_return == UPDATE_ERROR)
				{
					LOG("Application Update exits with ERROR");
					state = MAIN_EXIT;
				}

				if (update_return == UPDATE_STOP)
					state = MAIN_FINISH;
				lastUpdateTime = currentTime;
			}
		}
			break;

		case MAIN_FINISH:

			LOG("-------------- Application CleanUp --------------");
			if (App->CleanUp() == false)
			{
				LOG("Application CleanUp exits with ERROR");
			}
			else
				main_return = EXIT_SUCCESS;

			state = MAIN_EXIT;

			break;

		}
	}

	delete App;
	ReportMemoryLeaks();
	LOG("\nBye :)\n");
	LOG("Exiting game '%s'...\n", TITLE);
	return main_return;
}