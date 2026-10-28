/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 25 de mayo de 2025, 09:46 PM
 */

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>

using namespace std;

#include "Funciones.h"

#include "Atencion.h"
#include "Comentario.h"
#include "Palabra.h"
#include "Plato.h"

#define NO_ENCONTRADO -1

#define MAX_CAR_LIN 150
#define MAX_CAR_POL 10
#define MAX_CAR_DIN 16
#define MAX_CAR_COD 16
#define MAX_CAR_HORA 18

void imprimeLinea(ofstream &archiv, char c){
    for (int i = 0; i < MAX_CAR_LIN; i++) {        
        archiv<<c;
    }
    archiv<<endl;
}
//MANEJO DE ARCHIVOS
void datosArchivoIf(int tamEl, ifstream &archivo, int &cantidad){
    archivo.seekg(0, ios::end);
    int tamArch = archivo.tellg();
    archivo.seekg(0, ios::beg);
    cantidad = tamArch/tamEl;
}
void datosArchivoF(int tamEl, fstream &archivo, int &cantidad){
    archivo.seekg(0, ios::end);
    int tamArch = archivo.tellg();
    archivo.seekg(0, ios::beg);
    cantidad = tamArch/tamEl;
}
void leeLexicon(const char *nombreArchivoCsv, const char *nombreArchivoBin){
    ifstream archivoCsv(nombreArchivoCsv, ios::in);
    if(not archivoCsv.is_open()){
        cout<<"ERROR: No se pudo abri "<<nombreArchivoCsv;
        exit(1);
    }
    ofstream archivoBin(nombreArchivoBin, ios::out|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se pudo abri "<<nombreArchivoBin;
        exit(1);
    }
    
    struct Palabra palabra;
    while(true){
        //rapido,1
        archivoCsv.getline(palabra.texto, MAX_TAM_PALABRA_TEXTO, ',');
        if(archivoCsv.eof()) break;
        archivoCsv>>palabra.polaridad;
        archivoCsv.get();
        
        archivoBin.write(reinterpret_cast<const char*>(&palabra), 
                sizeof(struct Palabra));                
    }
}
void verificaLexicon(const char *nombreArchivoTxt, const char *nombreArchivoBin){
    ifstream archivoBin(nombreArchivoBin, ios::in|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se pudo abri "<<nombreArchivoBin;
        exit(1);
    }
    ofstream archivoTxt(nombreArchivoTxt, ios::out);
    if(not archivoTxt.is_open()){
        cout<<"ERROR: No se pudo abri "<<nombreArchivoTxt;
        exit(1);
    }
    archivoTxt<<setw(MAX_CAR_LIN/2)<<"REPORTE LEXICON"<<endl;
    imprimeLinea(archivoTxt, '=');
    archivoTxt<<left<<setw(MAX_TAM_PALABRA_TEXTO)<<"PALABRA"
                <<right<<setw(MAX_CAR_POL)<<"POLARIDAD"<<endl;    
    imprimeLinea(archivoTxt, '=');
    
    int tamEl = sizeof(struct Palabra), 
            cantidad;
    datosArchivoIf(tamEl, archivoBin, cantidad);
            
    struct Palabra palabra;
    archivoBin.seekg(0, ios::beg);
    for (int i = 0; i < cantidad; i++) {        
        archivoBin.read(reinterpret_cast<char*>(&palabra), tamEl);
        archivoTxt<<left<<setw(MAX_TAM_PALABRA_TEXTO)<<palabra.texto
                <<right<<setw(MAX_CAR_POL)<<palabra.polaridad<<endl;
    }

}

