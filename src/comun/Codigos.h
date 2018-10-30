#ifndef WORMS_SRC_CODIGOSCOMUNES_H_
#define WORMS_SRC_CODIGOSCOMUNES_H_

//Codigos de direccion
#define IZQUIERDA 0
#define DERECHA 1

//Codigos de inclinaciones
#define ABAJO 0
#define NORMAL 1
#define ARRIBA 2

//Codigos de tipo de armas
#define SIN_ARMA -1
#define BAZOOKA 0
#define BANANA 1
#define MORTERO 2
#define GRANADA_ROJA 3
#define GRANADA_VERDE 4
#define GRANADA_SANTA 5
#define DINAMITA 6
#define ATAQUE_AEREO 7
#define BATE_DE_BASEBALL 8
#define TELETRANSPORTACION 9

// Ángulos válidos para construir vigas
#define VIGA_ANGULO_GRADOS_0 0
#define VIGA_ANGULO_GRADOS_45 45
#define VIGA_ANGULO_GRADOS_60 60
#define VIGA_ANGULO_GRADOS_90 90
#define VIGA_ANGULO_GRADOS_120 120
#define VIGA_ANGULO_GRADOS_135 135

// Medidas del enunciado
#define ALTURA_VIGA_EN_METROS 0.8
#define TAM_GUSANO_EN_METROS 0.5
#define TAM_BALA_EN_METROS 0.25
#define ALTURA_AGUA_EN_METROS 1
#define LONGITUD_VIGA_CORTA_EN_METROS 3
#define LONGITUD_VIGA_LARGA_EN_METROS 6

//Códigos de tamaños
#define ALTURA_VIGA (ALTURA_VIGA_EN_METROS * ESCALAR_CONSTANTES)
#define TAM_GUSANO (TAM_GUSANO_EN_METROS * ESCALAR_CONSTANTES)
#define ALTURA_AGUA (ALTURA_AGUA_EN_METROS * ESCALAR_CONSTANTES)
#define LONGITUD_VIGA_CORTA (LONGITUD_VIGA_CORTA_EN_METROS * ESCALAR_CONSTANTES)
#define LONGITUD_VIGA_LARGA (LONGITUD_VIGA_LARGA_EN_METROS * ESCALAR_CONSTANTES)
#define TAM_BALA (TAM_BALA_EN_METROS * ESCALAR_CONSTANTES)

#define DURACION_DE_UN_TURNO_EN_SEGUNDOS 60

// Factores de escala
#define ESCALAR_CONSTANTES 10
#define FACTOR_ESCALA_DE_MODELO_A_VISTA 50
#define MULTIPLICAR_VISTA 5

//Estados Gusano
#define QUIETO 0
#define CAMINANDO 1
#define SALTANDO 2
#define RETROCESO 3
#define DESLIZANDO 4
#define CAYENDO 5
#define VOLANDO 6
#define CHOCANDO 7
#define MUERTO 8

// Estados Gusanos válidos para Mover:
#define QUIETO_STR "quieto"
#define CAMINANDO_STR "caminando"
#define SALTANDO_STR "saltando"
#define RETROCESO_STR "retroceso"
#define CAYENDO_STR "cayendo"
#define CHOCANDO_STR "chocando"
#define VOLANDO_STR "volando"

// Tipos de notificaciones que llegan a los clientes:
#define NOTIFICACION_ERROR 0
#define NOTIFICACION_AVISO 1
#define NOTIFICACION_EXITO 2

//Estados de turno
#define SIN_TURNO 0
#define EN_TURNO 1
#define TERMINANDO 2
#define TERMINADO 3

// Puntería para la vista
#define BAJAR_PUNTERIA 0
#define SUBIR_PUNTERIA 1

#endif /* WORMS_SRC_CODIGOSCOMUNES_H_ */
