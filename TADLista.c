#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TADLista.h"


Nodo *nodoNuevo(void *info, size_t tam) {
    Nodo *nodo;
    nodo = malloc(sizeof(Nodo));
    nodo->TAD = malloc(tam);
    memcpy(nodo->TAD, info, tam);
    nodo->sig = NULL;
    nodo->ant = NULL;
    return nodo;
}

TADLista *TADListaCrear(size_t tamInfo) {
    TADLista *cola;
    cola = malloc(sizeof(TADLista));
    cola->TADTam = tamInfo;
    cola->inicio = NULL;
    cola->fin = NULL;
    return cola;
}

int TADListaVacia(TADLista *cola) {
    return cola->inicio == NULL || cola->fin == NULL;
}

void TADListaAgregar(TADLista *cola,void *info) {
    Nodo *nuevo;
    if (info==NULL) {
        printf("ERROR (TADLista.c) TADListaAgregar: Se ha intentado agregar a la lista un apuntador NULL\n");
        printf("Sistema detenido");
        exit(0);
    }
    nuevo = nodoNuevo(info,cola->TADTam);
    if (TADListaVacia(cola)) {
        cola->inicio = nuevo;
        cola->fin = nuevo;
        return;
    }
    nuevo->ant = cola->fin;
    cola->fin->sig = nuevo;
    cola->fin = nuevo;
}

int TADListaRetirar(TADLista *cola, void *info) {
    Nodo *p;
    if (TADListaVacia(cola)) {
        return 0;
    }
    if (cola->inicio==cola->fin) {
        p = cola->inicio;
        cola->inicio = NULL;
        cola->fin = NULL;

    } else {
        p = cola->inicio;
        cola->inicio=p->sig;
        cola->inicio->ant = NULL;
    }
    memcpy(info,p->TAD,cola->TADTam);
    free(p);
    return 1;
}

void TADListaIterar(TADLista *cola, void (funcion)(void *TAD)) {
    Nodo *p;
    p = cola->inicio;
    while (p!=NULL) {
        (*funcion)(p->TAD);
        p = p->sig;
    }
}

void TADListaIterarCopiarLista(TADLista *listaOriginal, TADLista *listaNueva) {
    Nodo *p;
    p = listaOriginal->inicio;
    while (p!=NULL) {
        TADListaAgregar(listaNueva, (void *)p->TAD);
        p = p->sig;
    }
}

float TADListaIterarPrecioTotal(TADLista *cola, float (funcion)(void *TAD)) {
    Nodo *p;
    float venta;
    p = cola->inicio;
    while (p!=NULL) {
        venta = venta + (*funcion)(p->TAD);
        p = p->sig;
    }
    return venta;
}

void TADListaIterarArchivo(TADLista *cola, void (funcion)(FILE *archivo, void *TAD), FILE *fp){
    Nodo *p;
    p = cola->inicio;
    while (p!=NULL) {
        (*funcion)(fp, p->TAD);
        p = p->sig;
    }
}