void leePlatos(const char *nombreArchivoCsv, const char *nombreArchivoBin){
    ifstream archivoCsv(nombreArchivoCsv, ios::in);
    if(not archivoCsv.is_open()){
        cout<<"ERROR: No se pudo abri "<<nombreArchivoCsv;
        exit(1);
    }
    ofstream archivoBin(nombreArchivoBin, ios::out|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se pudo abri "<<nombreArchivoBin;
        exit(1);
    }
    
    struct Plato plato;
    while(true){
        //LSUCD6,Chupe de Camarones,31.34
        archivoCsv.getline(plato.codigo, MAX_TAM_PLATO_CODIGO, ',');
        if(archivoCsv.eof()) break;
        archivoCsv.getline(plato.nombre, MAX_TAM_PLATO_NOMBRE, ',');
        archivoCsv>>plato.precio;
        archivoCsv.get();
        
        archivoBin.write(reinterpret_cast<const char*>(&plato), 
                sizeof(struct Plato));                
    }
}
void verificaPlatos(const char *nombreArchivoTxt, const char *nombreArchivoBin){
    ifstream archivoBin(nombreArchivoBin, ios::in|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se pudo abri "<<nombreArchivoBin;
        exit(1);
    }
    ofstream archivoTxt(nombreArchivoTxt, ios::out);
    if(not archivoTxt.is_open()){
        cout<<"ERROR: No se pudo abri "<<nombreArchivoTxt;
        exit(1);
    }
    archivoTxt<<fixed<<setprecision(2);
    
    archivoTxt<<setw(MAX_CAR_LIN/2)<<"REPORTE PLATOS"<<endl;
    imprimeLinea(archivoTxt, '=');
    archivoTxt<<left<<setw(MAX_TAM_PLATO_CODIGO)<<"CODIGO"
            <<setw(MAX_TAM_PLATO_NOMBRE)<<"NOMBRE"
            <<setw(MAX_CAR_DIN)<<"PRECIO"<<endl;    
    imprimeLinea(archivoTxt, '=');
    
    int tamEl = sizeof(struct Plato), 
            cantidad;
    datosArchivoIf(tamEl, archivoBin, cantidad);
            
    struct Plato plato;
    archivoBin.seekg(0, ios::beg);
    for (int i = 0; i < cantidad; i++) {        
        archivoBin.read(reinterpret_cast<char*>(&plato), tamEl);
        archivoTxt<<left<<setw(MAX_TAM_PLATO_CODIGO)<<plato.codigo
                <<setw(MAX_TAM_PLATO_NOMBRE)<<plato.nombre
                <<right<<setw(MAX_CAR_DIN/2)<<plato.precio<<setw(MAX_CAR_DIN/2)<<' '
                <<endl;
                        
    }

}

int leeHora(ifstream &archivo){
    int hh, mm;
    char sep;
    archivo>>hh>>sep>>mm;
    
    return hh*60+mm;
}
void leeAtenciones(const char *nombreArchivoTxt, 
        const char *nombreArchivoAtenciones, 
        const char *nombreArchivoPlatos){
    ifstream archivoTxt(nombreArchivoTxt, ios::in);
    if(not archivoTxt.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoTxt;
        exit(1);
    }
    ofstream archivoAtencion(nombreArchivoAtenciones, ios::out|ios::binary);
    if(not archivoAtencion.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoAtenciones;
        exit(1);
    }
    ifstream archivoPlatos(nombreArchivoPlatos, ios::in|ios::binary);
    if(not archivoPlatos.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoPlatos;
        exit(1);
    }
    
    int tamPlato = sizeof(struct Plato), 
            cantidadPlatos;
    datosArchivoIf(tamPlato, archivoPlatos, cantidadPlatos);
    
    struct Atencion atencion;
    while(true){
        //769950 20:24 2AFMEV 3 6SA0MW 5
        archivoTxt>>atencion.codigo;
        if(archivoTxt.eof()) break;
        atencion.hora = leeHora(archivoTxt);
        atencion.cantidad_comentarios=0;
        for (int i = 0; i < MAX_CANT_ATENCION_COMENTARIOS; i++) {            
            atencion.comentarios[i].cantidad_palabras=0;
            atencion.comentarios[i].polaridadTotal=0;
            strcpy(atencion.comentarios[i].texto, "WAZA");
        }
        atencion.total_venta=0;        
        
        struct Plato platoPedido;
        int cantidadPedida;
        while(true){
            if(archivoTxt.get()=='\n') break;
            archivoTxt>>ws;
            archivoTxt.getline(platoPedido.codigo, MAX_TAM_PLATO_CODIGO, ' ');
            archivoTxt>>cantidadPedida;
            
            platoPedido.precio = buscaPrecioPlato(archivoPlatos, cantidadPlatos, platoPedido.codigo);
            atencion.total_venta+=platoPedido.precio*cantidadPedida;
            
        }
        
        archivoAtencion.write(reinterpret_cast<const char*>(&atencion), sizeof(struct Atencion));
    }
    
}
double buscaPrecioPlato(ifstream &archivoPlatos, int cantidad, char *codigo){
    archivoPlatos.seekg(0, ios::beg);
    struct Plato plato;
    for (int i = 0; i < cantidad; i++) {        
        archivoPlatos.read(reinterpret_cast<char*>(&plato), sizeof(struct Plato));
        if(strcmp(plato.codigo, codigo) == 0) return plato.precio;
    }
    return 0;
}

