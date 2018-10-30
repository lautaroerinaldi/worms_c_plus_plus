#ifndef MAPAEDITOR_H
#define MAPAEDITOR_H

#include <map>
#include <string>

#include "VigaEditor.h"
#include "GusanoEditor.h"
#include "Dibujable.h"
#include "MunicionesYArmasEditor.h"

class MapaEditor : public Dibujable{
private:    
    std::map<int,GusanoEditor> gusanos;
    std::map<int,VigaEditor> vigas;
    
public:
    //constructor del mapa editor
    MapaEditor();
    
    //agrega un gusano en el mapa editor
    void agregarGusano(GusanoEditor gusano);
        
    //dibuja todo super magicamente
    void dibujar(const Cairo::RefPtr<Cairo::Context>& cr);

    
    //agrega una viga en el mapa editor
    void agregarViga(VigaEditor viga);
    
    //guarda el yaml
    int guardarYaml(const std::string &rutaElegida,MunicionesYArmasEditor &municiones);
    
    //limpiar los dos map
    void limpiarTodo();
    
    //destructor del mapa editor
    virtual ~MapaEditor();
    
    //devuelve la cantidad de gusanos
    int dameCantidadDeGusanos();
    
    //devuelve la cantidad de vigas
    int dameCantidadDeVigas();

};

#endif /* MAPAEDITOR_H */

