/*
 * serialize-adm.c
 *
 *  Created on: 17/2/2017
 *      Author: utnso
 */
#include "serialize-adm.h"

char* serializeHandshake(t_mensaje_HANDSHAKE* mensaje_handshake, int* largo) {
	char *empaquetado = malloc(sizeof(typeof(mensaje_handshake->codigoHandshake)));
	memset(empaquetado,0,sizeof(typeof(mensaje_handshake->codigoHandshake)));
	int offset = 0, tmp_size = 0;
	memcpy(empaquetado + offset, &mensaje_handshake->codigoHandshake, tmp_size = sizeof(typeof(mensaje_handshake->codigoHandshake)));
	offset += tmp_size;
	*largo = offset;
	return empaquetado;
}

t_mensaje_HANDSHAKE* deserializeHandshake(char* mensaje_handshake){
	t_mensaje_HANDSHAKE* msjeHandshake = malloc(sizeof(t_mensaje_HANDSHAKE));
	int offset = 0, tmp_len = 0;
	memcpy(&msjeHandshake->codigoHandshake, mensaje_handshake + offset, tmp_len = sizeof(typeof(msjeHandshake->codigoHandshake)));
	offset += tmp_len;
	return msjeHandshake;
}

int recibir_handshake(t_mensaje_HANDSHAKE *msjeHandshake,int sock_fd){
	t_mensaje_HANDSHAKE *auxMsje;
	int rta;
	int buffer_size = sizeof(typeof(msjeHandshake->codigoHandshake));
	char* buf = malloc(buffer_size);
	if(!recvall(sock_fd, buf, buffer_size)){
		rta = 0;
	}else{
		auxMsje=deserializeHandshake(buf);
		*msjeHandshake=*auxMsje;
		free(auxMsje);
		rta = 1;
	}
	free(buf);
	return rta;
}

int enviar_handshake(t_mensaje_HANDSHAKE *msjeHandshake,int sock_fd){
	int largo=0, rta;
	char *buf=serializeHandshake(msjeHandshake,&largo);
	rta = sendall(sock_fd, buf, largo);
	free(buf);
	return rta;
}

char* serialize_HEADER(t_mensaje_HEADER* mensaje_header, int* largo) {
	char *empaquetado = malloc(sizeof(typeof(mensaje_header->tamanio))+sizeof(typeof(mensaje_header->codigoMensaje)));
	memset(empaquetado,0,sizeof(typeof(mensaje_header->tamanio))+sizeof(typeof(mensaje_header->codigoMensaje)));
	int offset = 0, tmp_size = 0;
	memcpy(empaquetado + offset, &mensaje_header->codigoMensaje, tmp_size = sizeof(typeof(mensaje_header->codigoMensaje)));
	offset += tmp_size;
	memcpy(empaquetado + offset, &mensaje_header->tamanio, tmp_size = sizeof(typeof(mensaje_header->tamanio)));
	offset += tmp_size;
	*largo = offset;
	return empaquetado;
}

t_mensaje_HEADER* deserialize_HEADER(char* mensaje_handshake){
	t_mensaje_HEADER* msje_header = malloc(sizeof(t_mensaje_HEADER));
	int offset = 0, tmp_len = 0;
	memcpy(&msje_header->codigoMensaje, mensaje_handshake + offset, tmp_len = sizeof(typeof(msje_header->codigoMensaje)));
	offset += tmp_len;
	memcpy(&msje_header->tamanio, mensaje_handshake + offset, tmp_len = sizeof(typeof(msje_header->tamanio)));
	return msje_header;
}

int recibir_mensaje_header(t_mensaje_HEADER *msjeHeader,int sock_fd){
	int rta;
	t_mensaje_HEADER *auxMsje;
	int buffer_size = sizeof(t_mensaje_HEADER);
	char* buf = malloc(buffer_size);
	if(!recvall(sock_fd, buf, buffer_size)){
		rta =  0;
	}else{
		auxMsje=deserialize_HEADER(buf);
		*msjeHeader=*auxMsje;
		free(auxMsje);
		rta = 1;
	}
	free(buf);
	return rta;
}

int enviar_mensaje_header(t_mensaje_HEADER *msjeHeader,int sock_fd){
	int largo=0, rta;
	char *buf=serialize_HEADER(msjeHeader,&largo);
	rta = sendall(sock_fd, buf, largo);
	free(buf);
	return rta;
}

