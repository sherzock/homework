#include "WindowUI.h"
#include "j1Gui.h"
#include "j1UIelements.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"
#include "p2Log.h"
#include "j1Textures.h"
//#include "Brofiler\Brofiler.h"

WindowUI::WindowUI(Position alig) : j1UIelements(Type::INPUTBOX, Position::NO_POSITIONING)
{
	ali = alig;
}

WindowUI::~WindowUI()
{}

bool WindowUI::Start()
{
	if (tex != nullptr) {
		tex = App->gui->GetAtlas();
		rect = { 30, 542, 422, 454 };
	}
	ButtonPlacer();

	event = LEFT_CLICK; 
	previous_event = LEFT_CLICK;

	return true;
}

bool WindowUI::CleanUp()
{
	deleting = true;
	App->tex->UnLoad(tex);

	if (TextWindow) { TextWindow->CleanUp(); }

	for (p2List_item<ButtonUI*>* btt = ButtWindow.start; btt; btt = btt->next) {
		btt->data->CleanUp();
	}
	ButtWindow.clear();
	for (p2List_item<j1UIelements*>* item = ItemWindow.start; item; item = item->next) {
		item->data->CleanUp();
	}
	ItemWindow.clear();
	for (p2List_item<p2SString>* str = TextBttWindow.start; str; str = str->next) {
		str->data.Clear();
	}
	TextBttWindow.clear();
	//App->tex->UnLoad(tex);
	return true;
}

bool WindowUI::Update(float dt)
{
	//BROFILER_CATEGORY("GuiWindow_Update", Profiler::Color::OrangeRed);
	if (moving && kinetic) { Move(); }
	UpdatePosition();
	App->render->Blit(tex, position.x + movement.x, position.y + movement.y, &rect);
	return true;
}

void WindowUI::InputUpdate(Input status)
{
	switch (status)
	{
	case IDLE:
		inp = status;
		break;
	case HOVER:
		inp = status;
		break;
	case PRESSED_L:
		if (kinetic)
			MoveStart();
		inp = status;
		break;
	case UP_L:
		if (kinetic)
			MoveEnd();
		inp = status;
		break;
	}
}

void WindowUI::Move()
{
	iPoint mouse_position;
	App->input->GetMousePosition(mouse_position.x, mouse_position.y);
	movement.x += (mouse_position.x - OnClick.x);
	movement.y += (mouse_position.y - OnClick.y);
	WindowItemsMove({ mouse_position.x - OnClick.x , mouse_position.y - OnClick.y });
	OnClick = mouse_position;
}

void WindowUI::MoveStart()
{
	iPoint mouse_position;
	App->input->GetMousePosition(mouse_position.x, mouse_position.y);
	OnClick = mouse_position;

	moving = true;
}

void WindowUI::MoveEnd()
{
	OnClick = { 0,0 };
	moving = false;
}

void WindowUI::ButtonPlacer()
{
	if (ButtonCount > MAX_BUTTON_NUM)
	{
		LOG("Exceded max num buttons");
		ButtonCount = MAX_BUTTON_NUM;
	}
	iPoint localPos = { position.x + movement.x, position.y + movement.y };
	for (int i = 0; i < ButtonCount; i++)
	{
		p2SString butt_text;
		if (TextBttWindow.count() <= i)
		{
			butt_text = nullptr;
		}
		else
		{
			butt_text = TextBttWindow.At(i)->data;
		}
		ButtonUI* btt;

		btt = App->gui->AddButton(ali, butt_text, { localPos.x , localPos.y + 40 * (i + 1) }, listener);

		ButtWindow.add(btt);
	}
}
void WindowUI::WindowItemsMove(iPoint movement) {

	for (p2List_item<ButtonUI*>* butt = ButtWindow.start; butt; butt = butt->next) {
		butt->data->Move(movement);
	}
	for (p2List_item<j1UIelements*>* item = ItemWindow.start; item; item = item->next) {
		item->data->Move(movement);
	}
}

void WindowUI::MainButtonTag(p2SString txt) {

	if (TextBttWindow.count() >= MAX_BUTTON_NUM) {
		LOG("Exceded max num buttons");
		return;
	}
	TextBttWindow.add(txt);
}

void WindowUI::AddItemToWindow(j1UIelements* item) { ItemWindow.add(item); }