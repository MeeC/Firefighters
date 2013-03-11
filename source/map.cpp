#include "globals.h"
#include "functions.h"
#include "map.h"

/*Dimiourgei ton xarti. O xartis eimai einai ena dianysma apo antikeimena typou Mapslot.*/
void Map::createMap(int map_size){
  	for(int i=0;i<map_size;i++){
		for(int j=0;j<map_size;j++){
			places.push_back(new Mapslot(i,j));
		}
	}      
}
/*vazei fwties se tyxaies theseis ston xarti*/
void Map::set_random_fires(int num_of_fires){
	int fire_x,fire_y;
	do{
		fire_x=randomness(m_map_size)-1;
		fire_y=randomness(m_map_size)-1;
		if(set_fire(fire_x,fire_y))num_of_fires--;
	}while(num_of_fires>0);
}

/*vazei fwtia se kapoia thesi ston xarti*/
bool Map::set_fire(int x, int y){
	if(!(places[convert_2d_to_1d(x,y,m_map_size)]->isFire())){
        fires.push_back(new Fire(x,y,m_map_size));
		places[convert_2d_to_1d(x,y,m_map_size)]->setFire();
		m_total_fires++; 
		m_current_fires++;
		return true; //true if set fire is successfull
	}
	else{
		//cout <<"Error: Could not set fire at point: ("<<x<<", "<<y<<")"<<endl;
		return false;
	}
}

/*eksapnwnei tis fwties. kathe fwtia eksaplnwnetai se 0 ews 3 theseis.*/
void Map::spread_fire(void){
    /*Epeidi to vector allazei dinamika krarame to twrino megethos wste na eksaplwthoun mono oi fwties pou vriskontai ston xarti
    * mexri tin xroniki stigmi pou vrisketai i prosomoiwsi mexri twra.*/
    int cur_fires=fires.size();
    for(int i=0;i<cur_fires;i++){
        /* Metavlites gia ton elegxo tou loop. H spread pairnei tyxaies times apo 0 ews 3 kai einai oi theseis pou tha eksaplwthei i fwtia.
        * H tries xrisimopoihtai san orio stis prospathies pou epitrepontai gia na mpei mia nea fwtia*/
        int spread_fires=randomness(4)-1, tries=20;
        //an stin thesi pou epilextike tyxaia vrisketai alli fwtia tote i tyxaia epomeni thesi epilegetai ksana
        while(spread_fires>0 && tries>0){ 
            //epilegoume tyxaia kapoia geitoniki thesi gia na eksaplwthei i fwtia
            int next_position = fires[i]->findNearbySlot(RANDOM);
            tries--; // meiwnoume tis prospathies pou epemeinan kathe fora pou epilegetai mia nea thesi.
            //ekteleitai an sti nea thesi den vrisketai idi fwtia   
            if(set_fire(places[next_position]->getMapX(),places[next_position]->getMapY())){
                spread_fires--;
            }
        }
    }    
}

/*svinei mia fwtia stin thesi x,y*/
void Map::extinguish_fire(int x, int y){
    if(places[convert_2d_to_1d(x,y,m_map_size)]->isFire()){
        for(int i=0;i<fires.size();i++){
            if(fires[i]->getPositionX()==x && fires[i]->getPositionY()==y){
                delete fires[i];
                fires.erase(fires.begin()+i);
                break;    
            }    
        }        
        places[convert_2d_to_1d(x,y,m_map_size)]->clearFire();
        m_current_fires--;
    }
}

/*dimiourgei kai prosthetei tyxaia ston xarti enan arithmo oximatwn xrisimopoiwntas tin add_vehicle*/
void Map::add_random_vehicles(int num_of_vehicles){
	int pos_x,pos_y,type;
	do{
		type=randomness(4)-1;
		pos_x=randomness(m_map_size)-1;
		pos_y=randomness(m_map_size)-1;
		if(add_vehicle(pos_x,pos_y,type))num_of_vehicles--;
	}while(num_of_vehicles>0);

}

/* dimiourgei kai prosthetei ena oxima typou type ston xarti*/
bool Map::add_vehicle(int x, int y, int type){
	if(!(places[convert_2d_to_1d(x,y,m_map_size)]->isVehicle())){
		if(type==AIRPLANE){ 
			vehicles.push_back(new Airplane(x,y,m_map_size));
			m_num_of_aerial++; 
		}
		else if(type==HELICOPTER){ 
			vehicles.push_back(new Helicopter(x,y,m_map_size));
			m_num_of_aerial++;
		}
		else if(type==TRUCK){ 
			vehicles.push_back(new Truck(x,y,m_map_size));
			m_num_of_ground++;
		}
		else if(type==CAR){ 
			vehicles.push_back(new Car(x,y,m_map_size));
			m_num_of_ground++;
		}
		places[convert_2d_to_1d(x,y,m_map_size)]->setVehicle();
		return true; //true if vehicle addition is successfull
	}
	else{
		//cout <<"Error: Could not add vehicle at point: ("<<x<<", "<<y<<")"<<endl;
		return false;
	}
}

