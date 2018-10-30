#include <glibmm-2.4/glibmm/refptr.h>
#include <gdkmm-3.0/gdkmm/pixbuf.h>
#include <gdkmm-3.0/gdkmm/general.h>
#include <gtkmm-3.0/gtkmm/widget.h>

#include "Escenario.h"

#define ANCHO 2500 
#define ALTO 1350

Escenario::Escenario() {
}

bool Escenario::on_draw(const Cairo::RefPtr<Cairo::Context>& cr) {
    this->set_size_request(ANCHO,ALTO);
    this->mapa->dibujar(cr);
    return true;
}

void Escenario::setMapaEditor(MapaEditor* mapa){
    this->mapa = mapa;
}


Escenario::~Escenario() {
}

