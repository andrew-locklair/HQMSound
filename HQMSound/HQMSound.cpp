// HQMSound.cpp : main project file.
#include "stdafx.h"
#include "yse.hpp"
#include "HQMSound.h"
#include <iostream>
#include <cstdlib>
#include <tuple>
#if defined YSE_WINDOWS
#include <conio.h>
#else
#include "wincompat.h"
#endif

using namespace System;
using namespace HockeyEditor;


int main()
{
	NativeWrapInit();
	PrintPlayers();
	std::tuple<double, double> currentVelocity(0, 0);
	std::string currentDir = "C:\\Users\\Andrew\\Documents\\Repositories\\HQMSound\\Debug\\";
	std::string pulseSound = currentDir + "pulse1.ogg";
	std::string goal = "C:\\Users\\Andrew\\Music\\Soundboard\\HUSTLE.ogg";
	std::string puck = "C:\\Users\\Andrew\\Music\\HQMSound\\shot.ogg";
	YSE::sound sound;
	YSE::sound puckNoise;
	// initialize audio system
	YSE::System().init();

	// load a sound in memory
	if (GetLocalPlayerName().c_str() == "xParabolax")
		sound.create(pulseSound.c_str(), NULL, true);
	else
		sound.create(goal.c_str(), NULL, true);
	puckNoise.create(puck.c_str());

	// false on validation means the sound could not be loaded
	if (!sound.isValid()) {
		std::cout << "sound 'pulse1.ogg' not found" << std::endl;
		std::cin.get();
		goto exit;
	}

	std::cout << "This is a bare-bones YSE example. It contains the minimum you need to start your own projects." << std::endl;
	std::cout << "Press spacebar to toggle sound playing." << std::endl;
	std::cout << "Or e to exit." << std::endl;

	while (true) {
		YSE::Listener().setPosition(GetPlayerPos()).setOrientation(GetPlayerRot());
		std::tuple<double, double> newVelocity = *CheckVelocity();
		if (std::get<0>(currentVelocity) - std::get<0>(newVelocity) > 0.01 || 
			std::get<1>(currentVelocity) - std::get<1>(newVelocity) > 0.01)
		{
			puckNoise.play();
		}
		else if (puckNoise.isPlaying())
		{
			puckNoise.setPosition(GetPlayerPos());
		}
		else
		{
			puckNoise.setPosition(GetPuckPos());
		}
		currentVelocity = newVelocity;
		if (_kbhit()) {
			char ch = _getch();
			switch (ch) {
				// toggle function toggles play / pause
			case ' ': sound.toggle(); break;
			case 'a': sound.play(); break;
			case 's': sound.pause(); break;
			case 'd': sound.stop(); break;
			case 'e': goto exit;
			}
		}

		/* the sleep function can be used to make sure the update function doesn't run at full
		speed. In a simple demo it does not make sense to update that much. In real software
		this should probably not be used. Just call YSE::System.update() in your main program loop.
		*/
		YSE::System().sleep(5);

		/* The update function activates all changes you made to sounds and channels since the last call.
		This function locks the audio processing thread for a short time. Calling it more than 50 times
		a second is really overkill, so call it once in your main program loop, not after changing every setting.
		*/
		YSE::System().update();
	}
	exit:
		// don't forget this...
		YSE::System().close();
		return 0;
}
