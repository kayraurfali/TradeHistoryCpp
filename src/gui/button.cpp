#include "button.h"

button::button(int x, int y, int w, int h, button_callback callback) :
	x(x), y(y), w(w), h(h), usr_callback(callback)
{}
