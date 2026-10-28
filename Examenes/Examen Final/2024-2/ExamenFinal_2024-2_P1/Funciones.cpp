/* 
 * File:   Funciones.cpp
 * Author: arias
 * 
 * Created on 25 de mayo de 2025, 03:47 PM
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
#define MAX_CAR_COD 10
#define MAX_CAR_DESC 40
#define MAX_CAR_DIN 12

//LECTURA
char *leeCadenaExacta(ifstream &archivo, char del){
    char buff[100], *txt;
    
    archivo.getline(buff, 100, del);
    
    if(archivo.eof()) return nullptr;
    
    txt = new char[strlen(buff)+1];
    strcpy(txt, buff);
    
    return txt;
    
}
int leeHora(ifstream &archivo){
    int hh, mm;
    char sep;
    archivo>>hh>>sep>>mm;
    
    return hh*60+mm;
}
void leeLexicon(const char *nombreArchivo, 
        struct Palabra *lexicon, int &cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //rapido,1
        lexicon[cantidad].texto = leeCadenaExacta(archivo, ',');
        if(archivo.eof()) break;
        archivo>>lexicon[cantidad].polaridad;
        archivo.get(); // para el salto de linea
        
        cantidad++;
    }
}
struct Plato *leePlatos(const char *nombreArchivo,
        int max, int &cantidad){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    struct Plato buff[max]{}, *platos;
    
    while(true){
        //GCPRWS,Sopa de Quinua,32.18
        buff[cantidad].codigo = leeCadenaExacta(archivo, ',');
        if(archivo.eof()) break;
        buff[cantidad].nombre = leeCadenaExacta(archivo, ',');
        archivo>>buff[cantidad].precio;
        archivo.get();
        
        cantidad++;
    }
    
    platos = new struct Plato [cantidad]{};
    
    for (int i = 0; i < cantidad; i++) {
        platos[i].cantidad = buff[i].cantidad;
        
        platos[i].codigo = new char [strlen(buff[i].codigo)];
        strcpy(platos[i].codigo, buff[i].codigo);
        
        platos[i].precio = buff[i].precio;
        
        platos[i].nombre = new char [strlen(buff[i].nombre)];
        strcpy(platos[i].nombre, buff[i].nombre);
    }    
    return platos;
}
void leeAtenciones(const char *nombreArchivo,
        struct Atencion *atenciones, int &cantidadAtenciones,
        struct Plato *platos, int cantidadPlatos){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    while(true){
        //359567 11:07 2MLJAS 7 D7L3OI 5
        struct Atencion &atencionActual = atenciones[cantidadAtenciones];
        
        archivo>>atencionActual.codigo;
        if(archivo.eof()) break;
        atencionActual.hora = leeHora(archivo);
        atencionActual.cantidad_platos=0;
        atencionActual.cantidad_comentarios=0;        
        
        char *codigoPlato;
        int cantidadPedida;                        
        while(true){
            if(archivo.get() == '\n') break;
            
            archivo>>ws;
            codigoPlato = leeCadenaExacta(archivo, ' ');
            archivo>>cantidadPedida;
            
            int posPlato = buscaPlato(platos, cantidadPlatos, codigoPlato);            
            if(posPlato != NO_ENCONTRADO){                
                //copiamos el plato a la pocision de atencion
                if(atencionActual.cantidad_platos==0)
                    atencionActual.platos_atendidos = new struct Plato [MAX_CANT_ATENCION_PLATOS]{};
                
                atencionActual.platos_atendidos[atencionActual.cantidad_platos].codigo = new char[strlen(platos[posPlato].codigo)+1];                                                
                strcpy(atencionActual.platos_atendidos[atencionActual.cantidad_platos].codigo, platos[posPlato].codigo);                                                                
                
                atencionActual.platos_atendidos[atencionActual.cantidad_platos].nombre = new char[strlen(platos[posPlato].nombre)+1]{}; 
                strcpy(atencionActual.platos_atendidos[atencionActual.cantidad_platos].nombre, platos[posPlato].nombre);                
                
                atencionActual.platos_atendidos[atencionActual.cantidad_platos].cantidad= cantidadPedida;
                atencionActual.platos_atendidos[atencionActual.cantidad_platos].precio = platos[posPlato].precio;
                                
                atencionActual.total_venta+=cantidadPedida*platos[posPlato].precio;
                
                atencionActual.cantidad_platos++;                
            }
        }
        
        cantidadAtenciones++;
    }
    
}
void leeComentarios(const char *nombreArchivo,
        struct Atencion *atenciones, int cantidadAtenciones,
        struct Palabra *lexicon, int cantidadLexicon){
    ifstream archivo(nombreArchivo, ios::in);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    
    int codigoAtencion;
    char *comentario;
    while(true){
        //394386,"Los platos estuvieron muy ricos y sabrosos, el pedido fue rapido. ¡Volveria seguramente!"
        archivo>>codigoAtencion;
        if(archivo.eof()) break;
        archivo.get();
        comentario =leeCadenaExacta(archivo, '\n');
        
        int posAtencion = buscaAtencion(atenciones, cantidadAtenciones, codigoAtencion);
        if(posAtencion != NO_ENCONTRADO){
            struct Atencion &atencionActual = atenciones[posAtencion];
            if(atencionActual.cantidad_comentarios==0)
                atencionActual.comentarios = 
                        new struct Comentario[MAX_CANT_ATENCION_COMENTARIOS]{};
            
            
            atencionActual.comentarios[atencionActual.cantidad_comentarios].pre_procesado 
                    = preprocesaComentario(comentario);
            
            procesaComentario(atencionActual.comentarios[atencionActual.cantidad_comentarios], 
                    lexicon, cantidadLexicon);
            
            atencionActual.cantidad_comentarios++;
        }
    }
}
//BUSQUEDA
int buscaPlato(struct Plato *platos, int cantidad, char *codigo){
    for (int i = 0; i < cantidad; i++)
        if(strcmp(codigo, platos[i].codigo) == 0) return i;    
    return NO_ENCONTRADO;
}
int buscaAtencion(struct Atencion *atenciones, int cantidad, int codigo){
    for (int i = 0; i < cantidad; i++)
        if(codigo == atenciones[i].codigo) return i;    
    return NO_ENCONTRADO;
}
int buscaPolaridad(struct Palabra *lexicon, int cantidad, char *txt){
    for (int i = 0; i <cantidad; i++) {        
        if(strcmp(lexicon[i].texto,txt)==0) return i;
    }
    return NO_ENCONTRADO;   
}
//PROCESA COMENTARIO
char *preprocesaComentario(char *comentario){
    char aux[100], *preprocesado, c;
    int k = 0;
    for (int i = 0; comentario[i]; i++) {        
        c = comentario[i];
        if(isalpha(c) or c ==' '){
            aux[k] = tolower(c);
            k++;
        }
    }
    aux[k] = 0;
    
    preprocesado = new char [strlen(aux)+1];
    strcpy(preprocesado, aux);
    
    return preprocesado;
}
void procesaComentario(struct Comentario &comentario, 
        struct Palabra *lexicon, int cantidadLexicon){
    comentario.cantidad_palabras = cuentaPalabras(comentario.pre_procesado);
//    comentario.palabras = new struct Palabra [comentario.cantidad_palabras]{};
        
    int cantidadLetras=0;
    for (int i = 0; i<comentario.cantidad_palabras; i++) {
        procesaPalabra(comentario.palabras[i], &comentario.pre_procesado[cantidadLetras] , cantidadLetras);
        buscaPolaridad(lexicon, cantidadLexicon, comentario.palabras[i]);
        comentario.polaridad_total+= comentario.palabras[i].polaridad;
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

    palabra.texto = new char [cantidadLetras+1]{};
    int  i;
    for (i = 0; comentario[i]!=' ' and comentario[i]; i++) {        
        palabra.texto[i] = comentario[i];
    }
    palabra.texto[i] = 0;        

    cantidad+=cantidadLetras+1;    
}
void buscaPolaridad(struct Palabra *lexicon, int cantidad, struct Palabra &palabra){
    int posPol = buscaPolaridad(lexicon, cantidad, palabra.texto);
    if(posPol!= NO_ENCONTRADO){
        palabra.polaridad = lexicon[posPol].polaridad;
    }
    else{
        palabra.polaridad = 0;        
    }
}

//IMPRESION
void imprimeLinea(ofstream &archivo, char c){
    for (int i = 0; i < MAX_CAR_LIN; i++) {        
        archivo<<c;
    }
    archivo<<endl;
}
void emitirReporte(const char *nombreArchivo,
        struct Atencion *atenciones, int cantidad){
    ofstream archivo(nombreArchivo, ios::out);
    if(not archivo.is_open()){
        cout<<"ERROR: No se pudo abrir "<<nombreArchivo;
        exit(1);
    }
    archivo<<fixed<<setprecision(2);
    
    imprimeEncabezado(archivo);
    
    for (int i = 0; i < cantidad; i++) {        
        imprimeEncabezadoAtenciones(archivo,
                atenciones[i].codigo, atenciones[i].hora);
        for (int j = 0; j < atenciones[i].cantidad_platos; j++) {            
            archivo<<left
                    <<atenciones[i].platos_atendidos[j].codigo<<setw(5)<<')'
                    <<setw(MAX_CAR_DESC)<<atenciones[i].platos_atendidos[j].nombre
                    <<setw(MAX_CAR_DIN)<<atenciones[i].platos_atendidos[j].precio
                    <<setw(MAX_CAR_DIN)<<atenciones[i].platos_atendidos[j].cantidad
                    <<setw(MAX_CAR_DIN)<<atenciones[i].platos_atendidos[j].cantidad*atenciones[i].platos_atendidos[j].precio
                    <<endl;
                    
        }
        archivo<<"POLARIDAD TOTAL DE LOS COMENTARIOS: "<<sumaPolaridad(atenciones[i].comentarios, atenciones[i].cantidad_comentarios)<<endl;
        imprimeLinea(archivo, '=');

    }

    
}
void imprimeEncabezado(ofstream &archivo){
    archivo<<setw(MAX_CAR_LIN/2)<<"EMPRESA DE REPARTOS A DOMICILIO VENUS S.A."<<endl
            <<setw(MAX_CAR_LIN/2)<<"RELACION DE ATENCIONES"<<endl;
    imprimeLinea(archivo, '=');
}
void imprimeEncabezadoAtenciones(ofstream &archivo,
        int codigo, int hora){
    archivo<<left
            <<"No. ATENCION "<<setw(MAX_CAR_COD)<<codigo
            <<"ATENDIDO A ALAS ";
    imprimeHora(archivo, hora);
    archivo<<endl;
    imprimeLinea(archivo, '-');
    
    
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
            <<" AM";
}
int sumaPolaridad(struct Comentario *comentarios, int cantidad){
    int total = 0;
    for (int i = 0; i < cantidad; i++) {        
        total += comentarios[i].polaridad_total;
    }
    return total;
}