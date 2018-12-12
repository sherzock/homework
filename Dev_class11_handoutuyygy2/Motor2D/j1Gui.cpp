#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
//#include "Brofiler/Brofiler.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
//	BROFILER_CATEGORY("GUI_PreUpdate", Profiler::Color::OrangeRed);
	bool ret = true;

	for (p2List_item<j1UIelements*>* item = items.start; item != NULL; item = item->next)
	{
		item->data->PreUpdate();

		if (item->data->deleting)
			ItemDestory(item->data);
	}

	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN) 
	{ 
		debug = !debug; 
	}

	ItemEventUpdate();

	ret = ItemEventManager();

	return ret;
}

bool j1Gui::Update(float dt)
{
	//BROFILER_CATEGORY("GUI_Update", Profiler::Color::OrangeRed);
	for (p2List_item<j1UIelements*>* item = items.start; item != NULL; item = item->next)
	{
		item->data->Update(dt);

		if (debug) 
		{ 
		item->data->ShowDebug(); 
		}
	}
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");
	App->tex->UnLoad(atlas);
	p2List_item<j1UIelements*>* item = items.start;

	if (item != NULL) {

		for (; item != NULL; item = item->next) {

			item->data->CleanUp();

			ItemDestory(item->data);
		}

		items.clear();

	}

	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas() const
{
	return atlas;
}

// class Gui ---------------------------------------------------

void j1Gui::ItemEventUpdate() const
{
	iPoint pos;
	App->input->GetMousePosition(pos.x, pos.y);
	pos.x -= App->render->camera.x;


	p2List_item<j1UIelements*>* item;
	for (item = items.start; item != NULL; item = item->next)
	{
		iPoint item_pos = { item->data->position.x + item->data->movement.x,item->data->position.y + item->data->movement.y };
		if ((pos.x > item_pos.x && pos.x < item_pos.x + item->data->rect.w) && (pos.y > item_pos.y && pos.y < item_pos.y + item->data->rect.h))
		{
			if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_REPEAT)
			{
				item->data->event = Event::RIGHT_CLICK;
			}
			else if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_UP)
			{
				item->data->event = Event::RIGHT_CLICK_UP;
				break;
			}
			else if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_REPEAT)
			{
				item->data->event = Event::LEFT_CLICK;
			}
			else if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
			{
				item->data->event = Event::LEFT_CLICK_UP;
				break;
			}
			else { item->data->event = Event::MOUSE_INSIDE; }
		}
		else { item->data->event = Event::MOUSE_OUTSIDE; }
	}
}

bool j1Gui::ItemEventManager()
{
	bool ret = true;
	for (p2List_item<j1UIelements*>* item = items.end; item != NULL && ret != false; item = item->prev)
	{
		if ((item->data->event != item->data->previous_event)
			&& item->data->listener != nullptr) {
			ret = item->data->listener->OnEventChange(item->data, item->data->event);
			item->data->previous_event = item->data->event;
		}
	}
	return ret;
}

void j1Gui::ItemDestory(j1UIelements* item)
{
	int num = items.find(item);
	RELEASE(items.At(num)->data);
	items.del(items.At(num));
}

j1UIelements* j1Gui::AddItem(Type guitype, Position ali)
{
	j1UIelements* ret = nullptr;

	switch (guitype)
	{
	//case CHECK:
	//	ret = new GuiCheck(ali);
	//	items.add(ret);
	//	break;
	case IMAGE:
		ret = new ImageUI(ali);
		items.add(ret);
		break;
	//case BUTTON:
	//	ret = new GuiButton(ali);
	//	items.add(ret);
	//	break;
	//case INPUTBOX:
	//	ret = new GuiInput(ali);
	//	items.add(ret);
	//	break;
	case LABEL:
		ret = new LabelUI(ali);
		items.add(ret);
		break;
	/*case WINDOW:
		ret = new GuiWindow(ali);
		items.add(ret);
		break;*/
	}
	return ret;
}

ImageUI* j1Gui::AddImage(Position ali, char* path, SDL_Rect texture, iPoint movement, j1Module* listener)
{
	ImageUI* image = (ImageUI*)App->gui->AddItem(IMAGE, ali);
	image->rect = texture;
	image->movement = movement;
	image->listener = listener;
	image->Start();
	if (path != nullptr)
	{
		p2SString pat = path;
		image->tex = image->LoadTexture(pat.GetString());
	}
	return image;
}

//GuiButton* j1Gui::AddButton(Alignment align, p2SString text, iPoint displacement, j1Module* listener)
//{
//	GuiButton* button = (GuiButton*)App->gui->AddElement(BUTTON, align);
//	button->displacement = displacement;
//	button->text = text;
//	button->listener = listener;
//	button->Start();
//	return button;
//}
//
//GuiCheck* j1Gui::AddCheck(Alignment align, p2SString text, iPoint displacement, j1Module* listener)
//{
//	GuiCheck* check = (GuiCheck*)App->gui->AddElement(CHECK, align);
//	check->displacement = displacement;
//	check->text = text;
//	check->listener = listener;
//	check->Start();
//	return check;
//}

LabelUI* j1Gui::AddText(Position ali, p2SString text, iPoint movement, Fonts font, SDL_Color color, j1Module* listener)
{
	LabelUI* tex = (LabelUI*)App->gui->AddItem(LABEL, ali);
	tex->CreateText(text, color, font);
	tex->movement = movement;
	tex->listener = listener;
	tex->Start();
	return tex;
}

//GuiWindow* j1Gui::AddWindow(Alignment align, uint num_buttons, p2SString title, iPoint displacement, j1Module* listener)
//{
//	GuiWindow* window = (GuiWindow*)App->gui->AddElement(WINDOW, align);
//	window->displacement = displacement;
//	window->num_buttons = num_buttons;
//	window->title = title;
//	window->listener = listener;
//	window->Start();
//	return window;
//}