#include <iostream>
#include <fstream>

#include "MapaEditor.h"
#include "../Yaml/yaml-cpp/yaml.h"

#define ANCHO 2500 
#define ALTO 1350

MapaEditor::MapaEditor() {
}

void MapaEditor::agregarGusano(GusanoEditor gusano) {
    this->gusanos.insert(std::pair<int, GusanoEditor>((int)
            this->gusanos.size(), gusano));
}

void MapaEditor::agregarViga(VigaEditor viga) {
    this->vigas.insert(std::pair<int, VigaEditor>((int)
            this->vigas.size(), viga));
}

void MapaEditor::dibujar(const Cairo::RefPtr<Cairo::Context>& cr) {
    cr->set_source_rgb(1, 1, 1);
    cr->rectangle(0, 0, ANCHO, ALTO);
    cr->fill();
    std::map<int, GusanoEditor>::iterator it;
    for (it = this->gusanos.begin(); it != this->gusanos.end(); ++it) {
        it->second.dibujar(cr);
    }

    std::map<int, VigaEditor>::iterator it2;
    for (it2 = this->vigas.begin(); it2 != this->vigas.end(); ++it2) {
        it2->second.dibujar(cr);
    }
}

int MapaEditor::guardarYaml(const std::string& rutaElegida,
        MunicionesYArmasEditor &municiones) {
    YAML::Emitter out;

    out << YAML::BeginMap;
    out << YAML::Key << "municiones";
    out << YAML::Value;
    out << YAML::BeginMap;
    out << YAML::Key << "vida";
    out << YAML::Value << municiones.GetVidaGusanos();
    out << YAML::Key << "aereo";
    out << YAML::Value << municiones.GetMunicionAtaqueAereo();
    out << YAML::Key << "banana";
    out << YAML::Value << municiones.GetMunicionBanana();
    out << YAML::Key << "bate";
    out << YAML::Value << municiones.GetMunicionBate();
    out << YAML::Key << "bazooka";
    out << YAML::Value << municiones.GetMunicionBazooka();
    out << YAML::Key << "dinamita";
    out << YAML::Value << municiones.GetMunicionDinamita();
    out << YAML::Key << "roja";
    out << YAML::Value << municiones.GetMunicionGranadaRoja();
    out << YAML::Key << "verde";
    out << YAML::Value << municiones.GetMunicionGranadaVerde();
    out << YAML::Key << "santa";
    out << YAML::Value << municiones.GetMunicionGranadaSanta();
    out << YAML::Key << "mortero";
    out << YAML::Value << municiones.GetMunicionMortero();
    out << YAML::Key << "teletransportacion";
    out << YAML::Value << municiones.GetMunicionTeletransportacion();
    out << YAML::EndMap;

    std::map<int, VigaEditor>::iterator itViga;
    for (itViga = this->vigas.begin(); itViga != this->vigas.end(); ++itViga) {
        out << YAML::Key << "viga";
        out << YAML::Value;
        out << YAML::BeginMap;
        out << YAML::Key << "x";
        out << YAML::Value << itViga->second.GetPosX();
        out << YAML::Key << "y";
        out << YAML::Value << itViga->second.GetPosY();
        out << YAML::Key << "angulo";
        out << YAML::Value << itViga->second.GetAngulo();
        out << YAML::Key << "tamanio";
        out << YAML::Value << itViga->second.GetTamanio();
        out << YAML::EndMap;
    }

    std::map<int, GusanoEditor>::iterator itGusano;
    for (itGusano = this->gusanos.begin(); itGusano != this->gusanos.end(); ++itGusano) {
        out << YAML::Key << "gusano";
        out << YAML::Value;
        out << YAML::BeginMap;
        out << YAML::Key << "x";
        out << YAML::Value << itGusano->second.GetPosXDelGusano();
        out << YAML::Key << "y";
        out << YAML::Value << itGusano->second.GetPosYDelGusano();
        out << YAML::EndMap;
    }
    out << YAML::EndMap;
    std::ofstream fout(rutaElegida.c_str(), std::ofstream::out);
    fout << out.c_str();
    fout.close();
    return 1;
}

void MapaEditor::limpiarTodo(){
    this->gusanos.clear();
    this->vigas.clear();
}

int MapaEditor::dameCantidadDeGusanos(){
    return this->gusanos.size();
}

int MapaEditor::dameCantidadDeVigas(){
    return this->vigas.size();
}

MapaEditor::~MapaEditor() {
}

