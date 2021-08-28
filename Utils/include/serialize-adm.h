/*
 * serialize-adm.h
 *
 *  Created on: 17/2/2017
 *      Author: marcelo
 */

#ifndef SRC_SERIALIZE_ADM_H_
#define SRC_SERIALIZE_ADM_H_
#include "socket-adm.h"
#include <commons/collections/list.h>
#include <commons/string.h>
#include <string.h>

//codigos de handshake por proceso
typedef enum {
	HANDSHAKE_YAMA = 10,
	HANDSHAKE_MASTER = 30,
	HANDSHAKE_FS = 40,
	HANDSHAKE_WORKER = 50,
	HANDSHAKE_DATANODE = 60,
	ERROR_HANDSHAKE = 1
} handshake_t;

typedef enum {
	YAMA_CREAR_JOB = HANDSHAKE_YAMA + 1,
	PARAMETROS_TRANSFORMACION,//YAMA envia los parametros a MASTER para realizar la transformacion.
	SOLICITUD_REDUCCION_GLOBAL,
	SOLICITUD_REDUCCION_LOCAL,
	YAMA_TRANSFORMACION_OK,
	YAMA_TRANSFORMACION_ERROR,
	YAMA_REDUCCION_LOCAL_OK,
	YAMA_REDUCCION_LOCAL_ERROR,
	YAMA_REDUCCION_GLOBAL_OK,
	YAMA_REDUCCION_GLOBAL_ERROR,
	YAMA_ALMACENAMIENTO_FINAL_OK,
	YAMA_ALMACENAMIENTO_FINAL_ERROR,
	YAMA_ALMACENAMIENTO_FINAL,
	YAMA_ID_MASTER,
	YAMA_FINALIZAR_JOB,
	YAMA_SOLICITUD_ARCHIVO,
	DATANODE_LEER_BLOQUE =HANDSHAKE_DATANODE + 1,
	DATANODE_ESCRIBIR_BLOQUE,
	DATANODE_NUEVO_NODO,
	DATANODE_NUEVO_NODO_ACEPTADO,
	DATANODE_NUEVO_NODO_RECHAZADO,
	WORKER_MASTER_TRANSFORMACION=HANDSHAKE_WORKER + 1,
	WORKER_MASTER_REDUCCION_LOCAL,
	WORKER_MASTER_REDUCCION_GLOBAL,
	WORKER_MASTER_ALMACENAMIENTO_FINAL,
	WORKER_MASTER_ERROR_ENVIAR_ARCHIVO,
	WORKER_FS_ENVIAR_ARCHIVO,
	WORKER_APAREO_GLOBAL,
	WORKER_MASTER_ETAPA_OK,
	WORKER_MASTER_ETAPA_FAILED,
	WORKER_APAREO_LEER_LINEA,
	WORKER_APAREO_EOF,
	FS_ALMACENAMIENTO_OK = HANDSHAKE_FS +1,
	FS_ALMACENAMIENTO_ERROR
	} mensaje_t;

typedef struct mensaje_HEADER_t {
	mensaje_t codigoMensaje;
	uint32_t tamanio;
}__attribute__((__packed__)) t_mensaje_HEADER;

typedef struct mensaje_HANDSHAKE_t {
	handshake_t codigoHandshake;
}__attribute__((__packed__)) t_mensaje_HANDSHAKE;

typedef struct pSolicitar_Job_t{
	int32_t largoArchivoTransformar;
	char* nombreArchivoTransformar;
}t_pSolicitar_Job;


//estrutura que envia FS a yama al pedirle datos del archivo
typedef struct{
	char* nombre_archivo;
	int largo_nombre_Archivo;
	int nodo;
	t_list* bloques;
	int puerto;
	char* ip;
	int largo_ip;

}bloques_en_archivo;

//estructura para los bloques, lo maneja FS y Yama
typedef struct{

	int num_bloque_ficticio;
	int num_bloque_real;
	int bytes_ocupados;

}bloque;


// mensaje que indica el nodo y master que ya tienen
// un resultado de una operacion realizada
typedef struct mensaje_resultado_t{
	int id_master;
	int id_nodo;
	int bloque;
	int nombreArchivoLargo;
	char* nombreArchivo; // necesario el nombre del archivo para replanificar
}t_mensaje_resultado_etapa;

/*
 * Estructura de parametros del nodo asignado para la transformacion
 * */
typedef struct pNodo_transformacion_t{
	int32_t nodo_id;
	int32_t nodo_ip_largo;
	char* nodo_ip;
	int32_t nodo_puerto_largo;
	char* nodo_puerto;
	int32_t bloque;
	int32_t bytesOcupados;
	int32_t archivo_resultado_largo;
	char* archivo_resultado;
}t_pNodo_transformacion;

/*
 * Estructura de parametros del nodo asignado para la reduccion local
 * */
typedef struct pNodo_reduccion_local_t{
	int32_t nodo_id;
	int32_t nodo_ip_largo;
	char* nodo_ip;
	int32_t nodo_puerto_largo;
	char* nodo_puerto;
	int32_t archivos_reduccion_cantidad;
	t_list* archivos_reduccion;// lista de t_archivo_reducir_local
	int32_t destino_reduccion_largo;
	char* destino_reduccion;
}t_pNodo_reduccion_local;

/*
 * Estructura de parametros del nodo asignado para la reduccion global
 * */
typedef struct pNodo_reduccion_global_t{
	int32_t nodo_id;
	int32_t nodo_ip_largo;
	char* nodo_ip;
	int32_t nodo_puerto_largo;
	char* nodo_puerto;
	int32_t archivos_reduccion_cantidad;
	t_list* archivos_reduccion;//Lista de t_archivo_reducir_global
	int32_t destino_reduccion_largo;
	char* destino_reduccion;
}t_pNodo_reduccion_global;

