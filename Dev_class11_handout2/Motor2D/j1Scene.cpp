#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Scene.h"
#include "j1Fonts.h"
#include"ImageUI.h"
#include "LabelUI.h"
#include "WindowUI.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake()
{
	LOG("Loading Scene");
	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	if (App->map->Load("iso_walk.tmx") == true)
	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->pathfinding->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	debug_tex = App->tex->Load("maps/path2.png");

	// TODO 3: Create the banner (rect {485, 829, 328, 103}) and the text "Hello World"

	// -----Gui------

	background = App->tex->Load("gui/wow ui/login_background.png");
	WC_logo = App->gui->AddImage(POSITION_LEFT, "gui/wow ui/COMMON/Glues-WoW-Logo.png", { 0, 0, 256, 128 }, { 75, 10 }, this);
	rating = App->gui->AddImage(POSITION_LEFT, "gui/wow ui/LOGIN/Glues-ESRBRating.png", { 0, 0, 128, 128 }, { 75, 895 }, this);
	blizzard = App->gui->AddImage(POSITION_CENTER, "gui/wow ui/MainMenu/Glues-BlizzardLogo.png", { 0, 0, 128, 128 }, { 0, 900 }, this);

	p2SString txt = "Version 2.0.12 (6546) (Release)";
	release = App->gui->AddText(POSITION_LEFT, txt, { 50,1030 }, OPENSANS, { 255, 255,0,255 }, this);
	txt = "Mar 30 2007";
	date = App->gui->AddText(POSITION_LEFT, txt, { 50,1042 }, OPENSANS, { 255, 255,0,255 }, this);
	txt = "Copyright 2004-2007 blizzard Entertainment. All Rights Reserved";
	copyright = App->gui->AddText(POSITION_CENTER, txt, { 0,1020 }, OPENSANS, { 255, 255,0,255 }, this);
	txt = "WoWps.org TBC";
	web = App->gui->AddText(POSITION_RIGHT, txt, { -80,850 }, OPENSANS, { 255, 255,0,255 }, this);

	txt = "Login";
	login = App->gui->AddButton(POSITION_CENTER, txt, { 0, 750 }, this);

	txt = "Remember Account Name";
	window = App->gui->AddWindow(POSITION_CENTER, 10, txt, { 100,100 }, this);

	window->MainButtonTag("1");

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{

	// debug pathfing ------------------
	static iPoint origin;
	static bool origin_selected = false;

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);

	if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
	{
		if (origin_selected == true)
		{
			App->pathfinding->CreatePath(origin, p);
			origin_selected = false;
		}
		else
		{
			origin = p;
			origin_selected = true;
		}
	}

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{

	if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if (App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += floor(200.0f * dt);

	if (App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= floor(200.0f * dt);

	if (App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += floor(200.0f * dt);

	if (App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= floor(200.0f * dt);

	App->map->Draw();

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
		App->map->data.width, App->map->data.height,
		App->map->data.tile_width, App->map->data.tile_height,
		App->map->data.tilesets.count(),
		map_coordinates.x, map_coordinates.y);

	//App->win->SetTitle(title.GetString());

	// Debug pathfinding ------------------------------
	//int x, y;
	App->input->GetMousePosition(x, y);
	iPoint p = App->render->ScreenToWorld(x, y);
	p = App->map->WorldToMap(p.x, p.y);
	p = App->map->MapToWorld(p.x, p.y);

	App->render->Blit(debug_tex, p.x, p.y);
	SDL_Rect background_rect = { 0, 0, 1920, 1080 };
	App->render->Blit(background, 0, 0, &background_rect);

	const p2DynArray<iPoint>* path = App->pathfinding->GetLastPath();

	for (uint i = 0; i < path->Count(); ++i)
	{
		iPoint pos = App->map->MapToWorld(path->At(i)->x, path->At(i)->y);
		App->render->Blit(debug_tex, pos.x, pos.y);
	}

	// Gui ---


	// -------

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	bool ret = true;

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");

	return true;
}

void j1Scene::OnEventChange(j1UIelements* elem, Event event) const {
	if (elem == web) {
		if (event == Event::RIGHT_CLICK) {
			web->UpdateText("RIGHT CLICK");
		}
		if (event == Event::MOUSE_INSIDE || event == Event::MOUSE_OUTSIDE) {
			web->UpdateText("WoWps.org TBC");
		}
		if (event == Event::LEFT_CLICK) {
			web->UpdateText("LEFT CLICK");
		}
	}
	if (event == Event::MOUSE_INSIDE) {
		elem->MouseInput(HOVER);
		LOG("Entering");
	}
	if (event == Event::MOUSE_OUTSIDE) {
		elem->MouseInput(IDLE);
		LOG("Leaving");
	}
	if (event == Event::RIGHT_CLICK) {
		elem->MouseInput(PRESSED_R);
	}
	if (event == Event::LEFT_CLICK) {
		elem->MouseInput(PRESSED_L);
	}
	if (event == Event::LEFT_CLICK_UP) {
		elem->MouseInput(UP_L);
	}
	if (event == Event::RIGHT_CLICK_UP) {
		elem->MouseInput(UP_R);
	}
}