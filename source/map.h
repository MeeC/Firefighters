#ifndef MAP_H
#define MAP_H

#include "vehicle.h"
#include "mapslot.h"

class Map{
private:
    const int m_map_size; //stathero megethos xarti. Orizetai kata tin dimiourgia tou xarti.
	int m_total_fires, m_current_fires;
	int m_num_of_aerial, m_num_of_ground, m_num_of_damaged;
	HeadQuarters * HQ;
	vector<Vehicle*> vehicles;
    vector<Mapslot*> places;
    vector<Fire*> fires;
	
	
public:
	//dimiourgos kaleitai me orisma to megethos tou xarti kai tous arithmous oximatwn alliws me default times
	Map(int size=15, int initNumOfVehicles=14, int initNumOfFires=25)
		: m_map_size(size),m_total_fires(0), m_current_fires(0),
			m_num_of_aerial(0), m_num_of_ground(0), m_num_of_damaged(0)
	{
        createMap(m_map_size);
        HQ = new HeadQuarters(randomness(m_map_size)-1,randomness(m_map_size)-1,m_map_size);
		places[HQ->getMapSlotID()]->setHeadquarters();
		set_random_fires(initNumOfFires);
		add_random_vehicles(initNumOfVehicles);		
	}
	//O destructor. Kaleitai prin kleisei i eksomoiwsi gia na diagrapsei deiktes antikeimena vectors klp
	~Map()
	{   
        delete HQ;
        for(int i=0;i<vehicles.size();i++){   
            delete vehicles[i];
            vehicles.erase(vehicles.begin()+i);
        }
        for(int i=0;i<fires.size();i++){   
            delete fires[i];
            fires.erase(fires.begin()+i);
        }
        for(int i=0;i<places.size();i++){   
            delete places[i];
            places.erase(places.begin()+i);
        }                              
		cout<<"Simulation Terminated!"<<endl;
	}
    
    int getMsize(void){return m_map_size;}
    int getNumFires(void){return m_current_fires;}
    void createMap(int map_size);
	void set_random_fires(int num_of_fires);
	bool set_fire(int x, int y);
	void extinguish_fire(int x, int y);
	void spread_fire(void);
	void add_random_vehicles(int num_of_vehicles);
	bool add_vehicle(int x, int y, int type);
	void move_vehicle(Vehicle* v);
	void fight_nearby_fires(Vehicle * v);
	void move_and_extinguish(void);
	void break_and_withdraw(void);
	bool breakVehicle(int x, int y);
	bool isVehicle(int mapslot_id){return (places[mapslot_id]->isVehicle())? true : false;}
	bool isFire(int mapslot_id){return (places[mapslot_id]->isFire())? true : false;}
	bool isHQ(int mapslot_id){return (places[mapslot_id]->isHQ())? true : false;}
	void printMapStats(void);
	void printFireStats(void);
	void printVehicleStats(void);
};

#endif
