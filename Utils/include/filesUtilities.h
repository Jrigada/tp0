/*
 * files.h
 *
 *  Created on: 9/9/2017
 *      Author: utnso
 */

#ifndef SRC_FILESUTILITIES_H_
#define SRC_FILESUTILITIES_H_

#include <commons/log.h>
#include <commons/collections/list.h>
#include <pthread.h>
#include <commons/config.h>
#include <commons/string.h>
#include <commons/bitarray.h>
#include <stdlib.h>
#include <stdio.h>
#include <semaphore.h>
#include <ctype.h>
#include <string.h>
#include <ftw.h>
#include <unistd.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <libgen.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

/**
 * @NAME: map_file
 * @DESC: mapea en memoria el archivo pasado por parametro,
 * el tamano lo obtiene de la syscall stat
 * @PARAMS:
 * pathfile -> ruta del archivo a mapear
 * logger -> instancia del logger de la libreria commmons
 * @RETURN:
 * char* retorna un puntero que representa el archivo mapeado,
 * en caso de error retorna NULL
 */
char* map_file(char* pathfile,t_log *logger);


/**
 * @NAME: get_file_block
 * @DESC: obtiene un bloque del archivo mapeado pasado por parametro
 * @PARAMS:
 * filemap -> puntero que representa el archivo mapeado en memoria
 * blocknumber -> numero de bloque a leer
 * blocksize -> tamano del bloque en bytes.
 * logger -> instancia del logger de la libreria commmons
 * @RETURN:
 * retorna un puntero con el contenido leido.
 * No tiene valores para retornos de error, ya que memcpy no los tiene.
 */
char* get_file_block(char* filemap,int blocknumber,int blocksize,int readsize, t_log * logger);

/**
 * @NAME: write_file_block
 * @DESC: escribe el contenido pasado por parametro
 * en el bloque del archivo mapeado pasado por parametro
 * @PARAMS:
 * filemap -> puntero que representa el archivo mapeado en memoria
 * blocknumber -> numero de bloque a leer
 * blocksize -> tamano del bloque en bytes.
 * data -> contenido a escribir en el bloque.
 * logger -> instancia del logger de la libreria commmons
 * @RETURN:
 * No retorna ningun valor.
 * No tiene valores para retornos de error, ya que memcpy no los tiene.
 *
 */
void write_file_block(char* filemap,int blocknumber,int blocksize,char* data,int data_size,t_log * logger);

#endif /* SRC_FILESUTILITIES_H_ */
