#include "Casino.h"
#include "Ruta.h"
using namespace std;

struct Apuesta
{
	float monto;
	int elegido;
	int numApuesta;
	int caso;
};

struct Carril
{
	Ruta info;
	Carril* sig;

	Carril() : info("Desconocido", 0, 0, 0), sig(nullptr) {}

};

class Carrera
{
public:
	Carrera(int);
	void AñadirCarril();
	void MostrarCaballos();
	float CalcularApuesta(float, int, int);
	float MostrarCarrera();
	void BorrarUltimaLinea();
	void MoverCursorArriba(int);
	void MoverCursorAbajo(int);
	void Apuestas(int);
	void AgregarApuesta(float, int, int, int);
	void RecorrerApuestas();

private:
	string CrearNombre();
	int CrearVelocidad(int);
	float CrearMultiplicador(int, int, int);
	float PotenciadorCarril(int);

	Carril* cabecera, * final, * nodo;
	Ruta* nuevoCarril;
	Apuesta** apuestas;
	int totalApuestas;
	int longitud;
	int tope;
	int caballos;
	int numCaballosGanadores[3];
	float multCaballosGanadores[3];
	float multGanador;
	bool carreraTerminada;
	bool nombresUsados[20] = { false };
	float ganancia;
	float perdida;
};
