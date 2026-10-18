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
int leerEntero() {
    string linea;
    getline(cin, linea);
    return convertirEntero(linea);
}
string leerTexto() {
    string texto;
    getline(cin, texto);
    return texto;

}

int contarRegistros(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        return -1;
    }

    string linea;
    int contador = 0;

    getline(archivo, linea); // saltar el encabezado

    while (getline(archivo, linea)) {
        if (linea.length() > 0) {
            contador++;
        }
    }

    archivo.close();
    return contador;
}

void liberarPokedex(Pokedex& pokedex) {
    if (pokedex.pokemons != nullptr) {
        delete[] pokedex.pokemons;
        pokedex.pokemons = nullptr;
    }
    pokedex.cantidad = 0;
}

bool cargarPokedex(Pokedex& pokedex, const string& nombreArchivo) {
    int cantidadEnArchivo = contarRegistros(nombreArchivo);
    if (cantidadEnArchivo <=0) {
        return false;
    }

    pokedex.pokemons = new Pokemon[cantidadEnArchivo];
    pokedex.cantidad = 0;

    ifstream archivo(nombreArchivo);
    if (!archivo.is_open ()) {
        liberarPokedex(pokedex);
        return false;
    }

    string linea;
    string campos[CAMPOS_POR_LINEA];

    getline(archivo, linea);

    while (getline(archivo, linea) && pokedex.cantidad < cantidadEnArchivo) {
        if (linea.length() > 0) {
            separarCampos(linea, campos, CAMPOS_POR_LINEA);

            Pokemon* p = &pokedex.pokemons[pokedex.cantidad];

            p->numero     = convertirEntero(campos[0]);
            p->nombre     = campos[1];
            p->tipo1      = campos[2];
            p->tipo2      = campos[3];
            p->hp         = convertirEntero(campos[4]);
            p->ataque     = convertirEntero(campos[5]);
            p->defensa    = convertirEntero(campos[6]);
            p->velocidad  = convertirEntero(campos[7]);
            p->altura     = convertirEntero(campos[8]);
            p->peso       = convertirEntero(campos[9]);

            pokedex.cantidad++;
        }
    }

    archivo.close();
    return true;

}

int main() {
    setlocale(LC_ALL, "spanish");

    Pokedex pokedex;
    pokedex.pokemons = nullptr;
    pokedex.cantidad = 0;

    if (!cargarPokedex(pokedex, NOMBRE_ARCHIVO)) {
        cout << "No es posible leer: \"" << NOMBRE_ARCHIVO << "\"." << endl;
        cout << "Verifica si el archivo esta en la misma carpeta desde donde ejecuta el programa." << endl;
        return 1;
    }

    cout << "Pokedex cargada: " << pokedex.cantidad << " Pokemon." << endl;

    liberarPokedex(pokedex);
    return 0;
}

void mostrarPokemon(const Pokemon* p) {
    if (p == nullptr) {
        cout << "EEEEEEHHGG, ESTA MAL: No es valido ese pokemon" << endl;
        return;
    }

    cout << "\n==============================" << endl;
    cout << " #" << p->numero << " - " << p->nombre << endl;
    cout << "==============================" << endl;

    cout << " Es tipo:        " << p->tipo1;
    if (p->tipo2.length() > 0) {
        cout << " / " << p->tipo2;
    }
    cout << endl;

    cout << " Es de generacion:  " << p->generacion << endl;

    cout << " Es un Pokemon legendario?:  ";
    if (p->legendario) {
        cout << "Siuuu" << endl;
    } else {
        cout << "Nada que ver papi" << endl;
    }

    cout << right; 
    cout << " //Sus Estadisticas son// " << endl;
    cout << " HP:          " << setw(4) << p->hp << endl;
    cout << " Ataque:      " << setw(4) << p->ataque << endl;
    cout << " Defensa:     " << setw(4) << p->defensa << endl;
    cout << " Ataque Especial: " << setw(4) << p->ataqueEsp << endl;
    cout << " Defensa Especial:" << setw(4) << p->defensaEsp << endl;
    cout << " Velocidad:   " << setw(4) << p->velocidad << endl;
    cout << " TOTAL:       " << setw(4) << p->total << endl;
}

void mostrarEncabezadoTabla() {
    cout << left
         << setw(6)  << "#"
         << setw(14) << "Nombre"
         << setw(10) << "Tipo 1"
         << setw(10) << "Tipo 2"
         << setw(6)  << "Total" << endl;
    cout << "----------------------------------------------" << endl;
}

void mostrarFilaPokemon(const Pokemon* p) {
    if (p == nullptr) {
        return;
    }
    cout << left
         << setw(6)  << p->numero
         << setw(14) << p->nombre
         << setw(10) << p->tipo1
         << setw(10) << p->tipo2
         << setw(6)  << p->total << endl;
}