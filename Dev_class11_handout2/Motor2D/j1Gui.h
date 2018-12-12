#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "p2List.h"
#include "j1UIelements.h"
#include "LabelUI.h"
#include "ImageUI.h"
#include "ButtonUI.h"
#include "WindowUI.h"

#define CURSOR_WIDTH 2

// TODO 1: Create your structure of classes

// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	//Update
	bool Update(float dt);

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Gui creation functions

	SDL_Texture* GetAtlas() const;

	ImageUI* AddImage(Position ali, char* path, SDL_Rect texture = { 0,0,0,0 }, iPoint movement = { 0,0 }, j1Module* listener = nullptr);
	ButtonUI* AddButton(Position ali, p2SString text, iPoint movement = { 0,0 }, j1Module* listener = nullptr);
	/*GuiCheck* AddCheck(Alignment align, p2SString text, iPoint displacement = { 0,0 }, j1Module* listener = nullptr);*/
	LabelUI* AddText(Position ali, p2SString text, iPoint movement = { 0,0 }, Fonts = OPENSANS, SDL_Color color = { 255,255,255,255 }, j1Module* listener = nullptr);
	WindowUI* AddWindow(Position ali, uint num_buttons, p2SString title, iPoint movement = { 0,0 }, j1Module* listener = nullptr);

private:


	j1UIelements * AddItem(Type guitype, Position ali = Position::NO_POSITIONING);
	
	void ItemEventUpdate() const;
	void ItemDestory(j1UIelements* item);

	bool debug = false;
	bool ItemEventManager();

	p2List<j1UIelements*> items;

	SDL_Texture* atlas;
	p2SString atlas_file_name;
};

#endif // __j1GUI_H__