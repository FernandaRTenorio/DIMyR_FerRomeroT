#include<stdio.h>
#include<conio.h>
#include<stdlib.h>

/*Programa hecho por María Fernanda Romero Tenorio
 Fecha: 23 Sep 2016
 Materia: Diseño de Interfaces, multimedia y Realidad Virtual
 Descripcion: Programa que recibe una recta y un punto y verifica si el punto esta del lado 
 */ 
bool evaluar_punto(float px, float py, float qx, float qy, float rx, float ry){
	printf("\n\nEvaluando el punto...\n");
	float determinante = 0.0f;
	determinante = qx*ry - rx*qy - ( -px*qy + px*ry) + py *rx - py*qx;
	if(determinante >=  0){
		return false;
	}
	else{
		return true;
	}
}

int main(){
	
	bool posicion;
	printf("Programa 1. Este programa indica si un punto dado se encuentra del lado derecho o izquierdo de una recta.");	
	float px, py, qx, qy, rx, ry;
	printf("\nIngrese los puntos que conforman la recta: \n");
	printf("Coordenada x del primer punto:");
	scanf("%f",&px);
	printf("\nCoordenada y del primer punto:");
	scanf("%f",&py);
	printf("\nCoordenada x del segundo punto:");
	scanf("%f",&qx);
	printf("\nCoordenada y del segundo punto:");
	scanf("%f",&qy);
	printf("\nLas coordenadas de la recta son:\n");
	printf("Primer punto: %.2f,%.2f",px,py);
	printf("\nSegundo punto: %.2f,%.2f\n",qx,qy);
	printf("\nIngrese las coordenadas del punto a evaluar:");
	printf("\nrx: ");
	scanf("%f",&rx);
	printf("\nry: ");
	scanf("%f",&ry);
	posicion = evaluar_punto(px,py,qx,qy,rx,ry);
	if(posicion){
		printf("\nEsta del lado derecho");
	}
	else{
		printf("\nEsta del lado izquierdo");
	}
	
}





