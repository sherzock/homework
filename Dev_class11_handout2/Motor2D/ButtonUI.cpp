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
	if (text == nullptr)
		PutTextOnButton();
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
	if (BttText)
		BttText->CleanUp();


	return true;
}
bool ButtonUI::PreUpdate() {

	if (deleting&&BttText)
	{
		BttText->deleting = true;
	}
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

void ButtonUI::PutTextOnButton()
{
	int width, heigh;
	App->font->CalcSize(text.GetString(), width, heigh);

	switch (ali)
	{
	case NO_POSITIONING:
		BttText = App->gui->AddText(NO_POSITIONING, text, { movement.x , movement.y + 2 }, OPENSANS, { 255, 255,0,255 });
		break;
	case POSITION_CENTER:
		BttText = App->gui->AddText(ali, text, { movement.x , movement.y + 2 }, OPENSANS, { 255, 255,0,255 });
		break;
	case POSITION_RIGHT:
		BttText = App->gui->AddText(ali, text, { movement.x + width / 2 - rect.w / 2 , movement.y + 2 }, OPENSANS, { 255, 255,0,255 });
		break;
	case POSITION_LEFT:
		BttText = App->gui->AddText(ali, text, { movement.x + (rect.w - width) / 2 , movement.y + 2 }, OPENSANS, { 255, 255,0,255 });
		break;
	}
}

void ButtonUI::InputUpdate(Input status)
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

void ButtonUI::ButtonTxtUpdate(p2SString txt)
{
	BttText->UpdateText(txt);
}

void ButtonUI::Move(iPoint movem)
{
	movement.x += movem.x;
	movement.y += movem.y;
	MoveButtonItems(movem);
}

void ButtonUI::MoveButtonItems(iPoint movement)
{
		BttText->Move(movement);
}

void ButtonUI::SettleTextToButton(p2SString idle, p2SString hover, p2SString pressed) {

	None = LoadTexture(idle);
	Over = LoadTexture(hover);
	Pressed = LoadTexture(pressed);
	tex = None;

}