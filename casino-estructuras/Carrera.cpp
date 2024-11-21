#include "Carrera.h"

const char* nombres[] = {
    "Rlmpgo", "Trmnt", "Trno", "Vnto", "Ágla", "Dstllo", "Rayo", "Cntlla",
    "Cmta", "Fnx", "Trndo", "Eclps", "R", "K", "Mterto", "Jgur",
    "Leo", "Smbra", "Lnce", "X" };

Carrera::Carrera(int Caballos)
{
    cabecera = final = NULL;
    tope = Caballos;
    caballos = 0;
    ganancia = 0;
    perdida = 0;

    AñadirCarril();

    for (int z = 0; z < Caballos; z++)
    {
        AñadirCarril();
    }

    cout << "\n--------------Se añadieron los caballos correctamente--------------" << endl;

}

float Carrera::MostrarCarrera()
{
    bool ganador1 = false, ganador2 = false, ganador3 = false;
    string nombreGanador;
    float resultado;

    system("cls");
    nodo = cabecera;
    cout << "INICIO" << endl;
    srand(time(0));

    while (!ganador3)
    {
        nodo = cabecera;

        while (nodo != NULL)
        {
            nombreGanador = nodo->info.GetNombreCaballo();

            nodo->info.MostrarCarril();
            this_thread::sleep_for(chrono::microseconds(1));

            int pasos = rand() % (nodo->info.GetVelocidad() - 5 + 1) + 5;

            for (int j = 0; j < pasos; j++)
            {
                BorrarUltimaLinea();
                nodo->info.RecorrerPasto(1);
                nodo->info.MostrarCarril();
                this_thread::sleep_for(chrono::microseconds(1));

                if (nodo->info.ganador(nombreGanador))
                {
                    if (!ganador1)
                    {
                        ganador1 = true;
                        numCaballosGanadores[0] = nodo->info.getNumero();
                        multCaballosGanadores[0] = nodo->info.GetMultiplicador(); // Lo guarda bien 

                    }
                    else if (!ganador2 && nodo->info.getNumero() != numCaballosGanadores[0])
                    {
                        ganador2 = true;              //cout << "Nodo multiplicador -> " << multCaballosGanadores[0] << endl;

                        numCaballosGanadores[1] = nodo->info.getNumero(); // Sigue multCaballosGanadores[0] estando integro

                        multCaballosGanadores[1] = nodo->info.GetMultiplicador();
                    }
                    else if (!ganador3 && nodo->info.getNumero() != numCaballosGanadores[0] && nodo->info.getNumero() != numCaballosGanadores[1])
                    {
                        ganador3 = true;
                        numCaballosGanadores[2] = nodo->info.getNumero();// Sigue multCaballosGanadores[0] estando integro
                        multCaballosGanadores[2] = nodo->info.GetMultiplicador();
                    }
                    break;
                }
            }

            if (ganador1 && ganador2 && ganador3)
            {
                // el multCaballosGanadores[0] deja de estar integro y cambia de valor

                MoverCursorAbajo((tope - nodo->info.getNumero()) + 2);

                cout << "¡El caballo ganador 1 es: " << numCaballosGanadores[0] << " (" << numCaballosGanadores[0] << ") !!!" << endl << endl;
                cout << "¡El caballo ganador 2 es: " << numCaballosGanadores[1] << " (" << numCaballosGanadores[1] << ") !!!" << endl << endl;
                cout << "¡El caballo ganador 3 es: " << numCaballosGanadores[2] << " (" << numCaballosGanadores[2] << ") !!!" << endl;

                break;
            }

            nodo = nodo->sig;
        }
        if (!ganador3)
        {
            MoverCursorArriba(tope + 1);
        }
    }

    MoverCursorAbajo((tope - nodo->info.getNumero()) + 2);

    MostrarCaballos();

    RecorrerApuestas();

    cout << "GANANCIA -> $" << ganancia << " PERDIDA -> $" << perdida << "." << endl;
    if (ganancia > perdida)
    {
        cout << "\n\tTOTAL -> $" << ganancia - perdida << "." << endl;
    }
    else
    {
        cout << "\n\tTOTAL -> $" << 0 << "." << endl;

    }

    resultado = ganancia;

    cout << endl;

    return resultado;
}