t_mensaje_resultado_etapa* deserializarResultado(char * buffer){
	t_mensaje_resultado_etapa* mnsjeResultado = malloc(sizeof(t_mensaje_resultado_etapa));
	int offset = 0, tmp_len = 0;
	memcpy(&mnsjeResultado->id_nodo, buffer + offset, tmp_len = sizeof(typeof(mnsjeResultado->id_nodo)));
	offset += tmp_len;
	memcpy(&mnsjeResultado->id_master, buffer + offset, tmp_len = sizeof(typeof(mnsjeResultado->id_master)));
	offset += tmp_len;
	memcpy(&mnsjeResultado->bloque, buffer + offset, tmp_len = sizeof(typeof(mnsjeResultado->bloque)));
	offset += tmp_len;
	memcpy(&mnsjeResultado->nombreArchivoLargo, buffer + offset, tmp_len = sizeof(typeof(mnsjeResultado->nombreArchivoLargo)));
	offset += tmp_len;
	if(mnsjeResultado->nombreArchivoLargo > 0){
		mnsjeResultado->nombreArchivo = malloc(mnsjeResultado->nombreArchivoLargo +1);
		memcpy(mnsjeResultado->nombreArchivo, buffer + offset, tmp_len = mnsjeResultado->nombreArchivoLargo);
		mnsjeResultado->nombreArchivo[mnsjeResultado->nombreArchivoLargo] = '\0';
	}

	return mnsjeResultado;
}


t_mensaje_leer_escribir_nodo* deserializarLeerEscribirNodo_COPIA(char* buffer){
	t_mensaje_leer_escribir_nodo* desempaquetado = malloc(sizeof(t_mensaje_leer_escribir_nodo));
	int offset = 0, tmp_len = 0;

	memcpy(&desempaquetado->bloque_id, buffer + offset, tmp_len = sizeof(typeof(desempaquetado->bloque_id)));
	offset += tmp_len;
	memcpy(&desempaquetado->buff_bloque_size, buffer + offset, tmp_len = sizeof(typeof(desempaquetado->buff_bloque_size)));
	offset += tmp_len;
	desempaquetado->buff_bloque = malloc(desempaquetado->buff_bloque_size);
	memcpy(desempaquetado->buff_bloque, buffer + offset, tmp_len = desempaquetado->buff_bloque_size);
	return desempaquetado;
}

t_mensaje_leer_escribir_nodo* deserializarLeer(char* buffer){
	t_mensaje_leer_escribir_nodo* desempaquetado = malloc(sizeof(t_mensaje_leer_escribir_nodo));
	int offset = 0, tmp_len = 0;

	memcpy(&desempaquetado->bloque_id, buffer + offset, tmp_len = sizeof(typeof(desempaquetado->bloque_id)));
	offset += tmp_len;
	memcpy(&desempaquetado->buff_bloque_size, buffer + offset, tmp_len = sizeof(typeof(desempaquetado->buff_bloque_size)));
	offset += tmp_len;
	return desempaquetado;
}


char* serializarLeerEscribirNodo_COPIA(t_mensaje_leer_escribir_nodo* msj_almacenamiento_final_worker, int* largo){
	char* empaquetado = malloc(sizeof(typeof(msj_almacenamiento_final_worker->bloque_id)) +sizeof(typeof(msj_almacenamiento_final_worker->buff_bloque_size))
			+ (sizeof(typeof(char))*msj_almacenamiento_final_worker->buff_bloque_size));

	int offset = 0, tmp_size = 0;
	//memset(empaquetado + offset, 0, sizeof(typeof(msj_almacenamiento_final_worker->bloque_id)));
	tmp_size =  sizeof(msj_almacenamiento_final_worker->bloque_id);
	memcpy(empaquetado + offset, &(msj_almacenamiento_final_worker->bloque_id),tmp_size);
	offset += tmp_size;

	//memset(empaquetado + offset, 0, sizeof(typeof(msj_almacenamiento_final_worker->buff_bloque_size)));
	tmp_size =  sizeof(msj_almacenamiento_final_worker->buff_bloque_size);
	memcpy(empaquetado + offset, &(msj_almacenamiento_final_worker->buff_bloque_size),tmp_size );
	offset += tmp_size;

	tmp_size =  msj_almacenamiento_final_worker->buff_bloque_size;
	memset(empaquetado + offset, 0, msj_almacenamiento_final_worker->buff_bloque_size);
	memcpy(empaquetado + offset, msj_almacenamiento_final_worker->buff_bloque,tmp_size);
	offset += tmp_size;

	*largo = offset;
	return empaquetado;
}

char* serializarLeer(t_mensaje_leer_escribir_nodo* msj_almacenamiento_final_worker, int* largo){
	char* empaquetado = malloc(sizeof(typeof(msj_almacenamiento_final_worker->bloque_id)) +sizeof(typeof(msj_almacenamiento_final_worker->buff_bloque_size)));

	int offset = 0, tmp_size = 0;
	//memset(empaquetado + offset, 0, sizeof(typeof(msj_almacenamiento_final_worker->bloque_id)));
	tmp_size =  sizeof(msj_almacenamiento_final_worker->bloque_id);
	memcpy(empaquetado + offset, &(msj_almacenamiento_final_worker->bloque_id),tmp_size);
	offset += tmp_size;

	//memset(empaquetado + offset, 0, sizeof(typeof(msj_almacenamiento_final_worker->buff_bloque_size)));
	tmp_size =  sizeof(msj_almacenamiento_final_worker->buff_bloque_size);
	memcpy(empaquetado + offset, &(msj_almacenamiento_final_worker->buff_bloque_size),tmp_size );
	offset += tmp_size;

	*largo = offset;
	return empaquetado;
}
