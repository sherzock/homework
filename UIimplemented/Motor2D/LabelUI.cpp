#include "LabelUI.h"
#include "j1Gui.h"
#include "j1UIelements.h"
#include "j1App.h"
#include "j1Fonts.h"
#include "j1Render.h"
#include "j1Textures.h"
//#include "Brofiler\Brofiler.h"

LabelUI::LabelUI(Position alig) : j1UIelements(Type::LABEL, Position::NO_POSITIONING)
{
	ali = alig;

}

LabelUI::~LabelUI()
{}

bool LabelUI::Start()
{
	int width, height;
	App->font->CalcSize(text.GetString(), width, height, text_font);
	rect.w = width;
	rect.h = height;
	return true;
}

bool LabelUI::CleanUp()
{
	deleting = true;
	App->tex->UnLoad(tex);

	return true;
}

void LabelUI::CreateText(p2SString txt, SDL_Color color, Fonts font)
{
	_TTF_Font* fnt = nullptr;
	int font_size = DEFAULT_FONT_SIZE;
	const char* path = nullptr;
	switch (font)
	{
	case OPENSANS:
		path = "fonts/open_sans/OpenSans-Regular.ttf";
		break;
	
	}
	fnt = App->font->Load(path, font_size);


	text_color = color;
	text_font = fnt;
	text = txt;
	tex = App->font->Print(text.GetString(), text_color, text_font);
}

bool LabelUI::Update(float dt)
{
	//BROFILER_CATEGORY("GuiLabel_Update", Profiler::Color::OrangeRed);
	UpdatePosition();
	App->render->Blit(tex, position.x + movement.x, position.y + movement.y);
	return true;
}

void LabelUI::UpdateText(p2SString newtext)
{
	App->tex->UnLoad(tex);
	text = newtext;
	tex = App->font->Print(newtext.GetString(), text_color, text_font);
}

void LabelUI::Move(iPoint displace)
{
	movement.x += displace.x;
	movement.y += displace.y;
}