#ifndef MAPSLOT_H
#define MAPSLOT_H

/*H klasi mapslot perigrafei mia thesi mesa ston xarti*/
class Mapslot{
private:
    /*statheres syntetagmenes. Molis dimiourgithei mia thesi xarti den mpoun na allaksoun*/
    const int m_map_x, m_map_y;
    /*boolean metavlites gia tin yparksi i oxi kapoio antikeimeno sti thesi*/         
    bool m_fire,m_vehicle,m_headquarters;
    int m_num_of_fires; //krataei poses fores epiase fwtia i thesi

public:
    Mapslot(int x=0, int y=0)
        :m_map_x(x), m_map_y(y),m_fire(false),m_vehicle(false),m_headquarters(false),m_num_of_fires(0)
    {}

    /*get synartiseis pou dinoun tis sintetagmenes pou antistoixoun se afti ti thesi xarti.
    * den yparxoun set afou oi syntetagmenes einai statheres gia kathe thesi*/    
    int getMapX(void){return m_map_x;}
    int getMapY(void){return m_map_y;}
    /*set kai clear gia na deixnoume an yparxei kapoio antikeimeno stin thesi
    * den yparxei clear gia to arxigeio afou otan mpei se kapoia thesi den mporei na fygei apo afti*/
    void setFire(void){m_fire=true,m_num_of_fires++;}
    void setVehicle(void){m_vehicle=true;}
    void setHeadquarters(void){m_headquarters=true;}
    void clearFire(void){m_fire=false;}
    void clearVehicle(void){m_vehicle=false;}
    bool isFire(void){return m_fire;}
    bool isVehicle(void){return m_vehicle;}
    bool isHQ(void){return m_headquarters;}
};

#endif
