#ifndef ESCENARIO_H
#define ESCENARIO_H

#include "Dibujable.h"
#include "MapaEditor.h"
#include <cairomm-1.0/cairomm/refptr.h>
#include <cairomm-1.0/cairomm/context.h>
#include <gtkmm-3.0/gtkmm/drawingarea.h>

class Escenario : public Gtk::DrawingArea{
private:
    MapaEditor *mapa;
public:
    //constructor del escenario
    Escenario();
    
    //on draw super magico
    bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
    
    //setea el mapa editor
    void setMapaEditor(MapaEditor *mapa);
    
    //destructor
    virtual ~Escenario();
};

#endif /* ESCENARIO_H */

