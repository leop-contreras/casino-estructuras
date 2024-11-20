#include "Ruta.h"
#include "Carrera.h"

using namespace std;

float ApostarMenu(float saldo)
{
	system("cls");
	int noCaballos, elegido;
	float monto, ganado, resultado;
	cout << "----------------------------------------------------------\n";
	cout << "	CARRERA DE POTROOOOOOOOS!                \n";
	cout << "----------------------------------------------------------\n";
	cout << "En este juego, puedes realizar apuestas sobre el resultado\n";
	cout << "de la carrera de caballos, eligiendo entre tres tipos de \n";
	cout << "apuestas:                                                 \n";
	cout << "  1. Win:   Apuesta a que el caballo seleccionado gana. (1.1x)\n";
	cout << "  2. Place: Apuesta a que el caballo queda en 1er o 2do. (1.2x)\n";
	cout << "  3. Show:  Apuesta a que el caballo queda en el top 3. (1.3x)\n";
	cout << "                                                        \n";
	cout << "Cada caballo tiene una velocidad, que afecta tanto su \n";
	cout << "rendimiento como el multiplicador de su apuesta.         \n";
	cout << "Los caballos más rápidos tienen menor multiplicador,     \n";
	cout << "mientras que los más lentos ofrecen multiplicadores      \n";
	cout << "más altos debido a su menor probabilidad de ganar.       \n";
	cout << "                                                        \n";
	cout << "Ejemplo de multiplicadores basados en velocidad:         \n";
	cout << "  - Caballo 1: Velocidad 10, Multiplicador 1.2x (Win)     \n";
	cout << "  - Caballo 2: Velocidad 7, Multiplicador 3.5x (Win)     \n";
	cout << "  - Caballo 3: Velocidad 5, Multiplicador 8.0x (Win)     \n";
	cout << "                                                        \n";
	cout << "                                                        \n";
	cout << "Decide si prefieres apostar por un caballo rápido con    \n";
	cout << "menores recompensas, o arriesgar con uno lento para      \n";
	cout << "ganancias más grandes. ¡Que comience la carrera!         \n";
	cout << "                                                        \n";
	cout << "Además, ten en cuenta que conforme el carril esté más    \n";
	cout << "lejos, es decir, el número del carril es mayor, el      \n";
	cout << "caballo recibirá un multiplicador adicional que aumentará\n";
	cout << "con la distancia del carril. Este multiplicador varía   \n";
	cout << "de 1 a 1.4, lo que significa que, cuanto más lejos esté el\n";
	cout << "carril, mayor será la recompensa.                       \n";
	cout << "                                                        \n";
	cout << "  - Carril 1: Multiplicador 1.0x     \n";
	cout << "  - Carril 2: Multiplicador 1.25x     \n";
	cout << "  - Carril 3: Multiplicador 1.5x     \n";
	cout << "                                                        \n";
	cout << "¡Así que elige sabiamente y ve si el multiplicador del   \n";
	cout << "carril te da la ventaja que necesitas para ganar!        \n";
	cout << "----------------------------------------------------------\n";


	bool band = false;

	do
	{
		cout << "\n\t¿Con cuantos caballos desea apostar? \n1.- 5 CABALLOS - 1.5x \n2.- 10 CABALLOS 2.0X \n3.- 20 Caballos 3.0x" << endl;
		cin >> noCaballos;
		cin.ignore();
		switch (noCaballos)
		{
		case 1:
		{
			noCaballos = 4;
			band = true;
			break;
		}
		case 2:
		{
			noCaballos = 9;
			band = true;
			break;
		}
		case 3:
		{
			noCaballos = 19;
			band = true;
			break;
		}
		default:
			cout << "Seleccione una opción valida" << endl;
			break;
		}
	} while (!band);

	Carrera carrera(noCaballos);
	carrera.MostrarCaballos();

	int totalApuestas;
	int caso, max;


	if (noCaballos == 4)
		max = 2;
	else
		max = 3;

	do
	{
		cout << "¿Cuantas apuestas desea colocar (" << max << ")?: " << endl;
		cin >> totalApuestas;
		cin.ignore();

		if (totalApuestas > max)
		{
			cout << "\n\tSolo puede mantener (" << max << ") apuestas A LA VEZ.\n" << endl;
		}
		else
		{
			carrera.Apuestas(totalApuestas);
		}

	} while (totalApuestas > max);


	for (int z = 0; z < totalApuestas; z++)
	{
		cout << "\n\tAPUESTA (" << z + 1 << ")." << endl;
		cout << "¿Por cual desea apostar?: ";
		cin >> elegido;
		cin.ignore();
		cout << endl;

		cout << "¿Que monto apostara?: ";
		cin >> monto;
		cin.ignore();
		cout << endl;

		cout << "¿Por cual desea apostar? \n\n\t1.- WIN 1.3x \n\t2.- PLACE 1.2x \n\t3.- SHOW 1.1X \n\nSu apuesta: ";
		cin >> caso;
		cin.ignore();
		cout << endl;

		saldo -= monto;
		cout << "SALDO MENOS MONTO -> " << saldo << "." << endl;
		carrera.AgregarApuesta(monto, elegido, z, caso);
	}

	int turnos = 0;
	bool carreraActiva = true;

	resultado = carrera.MostrarCarrera();

	saldo += resultado;

	cout << "SALDO FINAL -> " << saldo << "." << endl;

	cout << "\nPRESIONE CUALQUIER TECLA PARA CONTINUAR." << endl;

	cin.get();

	system("cls");

	return saldo;
}

/*int main()
{
	setlocale(LC_ALL, "");
	int opc, velocidad, longitud, pasos;
	float saldo = 10000;
	string nombre;
	do
	{
		cout << "CARRERA DE CABALLOS" << endl;
		cout << "MENú \n1.- Apostar \n2.- Ver carrera (Sin apostar) \n3.- Regresar" << endl;
		cin >> opc;
		cin.ignore();

		switch (opc)
		{
		case 1:
		{
			cout << "\n\tAPOSTAR" << endl;
			saldo = Apostar(saldo);
			break;
		}
		case 2:
		{
			cout << "\n\tCARRERA SIN APOSTAR" << endl;

			break;
		}
		case 3:
		{
			cout << "" << endl;
			break;
		}
		default:
			cout << "INTENTE DE NUEVO" << endl;
			break;
		}
	} while (opc != 3);
}*/

