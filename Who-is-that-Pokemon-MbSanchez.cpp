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

string aMinusculas(const string& texto) {
    string resultado = texto;
    for (int i = 0; i < (int)resultado.length(); i++) {
        if (resultado[i] >= 'A' && resultado[i] <= 'Z') {
            resultado[i] = resultado[i] + ('a' - 'A');
        }
    }
    return resultado;
}

bool contieneTexto(const string& texto, const string& buscado) {
    int largoTexto = texto.length();
    int largoBuscado = buscado.length();

    if (largoBuscado == 0 || largoBuscado > largoTexto) {
        return false;
    }

    for (int inicio = 0; inicio <= largoTexto - largoBuscado; inicio++) {
        bool coincide = true;
        for (int j = 0; j < largoBuscado; j++) {
            if (texto[inicio + j] != buscado[j]) {
                coincide = false;
                break;
            }
        }
        if (coincide) {
            return true;
        }
    }
    return false;
}

void separarCampos(const string& linea, string campos[], int cantidadCampos){
    for (int i=0; i < cantidadCampos; i++) {
        campos [i] = "";
    }
    int indice = 0;
    for (int i=0; i < (int)linea.length(); i++) {
        char c = linea[i];
        if (c == ',') {
            indice++;
            if (indice >= cantidadCampos) {
                break;
            }
        } else {
            campos[indice] += c;
        }
    }
}
intleerEntero() {
    string linea;
    getline(cin, linea);
    return convertirEntero(linea);
}