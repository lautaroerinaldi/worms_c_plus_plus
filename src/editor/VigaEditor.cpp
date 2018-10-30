#include <cairo/cairo.h>

#include <gdkmm-3.0/gdkmm/general.h>
#include <iostream>
#include <math.h>

#include "VigaEditor.h"

#define ALTO_VIGA 40
#define ESCALATE 50
#define PI 3.14159265

VigaEditor::VigaEditor(int posX, int posY, int angulo, int tamanio) : posX(posX),
posY(posY), angulo(angulo), tamanio(tamanio) {
    this->levantarImagen();
}

void VigaEditor::SetTamanio(int tamanio) {
    this->tamanio = tamanio;
}

int VigaEditor::GetTamanio() const {
    return tamanio;
}

void VigaEditor::SetAngulo(int angulo) {
    this->angulo = angulo;
}

int VigaEditor::GetAngulo() const {
    return angulo;
}

void VigaEditor::SetPosY(int posY) {
    this->posY = posY;
}

int VigaEditor::GetPosY() const {
    return posY;
}

void VigaEditor::SetPosX(int posX) {
    this->posX = posX;
}

int VigaEditor::GetPosX() const {
    return posX;
}

void VigaEditor::dibujar(const Cairo::RefPtr<Cairo::Context>& cr) {	
    Gdk::Cairo::set_source_pixbuf(cr, imagenEscalada, this->posX,
            this->posY);
    cr->paint();

}

void VigaEditor::ajustarPosicionAModelo(int x, int y){
	int tamanio_escalado = tamanio * ESCALATE;
	if (angulo==90){
		posX += (tamanio_escalado-ALTO_VIGA)/2;
		posY -= tamanio_escalado/2;
	} else if (angulo!= 0){
		posX+= (tamanio_escalado - x)/2;
		posY= posY - y/2 + ALTO_VIGA/2;
	}
}

void VigaEditor::levantarImagen() {
    int x = this->calcularAncho();
    int y = this->calcularAlto();
    switch (this->angulo) {
        case(0):
            imagen = Gdk::Pixbuf::create_from_file("img/viga0.png");
            imagenEscalada = imagen->scale_simple(this->tamanio * ESCALATE,
                    ALTO_VIGA, Gdk::INTERP_BILINEAR);
            break;
        case(45):
        {
            imagen = Gdk::Pixbuf::create_from_file("img/viga45.png");
            imagenEscalada = imagen->scale_simple(x,y, Gdk::INTERP_BILINEAR);
        }
            break;
        case(60):
        {
            imagen = Gdk::Pixbuf::create_from_file("img/viga60.png");
            imagenEscalada = imagen->scale_simple(x,y, Gdk::INTERP_BILINEAR);                    
        }
            break;
        case(90):
        {
            imagen = Gdk::Pixbuf::create_from_file("img/viga90.png");
            imagenEscalada = imagen->scale_simple(ALTO_VIGA,
                    this->tamanio * ESCALATE, Gdk::INTERP_BILINEAR);
        }
            break;
        case(120):
        {
            imagen = Gdk::Pixbuf::create_from_file("img/viga120.png");
            imagenEscalada = imagen->scale_simple(x,y, Gdk::INTERP_BILINEAR);                    
        }
            break;
        case(135):
        {
            imagen = Gdk::Pixbuf::create_from_file("img/viga135.png");
            imagenEscalada = imagen->scale_simple(x,y, Gdk::INTERP_BILINEAR);
        }
            break;
    }
	ajustarPosicionAModelo(x, y);

}

int VigaEditor::calcularAlto() {
	float res = sin(((float)angulo/180) * M_PI)* tamanio * ESCALATE;
	return (int)res;
}

int VigaEditor::calcularAncho() {
	float res = cos(((float)angulo/180) * M_PI)* tamanio * ESCALATE;
	if (angulo >= 90)
		res=-res;
	return (int)res;
}

VigaEditor::~VigaEditor() {
}
