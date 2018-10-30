#ifndef WORMS_SRC_MODEL_CODIGOS_H_
#define WORMS_SRC_MODEL_CODIGOS_H_

#define ALTURA_ESCENARIO 27
#define ANCHO_ESCENARIO 50

//Tipos de cuerpos ingresados al mundo de box2d

#define BORDE 0
#define AGUA 1
#define VIGA 2
#define GUSANO 3
#define BALA 4

#define GRAVEDAD b2Vec2(0.0f,1.0f)

//Angulos en radianes
#define RAD_45 b2_pi/4.0f
#define RAD_90 b2_pi/2.0f
#define RAD_135 3*b2_pi/4.0f

//Para convertir grado a radian y viceversa
#define TO_RAD b2_pi / 180.0f
#define FROM_RAD 180.0f / b2_pi

//Friccion Vigas
#define FRICCION_VIGA 1.0f

//Definiciones para crear al gusano en el mundo
#define DENSIDAD_GUSANO 1.0f
#define FRICCION_GUSANO 1.0f

//Definiciones para los pasos de simulacion
#define TIME_STEP 1.0f/10.0f
#define VEL_ITERATIONS 8
#define POS_ITERATIONS 3

//Mascaras de filtro
#define CAT_BORDE 0x0001
#define CAT_AGUA 0x0002
#define CAT_VIGA 0x0004
#define CAT_GUSANO 0x0008
#define CAT_BALA 0x0010

//Vida agregada para nivelar partida con gusanos desparejos
#define VIDA_EXTRA 25

//Magnitud rebote gusano golpeado
#define REBOTE_GUSANO 0.1f

#endif /* WORMS_SRC_MODEL_CODIGOS_H_ */
