/*
 * DefinicionesPrivadas.h
 */

#ifndef COMUN_DEFINICIONESPRIVADAS_H_
#define COMUN_DEFINICIONESPRIVADAS_H_

#define TIEMPO_ESPERA_EN_MICROSEGUNDOS 100000

// ruta de la carpeta (relativa con respecto a la carpeta actual) de donde se
// van a leer los archivos que contienen los escenarios y niveles
#define RUTA_DIRECTORIO_ESCENARIOS "./escenarios"

// extensión que se va a usar por defecto para los archivos con los escenarios
// y niveles
#define EXTENSION_ESCENARIOS ".yaml"

typedef enum {
	todos = 0, servidor = 1, emisor = 2, no_es_necesario = 3
} destinatarios_posibles;

typedef enum {
	solicitar_mover = 0,
	solicitar_saltar = 1,
	solicitar_retroceso = 2,
	solicitar_arma = 3,
	solicitar_atacar = 4,
	mover_punteria_reenviar = 5,
	descargar_arma_reenviar = 6,
	direccionar_reenviar = 7
} comandos_partida_posibles;

typedef enum {
	mover_gusano = 0,
	cargar_arma = 1,
	descargar_arma = 2,
	mover_punteria = 3,
	direccionar_gusano = 4,
	atacar = 5,
	actualizar_vida = 6,
	iniciar_partida = 7,
	finalizar_partida = 8,
	error = 9,
	teletransportar_gusano = 10,
	crear_bala = 11,
	mover_bala = 12,
	destruir_bala = 13,
	impactar_bala = 14,
	iniciar_turno = 15,
	finalizar_turno = 16,
	notificar_ganador = 17,
	notificacion = 18,
	volar_gusano = 19,
	tiempo_restante = 20,
	informar_viento = 21
} cmd_partida_en_juego;

typedef enum {
	crear_viga = 0, crear_gusano = 1, fin_escenario = 2
} cmd_cargando_escenario;

typedef enum {
	crear_partida = 0,
	solicitar_todas_las_partidas = 1,
	solicitar_partidas_no_iniciadas = 2,
	unirse_a_partida = 3,
	solicitar_escenarios = 4
} comandos_logueo_posibles;

typedef enum {
	creando = 0, cargando_escenario = 1, en_curso = 2, finalizada = 3
} estados_posibles_partida;

typedef enum {
	notificar_id_partida = 0,
	lista_partidas_no_iniciadas = 1,
	lista_escenarios = 2,
	notificar_id_jugador = 3,
	notificacion_recibida = 4
} respuestas_logueo_T;

#define CANTIDAD_MINIMA_DE_JUGADORES_PERMITIDA 1
#define ID_PARTIDA_MINIMO 1
#define ID_JUGADOR_MINIMO 1
#define ID_GUSANO_MINIMO 1

#define ID_ESCENARIO_MINIMO 1

#define COMANDO_INVALIDO ""
#define ID_JUGADOR_INVALIDO -1
#define GUSANO_INVALIDO -1
#define ARMA_INVALIDA -2
#define DIRECCION_INVALIDA -1
#define INCLINACION_INVALIDA -1
#define CANTIDAD_JUGADORES_INVALIDA 0
#define ID_ESCENARIO_INVALIDO -1
#define NOMBRE_PARTIDA_INVALIDO ""
#define ID_PARTIDA_INVALIDO -1
#define ID_EMISOR_AUN_NO_DEFINIDO -2
#define X_INVALIDA -1
#define Y_INVALIDA -1
#define VIDA_INVALIDA -1

#endif /* COMUN_DEFINICIONESPRIVADAS_H_ */
