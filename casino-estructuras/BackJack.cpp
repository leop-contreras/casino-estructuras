#include "BackJack.h"

BackJack::BackJack()
{
  
}



void BackJack::inicializarBaraja()
{
    string palos[] = { "Corazones", "Diamantes", "Tréboles", "Picas" };
    int valores[] = { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };

    int index = 0;
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 13; j++)
        {
            
            BarajaSM[index++] = { palos[i],valores[j] };
        }
    }
}

int generarIndiceAleatorio(bool usados[]) {
    int indice;
    do {
        indice = rand() % 52;
    } while (usados[indice]);
    usados[indice] = true;
    return indice;
}

void BackJack::barajear()
{
    inicializarBaraja();

    for (int i = 0; i < 52; ++i) {
        int indiceAleatorio = generarIndiceAleatorio(usados);
        BARAJA.push(BarajaSM[indiceAleatorio]);
    }

}

int BackJack::Puntaje(stack<Carta> pila)
{
    int puntaje = 0, as = 0;
    Carta carta;
    while (puntaje > 21)
    {
        if (pila.empty()) {
            carta = pila.top();
            pila.pop();
            if (carta.valor == 11) as++;
            if ((puntaje + carta.valor) > 21 && as > 0) {
                carta.valor = 1;
            }
            puntaje += carta.valor;
        }
        else
        {
            return puntaje;
        }
    }
    return -1;
}

int BackJack::Jugar(int apuesta)
{
    Carta carta;
    int opc;
    
    carta = BARAJA.top();
    BARAJA.pop();
    CASA.push(carta);
    cout << "\nCarta de la casa:: " << carta.nombre;
    do
    {
        carta = BARAJA.top();
        BARAJA.pop();
        JUGADOR.push(carta);
        cout << "\nCarta del Jugador:: " << carta.nombre << endl;
        cout << "\nDeseas otra carta?\n1)Si\n2)NO\nSelecciona una opcion:: ";
    } while (opc == 2);

    if (Puntaje(JUGADOR) == -1) {
        cout << "Perdiste";
        return 0;
    }
    while (Puntaje(JUGADOR) <= Puntaje(CASA)) {
        carta = BARAJA.top();
        BARAJA.pop();
        CASA.push(carta);
        cout << "\nCarta de la casa:: " << carta.nombre;
    }
    if (Puntaje(CASA) == -1) {
        cout << "La casa perdio";
        return (apuesta*2);
    }

    if (Puntaje(JUGADOR) == Puntaje(CASA)) {
        cout << "Empate";
        return apuesta;
    }

    cout << "La casa gano";
    return 0;
}




