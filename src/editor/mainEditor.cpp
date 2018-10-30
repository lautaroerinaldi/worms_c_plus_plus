#include <stdio.h>
#include <stdlib.h>
#include <gtkmm-3.0/gtkmm/application.h>
#include <glibmm-2.4/glibmm/init.h>
#include <iostream>
#include "Ventana.h"


int main(int argc, char** argv) {
    Glib::init();
    Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv);
    Ventana ventana;
    ventana.cargarGlade();
    ventana.run(app);
           
    return (EXIT_SUCCESS);
}

