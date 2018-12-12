#ifndef __j1UIELEMENTS_H__
#define __j1UIELEMENTS_H__

#include "j1Module.h"
#include "SDL\include\SDL_rect.h"
#include "p2Point.h"

struct SDL_Texture;

enum Position { NO_POSITIONING, POSITION_LEFT = 1, POSITION_CENTER, POSITION_RIGHT };
enum Input { IDLE = 0, HOVER, PRESSED_R, UP_R, PRESSED_L, UP_L, DISABLED };
enum Event { MOUSE_INSIDE = 1, MOUSE_OUTSIDE, LEFT_CLICK, LEFT_CLICK_UP, RIGHT_CLICK, RIGHT_CLICK_UP };
enum Type { CHECK = 1, IMAGE, BUTTON, INPUTBOX, LABEL, WINDOW };
enum Fonts {OPENSANS};

class j1UIelements : j1Module
{
public:
	j1UIelements(Type guitype,Position ali ,j1Module* listener = nullptr );
	virtual ~j1UIelements();


	virtual bool Awake(pugi::xml_node&) { return true; };
	virtual bool Start();
	virtual bool PreUpdate() { return true; };
	virtual bool Update(float dt);
	virtual bool PostUpdate() { return true; };
	virtual bool CleanUp();

	void UpdatePosition();
	virtual void ShowDebug();
	virtual void Move(iPoint movement) {};
	virtual void MouseInput(Input state) {};

	SDL_Texture* LoadTexture(p2SString path);
	SDL_Texture* tex = nullptr;

	Type guitype;
	Event event = Event::MOUSE_OUTSIDE;
	Event previous_event = Event::MOUSE_OUTSIDE;
	Input inp = Input::IDLE;
	Position ali;

	SDL_Rect rect;
	iPoint position;
	iPoint movement;
	j1Module* listener;

	bool show = true;
	bool deleting = false;
	bool kinetic = true;

private:

	bool Blit() const { return true; }
	bool debug = false;

protected:
	//bool moving = false;
	iPoint OnClick = { 0,0 };
};

#endif // __j1UIELEMENTS_H__