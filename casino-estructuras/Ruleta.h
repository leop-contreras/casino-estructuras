#pragma once
#include "Casino.h"

using namespace std;

class Ruleta
{
public:
	Ruleta();
	bool Numerodeljugador(int);
private:
	stack <int> ruleta, jugador;
};

