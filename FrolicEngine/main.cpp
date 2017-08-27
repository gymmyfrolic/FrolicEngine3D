#include "Window.h"

int main() {
	Window window;
	window.Initialize();

	while (true) {
		window.Update();
	}

	return 0;
}