#ifndef __WINDOWUI_H__
#define __WINDOWUI_H__

#include "j1UIelements.h"
#include "p2List.h"
#include "p2SString.h"

#define MAX_BUTTON_NUM 10

class j1UIelements;
class LabelUI;
class ButtonUI;

class WindowUI : public j1UIelements
{
public:

	WindowUI(Position ali = NO_POSITIONING);

	virtual ~WindowUI();
	bool Start();
	bool CleanUp();
	bool Update(float dt);

	p2SString title;
	uint ButtonCount;

	void AddItemToWindow(j1UIelements* item);
	void InputUpdate(Input state);
	void MainButtonTag(p2SString txt);

private:
	p2List<j1UIelements*> ItemWindow;
	p2List<ButtonUI*> ButtWindow;
	p2List<p2SString> TextBttWindow;
	LabelUI* TextWindow = nullptr;

	void Move();
	void MoveStart();
	void MoveEnd();
	void ButtonPlacer();
	void WindowItemsMove(iPoint movement);
};

#endif // __GUIWINDOW_H__