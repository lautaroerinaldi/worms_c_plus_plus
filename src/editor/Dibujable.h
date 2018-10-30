#ifndef DIBUJABLE_H
#define DIBUJABLE_H

#include <cairomm-1.0/cairomm/refptr.h>
#include <cairomm-1.0/cairomm/context.h>


class Dibujable {
private:    
public:
    //constructor del dibujable
    Dibujable();
    
    //hereda el metodo dibujar el cual se encarga de dibujar en la DrawArea
    virtual void dibujar(const Cairo::RefPtr<Cairo::Context>& cr)=0;
    
    //destructor del dibujable
    virtual ~Dibujable();


};

#endif /* DIBUJABLE_H */

