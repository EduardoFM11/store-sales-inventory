#include "funciones.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void imprime(void *n) {
    printf("--------\n");
    printf("[Informacion del Producto]\n");
    printf("Título: [%s]\n",((Producto *)n)->titulo);
    printf("Descripcion: [%s]\n",((Producto *)n)->descripcion);
    printf("Precio: [%.2f]\n",((Producto *)n)->precio);
    printf("Disponibles: [%d]\n",((Producto *)n)->disponibles);
    printf("Codigo: [%d]\n",((Producto *)n)->codigo);
    printf("--------\n");
    printf("\n");
}

void imprimeVenta(void *n) {
    printf("--------\n");
    printf("[Informacion del Producto]\n");
    printf("Título: [%s]\n",((Producto *)n)->titulo);
    printf("Descripcion: [%s]\n",((Producto *)n)->descripcion);
    printf("Precio Unitario: [%.2f]\n",((Producto *)n)->precio);
    printf("Cantidad: [%d]\n",((Producto *)n)->disponibles);
    printf("Codigo: [%d]\n",((Producto *)n)->codigo);
    printf("Precio total [%.2f]\n", ((Producto *)n)->precio * ((Producto *)n)->disponibles);
    printf("--------\n");
    printf("\n");
}

void imprimeVentaArchivo(FILE *fp,void *n) {
    fprintf(fp,"--------\n");
    fprintf(fp,"[Informacion del Producto]\n");
    fprintf(fp,"Título: [%s]\n",((Producto *)n)->titulo);
    fprintf(fp,"Descripcion: [%s]\n",((Producto *)n)->descripcion);
    fprintf(fp,"Precio Unitario: [%.2f]\n",((Producto *)n)->precio);
    fprintf(fp,"Cantidad: [%d]\n",((Producto *)n)->disponibles);
    fprintf(fp,"Codigo: [%d]\n",((Producto *)n)->codigo);
    fprintf(fp,"Precio total [%.2f]\n", ((Producto *)n)->precio * ((Producto *)n)->disponibles);
    fprintf(fp,"--------\n");
    fprintf(fp,"\n");
}

void imprimirLista(TADLista *lista) {
    if (TADListaVacia(lista)==1)
        printf("Lista vacia\n");
    else
        TADListaIterar(lista,imprime);
}

void imprimirListaVenta(TADLista *lista) {
    if (TADListaVacia(lista)==1)
        printf("Lista vacia\n");
    else
        TADListaIterar(lista,imprimeVenta);
}

void imprimirListaVentaArchivo(TADLista *lista, FILE *fp) {
    if (TADListaVacia(lista)==1)
        printf("Lista vacia\n");
    else
        TADListaIterarArchivo(lista,imprimeVentaArchivo, fp);
}

void imprimirDetallesTicket(FILE *fp){
	fprintf(fp, "%s\n", "Comercializadora TPD S.A. DE C.V.");
	fprintf(fp, "%s\n", "Av. Universidad 10-B Col. Valle Sur C.P. 14309");
	fprintf(fp, "%s\n", "RFC: TPD190617ASF");
	time_t t = time(NULL);
	struct tm tm = *localtime(&t);
	fprintf(fp,"Fecha:: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
}

float obtenerTotal(void *n){
	float venta;
	venta = ((Producto *)n)->precio * ((Producto *)n)->disponibles;
	return venta;
}

Producto *leerProducto(){
	Producto *producto;
	producto = (Producto *)malloc(sizeof(Producto));
	getchar();
	printf("Ingresa titulo: "); fgets(producto->titulo, 50, stdin);
	producto->titulo[strlen(producto->titulo)-1] = '\0';
	printf("Ingresa descripción: "); fgets(producto->descripcion, 100, stdin);
	producto->descripcion[strlen(producto->descripcion)-1] = '\0';
	printf("Ingresa precio: "); scanf("%f", &(producto->precio));
	printf("Ingresa disponibles: "); scanf("%d", &(producto->disponibles));
	printf("Ingresa codigo: "); scanf("%d", &(producto->codigo));
	fflush(stdin);

	return producto;
}

Producto *buscar(TADLista *lista, void *info, int opcion){
	Nodo *p;
	if (TADListaVacia(lista)){
		printf("El inventario esta vacio\n");
		return NULL;
	} else{
		p = lista->inicio;
		if(opcion == 1) {
			while(p != NULL && strcmp(((Producto *)p->TAD)->titulo, ((char *)info)) != 0) {
				p = p->sig;
			}
			if (p == NULL) {
				printf("PRODUCTO %s NO ENCONTRADO\n", ((char *)info));
				return NULL;
			} else if(strcmp(((Producto *)p->TAD)->titulo, ((char *)info)) == 0){
				printf("PRODUCTO ENCONTRADO\n");
				imprime((void *)(p->TAD));
				return ((Producto *)p->TAD);
			} 
		} else {
			while(p != NULL && ((Producto *)p->TAD)->codigo != *((int *)info)){
			p = p->sig;
			}
			if (p == NULL){
				printf("PRODUCTO %d NO ENCONTRADO\n", *((int *)info));
				return NULL;
			} else if(((Producto *)p->TAD)->codigo == *((int *)info)){
				printf("PRODUCTO ENCONTRADO\n");
				imprime((void *)(p->TAD));
				return ((Producto *)p->TAD);
			} 
		}
		return NULL;
	}
}

Producto *eliminar(TADLista *lista, int codigo){
	Nodo *p, *q;
	if (TADListaVacia(lista)){
		printf("Inventario vacio\n");
		return NULL;
	} else if(lista->inicio == lista->fin) {
		p = lista->inicio;
		lista->inicio = NULL;
		lista->fin = NULL;
		printf("HAS BORRADO:\n");
		imprime((void *)(p->TAD));
		return ((Producto *)p->TAD);
	} else if(((Producto *)lista->inicio->TAD)->codigo == codigo){
		p = lista->inicio;
		lista->inicio = lista->inicio->sig;
		lista->inicio->ant = NULL;
		p->sig = NULL;
		imprime((void *)(p->TAD));
		return ((Producto *)p->TAD);
	} else if(((Producto *)lista->fin->TAD)->codigo == codigo){
		p = lista->fin;
		lista->fin = lista->fin->ant;
		lista->fin->sig = NULL;
		p->ant = NULL;
		imprime((void *)(p->TAD));
		return ((Producto *)p->TAD);
	} else {
		q = lista->inicio; p= lista->inicio->sig;
		while(((Producto *)p->TAD)->codigo != codigo && p->sig != lista->fin){
			q = p;
			p = p->sig;
		}

		if (((Producto *)p->TAD)->codigo == codigo){
			q->sig = p->sig;
			p->sig = NULL;
			imprime((void *)(p->TAD));
			return ((Producto *)p->TAD);
		}
	}
	return NULL;
}

void eliminarTodo(TADLista *lista){
	Nodo *p;
	p = lista->inicio;
	while(p != NULL) 
	{   
	    lista->inicio = p->sig;
	    p->sig = NULL;
	    free(p);
	    p = lista->inicio;
	}
}


