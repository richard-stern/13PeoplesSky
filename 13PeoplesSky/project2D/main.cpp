#include <crtdbg.h>

#include "Application2D.h"
#include "Vector2.h"


int main() {
	// Memory leak checker
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	// allocation
	auto app = new Application2D();

	// initialise and loop
	app->run("AIE", 1280, 720, false);

	// deallocation
	delete app;

	Vector2(10, 10);

	return 0;
}