/* Laboratorio Programacion IV - INCO/FING/UDELAR
 * Laboratorio 0 - Implementacion de main
 * Autores (por nombre):
 * 	Alexis Baladon
 * 	Guillermo Toyos
 * 	Jorge Machado
 * 	Juan Jose Mangado
 * 	Mathias Ramilo
 */

#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>
#include "include/sistema.h"

using namespace std;

int main() {
    Sistema sys;
    
    int controlVar=0;
    while (controlVar != 7) {

        cout << "--- MENU --- \n\n";
        cout << "Seleccione una opcion\n";
        cout << " 1. Agregar Jugador\n";
        cout << " 2. Agregar Videojuego\n";
        cout << " 3. Obtener Jugadores\n";
        cout << " 4. Obtener Videojuegos\n";
        cout << " 5. Obtener Partidas\n";
        cout << " 6. Iniciar Partida\n";
        cout << " 7. Salir\n\n";
        cout << "Ingrese una opcion: ";
        cin >> controlVar;
        cout << endl;

        switch (controlVar) {
	    //Agregar Jugador
            case 1:{ 
                string nickname;
                int edad;
                string password;

                cout << "Nickname: ";
                cin >> nickname;
                cout << "Edad: ";
                cin >> edad;
                cout << "Password: ";
                cin >> password;

                try {
                    sys.agregarJugador(nickname, edad, password);
                    cout << "Se ha registrado a " << nickname << " en el sistema.\n";
                }
                catch (invalid_argument &e) {
                    cout << e.what() << endl;
                    break;
                }
                break;
	    }
            case 2:{ //Agregar Videojuego
                string nombre;
		string input_genero;
                TipoJuego genero;

                cout << "Nombre del videojuego: ";
                cin >> nombre;
                cout << "Genero (Accion/Aventura/Deporte/Otro): ";
                cin >> input_genero;
		if(input_genero == "Accion")
		    genero = TipoJuego::Accion;
		else if(input_genero == "Aventura")
		    genero = TipoJuego::Aventura;
		else if(input_genero == "Deporte")
		    genero = TipoJuego::Deporte;
		else if(input_genero == "Otro")
		    genero = TipoJuego::Otro;
                try {
                    sys.agregarVideojuego(nombre, genero);
                    cout << "Se ha registrado el videojuego " << nombre << " en el sistema.\n";
                }
                catch (invalid_argument &e) {
                    cout << e.what() << endl;
                    break;
                }
		break;
	    }
            case 3:{ //Obtener Jugadores
                int cantJugadores;
                DtJugador** arrayJugadores = sys.obtenerJugadores(cantJugadores);

                cout << "Hay " << cantJugadores << " jugadores registrados en el sistema.\n\n";
                for (int i = 0; i < cantJugadores; i++) {
                    cout << i+1 << ". Nickname: " << arrayJugadores[i]->getNickname() << endl;
                    cout << "   Edad: " << arrayJugadores[i]->getEdad() << endl;
                    cout << endl;
                } 
                delete[] arrayJugadores;
		break;
	    }
            case 4:{ //Obtener Videojuegos
                int cantVideojuegos;
                DtVideojuego** arrayVideojuegos = sys.obtenerVideojuegos(cantVideojuegos);
			
                cout << "Hay " << cantVideojuegos << " videojuegos registrados en el sistema.\n";
                cout << endl;
		TipoJuego gen;
		string gen_str;
                for (int i = 0; i < cantVideojuegos; i++) {
		    gen = arrayVideojuegos[i]->getGenero();
		    if(gen = TipoJuego::Accion)
			gen_str = "Accion";	
		    else if(gen = TipoJuego::Aventura)
			gen_str = "Aventura";
		    else if(gen = TipoJuego::Deporte)
			gen_str = "Deporte";
		    else if(gen = TipoJuego::Otro)
			gen_str = "Otro";
                    cout << i+1 << ". Titulo: " << arrayVideojuegos[i]->getNombre() << endl;
                    cout << "   Genero: " << gen_str << endl;
                    cout << "   Total horas de juego: " << arrayVideojuegos[i]->getTotalHorasDeJuego() << endl;
                    cout << endl;
                }
                delete[] arrayVideojuegos;
		break;
	    }
            case 5:{ //Obtener Partidas
                string videojuego;
                int cantPartidas;

                cout << "Videojuego del cual desea obtener sus partidas: ";
                cin >> videojuego;

                try {
                    DtPartida** arrayPartidas = sys.obtenerPartidas(videojuego, cantPartidas);
                    cout << "Hay " << cantPartidas << " partidas registradas en el sistema.\n";
                    DtPartidaIndividual* ptrIndividual;
                    DtPartidaMultijugador* ptrMulti;
                    for (int i = 0; i < cantPartidas; i++) {
                        ptrIndividual = dynamic_cast<DtPartidaIndividual*>(arrayPartidas[i]);
                        if (ptrIndividual == nullptr) { //Multijugador
                            ptrMulti = dynamic_cast<DtPartidaMultijugador*>(arrayPartidas[i]);
                            cout << i+1 << ". Fecha: " << ptrMulti->getFecha() << endl;
                            cout << "   Duracion: " << ptrMulti->getDuracion() << endl;
                            string tev = "NO";
                            if (ptrMulti->getTransmitidaEnVivo()) {
                                tev = "SI";
                            }
                            cout << "   Trasmtida en vivo: " << tev << endl;
                            cout << "   Jugadores unidos: " << ptrMulti->getCantidadJugadoresUnidos() << endl << endl;
                            for (int j = 0; j < ptrMulti->getCantidadJugadoresUnidos(); j++) {
                                cout << "    " << j+1 << ". " << ptrMulti->getNicknameJugadoresUnidos[j] << endl;
                            }
                        } else { //Individual
                            cout << i+1 << ". Fecha: " << ptrIndividual->getFecha() << endl;
                            cout << "   Duracion: " << ptrIndividual->getDuracion() << endl;
                            string cpa = "NO";
                            if (ptrIndividual->getContinuarPartidaAnterior()) {
                                cpa = "SI";
                            }
                            cout << "   Es continuacion de una partida anterior: " << cpa << endl;
                        }
                    }
                    delete[] arrayPartidas;
                }
                catch (invalid_argument &e) {
                    cout << e.what() << endl;
                    break;
                }
		break;
	    }
            case 6:{ //Iniciar Partida
                string nickname;
                string videojuego;
                DtPartida* datos;
                float duracion;
                int tipoPartida;
                DtPartidaIndividual* ptrIndividual;
                DtPartidaMultijugador* ptrMulti;

                cout << "Nickname: ";
                cin >> nickname;
                cout << "Videojuego: ";
                cin >> videojuego;
                
                time_t now = time(0);
                tm * time = localtime(&now);
                DtFechaHora fechaSistema(time->tm_year, time->tm_mon, time->tm_mday, time->tm_hour, time->tm_min);

                cout << "Duracion: ";
                cin >> duracion; 
                cout << endl;

                cout << "Tipo de partida:" << endl;
                cout << " 1.Individual" << endl;
                cout << " 2.Multijugador" << endl << endl;
                cout << "Seleccione una opcion: ";
                cin >> tipoPartida;
                cout << endl;

                switch(tipoPartida) {
                    case 1: //Individual
                        bool cpa;
                        cout << "Es continuacion de una partida anterior (1.Si/0.No): ";
                        cin >> cpa;
                        ptrIndividual->setFechaHora(fechaSistema);
                        ptrIndividual->setDuracion(duracion);
                        ptrIndividual->setContinuarPartidaAnterior(cpa);
                        try {
                            sys.iniciarPartida(nickname, videojuego, ptrIndividual);
                        }
                        catch (invalid_argument &e) {
                            cout << e.what() << endl;
                            break;
                         }
			break;

                    case 2: //Multijugador
                        bool tev;
                        cout << "Es transmitida en vivo (1.Si/0.No): ";
                        cin >> tev;
                        int cantJugadoresUnidos;
                        cout << "Cantidad de jugadores unidos: ";
                        cin >> cantJugadoresUnidos;
                        string *nicknameJugadoresUnidos;
                        nicknameJugadoresUnidos = new string[cantJugadoresUnidos];
                        cout << "Ingrese el nickname de los jugadores unidos" << endl;
                        for (int i = 0; i < cantJugadoresUnidos; i++) {
                            cout << "Jugador " << i+1 << ":";
                            cin >> nicknameJugadoresUnidos[i];
                        }
                        ptrMulti->setFechaHora(fechaSistema);
                        ptrMulti->setDuracion(duracion);
                        ptrMulti->setTransmitidaEnVivo(tev);
                        ptrMulti->setNicknameJugadoresUnidos(nicknameJugadoresUnidos);
                        ptrMulti->setCantidadJugadoresUnidos(cantJugadoresUnidos);
                        try {
                            sys.iniciarPartida(nickname, videojuego, ptrMulti);
                        }
                        catch (invalid_argument &e) {
                            cout << e.what() << endl;
                            break;
                        }
			break;

                    default:
                        cout << "La opcion ingresada no es valida, ingrese otra porfavor." << endl;
               	    	break;

		}
            case 7: //Salir
		break;
            default:
                cout << "La opcion ingresada no es valida, ingrese otra porfavor.\n";
		break;
	}
        
	}
    }
    return 0;
}

