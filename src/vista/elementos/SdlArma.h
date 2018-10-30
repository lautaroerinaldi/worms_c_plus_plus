#ifndef SDLARMA_H
#define SDLARMA_H

class SdlArma {
private:
    int tipo;
    int conteo;
    int potencia;  
    
public:
    //constructor del arma
    SdlArma();
    
    //obtiene el tipo de arma
    int getTipo();
    
    //setea un nuevo tipo de arma
    void setTipo(int tipo);
    
    //devuelve la potencia
    int getPotencia();
    
    //setea la potencia del arma
    void setPotencia(int potencia);

    //devuelve el conteo del arma
    int getConteo();
    
    //setea el conteo del arma
    void setConteo(int conteo);    
    
    //acumula la potencia
    void acumularPotencia();       
    
    //valida si tiene tiempo
    int tieneTiempo();
    
    //valida si tiene potencia
    int tienePotencia();
    
    //destructor del arma
    virtual ~SdlArma();

};

#endif /* SDLARMA_H */

