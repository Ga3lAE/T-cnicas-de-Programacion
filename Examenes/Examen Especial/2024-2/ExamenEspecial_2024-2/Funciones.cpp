/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 24 de junio de 2025, 10:18 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Atencion.h"
#include "Comentario.h"
#include "Funciones.h"
#include "Plato.h"
#include "Palabra.h"
#include "NodoPalabra.h"
#include "NodoPlato.h"
#include "NodoAtencion.h"

#define MAX_TAM_LIN 150
#define MAX_TAM_POL 6 
#define MAX_TAM_PAL 15
#define MAX_TAM_COD 10
#define MAX_TAM_CANT 13
#define MAX_TAM_DESC 35
#define MAX_TAM_DIN 12

//LECTURA
char *leeCadenaExacta(ifstream &archivo, char del){
    char aux[100], *cad;
    archivo.getline(aux, 100, del);
    
    if(archivo.eof()) return NULL;
    
    cad = new char [strlen(aux)+1]{};
    strcpy(cad, aux);
    return cad;
}
char *copiaCadena(const char *cadena){
    char *nueva;
    nueva = new char [strlen(cadena)+1]{};
    strcpy(nueva, cadena);
    return nueva;
}
void leeLexicon(const char *nombreArchivo, struct NodoPalabra *&lista){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    struct Palabra palabra;
    while(true){
        //excelente,3
        palabra.texto = leeCadenaExacta(archivo, ',');
        if(archivo.eof()) break;
        archivo>>palabra.polaridad;
        archivo.get(); // salto de linea
        
        insertaPalabra(palabra, lista);
    }
}
void leePlatos(const char *nombreArchivo, struct NodoPlato *&lista){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    struct Plato plato;
    while(true){
        //25FQ4T,Sanguchon de Chicharron,39.4
        plato.codigo = leeCadenaExacta(archivo, ',');
        if(archivo.eof()) break;
        plato.nombre = leeCadenaExacta(archivo, ',');
        archivo>>plato.precio;
        archivo.get(); // salto de linea
        
        plato.cantidad = 0;
        
        insertaOrdenadoPlato(plato, lista);
    }
}
void leeAtenciones(const char *nombreArchivo, struct NodoAtencion *&lista, 
        struct NodoPlato *listaPlatos){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    struct Atencion atencion;
    int hh, mm, cantidadPedida;
    char descC, codigoPlato[7]{};
    while(true){
        //190980 16:07 LNW85C 7 AJTYPT 7 0P69H5 4 DMGVVD 4 S92K8X 10
        archivo>>atencion.codigo;
        if(archivo.eof()) break;
        archivo>>hh>>descC>>mm;
        atencion.hora = hh*3600+mm*60;
        atencion.cantidadPlatos = 0;
        atencion.cantidadComentarios = 0;
        atencion.totalVenta = 0;
        
        while(true){
            if(archivo.get() == '\n')  break;
            archivo>>codigoPlato>>cantidadPedida;
            struct NodoPlato *plato = buscaPlato(listaPlatos, codigoPlato);                        
            if(plato != NULL)
                completaPlato(atencion.platosAtendidos[atencion.cantidadPlatos], 
                        atencion.cantidadPlatos, 
                        plato, 
                        atencion.totalVenta, cantidadPedida);                        
        }
        insertaAtencion(atencion, lista);
                                        
    }
}
void leeComentarios(const char *nombreArchivo, struct NodoAtencion *lista, 
        struct NodoPalabra *listaLexicon){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }

    struct Comentario comentario;
    int codigoPedido;
    while(true){
        //723044,"Fue aceptable, aunque no fue lo que esperaba."
        archivo>>codigoPedido;
        if(archivo.eof()) break;
        archivo.get();
        comentario.texto = leeCadenaExacta(archivo, '\n');
        
        struct NodoAtencion *atencion = buscaAtencion(lista, codigoPedido);
        if(atencion != NULL){
            procesaComentario(comentario, listaLexicon);
            atencion->atencion.comentarios[atencion->atencion.cantidadComentarios] = comentario;
            atencion->atencion.cantidadComentarios++;
        }
                
                                        
    }
}

