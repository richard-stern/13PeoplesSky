#include <crtdbg.h>
#include <random>
#include <ctime>
#include <Windows.h>
#include <Mmsystem.h>
#include <mciapi.h>
//these two headers are already included in the <Windows.h> header
#pragma comment(lib, "Winmm.lib")

#include "Application2D.h"
#include "Vector2.h"


int main() {
	// Memory leak checker
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	std::time_t time = std::time(0);
	std::tm* now = std::localtime(&time);
	int seed = now->tm_sec;
	seed += now->tm_hour << 8;
	seed += now->tm_min << 16;
	seed += now->tm_year << 24;

	srand(seed);

	// allocation
	auto app = new Application2D();

	mciSendString(L"open \"..\\8.mp3\" type mpegvideo alias mp3", NULL, 0, NULL);
	
	//mciSendString(L"play mp3", NULL, 0, NULL);	
	//mciSendString(L"play mp3 from 0", NULL, 0, NULL);	
	//mciSendString(L"play mp3 from 0 wait", NULL, 0, NULL);	
	mciSendString(L"play mp3 repeat", NULL, 0, NULL);

	// initialise and loop
	app->run("13 People's Sky", 1280, 720, false);

	// deallocation
	delete app;

	Vector2(10, 10);

	return 0;
}