#ifndef __WINDOWUI_H__
#define __WINDOWUI_H__

#include "j1UIelements.h"
#include "p2List.h"
#include "p2SString.h"

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
	void ChangeEvent(j1UIelements* item, Event event);
	void AddItemToWindow(j1UIelements* item);
	void MouseInput(Input state);

	bool movable = false;

private:
	p2List<j1UIelements*> ItemWindow;
	p2List<ButtonUI*> ButtWindow;
	p2List<p2SString> TextBttWindow;
	LabelUI* TextWindow = nullptr;
	
	void Move();
	void MoveStart();
	void MoveEnd();
	void WindowItemsMove(iPoint movement);
};

#endif // __GUIWINDOW_H__