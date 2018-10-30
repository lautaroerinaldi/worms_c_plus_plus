/*
 * Excepcion.cpp
 */

#include "../../comun/Utiles/Excepcion.h"

Excepcion::Excepcion(const std::string & detalle) noexcept {
	this->detalle = detalle;
}

const char * Excepcion::what() const noexcept {
	return detalle.c_str();
}
