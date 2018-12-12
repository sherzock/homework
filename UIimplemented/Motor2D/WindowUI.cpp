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
	if (kinetic) { Move(); }
	UpdatePosition();
	App->render->Blit(tex, position.x + movement.x, position.y + movement.y, &rect);
	return true;
}

void WindowUI::MouseInput(Input status)
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
		if (movable)
			MoveStart();
		inp = status;
		break;
	case UP_L:
		if (movable)
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

}

void WindowUI::MoveEnd()
{
	OnClick = { 0,0 };
}


void WindowUI::WindowItemsMove(iPoint movement) {

	for (p2List_item<ButtonUI*>* butt = ButtWindow.start; butt; butt = butt->next) {
		butt->data->Move(movement);
	}
	for (p2List_item<j1UIelements*>* item = ItemWindow.start; item; item = item->next) {
		item->data->Move(movement);
	}
}

void WindowUI::AddItemToWindow(j1UIelements* item) { ItemWindow.add(item); }

void WindowUI::ChangeEvent(j1UIelements* item, Event event)
{
	switch (event)
	{
	case Event::MOUSE_INSIDE:
		item->MouseInput(HOVER);
		break;
	case Event::MOUSE_OUTSIDE:
		item->MouseInput(IDLE);
		break;
	case Event::RIGHT_CLICK:
		item->MouseInput(PRESSED_R);
		break;
	case Event::LEFT_CLICK:
		item->MouseInput(PRESSED_L);
		break;
	case Event::LEFT_CLICK_UP:
		item->MouseInput(UP_L);
		break;
	case Event::RIGHT_CLICK_UP:
		item->MouseInput(UP_R);
		break;

	}
}