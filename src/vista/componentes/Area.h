#ifndef AREA_H
#define AREA_H

class Area {
private:
	int x, y;
	int width, height;    
public:
        //constructor del Area
	Area(int x, int y, int width, int height);
        
        //devuelve el valor x del area
	int getX() const;
        
        //devuelve el valor y del area
	int getY() const;
        
        //devuelve el ancho del area
	int getWidth() const;
        
        //devuelve el alto del area
	int getHeight() const;
        
        //setea el x del area
        void setX(const int x);
        
        //setea el Y del area
	void setY(const int y);
        
        //setea el ancho del area
	void setWidth(const int w) ;
        
        //setea el alto del area
	void setHeight(const int h);
};

#endif