/*metakinei ena oxima*/
void Map::move_vehicle(Vehicle* v){
    /*0 mexri na ginei i kinisi kapoiou oximatos ,i tries xrisimopoihtai san orio stis prospathies pou epitrepontai gia mia metakinisi*/
    int move_done_flag=0, tries=20; 
    /*an stin thesi pou epilextike tyxaia vrisketai kapoio allo oxima tote i tyxaia epomeni thesi epilegetai ksana
    * An to oxima einai leitourgiko kineitai kanonika alliws to stelnoume sto kentro tis pirosvestikis*/
    while(move_done_flag==0 && tries>0 && v->isFunctional()){ 
        //epilegoume tyxaia tin epomeni geitoniki thesi pou tha kinithei to antikeimeno
        int next_position = v->findNearbySlot(RANDOM);
        tries--; // meiwnoume tis prospathies pou epemeinan kathe fora pou epilegetai mia nea thesi.
        //ekteleitai an sti nea thesi den vrisketai allo oxima i an prokeitai gia to kentro tis pyrosvestikis   
        if(!(places[next_position]->isVehicle()) || places[next_position]->isHQ()){
            places[v->getMapSlotID()]->clearVehicle(); //vgazoume to oxima ap tin twrini thesi
            places[next_position]->setVehicle(); //topothetoume to oxima stin nea thesi ston xarti
            v->moveVehicleTo(next_position); //allazoume kai tin thesi sto antikeimeno tou oximatos
            v->consumeFuel(); //katalanwnoume tin venzini pou xreiastike gia tin metakinisi
            v->incrTotalFuel(); //afksanoume ta synolika kafsima pou katanalwsw to oxima
            /*an i nea thesi tyxei na einai to kedro, tote gemizoume kafsima kai nero to oxima*/
            if(places[next_position]->isHQ())v->doService();
            move_done_flag=1;
        }
    }
    /*An to oxima exei parousiasei provlima to xeirizomaste diaforetika stelnontas sto pros to kentro*/
    if(!(v->isFunctional())){
        /*H syntomoteri apostasi pou vrethike (arxikopoieitai se megalo arithmo) kai i kaliteri pithani epomeni thesi*/
        int shortest_dist=9999, best_next_pos;
        //H apostasi tou kentrou apo tin twrini thesi
        shortest_dist=getManhattanDistCirc(v->getPositionX(),v->getPositionY(),HQ->getPositionX(),HQ->getPositionY(),getMsize());
        best_next_pos=v->getMapSlotID();
        // elegxoume poia geitoniki thesi vrisketai pio konta sto kentro
        for(int i=UP;i<DOWNRIGHT+1;i++){
            int pos=v->findNearbySlot(i);
            int dist=getManhattanDistCirc(places[pos]->getMapX(),places[pos]->getMapY(),HQ->getPositionX(),HQ->getPositionY(),getMsize());   
            /*Gia na thewrithei mia thesi kaliteri epilogi prepei na vrisketai poio konta sto kentro alla kai na min exei kapoio oxima panw*/
            if(dist<shortest_dist && !(places[pos]->isVehicle())){
                shortest_dist=dist;
                best_next_pos=pos;    
            }                
        }    
        places[v->getMapSlotID()]->clearVehicle(); //vgazoume to oxima ap tin twrini thesi
        places[best_next_pos]->setVehicle(); //topothetoume to oxima stin nea thesi ston xarti
        v->moveVehicleTo(best_next_pos); //allazoume kai tin thesi sto antikeimeno tou oximatos 
        /*an ftasame sto kedro, tote gemizoume kafsima kai nero to oxima*/
        if(places[best_next_pos]->isHQ())v->doService();       
    }     
}

/*vazei ena oxima na svisei tis fwties gyrw tou*/
void Map::fight_nearby_fires(Vehicle * v){
    //elegxoume an to oxima vrisketai panw se vwtia
    if(places[v->getMapSlotID()]->isFire() && v->isFunctional()){
        //an yparxei fwtia tin svinoume
        extinguish_fire(v->getPositionX(),v->getPositionY()); 
        v->useWater(); //katalwnoume to nero tis pyrosvesis
        v->incrTotalWater();
    }
    int slot;
    for(int i=UP;i<DOWNRIGHT+1;i++){
        /*xrisimopoioume aftin tin synartisi me orisma kathe pithani katefthinsi gia
        * na vroume oles tis geitonikes theseis kai na psaksoume gia fwtia*/
        slot=v->findNearbySlot(i);
        //svinoume tin fwtia se opoia ap tis geitonikes theseis exei anapsei.     
        if(places[slot]->isFire() && v->isFunctional()){
            extinguish_fire(places[slot]->getMapX(), places[slot]->getMapY());
            v->useWater(); //katalwnoume to nero tis pyrosvesis
            v->incrTotalWater();   
        }  
    }
}

