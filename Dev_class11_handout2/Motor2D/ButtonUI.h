#ifndef __ButtonUI_H__
#define __ButtonUI_H__

#include "j1UIelements.h"

class LabelUI;

class ButtonUI : public j1UIelements
{
public:

	ButtonUI(Position alignment = NO_POSITIONING);
	virtual ~ButtonUI();

	bool Start();
	bool CleanUp();
	bool PreUpdate();
	bool Update(float dt);

	p2SString text;
	void InputUpdate(Input state);
	void ButtonTxtUpdate(p2SString txt);
	void Move(iPoint movement);

	void SettleTextToButton(p2SString path_idle, p2SString path_hover, p2SString path_pressed = nullptr);

	bool active = true;

private:
	SDL_Texture * None = nullptr;
	SDL_Texture* Over = nullptr;
	SDL_Texture* Pressed = nullptr;


	void PutTextOnButton();
	void MoveButtonItems(iPoint movement);
	LabelUI* BttText = nullptr;

};

#endif // __GUIBUTTON_H__
