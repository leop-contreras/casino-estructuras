#pragma once
#include <iostream>
#include <stack>
#include <cstdlib>

using namespace std;

class Ruleta
{
public:
	Ruleta();
	bool Numerodeljugador(int);
private:
	stack <int> ruleta, jugador;
};

