#include <stddef.h>
#include <stdio.h>

struct NODO {
    void *TAD;
    struct NODO *sig;  
    struct NODO *ant;
};

typedef struct NODO Nodo;

struct TADLista {
    size_t TADTam;
    Nodo *inicio;
    Nodo *fin;
};

typedef struct TADLista TADLista;

TADLista *TADListaCrear(size_t tamInfo);
int TADListaVacia(TADLista *cola);
void TADListaAgregar(TADLista *cola,void *info);
int TADListaRetirar(TADLista *cola, void *info);
void TADListaIterar(TADLista *cola, void (funcion)(void *TAD));
void TADListaIterarArchivo(TADLista *cola, void (funcion)(FILE *archivo, void *TAD), FILE *fp);
float TADListaIterarPrecioTotal(TADLista *cola, float (funcion)(void *TAD));
void TADListaIterarCopiarLista(TADLista *colaOriginal, TADLista *listaNueva);