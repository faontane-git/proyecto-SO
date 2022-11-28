#include "csapp.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> /* Nueva librería necesaria para la función srand */
#include <math.h>

int motorizadosDisponibles = 0;
int dimension = 0;
int *arreglo;

struct recorrido
{
  int ejeX;
  int ejeY;
  int distancia_recorrida;
};

void print_help()
/******************************************************************************/
{
  printf("Este programa que permite crear y monitoriar los pedidos de una emperesa\n"
         "uso:\n"
         "Primero Compile el programa usando make\n"
         "Opciones:\n"
         " -h	Ayuda,			Muestra este mensaje\n");
}

// Para usar esta función para calcular la probabilidad que se necesite
bool probabilidad(int pProbabilidad)
{
  float x = rand() % (101) / 100.0f;
  if (x <= (pProbabilidad / 100.0f))
  {
    return true;
  }
  else
  {
    return false;
  }
}

void imprimirMatriz(int *p, int dimension)
{
  for (int i = 0; i < dimension; i++)
  {
    for (int j = 0; j < dimension; j++)
    {
      printf("%d", *(&arreglo + i * dimension + j));
    }
    printf("\n");
  }
}

int num_aleatorio(int dimension)
{
  int numAleatoreo = 0;
  numAleatoreo = rand() % dimension;
  return numAleatoreo;
}

int *realizar_matrix(int dimension)
{
  int matrix[dimension][dimension];
  for (int i = 0; i < dimension; i++)
  {
    for (int j = 0; j < dimension; j++)
    {
      matrix[i][j] = 0;
    }
  }

  return matrix;
}

double calcularDistancia(int x1, int y1, int x2, int y2)
{
  /*
      Aplicar la fórmula que dice:
      distancia = raiz_cuadrada_de(elevar_al_cuadrado(x1-x2) + elevar_al_cuadrado(y1-y2))
      Nota: no importa el orden de los puntos ni si la distancia al restar es negativa
  */
  return sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
}

// FUNCIÓN QUE EJECUTARÁ CADA HILO
/******************************************************************************/
void *thread(void *vargp)
{
  // Ubicación del cliente
  int contador3 = 0;
  while (contador3 != 1)
  {
    int num1 = 0;
    int num2 = 0;
    srand(time(NULL));
    num1 = num_aleatorio(dimension);
    num2 = num_aleatorio(dimension);
    if (*(&arreglo + num1 * dimension + num2) == 0)
    {
      *(&arreglo + num1 * dimension + num2) = 3;
      contador3 += 1;
    }
    else
    {
      continue;
    }
  }

  // Ofrecer Dinero cliente->Motorizado
  float x = rand() % (101);
}

void seleccion_motorizado(int distancia_z)
{
  for (int i = 0; i < dimension; i++)
  {
    for (int j = 0; j < dimension; j++)
    {
      int objeto1 = *(&arreglo + i * dimension + j);
      if (objeto1 == 2)
      {
        for (int k = 0; k < dimension; k++)
        {
          for (int l = 0; l < dimension; l++)
          {
            int objeto2 = *(&arreglo + i * dimension + j);
            if(objeto2==1){
              double resultado=calcularDistancia(j,i,l,k);
              if(resultado<=distancia_z){
                struct recorrido motociclista;
                motociclista.distancia_recorrida=resultado;
                motociclista.ejeX=j;
                motociclista.ejeY=i;
              }
            }
          }
        }
      }
    }
  }
}

int main(int argc, char *argv[])
{

  char *file_name_in = NULL;
  int i, x, ysize, max, opt, status = 0;
  int n = get_nprocs() - 1;
  pid_t cpid;
  dimension = (int)strtol(argv[1], NULL, 10);
  int restaurantes = (int)strtol(argv[2], NULL, 10);
  int intervalo = (int)strtol(argv[3], NULL, 10);
  int motorizados = (int)strtol(argv[4], NULL, 10);
  motorizadosDisponibles = motorizados;
  int kilometros = (int)strtol(argv[5], NULL, 10);

  if (argc != 6)
  {
    printf("¡Error de Ingreso!\n");
    print_help();
    exit(1);
  }
  else
  {
    // Creación de la grilaa (0/1/2) donde 0 significa vacío. 1 la presencia de un
    // restaurante en esa posición, 2 la presencia de una moto en esa
    // posición y 3 la presencia de un cliente, incialzaremos la matrix en 0.
    if (dimension % 2 != 0)
    {
      if (dimension > 1)
      {
        // Mensaje Principal
        printf("Grilla de %dx%d, %d restaurantes, intervalo %d milisengundos, %d morotizados, %d kilómetros de distancia\n", dimension, dimension, restaurantes, intervalo, motorizados, kilometros);

        // Creación de la Matrix

        arreglo = realizar_matrix(dimension);
        // Ubicación de los restuarantes

        int contador1 = 0;
        while (contador1 != dimension)
        {
          int num1 = 0;
          int num2 = 0;
          srand(time(NULL));
          num1 = num_aleatorio(dimension);
          num2 = num_aleatorio(dimension);
          if (*(&arreglo + num1 * dimension + num2) == 0)
          {
            *(&arreglo + num1 * dimension + num2) = 1;
            contador1 += 1;
          }
          else
          {
            continue;
          }
        }

        // Ubicación de los motorizados

        int contador2 = 0;
        while (contador2 != motorizados)
        {
          int num1 = 0;
          int num2 = 0;
          srand(time(NULL));
          num1 = num_aleatorio(dimension);
          num2 = num_aleatorio(dimension);
          if (*(&arreglo + num1 * dimension + num2) == 0)
          {
            *(&arreglo + num1 * dimension + num2) = 2;
            contador2 += 1;
          }
          else
          {
            continue;
          }
        }

        // Ubicación de los clientes
        while (motorizadosDisponibles > 0)
        {
          sleep(intervalo / 1000);
          pthread_t tid;
          if (probabilidad(50) == 1)
          {
            Pthread_create(&tid, NULL, thread, NULL);
          }
          motorizadosDisponibles--;
        }

        imprimirMatriz(&arreglo, dimension);
      }
      else
      {

        printf("No se puede crear una matriz de valor menor a 1");
        exit(1);
      }
    }
    else
    {
      printf("No se puede crear una matriz con un valor par."
             "\n");
      exit(1);
    }
  }

  return 0;
}