/*metakinei ola ta oximata kai ta vazei na svinoun fwrties*/
void Map::move_and_extinguish(void){
    m_num_of_damaged=0; //metrame ap to 0 ta provlimatika oximata aftou tou gyrou
    for(int i=0;i<vehicles.size();i++){
        /*se kathe xroniki stigmi afksanetai ilikia tou oximatos*/
        vehicles[i]->incrAge();
        /*to oxima kineitai oses fores einai i taxitita tou*/
        int moves=vehicles[i]->getSpeed();        
        while(moves>0){
            /*Mono ta oximata xwris provlimata svinoun fwties*/
            if(vehicles[i]->isFunctional())
                fight_nearby_fires(vehicles[i]);
            /*Kathe oxima kineitai. An einai leitourgiko tha kinithei kanonika alliws tha katefthinthei sto kentro*/
            move_vehicle(vehicles[i]);
            moves--;
        }
        if(!(vehicles[i]->isFunctional()))m_num_of_damaged++; //katagrafoume ta inactive        
    }    
    
}

/*Xrisimopoieitai se kathe gyro kai prokalei vlaves sta oximata me pithanotita analogi me tin
* ilikia tous. Episis aposyrei oximata pou vriskontai stin fasi tis aposirsis*/
void Map::break_and_withdraw(void){
    for(int i=0;i<vehicles.size();i++){
        if(vehicles[i]->isWithdrawal()){
            places[vehicles[i]->getMapSlotID()]->clearVehicle();
            (vehicles[i]->getType()==AIR)? m_num_of_aerial-- : m_num_of_ground--;
            delete vehicles[i];
            vehicles.erase(vehicles.begin()+i); 
            m_num_of_damaged--; // to oxima den einai inactive (efyge apo tin prosomoiwsi) 
            break;
        }
        else if(vehicles[i]->isFunctional()){
            int break_possibility, v_age, v_max_age;
            v_age = vehicles[i]->getAge();
            v_max_age = vehicles[i]->getMaxAge();
            /*analoga me tin ilikia tou oximatos 1/4, 1/2, 3/4 tis megistis ilikias prokiptei to pososto vlavwn*/
            if(v_age>v_max_age/4)break_possibility=5;
            if(v_age>v_max_age/2)break_possibility=10;
            if(v_age>v_max_age/2+v_max_age/4)break_possibility=15;
            if(randomness(100)<break_possibility)
                vehicles[i]->breakDown();    
        } 
    }
}

/*Prokalei vlavi sto oxima pou vrisketai stin thesi x,y pou dilwnoume*/
bool Map::breakVehicle(int x, int y){
    if(places[convert_2d_to_1d(x,y,m_map_size)]->isVehicle()){
        for(int i=0;i<vehicles.size();i++){
            if(vehicles[i]->getMapSlotID()==convert_2d_to_1d(x,y,m_map_size)){
                vehicles[i]->breakDown();
                break;   
            }
        }
        return true;
    }
    else
        return false;
}


/* Methodoi pou ektypwnoun stoixeia kai plirofories gia ta antikeimena tou kosmou mas*/
void Map::printMapStats(void){
	cout << "Simulation Stats"<<endl;
	cout << "Map Size: "<<m_map_size<<endl;
	cout << "Fire Headquarters: ("<<HQ->getPositionX()<<", "<<HQ->getPositionY()<<")"<<endl;
	cout << "Total Vehicles: "<<m_num_of_aerial+m_num_of_ground<<endl;
	cout << "Ground Vehicles: "<<m_num_of_ground<<endl;
	cout << "Aerial Vehicles: "<<m_num_of_aerial<<endl;
	cout << "Non Active Vehicles: "<<m_num_of_damaged<<endl;
	cout << "Total Fires Started: "<<m_total_fires<<endl;
	cout << "Fires Extinguished: "<<m_total_fires-m_current_fires<<endl;
	cout << "Currently active fires: "<<m_current_fires<<endl;
    cout << endl;
}

void Map::printFireStats(void){
	cout << "Fire Stats"<<endl;
	cout << "Currently active fires: "<<m_current_fires<<endl;
	cout << "Total Fires Started: "<<m_total_fires<<endl;
	cout << "Fires Extinguished: "<<m_total_fires-m_current_fires<<endl;
	cout << "Coordinates of Active Fires: ";
	for(int i=0;i<places.size();i++){
            if(places[i]->isFire())
                cout << "("<<places[i]->getMapX()<<","<<places[i]->getMapY()<<")";
    }
	cout << endl;
}

void Map::printVehicleStats(void){
	cout << "Vehicle Stats"<<endl;
	cout << "Total Vehicles: "<<m_num_of_aerial+m_num_of_ground<<endl;
	cout << "Currently active Vehicles: "<<m_num_of_aerial+m_num_of_ground-m_num_of_damaged<<endl;
	cout << "Vehicle Information Details: "<<endl;
	for(int i=0;i<vehicles.size();i++){
        vehicles[i]->showID();
    }    
	cout << endl;
}
