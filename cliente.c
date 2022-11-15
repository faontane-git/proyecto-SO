# include "csapp.h"
# include <stdbool.h>

void print_help()
/******************************************************************************/
{
    printf("Este programa que permite hacer pedidos"
			"uso:\n"
			"		-h\n"
			"Opciones:\n"
			" -h	Ayuda,			Muestra este mensaje\n"
    );
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
    while( token != NULL ) {
        buf[i++] = token;
        token = strtok(NULL, delim);
    }
    free(token);
    buf[i++] = NULL;
    return i;
}


int main(int argc, char *argv[] ){

	char *file_name_in = NULL;
	int i, x, ysize, max, opt, status = 0;
	int n = get_nprocs()-1;
	pid_t cpid;
	
	printf("Aplicación-Cliente.\n");
	print_help();
	
	// Recoge los argumentos enviados por consola
	while ( (opt = getopt (argc, argv, "s:l:t:b:r:h")) != -1){
        switch(opt){
            case 'h':
                print_help();
                return -1;
			case 's':
				 
				file_name_in = optarg;
                break;
			case 'b':
		 
				file_name_in = optarg;
                break;
			case 'r':
 
				file_name_in = optarg;
                break;
			case 't':
			 
				file_name_in = optarg;
                break;
			case 'l':
 
				file_name_in = optarg;
                break;
            case '?':
            default:
				fprintf(stderr, "uso:  n"
								"	-h\n", argv[0]);
				return -1;
            }
    }


    return 0;
}