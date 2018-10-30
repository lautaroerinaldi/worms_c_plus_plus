#include "EstadoMuriendo.h"

#include "EstadoMuriendo.h"


EstadoMuriendo::EstadoMuriendo(std::shared_ptr<SdlTexture> &textura):
                            textura(textura),animacion(textura){
    this->animacion.cargarDesdeElUltimo();
}

int EstadoMuriendo::Handle(const std::string &nombreSprite) {
    std::string nombre = "img/"+nombreSprite+".png";
    return nombre == this->textura->getNombreTextura();         
}

void EstadoMuriendo::render(Area &posicion,int direccion, int color) {
    this->actualizarInicioSprite();
    int respuesta = animacion.animar(posicion, 0, direccion, color);
    if (respuesta < 0) {
        printf("NO SE PUDO MOSTRAR EL PROYECTIL!\n");
    }
}

void EstadoMuriendo::actualizarInicioSprite() {
    Area inicio = this->animacion.getInicio();
    if (inicio.getY() > this->animacion.getFrameAlto()) {
        inicio.setY(inicio.getY() - this->animacion.getFrameAlto());
    }
    this->animacion.setInicio(inicio);
}

void EstadoMuriendo::mover(int direccion){    
}

int EstadoMuriendo::direccionar(){
    return 0;
}

int EstadoMuriendo::puedeAtacar(){
    return 0;
}

int EstadoMuriendo::getAngulo(){
    return -1;
}

EstadoMuriendo::~EstadoMuriendo() {
}