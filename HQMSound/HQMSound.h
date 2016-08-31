#pragma once

#using <mscorlib.dll>
#using <HockeyEditor.dll>
#include "yse.hpp"
#include <msclr\marshal_cppstd.h>
#include <string>
#include <iostream>
#include <tuple>
using namespace HockeyEditor;

void NativeWrapInit()
{
	MemoryEditor::Init();
}

void PrintPlayers()
{
	for each (Player^ p in PlayerManager::Players)
	{
		System::Console::WriteLine(p->Name);
	}
}

std::string GetLocalPlayerName()
{
	Player^ p = PlayerManager::Players[0];
	msclr::interop::marshal_context context;
	std::string standardString = context.marshal_as<std::string>(p->Name);

	return standardString;
}

std::tuple<double,double>* CheckVelocity()
{
	double x, z;
	x = Puck::Velocity->X;
	z = Puck::Velocity->Z;
	return new std::tuple<double,double>(x, z);
}

YSE::Vec GetPuckPos()
{
	Flt x, z;
	x = Puck::Position->X;
	z = Puck::Position->Z;
	return YSE::Vec(x, 0, z);
}

YSE::Vec GetPlayerPos()
{
	Flt x, z;
	x = PlayerManager::LocalPlayer->Position->X;
	z = PlayerManager::LocalPlayer->Position->Z;
	return YSE::Vec(x, 0, z);
}

YSE::Vec GetPlayerRot()
{
	float sin = PlayerManager::LocalPlayer->SinRotation;
	float cos = PlayerManager::LocalPlayer->CosRotation;
	return YSE::Vec(-cos, 0, -sin);
}