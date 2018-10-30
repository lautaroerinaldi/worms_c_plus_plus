#include <gdkmm-3.0/gdkmm/general.h>

#include "GusanoEditor.h"

#define ANCHO_GUSANO 25
#define ALTO_GUSANO 25

GusanoEditor::GusanoEditor(int posX, int posY): posXDelGusano(posX),
                                                           posYDelGusano(posY) {
    imagen = Gdk::Pixbuf::create_from_file("img/speed.1.png");        
    imagenEscalada = imagen->scale_simple(ANCHO_GUSANO,ALTO_GUSANO,
                                                        Gdk::INTERP_BILINEAR);
}

GusanoEditor::~GusanoEditor() {
}

void GusanoEditor::SetPosYDelGusano(int posYDelGusano) {
    this->posYDelGusano = posYDelGusano;
}

int GusanoEditor::GetPosYDelGusano() const {
    return posYDelGusano;
}

void GusanoEditor::SetPosXDelGusano(int posXDelGusano) {
    this->posXDelGusano = posXDelGusano;
}

int GusanoEditor::GetPosXDelGusano() const {
    return posXDelGusano;
}

void GusanoEditor::dibujar(const Cairo::RefPtr<Cairo::Context>& cr){    
    Gdk::Cairo::set_source_pixbuf(cr, imagenEscalada, this->posXDelGusano, 
                                                           this->posYDelGusano);    
    cr->paint();                                                           
}
