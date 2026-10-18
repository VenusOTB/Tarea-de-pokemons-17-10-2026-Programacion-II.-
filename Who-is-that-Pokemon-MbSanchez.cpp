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