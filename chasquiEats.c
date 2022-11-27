#include "csapp.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> /* Nueva librería necesaria para la función srand */

int motorizadosDisponibles = 0;

struct motorizados
{
  int coordenada_x;
  int coordenada_y;
  bool disponible;
  bool trabajando;
  int recorrido;
};

void print_help()
/******************************************************************************/
{
  printf("Este programa que permite hacer pedidos \n"
         "uso:\n"
         "		-h\n"
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

int num_aleatorio(int dimension)
{
  int numAleatoreo = 0;
  numAleatoreo = rand() % dimension;
  return numAleatoreo;
}

// FUNCIÓN QUE EJECUTARÁ CADA HILO
/******************************************************************************/
void *thread(void *vargp)
{
  printf("Hola MUNDO");
}

int main(int argc, char *argv[])
{

  char *file_name_in = NULL;
  int i, x, ysize, max, opt, status = 0;
  int n = get_nprocs() - 1;
  pid_t cpid;
  int dimension = (int)strtol(argv[1], NULL, 10);
  int restaurantes = (int)strtol(argv[2], NULL, 10);
  int intervalo = (int)strtol(argv[3], NULL, 10);
  int motorizados = (int)strtol(argv[4], NULL, 10);
  motorizadosDisponibles = motorizados;
  int kilometros = (int)strtol(argv[5], NULL, 10);
  int arreglo[dimension][dimension];

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
        arreglo[dimension][dimension];
        for (int i = 0; i < dimension; i++)
        {
          for (int j = 0; j < dimension; j++)
          {
            arreglo[i][j] = 0;
          }
        }
        // Ubicación de los restuarantes
        int contador1 = 0;
        while (contador1 != dimension)
        {
          int num1 = 0;
          int num2 = 0;
          srand(time(NULL));
          num1 = num_aleatorio(dimension);
          num2 = num_aleatorio(dimension);
          if (arreglo[num1][num2] == 0)
          {
            arreglo[num1][num2] = 1;
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
          if (arreglo[num1][num2] == 0)
          {
            arreglo[num1][num2] = 2;
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
        }
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

  for (int i = 0; i < dimension; i++)
  {
    for (int j = 0; j < dimension; j++)
    {
      printf("%d", arreglo[i][j]);
    }
    printf("\n");
  }

  return 0;
}