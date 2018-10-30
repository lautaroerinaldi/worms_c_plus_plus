#ifndef VIGAEDITOR_H
#define VIGAEDITOR_H

#include <glibmm-2.4/glibmm/refptr.h>
#include <gdkmm-3.0/gdkmm/pixbuf.h>

#include "Dibujable.h"

class VigaEditor : public Dibujable{
private:
    int posX;
    int posY;
    int angulo;
    int tamanio;    
    Glib::RefPtr<Gdk::Pixbuf> imagen;
    Glib::RefPtr<Gdk::Pixbuf> imagenEscalada;
    
    void ajustarPosicionAModelo(int x, int y);
    
public:
    //constructor de la viga editada
    VigaEditor(int posX, int posY, int angulo, int tamanio);
    
    //destructor de la viga editada
    virtual ~VigaEditor();
    
    //setea el tamanio de la viga
    void SetTamanio(int tamanio);
    
    //devuelve el tamanio de la viga
    int GetTamanio() const;
    
    //setea el angulo de la viga
    void SetAngulo(int angulo);
    
    //devuelve el angulo de la viga
    int GetAngulo() const;
    
    //setea la posicion Y de la viga
    void SetPosY(int posY);
    
    //devuelve la posicion Y de la viga
    int GetPosY() const;
    
    //setea la posicion X de la viga
    void SetPosX(int posX);
    
    //devuelve la posicion X de la viga
    int GetPosX() const;

    //dibuja la viga super loca de manera super magica
    void dibujar(const Cairo::RefPtr<Cairo::Context>& cr);
    
    //levanta la imagen segun el angulo de la viga
    void levantarImagen();
    
    //calcula el ancho
    int calcularAncho();
    
    //calcula el alto
    int calcularAlto();
};

#endif /* VIGAEDITOR_H */

