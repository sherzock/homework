#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;
class GuiImage;
class GuiText;

class WindowUI;
class ButtonUI;
class LabelUI;
class ImageUI;

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

	bool OnEventChange(j1UIelements* elem, Event event);

private:
	SDL_Texture * debug_tex;
	GuiImage* banner;
	GuiText* text;
	LabelUI* test = nullptr;
	ImageUI* test2 = nullptr;
	ButtonUI* testbutt = nullptr;
	WindowUI* window = nullptr;
};

#endif // __j1SCENE_H__