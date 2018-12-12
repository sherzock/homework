#include "j1Gui.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Fonts.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1UIelements.h"

j1UIelements::j1UIelements(Type guitype,Position ali , j1Module* listener) : guitype(guitype), ali(ali), listener(listener) {}
bool j1UIelements::Start() {return true;}
bool j1UIelements::Update(float dt) {return true;}
bool j1UIelements::CleanUp() {return true;}
j1UIelements::~j1UIelements() {}

SDL_Texture* j1UIelements::LoadTexture(p2SString path)
{
	SDL_Texture* ret = App->tex->Load(path.GetString());
	return ret;
}

void j1UIelements::ShowDebug(){App->render->DrawQuad({ position.x + movement.x, position.y + movement.y, rect.w, rect.h }, 255, 255, 0, 100, false);}

void j1UIelements::UpdatePosition()
{
	switch (ali)
	{
	case NO_POSITIONING:

		break;
	case POSITION_CENTER:

		position.x = (-App->render->camera.x + App->render->camera.w / 2) - (rect.w / 2);

		position.y = -App->render->camera.y;

		break;

	case POSITION_RIGHT:

		position.x = (-App->render->camera.x + App->render->camera.w) - rect.w;

		position.y = -App->render->camera.y;

		break;

	case POSITION_LEFT:

		position.x = -App->render->camera.x;

		position.y = -App->render->camera.y;

		break;

	}
}