/*
 * Estructura de parametros del nodo asignado para el almacenamiento final.
 * */
typedef struct pNodo_almacenamiento_final_t{
	int32_t nodo_id;
	int32_t nodo_ip_largo;
	char* nodo_ip;
	int32_t nodo_puerto_largo;
	char* nodo_puerto;
	int32_t archivo_final_largo;
	char* archivo_final;
}t_pNodo_almacenamiento_final;

/*
 *Mensaje a enviar de Master a worker para la tansformacion.
 * */
typedef struct msj_transformacion_worker_t{
	int32_t bloqueATransformar;
	int32_t bloqueATransformar_tamanio;
	int32_t scripTransformador_largo;
	char* scriptTransformador;
	int32_t archivo_destino_transformacion_largo;
	char* archivo_destino_transformacion;
}t_msj_transformacion_worker;

typedef struct archivo_reducir_local_t{
	int32_t nombreArchivoLargo;
	char* nombreArchivo;
}t_archivo_reducir_local;

/*
 *Mensaje a enviar de Master a worker para la reduccion local.
 * */
typedef struct msj_reduccion_local_worker_t{
	int32_t archivos_reduccion_cantidad;
	t_list* archivos_reduccion;// lista de t_archivo_reducir_local
	int32_t scriptReduccion_largo;
	char* scriptReduccion;
	int32_t destino_reduccion_largo;
	char* destino_reduccion;
}t_msj_reduccion_local_worker;

/*
 *Archivo a reducir para enviar de Master a worker para la reduccion global.
 * */
typedef struct archivo_reducir_global_t{
	int32_t nombreArchivoLargo;
	char* nombreArchivo;
	int32_t nodo_ip_largo;
	char* nodo_ip;
	int32_t nodo_puerto_largo;
	char* nodo_puerto;
}t_archivo_reducir_global;

/*
 *Mensaje a enviar de Master a worker para la reduccion global.
 * */
typedef struct msj_reduccion_global_worker_t{
	int32_t archivos_reduccion_cantidad;
	t_list* archivos_reduccion;//Lista de t_archivo_reducir_global
	int32_t scriptReduccion_largo;
	char* scriptReduccion;
	int32_t destino_reduccion_largo;
	char* destino_reduccion;
}t_msj_reduccion_global_worker;

/*
 *Mensaje a enviar de Master a worker para almacenamiento final.
 * */
typedef struct msj_almacenamiento_final_worker_t{
	int32_t archivo_almacenamiento_final_largo;
	char* archivo_almacenamiento_final;
	int32_t archivo_reduccion_global_largo;
	char* archivo_reduccion_global;
}t_msj_almacenamiento_final_worker;


/*
 *Mensaje a enviar de Worker a Filesystem para almacenamiento final.
 * */
typedef struct msj_almacenamiento_final_fs_t{
	int32_t path_archivo_largo;
	char* path_archivo;
	int32_t contenido_archivo_largo;
	char* contenido_archivo;
}t_msj_almacenamiento_final_fs;

/*
 *Mensaje a enviar entre FS y Datanode para agregar un nuevo nodo al sistema.
 * */
typedef struct {
	int32_t datanode_id;
	int32_t ip_nodo_size;
	char* ip_nodo;
	int32_t puerto_worker;
	uint32_t bloques_totales;
}t_mensaje_nuevo_nodo;

/*
 *Mensaje a enviar entre FS y Datanode para escribir y leer bloques.
 * */
typedef struct {
	uint32_t bloque_id;
	uint32_t buff_bloque_size;
	char* buff_bloque;
}t_mensaje_leer_escribir_nodo;

 /*
 * serializeHandshake:
 * Serializa una estructura del tipo t_mensaje_HANDSHAKE;
 * */
char* serializeHandshake(t_mensaje_HANDSHAKE* mensaje_handshake, int* largo);

/*
 * deserializeHandshake:
 * Deserializa una estructura del tipo t_mensaje_HANDSHAKE;
 * */
t_mensaje_HANDSHAKE* deserializeHandshake(char* mensaje_handshake);

/*
 * recibir_handshake:
 * recibe un mensaje del tipo handshake
 * */
int recibir_handshake(t_mensaje_HANDSHAKE *msjeHandshake, int sock_fd);

/*
 * enviar_handshake:
 * envia un mensaje del tipo handshake
 * */
int enviar_handshake(t_mensaje_HANDSHAKE *msjeHandshake, int sock_fd);

/*
 * serialize_HEADER:
 * Serializa una estructura del tipo t_mensaje_HEADER;
 * */
char* serialize_HEADER(t_mensaje_HEADER* mensaje_header, int* largo);

/*
 * deserialize_HEADER:
 * Deserializa una estructura del tipo t_mensaje_HEADER;
 * */
t_mensaje_HEADER* deserialize_HEADER(char* mensaje_header);

int recibir_mensaje_header(t_mensaje_HEADER *msjeHeader, int sock_fd);

/*
 * enviar_mensaje_header:
 * envia una estructura del tipo header al sock_fd pasado por parametro
 * */
int enviar_mensaje_header(t_mensaje_HEADER *msjeHeader, int sock_fd);

t_mensaje_leer_escribir_nodo* deserializarLeerEscribirNodo_COPIA(char* buffer);
char* serializarLeerEscribirNodo_COPIA(t_mensaje_leer_escribir_nodo* msj_almacenamiento_final_worker, int* largo);
t_mensaje_leer_escribir_nodo* deserializarLeer(char* buffer);
char* serializarLeer(t_mensaje_leer_escribir_nodo* msj_almacenamiento_final_worker, int* largo);
#endif /* SRC_SERIALIZE_ADM_H_ */

