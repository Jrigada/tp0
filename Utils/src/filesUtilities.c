/*
 * filesUtilities.c
 *
 *  Created on: 9/9/2017
 *      Author: utnso
 */
#include "filesUtilities.h"


char* map_file(char* pathfile,t_log *logger){
	int fd_file;
	struct stat stat_file;
	char* result=NULL;
	log_trace(logger,"filesUtilities->map_file - init");
	fd_file = open(pathfile, O_RDWR);
	if(fd_file==-1){
		log_error(logger,"filesUtilities->map_file - Error al abrir el archivo %s",pathfile);
		log_trace(logger,"filesUtilities->map_file - end");
		return result;
	}else{
		log_trace(logger,"filesUtilities->map_file - file %s opened successfully",pathfile);
		if(fstat(fd_file, &stat_file)==-1){
			log_error(logger,"filesUtilities->map_file - Error al realizar stat del archivo %s",pathfile);
			log_trace(logger,"filesUtilities->map_file - end");
			return result;
		}
		result = mmap((caddr_t)0, stat_file.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd_file,0);
		if(result==MAP_FAILED){
			fprintf(stderr, "mmap failed: %s\n", strerror(errno));
			log_error(logger,"filesUtilities->map_file - Error al mapear el archivo %s",pathfile);
			result=NULL;
			log_trace(logger,"filesUtilities->map_file - end");
			return result;
		}else{
			close(fd_file);
			log_trace(logger,"filesUtilities->map_file - file %s closed successfully",pathfile);
		}

	}
	log_trace(logger,"filesUtilities->map_file - end");
	return result;
}

char* get_file_block(char* filemap,int blocknumber,int blocksize,int readsize,t_log * logger){
	char* result = malloc(blocksize);
	int offset_file=blocknumber*blocksize;
	log_trace(logger,"filesUtilities->get_file_block - init");
	memcpy(result,filemap+offset_file,readsize);
	log_trace(logger,"filesUtilities->get_file_block - end");
	return result;
}

void write_file_block(char* filemap,int blocknumber,int blocksize,char* data,int data_size,t_log * logger){
	int offset_file=blocknumber*blocksize;
	log_trace(logger,"filesUtilities->write_file_block - init");
	log_trace(logger,"filesUtilities->write_file_block - blocknumber: %d",blocknumber);
	log_trace(logger,"filesUtilities->write_file_block - blocksize: %d",blocksize);
	log_trace(logger,"filesUtilities->write_file_block - sizedata: %d",data_size);
	memcpy(filemap+offset_file,data,data_size);
	log_trace(logger,"filesUtilities->write_file_block - end");
	return;
}
