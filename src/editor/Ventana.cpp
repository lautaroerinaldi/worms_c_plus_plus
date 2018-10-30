#include <iostream>

#include "Ventana.h"
#include <gtkmm-3.0/gtkmm/dialog.h>
#include <gtkmm-3.0/gtkmm/messagedialog.h>
#include <gtk-3.0/gtk/gtkwindow.h>
#include <gtk-3.0/gtk/gtktypes.h>
#include <gdkmm-3.0/gdkmm/pixbuf.h>
#include <gdkmm-3.0/gdkmm/general.h>
#include <cairomm-1.0/cairomm/context.h>
#include "../Yaml/yaml-cpp/yaml.h"

Ventana::Ventana() : window(NULL) {
    this->builder = Gtk::Builder::create();
    this->builder->add_from_file("glade/editor.glade");
    this->inicializarAtributos();
}

void Ventana::cargarGlade() {
    this->cargarWidget();
    this->capturarEventos();
}

void Ventana::run(Glib::RefPtr<Gtk::Application>& app) {
    if (this->window) {
        this->window->show_all();
        app->run(*this->window);
    }
}

void Ventana::inicializarAtributos() {
    //datos del menu
    menuGuardar = NULL;
    menuGuardarComo = NULL;
    menuAbrir = NULL;
    menuSalir = NULL;

    //vida y municiones
    this->vidaGusanosSB = NULL;
    this->municionBazookaSB = NULL;
    this->municionMorteroSB = NULL;
    this->municionGranadaVerdeSB = NULL;
    this->municionGranadaRojaSB = NULL;
    this->municionGranadaSantaSB = NULL;
    this->municionBananaSB = NULL;
    this->municionDinamitaSB = NULL;
    this->municionAtaqueAereoSB = NULL;
    this->municionBateSB = NULL;
    this->municionTeletransportacionSB = NULL;

    //info del gusano
    this->posXDelGusanoSB = NULL;
    this->posYDelGusanoSB = NULL;
    this->agregarGusanoPtr = NULL;

    //info de la viga
    this->posXDeLaVigaSB = NULL;
    this->posYDeLaVigaSB = NULL;
    this->anguloDeLaVigaCB = NULL;
    this->tamVigaCB = NULL;
    this->agregarVigaPtr = NULL;
    
    this->viewPortPtr = NULL;
}

void Ventana::cargarWidget() {
    builder->get_widget("window1", window);
    //datos del menu
    builder->get_widget("menuGuardar", menuGuardar);
    builder->get_widget("menuGuardarComo", menuGuardarComo);
    builder->get_widget("menuAbrir", menuAbrir);
    builder->get_widget("menuSalir", menuSalir);

    //vida del gusano y municiones
    builder->get_widget("vidaGusanos", this->vidaGusanosSB);
    builder->get_widget("municionBazooka", this->municionBazookaSB);
    builder->get_widget("municionMortero", this->municionMorteroSB);
    builder->get_widget("municionGranadaVerde", this->municionGranadaVerdeSB);
    builder->get_widget("municionGranadaRoja", this->municionGranadaRojaSB);
    builder->get_widget("municionGranadaSanta", this->municionGranadaSantaSB);
    builder->get_widget("municionBanana", this->municionBananaSB);
    builder->get_widget("municionDinamita", this->municionDinamitaSB);
    builder->get_widget("municionAtaqueAereo", this->municionAtaqueAereoSB);
    builder->get_widget("municionBate", this->municionBateSB);
    builder->get_widget("municionTeletransportacion",
            this->municionTeletransportacionSB);

    //informacion del gusano
    builder->get_widget("posXGusano", this->posXDelGusanoSB);
    builder->get_widget("posYGusano", this->posYDelGusanoSB);
    builder->get_widget("AgregarGusano", this->agregarGusanoPtr);

    //informacion de la viga
    builder->get_widget("posXViga", this->posXDeLaVigaSB);
    builder->get_widget("posYViga", this->posYDeLaVigaSB);
    builder->get_widget("anguloVigaCB", this->anguloDeLaVigaCB);
    builder->get_widget("tamanioVigaCB", this->tamVigaCB);
    builder->get_widget("agregarViga", this->agregarVigaPtr);

    builder->get_widget("viewport", this->viewPortPtr);
    this->viewPortPtr->add(this->escenario);
  
    escenario.setMapaEditor(&this->mapaEditor);    
}

