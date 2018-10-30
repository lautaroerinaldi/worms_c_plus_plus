#include "../modelo/CuerpoMundo.h"

CuerpoMundo::CuerpoMundo(int tipo_objeto) {
    this->tipo = tipo_objeto;
}

CuerpoMundo::~CuerpoMundo() {
}

int CuerpoMundo::obtenerTipo() {
    return this->tipo;
}
