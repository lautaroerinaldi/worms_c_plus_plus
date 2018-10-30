#include "EstadoAtacando.h"


EstadoAtacando::EstadoAtacando(std::shared_ptr<SdlTexture> &textura,int angulo):
                            textura(textura),animacion(textura),angulo(angulo){
}

int EstadoAtacando::Handle(const std::string &nombreSprite) {
    std::string nombre = "img/"+nombreSprite+".png";
    return nombre == this->textura->getNombreTextura();         
}

void EstadoAtacando::render(Area &posicion,int direccion, int color) {
    this->actualizarInicioSprite();
    int respuesta = animacion.animar(posicion, 0, direccion, color);
    if (respuesta < 0) {
        printf("NO SE PUDO MOSTRAR EL PROYECTIL!\n");
    }
}

void EstadoAtacando::actualizarInicioSprite() {
    Area inicio = this->animacion.getInicio();
    if (inicio.getY() < (this->animacion.getTextureAlto() - this->animacion.getFrameAlto())) {
        inicio.setY(inicio.getY() + this->animacion.getFrameAlto());
    }
    this->animacion.setInicio(inicio);
}

void EstadoAtacando::mover(int direccion){    
}

int EstadoAtacando::direccionar(){
    return 0;
}

int EstadoAtacando::puedeAtacar(){
    return 0;
}

int EstadoAtacando::getAngulo(){
    return this->angulo;
}

EstadoAtacando::~EstadoAtacando() {
}