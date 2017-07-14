#include "main.h"
#include "AppDelegate.h"
#include "RioEngine.h"

#include <memory>
#include <exception>
#include <string>

#include "Game.h"
#include "World/World.h"

#ifdef WIN32
#include "windows.h"
#else
#include <iostream>
#endif

void printMessage(const std::string&, const std::string&);

using namespace RioEngine;

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

	int result = 0;

	try
	{
		AppDelegate app;
		result = Application::getInstance()->run();

		using namespace RioGame;

		Game game{};

		game.getWorld()->init(&game);

		game.run();
	}
	catch (const std::exception& ex)
	{
		printMessage(ex.what(), "Std Exception!");
		result = 1;
	}
	catch (...)
	{
		printMessage("Unknown exception caught in main!", "Unknown Exception!");
		result = 1;
	}

	return result;
}

// Prints a message to the screen, either in a message box (win) or to the command line
void printMessage(const std::string& msg, const std::string& title = "NULL")
{
#ifdef WIN32
	MessageBoxA(nullptr, msg.c_str(), title.c_str(), 0);
#else
	std::cout << "[" << title << "] " << msg << std::endl;
#endif
}