void imprimeAtencion(const char *nombreArchivoTxt, const char *nombreArchivoBin){
    ofstream archivoTxt(nombreArchivoTxt, ios::out);
    if(not archivoTxt.is_open()){
        cout<<"ERROR: No se pudo abrir: "<<nombreArchivoTxt;
        exit(1);
    }
    archivoTxt<<fixed<<setprecision(2);
    ifstream archivoBin(nombreArchivoBin, ios::in|ios::binary);
    if(not archivoBin.is_open()){
        cout<<"ERROR: No se pudo abrir: "<<nombreArchivoBin;
        exit(1);
    }
    
    struct Atencion atencion;
    int tamEl = sizeof(atencion), 
            cantidad;
    datosArchivoIf(tamEl, archivoBin, cantidad);
    
    archivoTxt<<setw(MAX_CAR_LIN/2)<<"ATENCIONES"<<endl;
    imprimeLinea(archivoTxt, '=');
    archivoTxt<<left
            <<setw(MAX_CAR_COD)<<"ATENCION No."
            <<setw(MAX_CAR_HORA)<<"HORA"
            <<setw(MAX_CAR_DIN)<<"MONTO TOTAL"<<endl;        
    
    
    archivoBin.seekg(0, ios::beg);
    for (int i = 0; i < cantidad; i++) {
        archivoBin.read(reinterpret_cast<char *>(&atencion), sizeof(struct Atencion));
        imprimeLinea(archivoTxt, '=');
        archivoTxt<<left
                <<setw(MAX_CAR_COD)<<atencion.codigo;
        imprimeHora(archivoTxt, atencion.hora);
        archivoTxt<<right<<setw(MAX_CAR_DIN/2)<<atencion.total_venta<<left<<setw(MAX_CAR_DIN/2)<<' '<<endl;
        imprimeLinea(archivoTxt, '-');
        
        archivoTxt<<"COMENTARIOS"<<endl;
        imprimeLinea(archivoTxt, '-');;
        for (int j = 0; j < atencion.cantidad_comentarios; j++) {            
            archivoTxt<<atencion.comentarios[j].texto<<endl;
            
            archivoTxt<<"PALABRAS: "<<endl;
            for (int k = 0; k < atencion.comentarios[j].cantidad_palabras; k++) {
                archivoTxt<<setw(MAX_TAM_PALABRA_TEXTO)<<atencion.comentarios[j].palabras[k].texto
                        <<atencion.comentarios[j].palabras[k].polaridad<<endl;
            }
            archivoTxt<<"POLARIDAD: "<<atencion.comentarios[j].polaridadTotal<<endl;           
        }
                      
    }

}
void imprimeHora(ofstream &archivo, int hora){
    int hh, mm;
    char sep = ':';
    
    hh = hora/60;
    mm = hora%60;
    
    archivo<<right<<setfill('0')
            <<setw(2)<<hh<<sep
            <<setw(2)<<mm
            <<left<<setfill(' ')
            <<setw(MAX_CAR_HORA-5)<<" AM";
}