//PROCESAMIENTO
void completaPlato(struct Plato &platoNuevo,
        int &cantidadPlatos,
        struct NodoPlato *plato, 
        double &total, int cantidad){
    platoNuevo.codigo = copiaCadena(plato->plato.codigo);
    platoNuevo.nombre = copiaCadena(plato->plato.nombre);
    platoNuevo.precio = plato->plato.precio;
    platoNuevo.cantidad = cantidad;
    total+=platoNuevo.precio*cantidad;
    
    cantidadPlatos++;
}
void procesaComentario(struct Comentario &comentario, struct NodoPalabra *lista){
    comentario.preProcesado = preprocesaTexto(comentario.texto);
    comentario.cantidadPalabras = cuentaPalabras(comentario.preProcesado);    
    completaArregloPalabras(comentario.preProcesado, comentario.palabras);      
    comentario.polaridadTotal = sumaPolaridad(comentario.palabras, comentario.cantidadPalabras, lista);
    
}
char *preprocesaTexto(const char *texto){
    char aux[strlen(texto)+1]{}, *cad;    
    int k = 0;
    
    for (int i = 0; texto[i]; i++) {        
        if(texto[i]<='z' and texto[i]>='A' or texto[i] == ' '){ // es una letra
            if(texto[i]<='Z' and texto[i]>='A') 
                aux[k] = texto[i]- ('A'- 'a');
            else
                aux[k] = texto[i];                
            k++;
        }
    }
    aux[k] = 0;
    
    cad = new char [strlen(aux)+1]{};
    strcpy(cad, aux);
    return cad;

}
int cuentaPalabras(const char *texto){
    int cantidad =  0;
    for (int i = 0; texto[i]; i++) {        
        if(texto[i] == ' ') cantidad++;
    }
    cantidad++;//siempre la ultima palabra
    return cantidad;
}
void completaArregloPalabras(const char *texto, struct Palabra *palabras){    
    int posPalabra=0, k = 0;  
    char aux[50]{};
    for (int i = 0; texto[i]; i++) {        
        if(texto[i] == ' '){
            aux[k] = 0;            
            palabras[posPalabra].texto = copiaCadena(aux);
            
            posPalabra++;
            k = 0; // reinicio
        } 
        else{            
            aux[k] = texto[i];
            k++;
        }                        
    }
    //para la ultima palabra
    aux[k] = 0;    
    palabras[posPalabra].texto = copiaCadena(aux);    
}
int sumaPolaridad(struct Palabra *palabras, int cantidad, struct NodoPalabra *lista){
    int suma = 0;
    struct NodoPalabra *palabra;
    for (int i = 0; i < cantidad; i++) {
        palabra = buscaPalabra(lista, palabras[i].texto);
        if(palabra){
            suma+=palabra->palabra.polaridad;
            palabras[i].polaridad = palabra->palabra.polaridad;
        }
        else
            palabras[i].polaridad = 0;
            
        
    }
    return suma;
}

//INSERCION
void insertaPalabra(struct Palabra palabra, struct NodoPalabra *&lista){
    struct NodoPalabra *nuevo;
    nuevo = new struct NodoPalabra;
    nuevo->palabra = palabra;
    nuevo->siguiente = lista;
    lista = nuevo;
}
void insertaOrdenadoPlato(struct Plato plato, struct NodoPlato *&lista){
    struct NodoPlato *nuevo, *ptr, *anterior;
    ptr = lista;
    anterior = NULL;
    nuevo = new struct NodoPlato;
    nuevo->plato = plato;
    
    while(ptr){
        if(strcmp(ptr->plato.codigo, nuevo->plato.codigo)>0) break;
        anterior = ptr;
        ptr = ptr->siguiente;
    }
    nuevo->siguiente = ptr;
    if(anterior == NULL) lista = nuevo;
    else anterior->siguiente = nuevo;
}
void insertaAtencion(struct Atencion atencion, struct NodoAtencion *&lista){
    struct NodoAtencion *nuevo;
    nuevo = new struct NodoAtencion;
    nuevo->atencion = atencion;
    nuevo->siguiente = lista;
    lista = nuevo;
}

//BUSQUEDA
struct NodoPlato *buscaPlato(struct NodoPlato *lista, const char *codigo){
    struct NodoPlato *ptr = lista;
    
    while(ptr){
        if(strcmp(ptr->plato.codigo, codigo) == 0) return ptr;
        ptr=ptr->siguiente;
    }
    return NULL;
}
struct NodoAtencion *buscaAtencion(struct NodoAtencion *lista, int codigo){
    struct NodoAtencion *ptr = lista;
    
    while(ptr){
        if(ptr->atencion.codigo == codigo) return ptr;
        ptr=ptr->siguiente;
    }
    return NULL;
}
struct NodoPalabra *buscaPalabra(struct NodoPalabra *lista, const char *pal){
    struct NodoPalabra *ptr = lista;
    