void Carrera::BorrarUltimaLinea()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);

    // Mover el cursor una línea hacia arriba
    csbi.dwCursorPosition.Y -= 1;
    SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);

    // Borrar la línea (sobrescribir con espacios)
    std::cout << "\r";  // Mueve el cursor al inicio de la línea
    std::cout << std::string(csbi.dwSize.X, ' ');  // Llena la línea con espacios

    // Vuelve a colocar el cursor al inicio de la línea
    SetConsoleCursorPosition(hConsole, csbi.dwCursorPosition);
}

void Carrera::MoverCursorArriba(int lineas)
{
    for (int i = 0; i < lineas; ++i)
    {
        cout << "\033[F";
    }

}

void Carrera::MoverCursorAbajo(int lineas)
{
    cout << "\033[" << lineas << "B";  // Mueve el cursor hacia abajo
}

void Carrera::Apuestas(int numApuestas)
{
    apuestas = new Apuesta * [numApuestas];
    totalApuestas = numApuestas;

    for (int i = 0; i < totalApuestas; i++)
    {
        apuestas[i] = new Apuesta;
    }
}

void Carrera::AgregarApuesta(float cantidadAp, int elegidoAp, int numApuesta, int caso)
{
    apuestas[numApuesta]->monto = cantidadAp;
    apuestas[numApuesta]->elegido = elegidoAp;
    apuestas[numApuesta]->caso = caso;
}

void Carrera::RecorrerApuestas()
{
    for (int y = 0; y < totalApuestas; y++)
    {
        float ganado;

        cout << "\n--------------------------------" << endl;

        cout << "\n\tTú caballo fue: " << apuestas[y]->elegido << "." << endl;

        ganado = CalcularApuesta(apuestas[y]->monto, apuestas[y]->elegido, apuestas[y]->caso);

        if (ganado == 0)
        {
            cout << "\n\tTú caballo no ganó, perdiste " << apuestas[y]->monto << endl;
            perdida += apuestas[y]->monto;
        }
        else
        {
            ganancia += ganado - apuestas[y]->monto;
            total += ganancia + apuestas[y]->monto;
            cout << "\n\tGANASTE! MONTO-> $" << ganancia << "\n\n\SALDO FINAL -> $" << total<< "." << endl;
        }
        cout << "\n\n--------------------------------" << endl;
    }
}

float Carrera::PotenciadorCarril(int carril)
{
    float max;
    if (carril <= 5)
    {
        max = 1.25;
    }
    else if (carril <= 10)
    {
        max = 1.5;
    }
    else
    {
        max = 1.75;
    }

    float potenciador = 1.0f + ((float)(carril - 1) / ((tope + 1) - 1)) * (max - 1.0f);
    return potenciador;
}

void Carrera::AñadirCarril()
{
    caballos++;
    string nombre = CrearNombre();
    int velocidad = CrearVelocidad(tope + 1);
    float multiplicador = CrearMultiplicador(velocidad, tope + 1, caballos);

    nuevoCarril = new Ruta(nombre, velocidad, multiplicador, caballos);

    nodo = new Carril();

    nodo->info = *nuevoCarril;

    nodo->sig = NULL;

    if (cabecera == NULL)
    {
        cabecera = nodo;
        final = nodo;
    }
    else
    {
        final->sig = nodo;
        final = nodo;
    }
}

string Carrera::CrearNombre()
{
    string nombre;

    srand(time(0));

    bool nombreUnico = false;

    while (!nombreUnico)
    {
        int indice = rand() % 20;
        nombre = nombres[indice];

        if (!nombresUsados[indice])
        {
            nombresUsados[indice] = true;
            nombreUnico = true;
        }
    }
    return nombre;
}

int Carrera::CrearVelocidad(int numCaballos)
{
    int rango = 0;
    switch (numCaballos)
    {
    case 5:
    {
        rango = 3;
        break;

    }
    case 10:
    {
        rango = 4;
        break;

    }
    case 20:
    {
        rango = 6;
        break;
    }
    }

    return rand() % rango + 5;
}

