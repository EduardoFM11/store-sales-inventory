#include <stdio.h>
#include <time.h>
#include "TADLista.h"

struct PRODUCTO {
	int disponibles;
	int codigo;
	char titulo[50];
	char descripcion[100];
	float precio;

};

typedef struct PRODUCTO Producto;

void imprimirLista(TADLista *lista);
void imprimirListaVenta(TADLista *lista);
void imprimirListaVentaArchivo(TADLista *lista, FILE *fp);

void imprime(void *n);
void imprimeVenta(void *n);
void imprimeVentaArchivo(FILE *fp,void *n);

void imprimirDetallesTicket(FILE *fp);

Producto *leerProducto();
Producto *buscar(TADLista *lista, void *info, int opcion);
Producto *eliminar(TADLista *lista, int codigo);
void eliminarTodo(TADLista *lista);
float obtenerTotal(void *n);