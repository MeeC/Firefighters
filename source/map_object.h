#ifndef MAP_OBJECT_H
#define MAP_OBJECT_H

/* H klasi Map_object einai i yperklasi twn antikeimenwn pou mporoun na topothetithoun panw ton xarti*/
class Map_object{
private:
	int m_pos_x, m_pos_y;
    const int m_map_size; //stathero megethos xarti
public:    
    Map_object(int pos_x=0, int pos_y=0, int map_size=0)
        : m_pos_x(pos_x), m_pos_y(pos_y), m_map_size(map_size)
    {}
    
	int getPositionX(void){return m_pos_x;}

	int getPositionY(void){return m_pos_y;}   

    void setPosition(int posX, int posY){m_pos_x=posX, m_pos_y=posY;}
	
	int getMaxDim(void){return m_map_size;}
    
    int getMapSlotID(void);
    
    int findNearbySlot(int type_of_move);
};

/*Oi klaseis fwtia kai kentro einai ypoklaseis tis map_object kai tis diaxeirizomaste diaforetika apo tin klasi tou xarti*/
class Fire : public Map_object{
private:
public:    
    Fire(int pos_x=0, int pos_y=0, int map_size=0)
        :Map_object(pos_x, pos_y, map_size)
    {}
};

class HeadQuarters : public Map_object{
private:
public:    
    HeadQuarters(int pos_x=0, int pos_y=0, int map_size=0)
        :Map_object(pos_x, pos_y, map_size)
    {}
};

#endif
