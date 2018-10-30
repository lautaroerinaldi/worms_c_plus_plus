#ifndef GUSANOEDITOR_H
#define GUSANOEDITOR_H

#include <glibmm-2.4/glibmm/refptr.h>
#include <gdkmm-3.0/gdkmm/pixbuf.h>

#include "Dibujable.h"

class GusanoEditor : public Dibujable{
private:
    int posXDelGusano;
    int posYDelGusano;
    Glib::RefPtr<Gdk::Pixbuf> imagen;
    Glib::RefPtr<Gdk::Pixbuf> imagenEscalada;
    
public:
    //constructor del gusano editado
    GusanoEditor(int posX, int posY);
    
    //destructor del gusano editado
    virtual ~GusanoEditor();
    
    //setea la posicion Y del gusano
    void SetPosYDelGusano(int posYDelGusano);
    
    //devuelve la posicion Y del gusano
    int GetPosYDelGusano() const;
    
    //setea la posicion X del gusano
    void SetPosXDelGusano(int posXDelGusano);
    
    //devuelve la posicion x del gusano
    int GetPosXDelGusano() const;

    //dibuja el gusano super loco de manera super magica    
    void dibujar(const Cairo::RefPtr<Cairo::Context>& cr);
    
};

#endif /* GUSANOEDITOR_H */

