#include "ButtonUI.h"
#include "j1Gui.h"
#include "j1UIelements.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Textures.h"
//#include "Brofiler\Brofiler.h"

ButtonUI::ButtonUI(Position alig) : j1UIelements(Type::BUTTON, Position::NO_POSITIONING)
{
	ali = alig;
}

ButtonUI::~ButtonUI()
{}

bool ButtonUI::Start()
{

	rect = { 0,0, 339, 63 };
	tex = None;

	return true;
}

bool ButtonUI::CleanUp()
{
	//App->tex->UnLoad(tex);

	deleting = true;
	if (tex != nullptr)
		App->tex->UnLoad(tex);
	App->tex->UnLoad(None);
	App->tex->UnLoad(Over);
	App->tex->UnLoad(Pressed);


	return true;
}
bool ButtonUI::PreUpdate() {


	return true;
}

bool ButtonUI::Update(float dt)
{
	//BROFILER_CATEGORY("ButtonUI_Update", Profiler::Color::OrangeRed);
	if (active == false) {

		tex = Pressed;
	}
	UpdatePosition();
	App->render->Blit(tex, position.x + movement.x, position.y + movement.y, &rect);
	return true;
}

void ButtonUI::MouseInput(Input status)
{
	switch (status)
	{
	case IDLE:
		tex = None;
		inp = status;
		break;
	case HOVER:
		tex = Over;
		inp = status;
		break;
	case PRESSED_L:
		if (Pressed != NULL)
			tex = Pressed;
		inp = status;
		break;
	case UP_L:
		tex = None;
		break;
	}
}

void ButtonUI::Move(iPoint movem)
{
	movement.x += movem.x;
	movement.y += movem.y;
}

void ButtonUI::SettleTextureToButton(p2SString idle, p2SString hover, p2SString pressed) {

	None = LoadTexture(idle);
	Over = LoadTexture(hover);
	Pressed = LoadTexture(pressed);
	tex = None;

}

void ButtonUI::ChangeEvent(j1UIelements* item, Event event)
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