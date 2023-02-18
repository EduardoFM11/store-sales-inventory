#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>

#include "funciones.h"

int entradaMenuPrincipal(){
	int opcion;
		printf("1.- Administrar 2.- Venta 3.- Salir\n"); printf("Opcion: ");
		while(scanf("%d", &opcion)==0){//if scanf failed to scan an integer
			printf("1.- Administrar 2.- Venta 3.- Salir\n");
    		printf("Entrada invalida. Intenta de nuevo\n");
    		int c;
    		while((c=getchar())!='\n' && c!= EOF); //clear the stdin
		}	
	return opcion;
}

int entradaMenuSecAdmin(){
	int opcion;
		printf("1.- Agregar 2.- Buscar 3.- Desplegar inventario 4.- Eliminar producto 5.- Generar Reporte del día 6.- Salir\n"); printf("Opcion: ");
		while(scanf("%d", &opcion)==0){//if scanf failed to scan an integer
			printf("1.- Agregar 2.- Buscar 3.- Desplegar inventario 4.- Eliminar producto 5.- Generar Reporte del día 6.- Salir\n");
    		printf("Entrada invalida. Intenta de nuevo\n");
    		int c;
    		while((c=getchar())!='\n' && c!= EOF); //clear the stdin
		}	
	return opcion;
}


