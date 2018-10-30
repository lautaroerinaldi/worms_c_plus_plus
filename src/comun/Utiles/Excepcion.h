/*
 * Excepcion.h
 */

#ifndef COMUN_UTILES_EXCEPCION_H_
#define COMUN_UTILES_EXCEPCION_H_

#include <exception>
#include <string>

class Excepcion: public std::exception {
	std::string detalle;
public:
	explicit Excepcion(const std::string & detalle) noexcept;
	virtual const char * what() const noexcept;
};

#endif /* COMUN_UTILES_EXCEPCION_H_ */
