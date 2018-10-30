#ifndef VENTANA_H
#define VENTANA_H

#include <gtkmm-3.0/gtkmm/builder.h>
#include <gtkmm-3.0/gtkmm.h>
#include <gtkmm-3.0/gtkmm/application.h>
#include <gtkmm-3.0/gtkmm/window.h>
#include <glibmm-2.4/glibmm/refptr.h>
#include <glibmm-2.4/glibmm/signalproxy.h>
#include <sigc++-2.0/sigc++/functors/ptr_fun.h>
#include <map>
#include <gdkmm-3.0/gdkmm.h>
#include <cairomm-1.0/cairomm/context.h>
#include "GusanoEditor.h"
#include "MunicionesYArmasEditor.h"
#include "VigaEditor.h"
#include "Escenario.h"
#include "MapaEditor.h"


class Ventana {
private:
    MapaEditor mapaEditor;
    
    Gtk::Window *window;        
    Glib::RefPtr<Gtk::Builder> builder;    
    
    //datos del menu
    Gtk::MenuItem *menuGuardar;
    Gtk::MenuItem *menuGuardarComo;
    Gtk::MenuItem *menuAbrir;
    Gtk::MenuItem *menuSalir;
    
    //vida y municiones
    Gtk::SpinButton *vidaGusanosSB;    
    
    Gtk::SpinButton *municionBazookaSB;    
    Gtk::SpinButton *municionMorteroSB;    
    Gtk::SpinButton *municionGranadaVerdeSB;    
    Gtk::SpinButton *municionGranadaRojaSB;    
    Gtk::SpinButton *municionGranadaSantaSB;    
    Gtk::SpinButton *municionBananaSB;    
    Gtk::SpinButton *municionDinamitaSB;    
    Gtk::SpinButton *municionAtaqueAereoSB;    
    Gtk::SpinButton *municionBateSB;    
    Gtk::SpinButton *municionTeletransportacionSB;
    
    //info del gusano
    Gtk::SpinButton *posXDelGusanoSB;    
    Gtk::SpinButton *posYDelGusanoSB;    
    Gtk::Button *agregarGusanoPtr;
    
    
    //info de la viga
    Gtk::SpinButton *posXDeLaVigaSB;    
    Gtk::SpinButton *posYDeLaVigaSB;       
    Gtk::ComboBox *anguloDeLaVigaCB;
    Gtk::ComboBox *tamVigaCB;
    Gtk::Button *agregarVigaPtr;    
    
    Gtk::Viewport *viewPortPtr;

    MunicionesYArmasEditor municiones;
    
    Escenario escenario;
    
    std::string rutaElegida;
    
    //agrega un gusano al mapa
    void agregarGusanoV();
    
    //agrega una viga al mapa
    void agregarVigaV();
    
    //inicializa los elementos
    void inicializarAtributos();
    
    //carga los widgets
    void cargarWidget();          
    
public:
    //constructor de la ventana del editor
    Ventana();
    
    //carga el glade creado
    void cargarGlade();
    
    //corre la aplicacion
    void run(Glib::RefPtr<Gtk::Application> &app);
    
    //guarda los cambios en un nuevo archivo
    void guardarComoArchivo();
    
    //guarda los cambios
    void guardarArchivo();
    
    //sale del editor
    void salir();
    
    //abre un archivo
    void abrirArchivo();
    
    //captura los eventos de la ventana
    void capturarEventos();
    
    //dibujar
    bool on_draw(const Cairo::RefPtr<Cairo::Context> &cr);
    
    //devuelve el valor del tamanio de la viga
    int getValueTamanioViga(int tamanio);
    
    //devuelve el valor del angulo de la viga
    int getValueAnguloViga(int value);
    
    //verifica si pudo guardar
    int pudoGuardar();
    
    //abre la logica de los archivos
    void abrirLogicaArchivo();
    
    //valida si puede guardar el archivo
    int validarGuardar();
    
    //destructor de la ventana
    virtual ~Ventana();
};

#endif /* VENTANA_H */