int main (){

	//Inventario disponible de prueba
	Producto tvSamsung3500;
	tvSamsung3500.disponibles = 15;
	tvSamsung3500.precio = 5000;
	tvSamsung3500.codigo = 983371;
	strcpy(tvSamsung3500.titulo, "Samsung TV 4K 3500S");
	strcpy(tvSamsung3500.descripcion, "Resolucion 4K, 40 pulgadas, 4 entradas HDMI");

	Producto iPhoneX;
	iPhoneX.disponibles = 10;
	iPhoneX.precio = 19500;
	iPhoneX.codigo = 543867;
	strcpy(iPhoneX.titulo, "iPhone X 128GB");
	strcpy(iPhoneX.descripcion, "Capacidad 128GB, pantalla alta resolución, FaceID");


	Producto XBOX1S;
	XBOX1S.disponibles = 8;
	XBOX1S.precio = 7490;
	XBOX1S.codigo = 254362;
	strcpy(XBOX1S.titulo, "Xbox OneS 1TB");
	strcpy(XBOX1S.descripcion, "Capacidad de 1TB, 3.5ghz, 2 entradas ethernet");


	Producto FH4;
	FH4.disponibles = 18;
	FH4.precio = 959;
	FH4.codigo = 113468;
	strcpy(FH4.titulo, "Forza Horizon 4");
	strcpy(FH4.descripcion, "450 automoviles, climas dinamicos");

	TADLista *listaInventario;
	TADLista *listaVenta;
	TADLista *listaMovimientos;
	Producto *producto;
	Producto temp;
	FILE *fp;

	listaInventario = TADListaCrear(sizeof(Producto));
	listaVenta = TADListaCrear(sizeof(Producto));
	listaMovimientos = TADListaCrear(sizeof(Producto));

	TADListaAgregar(listaInventario, (void*)(&tvSamsung3500));
	TADListaAgregar(listaInventario, (void*)(&iPhoneX));
	TADListaAgregar(listaInventario, (void*)(&XBOX1S));
	TADListaAgregar(listaInventario, (void*)(&FH4));

	setlocale(LC_ALL, "");

	int opcion, opcion2, opcion3, opcion4, opcion5;
	float totalVenta = 0;
	float ventasTotales = 0;
	float cantidadEliminar;
	float diferenciaVenta;
	char nombreB[50]; int codigoB; int cantidad;

	do{
		opcion = entradaMenuPrincipal();

		switch(opcion){
			//Administrar
			case 1:
				do {
					opcion2 = entradaMenuSecAdmin();
					switch(opcion2){
						case 1:
							producto = leerProducto();
							TADListaAgregar(listaInventario, (void *)(producto));
						break;
						case 2:
						do{
							printf("1.- Por título 2.- Por código 3.- Regresar\n"); printf("Opción: "); scanf("%d", &opcion3);
							switch(opcion3){
								case 1:
									getchar();
									printf("Ingresa título: "); fgets(nombreB, 50, stdin);
									nombreB[strlen(nombreB)-1] = '\0';
									producto = buscar(listaInventario, (void *)(nombreB), opcion3);
								break;
								case 2:
									printf("Ingresa código: "); scanf("%d", &codigoB);
									producto = buscar(listaInventario, (void*)(&codigoB), opcion3);
								break;
								case 3:
								break;
								default:
									printf("SELECCIÓN INVALIDA\n");
							}
						}while(opcion3 != 3);
						break;
						case 3:
							imprimirLista(listaInventario);
						break;
						case 4:
							 printf("Ingresa el código del producto a eliminar: "); scanf("%d", &codigoB);
							 producto = eliminar(listaInventario, codigoB);
						break;
						case 5:
							if (TADListaVacia(listaMovimientos)){
								printf("La lista esta vacia, no se generó reporte\n");
							} else {
								fp = fopen("Reporte Venta.txt", "w");
								if (fp == NULL){
									printf("ERROR: NO SE PUDO CREAR EL ARCHIVO\n");
								} else {
									printf("REPORTE GENERADO\n");
									imprimirDetallesTicket(fp);
									imprimirListaVentaArchivo(listaMovimientos, fp);
									fprintf(fp, "VENTAS TOTALES DEL DÍA---%.2f", ventasTotales);
								}
								fclose(fp);
							}
						break;
						case 6:
						break;
						default:
							printf("SELECCIÓN INVALIDA\n");
					}
				}while(opcion2 != 6);
			break;
			//Venta
			case 2:
				do{
					printf("1.- Agregar 2.- Actualizar 3.- Desplegar venta 4.- Generar ticket y salir\n"); printf("Opción: "); scanf("%d", &opcion4);
					switch(opcion4){
						case 1:
							printf("Ingresa el código del producto: "); scanf("%d", &codigoB);
							printf("Ingresa la cantidad: "); scanf("%d", &cantidad);
							producto = buscar(listaInventario, (void *)(&codigoB), 2);
							if (producto == NULL){
								printf("ERROR: NO ENCONTRADO\n");
							} else{
								if (listaVenta == NULL)
									listaVenta = TADListaCrear(sizeof(Producto));
								temp = *producto;
								producto->disponibles = producto->disponibles - cantidad;
								temp.disponibles = cantidad;
								printf("CARRITO:\n");
								TADListaAgregar(listaVenta, (void *)(&temp));
								imprimirListaVenta(listaVenta);
								totalVenta = TADListaIterarPrecioTotal(listaVenta, obtenerTotal);
								ventasTotales = ventasTotales + totalVenta;
								printf("TOTAL VENTA: %.2f\n", totalVenta);
								cantidad = 0;
							}
						break;
						case 2:
							if (TADListaVacia(listaVenta)){
								printf("ERROR: LISTA VACIA\n");
							} else {
							do{
								printf("1.- Cantidad 2.-Eliminar del carrito 3.-Salir\n"); printf("Opción: "); scanf("%d", &opcion5);
								switch(opcion5){
								case 1:
									printf("Ingresa el código del producto a modificar: "); scanf("%d", &codigoB);
									producto = buscar(listaVenta, (void *)(&codigoB),2 );
									if (producto == NULL){
										printf("ERROR: NO ENCONTRADO\n");
									} else {
										printf("Ingresa la cantidad que quieras agregar (Ej. +1/-1): "); scanf("%d", &cantidad);
										if (cantidad > 0){
											producto->disponibles = producto->disponibles + cantidad;
											cantidadEliminar = totalVenta;
											totalVenta = TADListaIterarPrecioTotal(listaVenta, obtenerTotal);
											diferenciaVenta = totalVenta - cantidadEliminar;
											ventasTotales = ventasTotales + diferenciaVenta;
											producto = buscar(listaInventario, (void *)(&codigoB), 2);
											producto->disponibles = producto->disponibles - cantidad;
										} else if (cantidad < 0){
											if (cantidad > producto->disponibles){
												printf("ERROR: TRATANDO DE QUITAR MÁS DE LO POSIBLE\n");
											} else {
												producto->disponibles = producto->disponibles + cantidad;	
												cantidadEliminar = totalVenta;
												totalVenta = TADListaIterarPrecioTotal(listaVenta, obtenerTotal);
												diferenciaVenta = totalVenta - cantidadEliminar;
												ventasTotales = ventasTotales + diferenciaVenta;
												producto = buscar(listaInventario, (void *)(&codigoB), 2);
												producto->disponibles = producto->disponibles + cantidad;
											}
										} else {
											printf("ERROR: CANTIDAD NO PUEDE SER 0, DIRIGETE A ELIMINAR PRODUCTO\n");
										}
									printf("ÉXITO: CANTIDAD ACTUALIZADA\n");
									}
								break;
								case 2:
									printf("Ingresa el código del producto a eliminar: "); scanf("%d", &codigoB);
									producto = buscar(listaVenta, (void *)(&codigoB),2 );
									if (producto == NULL){
										printf("ERROR: NO ENCONTRADO\n");
									} else {
										producto = eliminar(listaVenta, codigoB);
										cantidadEliminar = obtenerTotal((void *)producto);
										ventasTotales = ventasTotales - cantidadEliminar;
										if (producto != NULL)
											printf("ÉXITO: BORRADO\n");
									}
								break;
								case 3:
								break;
								default:
									printf("ERROR: ENTRADA\n");
								}
								
							}while(opcion5 != 3);
						}
						break;
						case 3:
						imprimirListaVenta(listaVenta);
						printf("TOTAL VENTA: %.2f\n", totalVenta);
						break;
						case 4:
							if (TADListaVacia(listaVenta)){
								printf("La lista esta vacia, no se generó ticket de compra\n");
							} else {
								fp = fopen("Ticket de compra.txt", "w");
								if (fp == NULL) {
									printf("ERROR: NO SE PUDO CREAR EL ARCHIVO\n");
								} else {
									printf("TICKET GENERADO\n");
									imprimirDetallesTicket(fp);
									imprimirListaVentaArchivo(listaVenta, fp);
									fprintf(fp, "TOTAL---%.2f", totalVenta);
								}
								fclose(fp);
							}
							TADListaIterarCopiarLista(listaVenta, listaMovimientos);
							free(listaVenta);
							listaVenta = NULL;
						break;
						default:
							printf("SELECCION INVÁLIDA\n");
					}
				}while(opcion4 != 4);
			break;
			//Salir
			case 3:
			break;
			default:
				printf("ERROR EN LA SELECCIÓN\n");
		}

	}while(opcion != 3);

	fp = NULL;
	free(listaInventario);
	listaInventario = NULL;
	free(listaVenta);
	listaVenta = NULL;
	free(producto);
	producto = NULL;
	return 0;
}