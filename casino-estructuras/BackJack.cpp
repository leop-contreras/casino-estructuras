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

int BackJack::generarIndiceAleatorio(bool usados[]) {
    srand(time(0));
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

    while (!pila.empty()) {
        carta = pila.top();
        pila.pop();

        if (carta.valor == 11) as++;  
        puntaje += carta.valor;

        
        while (puntaje > 21 && as > 0) {
            puntaje -= 10;  
            as--;  
        }
    }

    if (puntaje > 21) return -1;

    return puntaje; 
}
int BackJack::Jugar(int apuesta)
{
    Carta carta;
    while(!JUGADOR.empty()){
        JUGADOR.pop();
    }
    while (!CASA.empty()) {
        CASA.pop();
    }
    while (!BARAJA.empty()) {
        BARAJA.pop();
    }
    int opc;
    
    barajear();
    

    carta = BARAJA.top();
    BARAJA.pop();
    CASA.push(carta);
    cout << "\nCarta de la casa:: " << carta.valor << " de " << carta.nombre;
    do
    {
        carta = BARAJA.top();
        BARAJA.pop();
        JUGADOR.push(carta);
        cout << "\nCarta del Jugador:: " << carta.valor << " de " << carta.nombre << endl;
        cout << "\nDeseas otra carta?\n1)Si\n2)NO\nSelecciona una opcion:: ";
        cin >> opc;
    } while (opc != 2);

    if (Puntaje(JUGADOR) == -1) {
        cout << "\tPerdiste (1)";
        
        return 0;
    }
    do{
        carta = BARAJA.top();
        BARAJA.pop();
        CASA.push(carta);
        cout << "\nCarta de la casa:: " << carta.valor << " de " << carta.nombre;
    } while (Puntaje(JUGADOR) > Puntaje(CASA));
    if (Puntaje(CASA) == -1) {
        cout << "\tLa casa perdio";
        
        return (apuesta*2);
    }

    if (Puntaje(JUGADOR) == Puntaje(CASA)) {
        cout << "\tEmpate";
        
        return apuesta;
    }

    cout << "\tLa casa gano";
    
    return 0;
}




