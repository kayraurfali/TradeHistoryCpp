#pragma once

class button
{
	typedef void (*button_callback)(void);
public:
	button(int x, int y, int w, int h, button_callback callback);
private:
	int x, y, w, h;
	button_callback usr_callback;
};

