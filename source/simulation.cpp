#include "globals.h"
#include "functions.h"
#include "simulation.h"

/*O dimourgos. Friaxnei enan xarti kai ksekinaei tin eksomiwsi*/
Simulation::Simulation(int map_size,int numOfVehicles, int numOfFires):m_time(0){
	sim_map= new Map(map_size, numOfVehicles, numOfFires);
	sim_map->printMapStats();
	sim_map->printVehicleStats();
	sim_map->printFireStats();
	printMap();
	runSimulation();
	delete sim_map;
}

/* Oi leitourgies pou ginontai se kathe xroniki stigmi*/
void Simulation::doRound(void){
    incrSimTime(); //afksanoume ton xrono pou perase
    /*Oi fwties eksaplwnontai ston xarti*/
	sim_map->spread_fire();
	/*Ta oximata kinountai kai katapolemoun fwties*/
	sim_map->move_and_extinguish();

    sim_map->break_and_withdraw();	
	/*Se kathe xroniki stigmi yparxei 10% pithanotita na mpoun 1-5 nees fwties ston kosmo*/
	if(randomness(100)<10)
	   sim_map->set_random_fires(randomness(5));
	
	system("cls");
	cout << "Age of simulation: ["<<getSimTime()<<"]"<<endl;
	printMap();
    cout << "[Press Any Button to Pause Simulation...]";
	
}

/* i eksomoiwsi ginetai se ena loop ana gyrous mexri na parei fwtia olos o xartis.
* an patithei koumpi kata tin diarkeia tis mpainoume sto menu epilogwn tou xristi*/
void Simulation::runSimulation(void){
    for(;;){
        if(kbhit())
        {
            char c = getch();
            open_ui();
        } 
        Sleep(400);   
        doRound();            
        if(sim_map->getNumFires()==(sim_map->getMsize()*sim_map->getMsize())){
    	   cout << "Everything is On fire!!"<<endl;
    	   cout << "Simulation is Over!"<<endl;
    	   break;
        }    
    }
}

/*ektypwnoume mia anaparastasi tou xarti*/
void Simulation::printMap(void){
    string f,v,h;
    cout << "[World map: (V=Vehicle,F=Fire,H=HeadQuarters)]"<<endl;
    for(int i=0;i<sim_map->getMsize()*sim_map->getMsize();i++){
        v=(sim_map->isVehicle(i))? "V":"-";
        f=(sim_map->isFire(i))? "F":"-";
        h=(sim_map->isHQ(i))? "H":"-";
        cout <<"|"<< v <<"-"<< h <<"-"<<f;
        if(i%sim_map->getMsize()==sim_map->getMsize()-1)cout << "|"<<endl;            
    }        
}

/* anoigoume ena menu ap opou mporei na pragmatopoiei energies o xristis*/
void Simulation::open_ui(void){ 
    system("cls");   
    while(1){
        string sOption,sx,sy,stype;
        int nOption,nx,ny,ntype;
        cout << "-Simulation Paused!- User Options below:"<<endl;
        cout << "[What do you want to do?]"<<endl;
        cout << "[1] Show Map"<<endl;
        cout << "[2] Show Map Statistics"<<endl;
        cout << "[3] Show Fire Statistics"<<endl;
        cout << "[4] Show Vehicle Statistics"<<endl;
        cout << "[5] Show All Statistics"<<endl;
        cout << "[6] Add New Vehicle"<<endl;
        cout << "[7] Set New Fire"<<endl;
        cout << "[8] Breakdown a Vehicle"<<endl;
        cout << "[9] Continue Simulation"<<endl;
        cout << "[Enter the number of option you want]:";
        cin >> sOption;
        nOption=atoi(sOption.c_str());
        
        if(nOption==1)printMap();
        else if(nOption==2)sim_map->printMapStats();
        else if(nOption==3)sim_map->printFireStats(); 
        else if(nOption==4)sim_map->printVehicleStats();
        else if(nOption==5)showAllStats();
        else if(nOption==6){
            cout << "What kind of Vehicle you want?"<<endl;
            cout << "[0] Airplane" <<endl;             
            cout << "[1] Helicopter" <<endl;
            cout << "[2] Truck" <<endl;
            cout << "[3] Car" <<endl;
            cout << "Choose your vehicle:";
            cin >> stype;
            ntype=atoi(stype.c_str());
            cout << "Give positions X and Y for your vehicle:"<<endl;
            cout << "Enter X(acceptable values: 0 - "<<sim_map->getMsize()-1<<"):";
            cin >> sx;
            nx=atoi(sx.c_str());                   
            cout << "Enter Y(acceptable values: 0 - "<<sim_map->getMsize()-1<<"):";
            cin >> sy;
            ny=atoi(sy.c_str());
            if(ntype>3 || ntype<0 || nx<0 || ny<0 || nx>sim_map->getMsize()-1 || ny>sim_map->getMsize()-1)
                cout << "Not acceptable Input. Try again to add vehicle."<<endl;
            else{
                if(sim_map->add_vehicle(nx, ny, ntype))
                    cout << "New Vehicle Added succefully."<<endl;
                else
                    cout << "Vehicle could not be added. Try an other position without other vehicle on it." <<endl;
            }
        }
        else if(nOption==7){
            cout << "Give positions X and Y for your new Fire:"<<endl;
            cout << "Enter X(acceptable values: 0 - "<<sim_map->getMsize()-1<<"):";
            cin >> sx;
            nx=atoi(sx.c_str());                   
            cout << "Enter Y(acceptable values: 0 - "<<sim_map->getMsize()-1<<"):";
            cin >> sy;
            ny=atoi(sy.c_str());
            if(nx<0 || ny<0 || nx>sim_map->getMsize()-1 || ny>sim_map->getMsize()-1)
                cout << "Not acceptable Input. Try again to set Fire."<<endl;
            else{
                if(sim_map->set_fire(nx, ny))
                    cout << "New Fire was set succefully."<<endl;
                else
                    cout << "Fire could not be set. Try an other position without other fire on it." <<endl;
            }
        }
        else if(nOption==8){
            cout << "Give positions X and Y of Vehicle to make it broken:"<<endl;
            cout << "Enter X(acceptable values: 0 - "<<sim_map->getMsize()-1<<"):";
            cin >> sx;
            nx=atoi(sx.c_str());                   
            cout << "Enter Y(acceptable values: 0 - "<<sim_map->getMsize()-1<<"):";
            cin >> sy;
            ny=atoi(sy.c_str());
            if(nx<0 || ny<0 || nx>sim_map->getMsize()-1 || ny>sim_map->getMsize()-1)
                cout << "Not acceptable Input. Try again to set Fire."<<endl;
            else{
                if(sim_map->breakVehicle(nx, ny))
                    cout << "Vehicle is now Broken."<<endl;
                else
                    cout << "Vehicle did not get broken. Try an other position with a vehicle on it." <<endl;
            }          
        }
        else if(nOption==9)break;
        else cout<<"Wrong Option. Try Again."<<endl;
     
    }
    
}

/*emfanizei ola ta statistika gia tin ekswmoiwsi*/
void Simulation::showAllStats(void){
	printMap();
	sim_map->printMapStats();
	sim_map->printVehicleStats();	
	sim_map->printFireStats();    
}
