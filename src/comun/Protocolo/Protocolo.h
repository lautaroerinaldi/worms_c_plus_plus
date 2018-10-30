/*
 * Protocolo.h
 */

#ifndef COMUN_PROTOCOLO_PROTOCOLO_H_
#define COMUN_PROTOCOLO_PROTOCOLO_H_

// común a cliente y servidor:
#define DELIMITADOR_CAMPOS ' '		// para el envío y recepción de mensajes por el socket de comunicación
#define DELIMITADOR_REGISTROS '\n'	// para el envío y recepción de mensajes por el socket de comunicación

#define SALIR_MAIN 'q'
#define SALIR "q"

#define MENSAJE_DE_ERROR "Err"

// servidor envía:
#define INICIAR_PARTIDA "ip"
#define FINALIZAR_PARTIDA "fp"
#define FINALIZAR_ESCENARIO "fe"

#define CREAR_VIGA "cv"
#define CREAR_GUSANO "cg"

#define MOVER_GUSANO "mg"
#define CARGAR_ARMA "car"
#define ATACAR "at"
#define CREAR_BALA "cb"
#define MOVER_BALA "mb"
#define IMPACTAR_BALA "ib"
#define DESTRUIR_BALA "db"
#define VOLAR_GUSANO "vg"
#define TELETRANSPORTAR_GUSANO "tg"
#define ACTUALIZAR_VIDA "av"
#define INFORMAR_VIENTO "iv"

#define INICIAR_TURNO "it"
#define FINALIZAR_TURNO "ft"
#define TIEMPO_RESTANTE "tr"
#define NOTIFICAR_GANADOR "ng"
#define NOTIFICACION "notif"


#define NOTIFICAR_ID_PARTIDA "nidp"
#define NOTIFICAR_ID_JUGADOR "nidj"
#define LISTA_PARTIDAS_NO_INICIADAS "lpni"
#define LISTA_ESCENARIOS "le"


// Mensajes que reenvía el server sin pasar por el modelo
#define MOVER_PUNTERIA "mp"
#define DIRECCIONAR_GUSANO "dg"
#define DESCARGAR_ARMA "dar"

// cliente envía si partida NO iniciada:
#define CREAR_PARTIDA "cp"
#define SOLICITAR_TODAS_LAS_PARTIDAS "stlp"
#define SOLICITAR_PARTIDAS_NO_INICIADAS "spni"
#define SOLICITAR_ESCENARIOS "se"
#define UNIRSE_A_PARTIDA "up"

// cliente envía si partida iniciada:
#define SOLICITAR_MOVER "sm"
#define SOLICITAR_SALTAR "ss"
#define SOLICITAR_RETROCESO "sr"
#define SOLICITAR_ATACAR "sat"
#define SOLICITAR_ARMA "sar"

#endif /* COMUN_PROTOCOLO_PROTOCOLO_H_ */
