#include "globals.h"
#include "functions.h"
#include "vehicle.h"

/*emfanizei plirofories gia tin stoixeia enos oximatos */
void Vehicle::showID(void){
    string yes = "Yes", no="No", problem;
    
    if(!(isFunctional())){
        if(isOutOfGas()) problem="No Gas";
        else if(isOutOfWater()) problem="No Water";
        else if(isBroken()) problem="Is Broken";
        else if(isWithdrawal()) problem="Too Old";
    }
    
    cout <<"("<<getPositionX()<<","<<getPositionY()<<") Age:["<<getAge()<<"] Fuel Consumed:[";
    cout << getTotalFuel() << "] Water Used:[" << getTotalWater() << "] ";
    cout << "Active:["<< ((isFunctional())? yes : no) <<"] "; 
    if(!(isFunctional())) cout << "Reason:["<<problem<<"] " ;
    cout << "Type:["<<getName()<<"] "<< endl;
}

/*anefodiazei kai episkevazei to oxima*/
void Vehicle::doService(void){
    fullGas();
    fullWater();
    repair();    
}       

/*elegxei an to oxima einai leitourgiko*/ 
bool Vehicle::isFunctional(void){
    if(m_status==WORKING && m_fuel>m_consumption && m_water>10 && !(isWithdrawal())) return true;
    else return false;    
}		

/*elegxei an to oxima prepei na aposyrthei*/
bool Vehicle::isWithdrawal(void){
    if(m_age>m_max_age)return true;
    else return false;
}

/*metakinei to oxima se mia kainourgia thesi x,y me vasi omws tin thesi tou xarti ston 1d-pinaka*/
void Vehicle::moveVehicleTo(int mapslot){
    int x = mapslot/getMaxDim();
    int y = mapslot%getMaxDim();
    setPosition(x,y);  
}


