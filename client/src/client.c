#include "client.h"

int main(void)
{
	/*---------------------------------------------------PARTE 2-------------------------------------------------------------*/
	int conexion;
	char* ip;
	char* puerto;
	char* valor;

	t_log* logger;
	t_config* config;

	logger = iniciar_logger();

    log_info(logger, "Hola soy un log");
	// Usando el logger creado previamente
	// Escribi: "Hola! Soy un log"

	config = iniciar_config();

    ip = config_get_string_value(config, "IP");
    puerto = config_get_string_value(config, "Puerto");
    valor = config_get_string_value(config, "Valor");

	// Usando el config creado previamente
	// Lee las variables de IP, Puerto y Valor

	//Loggear valor de config
    log_info(logger, ip);
    log_info(logger, puerto);
    log_info(logger, valor);

	//leer_consola(logger);


	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo porque lo necesitaremos para lo que sigue.

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	//enviar CLAVE al servidor

	paquete(conexion);

	terminar_programa(conexion, logger, config);

	/*---------------------------------------------------PARTE 5-------------------------------------------------------------*/
	// Proximamente
}

t_log* iniciar_logger(void)
{
	t_log* nuevo_logger = log_create("/home/utn_so/Escritorio/repo_tp0/tp0/log.txt", "tp0", true, LOG_LEVEL_INFO);

	return nuevo_logger;
}

t_config* iniciar_config(void)
{
	t_config* nuevo_config = config_create("/home/utn_so/Escritorio/repo_tp0/tp0/tp0.config");

	return nuevo_config;
}

void leer_consola(t_log* logger)
{
	char* leido;

	//El primero te lo dejo de yapa
	leido = readline(">");

	// Acá la idea es que imprimas por el log lo que recibis de la consola.

    while (strcmp(leido, "\0") != 0) {
        log_info(logger, leido);
        free(leido);
        leido = readline(">");
    }
    free(leido);
}

void paquete(int conexion)
{
    char* clave;
    t_config* config = iniciar_config();
	//Ahora toca lo divertido!

    clave = config_get_string_value(config, "CLAVE");

    enviar_mensaje(clave,conexion);

	char* leido;

    leido = readline(">");
	t_paquete* paquete = crear_paquete();

    int tamanio = ((int)strlen(leido))+1;

    agregar_a_paquete(paquete,leido, tamanio);

    enviar_paquete(paquete,conexion);

    eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log* logger, t_config* config)
{
	//Y por ultimo, para cerrar, hay que liberar lo que utilizamos (conexion, log y config) con las funciones de las commons y del TP mencionadas en el enunciado
}
