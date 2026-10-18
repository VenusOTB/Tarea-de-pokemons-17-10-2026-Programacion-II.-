#include <iostream>
#include <fstream>   
#include <string>    
#include <iomanip>   
#include <locale>    
using namespace std;

const string NOMBRE_ARCHIVO = "pokemon_150_registros.csv";
const int CAMPOS_POR_LINEA = 13;  
const int MAX_TIPOS = 30;          
const int TOP = 3; 

struct Pokemon {
    int numero;
    string nombre;
    string tipo1;
    string tipo2;      
    int total;
    int hp;
    int ataque;
    int defensa;
    int ataqueEsp;
    int defensaEsp;
    int velocidad;
    int generacion;
    bool legendario;
};

struct Pokedex {
    Pokemon* pokemons;
    int cantidad;
}; 

int main () {
    return 0;
}

int convertirEntero(const string& texto) {
    if (texto.length() == 0) {
        return -1;
    }

    int resultado = 0;
    for (int i = 0; i < (int)texto.length(); i++) {
        char c = texto[i];
        if (c < '0' || c > '9') {
            return -1;
        }
        resultado = resultado * 10 + (c - '0');
    }
    return resultado;
}