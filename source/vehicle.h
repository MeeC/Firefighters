#ifndef VEHICLE_H
#define VEHICLE_H

#include "Map_object.h"

/*i klasi oxima pairnei vasikes idiotites apo tin map_object perigrafei ena oxima pou kineitai se enan 2d kikliko xarti*/
class Vehicle : public Map_object{
	private:
		int m_age, m_fuel, m_water, m_status, m_total_fuel,m_total_water;
		int m_fuel_tank, m_water_tank, m_consumption, m_speed, m_max_age;
		string m_name;
	public:
		/* dhlosh tou constructor */
		Vehicle(int pos_x=0, int pos_y=0, int map_size=0)
			: Map_object(pos_x, pos_y, map_size),m_age(0),m_status(WORKING),m_fuel_tank(100), m_water_tank(150), 
            m_consumption(5), m_speed(1),m_max_age(100),m_total_fuel(0),m_total_water(0)
		{
			//cout << "Im a vehicle!"<<endl;
		}	
		/* dhlosh ton methodon pou xrhsimopoiei h klash */
		void showID(void);

        /* methodoi gia tin diaxeirisi twn xaraktiristikwn twn oximatwn*/
        void incrAge(void){m_age++;}
        void fullGas(void){m_fuel = m_fuel_tank;}
        void fullWater(void){m_water = m_water_tank;}
        void repair(void){m_status=WORKING;}
        void breakDown(void){m_status=BROKEN;}
        void consumeFuel(void){if(m_fuel>m_consumption)m_fuel-=m_consumption;}
        void useWater(void){if(m_water>10)m_water-=10;} //me ypothesi oti ola ta oximata theloun tin idia posotita gia na svisoun fwtia
        void incrTotalWater(void){m_total_water+=10;}
        void incrTotalFuel(void){m_total_fuel+=m_consumption;}

        /*methodoi get*/
        int getAge(void){return m_age;}
        int getMaxAge(void){return m_max_age;}
        int getSpeed(void){return m_speed;}
        int getTotalFuel(void){return m_total_fuel;}
        int getTotalWater(void){return m_total_water;}
        
        /*episkevazei kai anevodiazei to oxima*/
        void doService(void);
        /*methodoi elegxou katastasis*/
        bool isWithdrawal(void);
        bool isFunctional(void);
        bool isBroken(void){ return (m_status==BROKEN)? true : false;}
        bool isOutOfGas(void){ return (m_fuel<=m_consumption)? true : false; }
        bool isOutOfWater(void){ return (m_water<=10)? true : false;}		
		void moveVehicleTo(int mapslot); //metakinei to oxima

        /*methodei set gia ta stoixeia tou oximatos*/
        void setName(string name){m_name=name;}
        string getName(void){return m_name;}
        void setVehicleStats(int fuel_tank, int water_tank, int consumption, int speed, int max_age){
            m_fuel_tank=fuel_tank, m_water_tank=water_tank, m_consumption=consumption, m_speed=speed, m_max_age=max_age;
        }
        
        /*virtual methodoi gia aftin tin ierarxia*/
		virtual void printStatus(void){
			 cout << "Im Ground vehicle in position:("<<getPositionX()<<","<<getPositionY()<<")"<<endl;	 	 		 
		}
	    virtual int getType(void){return 0;}// den tin xreiazomaste edw. Mono stis ypoklaseis.	
		

};

/*H klasi oximata aera me neo stoixeio ton typo kai diaforetiko tropo dimiourgias*/
class Aerial : public Vehicle{
    private:
        const int m_type;
	public:
		Aerial(int pos_x=0, int pos_y=0, int map_size)
			:Vehicle(pos_x, pos_y, map_size), m_type(AIR)
		{
			setVehicleStats(1000,120,40,6,25);
			doService();
		}
		
		virtual int getType(void){return m_type;}
		virtual void printStatus(void){
			 cout << "Im an aerial vehicle in position:("<<getPositionX()<<","<<getPositionY()<<")"<<endl;	 	 		 
		}

};

/*H klasi oxima edafous*/
class Ground : public Vehicle{
    private:
        const int m_type;
	public:
		Ground(int pos_x, int pos_y, int map_size)
			:Vehicle(pos_x, pos_y, map_size),m_type(GROUND)
		{
			setVehicleStats(100,90,5,1,40);
			doService();
		}
		virtual int getType(void){return m_type;}
		virtual void printStatus(void){
			 cout << "Im a firetruck in position:("<<getPositionX()<<","<<getPositionY()<<")"<<endl;	 	 		 
		}
};

/******************************************************************************/
/* Oi parakatw klaseis einai ypoklaseis twn oximatwn aera kai edafous *********/
/* kai apoteloun ta kanonika oximata pou xrisomopoioume kata tin eksomoiwsi ***/
/* Kathe klasi diaforopoieitai ws pros ta xaraktiristika tou oximatos *********/
/******************************************************************************/
class Airplane : public Aerial{
    private:

	public:
		Airplane(int pos_x=0, int pos_y=0, int map_size)
			:Aerial(pos_x, pos_y, map_size)
		{
            setName("Airplane");
			setVehicleStats(6500,520,60,7,55);
			doService();
		}
		
		virtual void printStatus(void){
			 cout << "Im an Airplane in position:("<<getPositionX()<<","<<getPositionY()<<")"<<endl;	 	 		 
		}

};
class Helicopter : public Aerial{
    private:

	public:
		Helicopter(int pos_x=0, int pos_y=0, int map_size)
			:Aerial(pos_x, pos_y, map_size)
		{
            setName("Helicopter");
			setVehicleStats(2700,280,100,4,75);
			doService();
		}
		
		virtual void printStatus(void){
			 cout << "Im a Helicopter in position:("<<getPositionX()<<","<<getPositionY()<<")"<<endl;	 	 		 
		}

};
class Truck : public Ground{
    private:

	public:
		Truck(int pos_x, int pos_y, int map_size)
			:Ground(pos_x, pos_y, map_size) 
		{
            setName("Truck");
			setVehicleStats(250,300,15,1,130);
			doService();
		}
		virtual void printStatus(void){
			 cout << "Im a Truck in position:("<<getPositionX()<<","<<getPositionY()<<")"<<endl;	 	 		 
		}
};



class Car : public Ground{
    private:

	public:
		Car(int pos_x, int pos_y, int map_size)
			:Ground(pos_x, pos_y, map_size)
		{
            setName("Car");
			setVehicleStats(120,180,5,2,100);
			doService();
		}
		virtual void printStatus(void){
			 cout << "Im a car in position:("<<getPositionX()<<","<<getPositionY()<<")"<<endl;	 	 		 
		}
};


#endif