    while(ptr){
        if(strcmp(ptr->palabra.texto, pal) ==0) return ptr;
        ptr=ptr->siguiente;
    }
    return NULL;
}

//ORDENAMIENTO
void ordenaAtenciones(struct NodoAtencion *lista){
    struct NodoAtencion *i = lista;    
    while(i){
        struct NodoAtencion *k = i->siguiente;
        while(k){
            if(i->atencion.codigo > k->atencion.codigo)
                cambiaAtencion(i->atencion, k->atencion);
            k = k->siguiente;
        }
        i = i->siguiente;        
    }
}
void cambiaAtencion(struct Atencion &d1, struct Atencion &d2){
    struct Atencion aux;
    aux = d1;
    d1 = d2;
    d2 = aux;
}

//IMPRESION
void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_TAM_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}
void verificaLexicon(const char *nombreArchivo, struct NodoPalabra *lista){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    archivo<<fixed<<setprecision(2);
    
    archivo<<setw(MAX_TAM_LIN/2)<<"VERIFICAC LEXICON"<<endl;
    imprimeLinea(archivo, '=');
    archivo<<left
            <<setw(MAX_TAM_PAL)<<"PALABRA"
            <<setw(MAX_TAM_POL)<<"POLARIDAD"
            <<endl;
    imprimeLinea(archivo, '=');
    
    struct NodoPalabra *ptr = lista;
    while(ptr){
        archivo<<left
                <<setw(MAX_TAM_PAL)<<ptr->palabra.texto
                <<right<<setw(MAX_TAM_POL)<<ptr->palabra.polaridad
                <<endl;
        ptr = ptr->siguiente;        
    }
}
void verificaPlatos(const char *nombreArchivo, struct NodoPlato *lista){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    archivo<<fixed<<setprecision(2);
    
    archivo<<setw(MAX_TAM_LIN/2)<<"VERIFICAC PLATOS"<<endl;
    imprimeLinea(archivo, '=');
    archivo<<left
            <<setw(MAX_TAM_COD)<<"CODIGO"
            <<setw(MAX_TAM_DESC)<<"DESCRIPCION"
            <<setw(MAX_TAM_DIN)<<"PRECIO"
            <<endl;
    imprimeLinea(archivo, '=');
    
    struct NodoPlato *ptr = lista;
    while(ptr){
        archivo<<left
                <<setw(MAX_TAM_COD)<<ptr->plato.codigo
                <<setw(MAX_TAM_DESC)<<ptr->plato.nombre
                <<right<<setw(MAX_TAM_DIN/2)<<ptr->plato.precio<<left<<setw(MAX_TAM_DIN/2)<<' '
                <<endl;
        ptr = ptr->siguiente;        
    }
}
void emiteReporte(const char *nombreArchivo, struct NodoAtencion *lista){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    archivo<<fixed<<setprecision(2);
    
    struct NodoAtencion *ptr = lista;
    
    while(ptr){
        struct Atencion atencion = ptr->atencion;
        archivo<<left
                <<setw(MAX_TAM_COD)<<atencion.codigo
                <<setfill('0')<<right
                <<setw(2)<<atencion.hora/3600<<':'
                <<setw(2)<<(atencion.hora%3600)/60
                <<setfill(' ')<<left
                <<endl;
        imprimeLinea(archivo, '-');
        
        for (int i = 0; i < atencion.cantidadPlatos; i++) {
            archivo<<left
                    <<setw(MAX_TAM_COD)<<atencion.platosAtendidos[i].codigo
                    <<setw(MAX_TAM_DESC)<<atencion.platosAtendidos[i].nombre
                    <<setw(MAX_TAM_DIN)<<atencion.platosAtendidos[i].precio
                    <<setw(MAX_TAM_CANT)<<atencion.platosAtendidos[i].cantidad
                    <<setw(MAX_TAM_DIN)<<atencion.platosAtendidos[i].precio*atencion.platosAtendidos[i].cantidad                    
                    <<endl;            
        }
        archivo<<"TOTAL: "<<atencion.totalVenta<<endl;
        imprimeLinea(archivo, '-');
        int polaridadTotal=0;
        for (int i = 0; i < atencion.cantidadComentarios; i++) {
            archivo<<left
                    <<setw(MAX_TAM_COD)<<atencion.comentarios[i].texto
                    <<endl;
            polaridadTotal+=atencion.comentarios[i].polaridadTotal;
        }
        archivo<<"TOTAL: "<<polaridadTotal<<endl;
        imprimeLinea(archivo, '=');


        
        ptr = ptr->siguiente;
    }
}