#include "csapp.h"
#include <stdbool.h>

void print_help()
/******************************************************************************/
{
  printf("Este programa que permite hacer pedidos \n"
         "uso:\n"
         "		-h\n"
         "Opciones:\n"
         " -h	Ayuda,			Muestra este mensaje\n");
}

// FUNCION QUE SEPARA EL STRING EN TOKENS PARA PODER USARLOS RESPECTIVAMENTE
/******************************************************************************/
int separar_tokens(char *linea, char *delim, char *buf[])
/******************************************************************************/
{
  char *token;
  int i = 0;
  /* obtiene el primer token */
  token = strtok(linea, delim);

  /* recorre todos los tokens */
  while (token != NULL)
  {
    buf[i++] = token;
    token = strtok(NULL, delim);
  }
  free(token);
  buf[i++] = NULL;
  return i;
}

int main(int argc, char *argv[])
{
  char *file_name_in = NULL;
  int i, x, ysize, max, opt, status = 0;
  int n = get_nprocs() - 1;
  pid_t cpid;
  int dimension = 0;
  int arreglo[dimension][dimension];

  if (argc != 6)
  {
    printf("No hagas wuebadas ingresa bien\n");
    exit(1);
  }
  else
  {
    // Creación del arreglo binario (1/0) donde 1 significa la presecia de un restaurante en esa posición
    // y 0 la no presencia del restaurante en esa posición, incialzaremos la matrix en 0.
    dimension = (int)strtol(argv[1], NULL, 10);
    if (dimension % 2 != 0)
    {
      for (int i = 0; i < dimension; i++)
      {
        for (int j = 0; j < dimension; j++)
        {
          arreglo[i][j] = 0;
        }
      }
    }else{
      printf("No se puede crear una matriz con un valor par. No hagas wuebadas \n");
      exit(1);
    }
  }

  for (int i = 0; i < dimension; i++)
  {
    for (int j = 0; j < dimension; j++)
    {
      printf("%d", arreglo[i][j]);
    }
    printf("\n ");
  }

  return 0;
}