#include "globals.h"
#include "vehicle.h"
#include "functions.h"
#include "map.h"
#include "simulation.h"

int main(int argc, char *argv[]){

	/*H srand() arxikopoiei enan arithmo seed, pou xrisimopoieitai apo tin rand() gia na paragei tyxaious arithmous-> Epeidi
	vazoume tin srand na xrisimopoei tin sinartisi time() to seed tha einai i wra se defterolepta kai tha einai diaforetiki
	kathefora pou ekteleitai to programma-> Synepws kanoume tin rand() na doulevei san gennitria tyxaiwn arithmwn->*/	
	srand ( (unsigned)time(NULL) );
	/*Vehicle* air=new Aerial(13,45);
	air->printStatus();
	Vehicle* air2=new Ground(3,5);
	air2->printStatus();
	vector<Vehicle*> G;	
	for (int i=10;i<20;i++)
		(i%2)? G.push_back(new Aerial(i+100,i+10)) : G.push_back(new Ground(i+100,i+10));
		//G.push_back(new Vehicle(i+i,i+i+100));
	cout << "Vector Size: "<< G.size()<<endl;
	delete G[3];
	G.erase(G.begin()+3);
	for(int i=0;i<G.size();i++)
			G[i]->printStatus();
	cout << "Vector Size: "<< G.size()<<endl;*/


	Simulation *sim= new Simulation(14,15,20);

    system("PAUSE");
    return EXIT_SUCCESS;
}