void Ventana::abrirArchivo() {
    Gtk::FileChooserDialog dialogo("abrir", Gtk::FILE_CHOOSER_ACTION_OPEN);
    dialogo.add_button("Abrir", Gtk::RESPONSE_OK);
    dialogo.add_button("Cancelar", Gtk::RESPONSE_CANCEL);
    Glib::RefPtr<Gtk::FileFilter> filtro = Gtk::FileFilter::create();
    filtro->set_name("Escenarios");
    filtro->add_pattern("*.yaml");
    dialogo.add_filter(filtro);
    int resultado = dialogo.run();
    if (resultado == Gtk::RESPONSE_OK) {
        try {
            rutaElegida = dialogo.get_filename();
            this->abrirLogicaArchivo();
        } catch (const std::exception& error) {
            Gtk::MessageDialog dialogo(error.what());
            dialogo.run();
        }
    }
}

void Ventana::guardarArchivo() {
}

void Ventana::guardarComoArchivo() {    
    if(this->validarGuardar()){                
        Gtk::FileChooserDialog dialogo("guardar", Gtk::FILE_CHOOSER_ACTION_SAVE);
        dialogo.add_button("GUARDAR", Gtk::RESPONSE_OK);
        dialogo.add_button("CANCELAR", Gtk::RESPONSE_CANCEL);
        dialogo.set_do_overwrite_confirmation();
        Glib::RefPtr<Gtk::FileFilter> filtrado = Gtk::FileFilter::create();
        filtrado->set_name("Escenarios");
        filtrado->add_pattern("*.yaml");
        dialogo.add_filter(filtrado);
        int res = dialogo.run();
        if (res == Gtk::RESPONSE_OK) {
            this->rutaElegida = dialogo.get_filename();
            if (!pudoGuardar()) {
                this->rutaElegida.clear();
            }
        }
    }         
}

void Ventana::salir() {
}

void Ventana::capturarEventos() {
    if (menuAbrir) {
        menuAbrir->signal_activate().connect(sigc::mem_fun(
                *this, &Ventana::abrirArchivo));
    }

    if (menuGuardar) {
        menuGuardar->signal_activate().connect(sigc::mem_fun(
                *this, &Ventana::guardarArchivo));
    }

    if (menuGuardarComo) {
        menuGuardarComo->signal_activate().connect(sigc::mem_fun(
                *this, &Ventana::guardarComoArchivo));
    }

    if (menuSalir) {
        menuSalir->signal_activate().connect(sigc::mem_fun(
                *this, &Ventana::salir));
    }

    if (agregarGusanoPtr) {
        agregarGusanoPtr->signal_clicked().connect(sigc::mem_fun(
                *this, &Ventana::agregarGusanoV));
    }

    if (agregarVigaPtr) {
        agregarVigaPtr->signal_clicked().connect(sigc::mem_fun(
                *this, &Ventana::agregarVigaV));
    }
}

void Ventana::agregarGusanoV() {
    std::stringstream mensaje;
    int posX = this->posXDelGusanoSB->get_adjustment()->get_value();
    int posY = this->posYDelGusanoSB->get_adjustment()->get_value();
    GusanoEditor gusano(posX, posY);
    this->mapaEditor.agregarGusano(gusano);
    mensaje << "Gusano agregado" << std::endl;
    Gtk::MessageDialog dialogo(mensaje.str());
    dialogo.run();
    this->escenario.show();
}

void Ventana::agregarVigaV() {
    std::stringstream mensaje;
    if (this->tamVigaCB && this->anguloDeLaVigaCB) {
        if (this->tamVigaCB->get_active_row_number() == -1) {
            mensaje << "Seleccione un tamanio de la viga!" << std::endl;
        } else if (this->anguloDeLaVigaCB->get_active_row_number() == -1) {
            mensaje << "Seleccione un angulo de la viga!" << std::endl;
        } else {
            int posX = this->posXDeLaVigaSB->get_adjustment()->get_value();
            int posY = this->posYDeLaVigaSB->get_adjustment()->get_value();
            int anguloViga = this->anguloDeLaVigaCB->get_active_row_number();
            int tamanioViga = this->tamVigaCB->get_active_row_number();
            int tamanio = this->getValueTamanioViga(tamanioViga);
            int angulo = this->getValueAnguloViga(anguloViga);
            VigaEditor viga(posX, posY, angulo, tamanio);
            this->mapaEditor.agregarViga(viga);
            mensaje << "Viga agregada" << std::endl;
        }
    } else {
        mensaje << "Seleccione tamanio y angulo de la viga!" << std::endl;
    }
    Gtk::MessageDialog dialogo(mensaje.str());
    dialogo.run();
}

