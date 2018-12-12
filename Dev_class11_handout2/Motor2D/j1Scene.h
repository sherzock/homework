#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
class ImageUI;
class LabelUI;
class ButtonUI;
class GuiCheck;
class GuiInput;
class WindowUI;


class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	void OnEventChange(j1UIelements* elem, Event event) const;

private:
	SDL_Texture * debug_tex;
	SDL_Texture* background;
	ImageUI* WC_logo;
	ImageUI* rating;
	ImageUI* blizzard;

	ButtonUI* login;

	LabelUI* release;
	LabelUI* copyright;
	LabelUI* date;
	LabelUI* web;

	WindowUI* window;

};

#endif // __j1SCENE_H__