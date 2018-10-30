#ifndef MUNICIONESYARMASEDITOR_H
#define MUNICIONESYARMASEDITOR_H

class MunicionesYArmasEditor {
private:
    int vidaGusanos;    
    
    int municionBazooka;
    int municionMortero;    
    int municionGranadaVerde;   
    int municionGranadaRoja;    
    int municionGranadaSanta;    
    int municionBanana;    
    int municionDinamita;    
    int municionAtaqueAereo;    
    int municionBate;    
    int municionTeletransportacion;
    
public:
    //constructor de las municiones y armas editadas
    MunicionesYArmasEditor();

    //destructor de las municiones y armas editadas
    virtual ~MunicionesYArmasEditor();
    
    //setea la municion de la teletransportacion
    void SetMunicionTeletransportacion(int municionTeletransportacion);
    
    //devuelve la municion de la teletransportacion
    int GetMunicionTeletransportacion() const;
    
    //setea la municion del bate
    void SetMunicionBate(int municionBate);
    
    //devuelve la municion del bate
    int GetMunicionBate() const;
    
    //setea la municion del ataque aereo
    void SetMunicionAtaqueAereo(int municionAtaqueAereo);
    
    //devuelve la municion del ataque aereo
    int GetMunicionAtaqueAereo() const;
    
    //setea la municion de la dinamita
    void SetMunicionDinamita(int municionDinamita);
    
    //devuelve la municion de la dinamita
    int GetMunicionDinamita() const;
    
    //setea la municion de la banana
    void SetMunicionBanana(int municionBanana);
    
    //devuelve la municion de la banana
    int GetMunicionBanana() const;
    
    //setea la municion de la santa
    void SetMunicionGranadaSanta(int municionGranadaSanta);
    
    //devuelve la municion de la santa
    int GetMunicionGranadaSanta() const;
    
    //setea la municion de la roja
    void SetMunicionGranadaRoja(int municionGranadaRoja);
    
    //devuelve la municion de la roja
    int GetMunicionGranadaRoja() const;
    
    //setea la municion de la verde
    void SetMunicionGranadaVerde(int municionGranadaVerde);
    
    //devuelve la municion de la verde
    int GetMunicionGranadaVerde() const;
    
    //setea la municion del mortero
    void SetMunicionMortero(int municionMortero);
    
    //devuelve la municion del mortero
    int GetMunicionMortero() const;
    
    //setea la municion de la bazooka
    void SetMunicionBazooka(int municionBazooka);
    
    //devuelve la municion de la bazooka
    int GetMunicionBazooka() const;
    
    //setea la vida de los gusanos
    void SetVidaGusanos(int vidaGusanos);
    
    //devuelve la vida de los gusanos
    int GetVidaGusanos() const;
};

#endif /* MUNICIONESYARMASEDITOR_H */