void leeComentarios(const char *nombreArchivoCsv, 
        const char *nombreArchivoAtenciones, 
        const char *nombreArchivoLexicon){
    ifstream archivoCsv(nombreArchivoCsv, ios::in);
    if(not archivoCsv.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoCsv;
        exit(1);
    }
    fstream archivoAtencion(nombreArchivoAtenciones, ios::in|ios::out|ios::binary);
    if(not archivoAtencion.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoAtenciones;
        exit(1);
    }
    ifstream archivoLexicon(nombreArchivoLexicon, ios::in|ios::binary);
    if(not archivoLexicon.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivoLexicon;
        exit(1);
    }
    
    int tamPalabra = sizeof(struct Palabra), 
            cantidadLexicon;
    datosArchivoIf(tamPalabra, archivoLexicon, cantidadLexicon);
    
    int tamAtencion = sizeof(struct Atencion), 
            cantidadAtenciones;
    datosArchivoF(tamAtencion, archivoAtencion, cantidadAtenciones);
    
    int codigoAtencion;
    char comentario[MAX_TAM_COMENTARIO_TEXTO]{};
    struct Atencion atencion;
    while(true){
        //284189,"Los platos estuvieron muy ricos y sabrosos, el pedido fue rapido. ¡Volveria seguramente!"
        archivoCsv>>codigoAtencion;
        if(archivoCsv.eof()) break;
        archivoCsv.get();
        archivoCsv.getline(comentario, MAX_TAM_COMENTARIO_TEXTO, '\n');
        
        int posAtencion = buscaAtencion(archivoAtencion, cantidadAtenciones, codigoAtencion);
        if(posAtencion!=NO_ENCONTRADO){
            archivoAtencion.seekg(tamAtencion*posAtencion, ios::beg);
            archivoAtencion.read(reinterpret_cast<char*>(&atencion), tamAtencion);
            
            strcpy(atencion.comentarios[atencion.cantidad_comentarios].texto, comentario);
            preprocesaComentario(atencion.comentarios[atencion.cantidad_comentarios].pre_procesado, 
                    atencion.comentarios[atencion.cantidad_comentarios].texto);
            procesaComentario(atencion.comentarios[atencion.cantidad_comentarios], 
                    archivoLexicon, cantidadLexicon);
            
            atencion.cantidad_comentarios++;
            
            archivoAtencion.seekg(tamAtencion*posAtencion, ios::beg);
            archivoAtencion.write(reinterpret_cast<const char*>(&atencion), tamAtencion);
        }
    }
    
}
int buscaAtencion(fstream &archivo, int cantidad, int codigo){
    archivo.seekg(0, ios::beg);
    struct Atencion atencion;
    for (int i = 0; i < cantidad; i++) {
        archivo.read(reinterpret_cast<char*>(&atencion), sizeof(struct Atencion));
        if(atencion.codigo == codigo) return i;
    }
    return NO_ENCONTRADO;

}
char *preprocesaComentario(char *preprocesado, const char *comentario){
    char c;
    int k = 0;
    for (int i = 0; comentario[i]; i++) {        
        c = comentario[i];
        if(isalpha(c) or c ==' '){
            preprocesado[k] = tolower(c);
            k++;
        }
    }
    preprocesado[k] = 0;        
        
}

void procesaComentario(struct Comentario &comentario, 
        ifstream &archivoLexicon, int cantidadLexicon){
    comentario.cantidad_palabras = cuentaPalabras(comentario.pre_procesado);
        
    int cantidadLetras=0;
    for (int i = 0; i<comentario.cantidad_palabras; i++) {
        procesaPalabra(comentario.palabras[i], &comentario.pre_procesado[cantidadLetras] , cantidadLetras);
        buscaPolaridad(archivoLexicon, cantidadLexicon, comentario.palabras[i]);
        comentario.polaridadTotal+= comentario.palabras[i].polaridad;
    }           
}
int cuentaPalabras(char *palabras){
    int cantidad = 0;
    for (int i = 0; palabras[i]; i++) {        
        if(palabras[i] == ' '){
            cantidad++;
        }
    }
    //contamos la ultima palabra aunque no tenga espacio
    cantidad++;
    return cantidad;

}
void procesaPalabra(struct Palabra &palabra, char *comentario, int &cantidad){
    int cantidadLetras = 0;
    for (int i = 0; comentario[i]!=' ' and comentario[i]; i++) {        
        cantidadLetras++;
    }
    
    int  i;
    for (i = 0; comentario[i]!=' ' and comentario[i]; i++) {        
        palabra.texto[i] = comentario[i];
    }
    palabra.texto[i] = 0;        

    cantidad+=cantidadLetras+1;    
}
void buscaPolaridad(ifstream &archivo, int cantidad, struct Palabra &palabra){
    archivo.seekg(0, ios::beg);
    struct Palabra palabraActual;
    for (int i = 0; i < cantidad; i++) {        
        archivo.read(reinterpret_cast<char*>(&palabra), sizeof(struct Palabra));
        if(strcmp(palabraActual.texto, palabra.texto)==0){
            palabra.polaridad = palabraActual.polaridad;
            return;
        }
    }
    palabra.polaridad = 0;  
}