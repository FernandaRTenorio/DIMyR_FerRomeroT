#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

/*Programa hecho por María Fernanda Romero Tenorio
 Fecha: 23 Sep 2016
 Materia: Diseño de Interfaces, multimedia y Realidad Virtual
 Descripcion: Programa que revisa si hay interseccion entre dos rectas dadas, y en qué punto intersectan
 */ 
bool evaluar_punto(float px, float py, float qx, float qy, float rx, float ry){
	//printf("\n\nEvaluando el punto...\n");
	float determinante = 0.0f;
	determinante = qx*ry - rx*qy - ( -px*qy + px*ry) + py *rx - py*qx;
	if(determinante >=  0){
		return false;
	}
	else{
		return true;
	}
}

bool evaluar_interseccion(float px, float py, float qx, float qy, float rx, float ry,float sx, float sy){
	bool punto_rxry;
	bool primer_punto = evaluar_punto(px,py,qx,qy,rx,ry);
	if(primer_punto){
		//printf("el primer punto esta del lado derecho");
		primer_punto = evaluar_punto(px,py,qx,qy,sx,sy);
		if(!primer_punto){
			printf("Las lineas se intersectan");
		  return true;
		}else{
			printf("No hay interseccion entre lineas");
			return false;
		}
	}else{
		//printf("el primer punto esta del lado izquierdo");
		primer_punto = evaluar_punto(px,py,qx,qy,sx,sy);
		if(primer_punto){
			printf("Las lineas se intersectan");
			return true;
		}else{
			printf("No hay interseccion entre lineas");
			return false;
		}
	}
	
}

void obtenerInterseccion(float px, float py, float qx, float qy, float rx, float ry, float sx, float sy){
	bool interseccion = false;
	float intx;
	float inty;
	interseccion = evaluar_interseccion(px,  py, qx,qy,  rx,  ry, sx, sy);
	if(interseccion){
		intx = ( (px*qy-py *qx)*(rx - sx)-(px - qx)*(rx*sy - ry*sx ))/((px - qx)*(ry - sy)-(py - qy)*(rx - sx));
		printf("\n\nEl punto de interseccion en x es: %.2f",intx);
		inty = ((px*qy-py*qx)*(ry-sy)-(py-qy)*(rx*sy-ry*sx))/((px-qx)*(ry-sy)-(py-qy)*(rx-sx));
		printf("\n\nEl punto de interseccion en y es: %.2f",inty);
	}else{
		printf("\n\nNo hay punto de interseccion");
	}
}

int main(){
	
	bool posicion;
	printf("Programa 1. Este programa indica si un punto dado se encuentra del lado derecho o izquierdo de una recta.");	
	float px, py, qx, qy, rx, ry,sx,sy;
	
	printf("\nIngrese los puntos que conforman la recta 1: \n");
	printf("Coordenada x del primer punto:");
	scanf("%f",&px);
	printf("\nCoordenada y del primer punto:");
	scanf("%f",&py);
	printf("\nCoordenada x del segundo punto:");
	scanf("%f",&qx);
	printf("\nCoordenada y del segundo punto:");
	scanf("%f",&qy);
	
	printf("\nLas coordenadas de la recta 1 son:\n");
	printf("Primer punto: %.2f,%.2f",px,py);
	printf("\nSegundo punto: %.2f,%.2f\n",qx,qy);
	
	printf("\nIngrese los puntos que conforman la recta 2: \n");
	printf("Coordenada x del primer punto:");
	scanf("%f",&rx);
	printf("\nCoordenada y del primer punto:");
	scanf("%f",&ry);
	printf("\nCoordenada x del segundo punto:");
	scanf("%f",&sx);
	printf("\nCoordenada y del segundo punto:");
	scanf("%f",&sy);
	printf("\nLas coordenadas de la recta 2 son:\n");
	printf("Primer punto: %.2f,%.2f",rx,ry);
	printf("\nSegundo punto: %.2f,%.2f\n",sx,sy);
	
	obtenerInterseccion(px,py,qx,qy,rx,ry,sx,sy);
	
	
}