int Ventana::getValueTamanioViga(int tamanioViga) {
    if (tamanioViga == 0) {
        return 3;
    }
    if (tamanioViga == 1) {
        return 6;
    }
    return -1;
}

int Ventana::getValueAnguloViga(int anguloViga) {
    switch (anguloViga) {
        case 0:
            return 0;
        case 1:
            return 45;
        case 2:
            return 60;
        case 3:
            return 90;
        case 4:
            return 120;
        case 5:
            return 135;
    }
    return -1;
}

int Ventana::pudoGuardar() {
    municiones.SetMunicionAtaqueAereo(this->municionAtaqueAereoSB->get_adjustment()->get_value());
    municiones.SetMunicionBanana(this->municionBananaSB->get_adjustment()->get_value());
    municiones.SetMunicionBate(this->municionBateSB->get_adjustment()->get_value());
    municiones.SetMunicionBazooka(this->municionBazookaSB->get_adjustment()->get_value());
    municiones.SetMunicionDinamita(this->municionDinamitaSB->get_adjustment()->get_value());
    municiones.SetMunicionGranadaRoja(this->municionGranadaRojaSB->get_adjustment()->get_value());
    municiones.SetMunicionGranadaVerde(this->municionGranadaVerdeSB->get_adjustment()->get_value());
    municiones.SetMunicionGranadaSanta(this->municionGranadaSantaSB->get_adjustment()->get_value());
    municiones.SetMunicionMortero(this->municionMorteroSB->get_adjustment()->get_value());
    municiones.SetMunicionTeletransportacion(this->municionTeletransportacionSB->get_adjustment()->get_value());
    municiones.SetVidaGusanos(this->vidaGusanosSB->get_adjustment()->get_value());
    return this->mapaEditor.guardarYaml(this->rutaElegida, this->municiones);
}

void Ventana::abrirLogicaArchivo() {
    this->mapaEditor.limpiarTodo();
    YAML::Node nodo_in = YAML::LoadFile(this->rutaElegida);
    for (YAML::const_iterator it = nodo_in.begin(); it != nodo_in.end(); ++it) {
        if (it->first.as<std::string>() == "gusano") {
            YAML::Node nodo_gusano = nodo_in[it->first];
            GusanoEditor gusano(nodo_gusano["x"].as<int>(), nodo_gusano["y"].as<int>());
            this->mapaEditor.agregarGusano(gusano);
        } else if (it->first.as<std::string>() == "viga") {
            YAML::Node nodo_viga = nodo_in[it->first];
            VigaEditor viga(
                    nodo_viga["x"].as<int>(),
                    nodo_viga["y"].as<int>(),
                    nodo_viga["angulo"].as<int>(),
                    nodo_viga["tamanio"].as<int>());
            this->mapaEditor.agregarViga(viga);
        } else if (it->first.as<std::string>() == "municiones") {
            YAML::Node nodo_municiones = nodo_in[it->first];

            this->vidaGusanosSB->get_adjustment()->set_value(nodo_municiones["vida"].as<int>());
            this->municionAtaqueAereoSB->get_adjustment()->set_value(nodo_municiones["aereo"].as<int>());
            this->municionBananaSB->get_adjustment()->set_value(nodo_municiones["banana"].as<int>());
            this->municionBateSB->get_adjustment()->set_value(nodo_municiones["bate"].as<int>());
            this->municionBazookaSB->get_adjustment()->set_value(nodo_municiones["bazooka"].as<int>());
            this->municionDinamitaSB->get_adjustment()->set_value(nodo_municiones["dinamita"].as<int>());
            this->municionGranadaRojaSB->get_adjustment()->set_value(nodo_municiones["roja"].as<int>());
            this->municionGranadaVerdeSB->get_adjustment()->set_value(nodo_municiones["verde"].as<int>());
            this->municionGranadaSantaSB->get_adjustment()->set_value(nodo_municiones["santa"].as<int>());
            this->municionMorteroSB->get_adjustment()->set_value(nodo_municiones["mortero"].as<int>());
            this->municionTeletransportacionSB->get_adjustment()->set_value(nodo_municiones["teletransportacion"].as<int>());
        }
    }
}

int Ventana::validarGuardar(){    
    if(this->mapaEditor.dameCantidadDeGusanos() < 2){        
        Gtk::MessageDialog dialogo("debe agregar al menos 2 gusanos al mapa");
        dialogo.run();
        return false;
    }
    if(this->mapaEditor.dameCantidadDeVigas() < 1){
        Gtk::MessageDialog dialogo("debe agregar al menos 1 viga al mapa");
        dialogo.run();
        return false;        
    }   
    return true;
}

Ventana::~Ventana() {
}

