#ifndef MODELO_CUERPOMUNDO_H_
#define MODELO_CUERPOMUNDO_H_

class CuerpoMundo {
protected:
	int tipo;
public:
    //Constructor
    explicit CuerpoMundo(int tipo);
    //Destructor
    virtual ~CuerpoMundo();
    //Devuelve el tipo de objeto que representa el cuerpo
    virtual int obtenerTipo();
};

#endif /* MODELO_CUERPOMUNDO_H_ */