float Carrera::CrearMultiplicador(int velocidad, int caso, int carril)
{
    int max;
    switch (caso)
    {
    case 5:
    {
        max = 1.25;
        break;

    }
    case 10:
    {
        max = 2;
        break;

    }
    case 20:
    {
        max = 3;
        break;
    }
    }

    float multiplicador = max - ((float)(velocidad - 1) / 9) * (max - 1.2);

    multiplicador = multiplicador * PotenciadorCarril(carril);

    multiplicador = (int)(multiplicador * 100 + 0.5) / 100.0;

    return multiplicador;
}

void Carrera::MostrarCaballos()
{
    int caballo = 0;
    nodo = cabecera;

    while (nodo != NULL)
    {
        caballo++;
        cout << "\t" << caballo << ".-NOMBRE : " << nodo->info.GetNombreCaballo() << " ---- VELOCIDAD: " << nodo->info.GetVelocidad() << " ---- MULTIPLICADOR: " << nodo->info.GetMultiplicador() << "x.";

        cout << endl << endl;

        nodo = nodo->sig;
    }
    cout << endl << endl;
}

float Carrera::CalcularApuesta(float monto, int apostado, int caso)
{
    float resultado = 0;
    float multiplicador = 0;
    float totalMultiplicador = 0;
    switch (caso)
    {
    case 1: // GANO PRIMER LUGAR -WIN-
        if (apostado == numCaballosGanadores[0])
        {

            multiplicador = (multCaballosGanadores[0] * 1.3f);
            resultado = monto * multiplicador; // Multiplicador de 2x

            cout << "\n\tTÚ APUESTA -> $" << monto << endl;

            cout << "\n\tMULTIPLICADOR DE CABALLO -> " << multCaballosGanadores[0] << "x." << endl;

            cout << "\n\tMULTIPLICADOR DE -WIN- -> 1.3x." << endl;

            cout << "\n\tMULTIPLICADOR TOTAL -> " << multiplicador << "x." << endl;

            cout << "RESULTADO? -> " << resultado << endl;

        }
        break;

    case 2: // GANO PRIMER O SEGUNDO LUGAR -PLACE-
        if (apostado == numCaballosGanadores[0] || apostado == numCaballosGanadores[1])
        {

            int indice = (apostado == numCaballosGanadores[0]) ? 0 : 1;

            multiplicador = (multCaballosGanadores[indice] * 1.2f);

            resultado = monto * multiplicador; // Multiplicador de 1.5x

            cout << "\n\tTÚ APUESTA -> $" << monto << endl;


            cout << "\n\tMULTIPLICADOR DE CABALLO -> " << multCaballosGanadores[indice] << "x." << endl;

            cout << "\n\tMULTIPLICADOR DE -PLACE- -> 1.2x." << endl;

            cout << "\n\tMULTIPLICADOR TOTAL -> " << multiplicador << "x." << endl;

        }
        break;

    case 3: // GANO PRIMER, SEGUNDO O TERCER LUGAR -SHOW-
        if (apostado == numCaballosGanadores[0] || apostado == numCaballosGanadores[1] || apostado == numCaballosGanadores[2])
        {

            int indice = (apostado == numCaballosGanadores[0]) ? 0 : (apostado == numCaballosGanadores[1]) ? 1 : 2;

            multiplicador = (indice == 2) ? 1.1f : 1.2f; // 1.5x para primeros dos y 1.25x para tercero

            totalMultiplicador = (multCaballosGanadores[indice] * multiplicador);

            resultado = monto * totalMultiplicador;

            cout << "\n\tTÚ APUESTA -> $" << monto << endl;

            cout << "\n\tMULTIPLICADOR DE CABALLO -> " << multCaballosGanadores[indice] << "x." << endl;

            cout << "\n\tMULTIPLICADOR DE -SHOW- -> 1.1x." << endl;

            cout << "\n\tMULTIPLICADOR TOTAL -> " << totalMultiplicador << "x." << endl;
        }
        break;
    }


    return resultado;
}
