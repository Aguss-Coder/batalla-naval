#include <iostream>

using namespace std;

class Game {
    protected:
        string partidaGuardada;
    private:
        void cargarPartida();
        void guardarPartida();
        void nuevaPartida();
        void elegirJugador();  
};