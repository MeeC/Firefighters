#ifndef SIMULATION_H
#define SIMULATION_H

#include "map.h"

class Simulation{
private:
	Map *sim_map; //deiktis se antikeimeno tis klasis xartis
	int m_time; //xroniki stigmi
public:
	Simulation(int map_size, int numOfVehicles, int numOfFires);

    void runSimulation(void); //ektelei tin eksomoiwsis
	void doRound(void); //ektelei tis energeies pou xreiazontai se kathe gyro

	int getSimTime(void){return m_time;}
	void incrSimTime(void){m_time++;}

	void printMap(void); //ektypwnei ton xarti
	void open_ui(void); //anoigei tin diepafi me ton xrisi
	void showAllStats(void); // deixnei ola ta statistika tis eksomeiwsis

};

#endif
