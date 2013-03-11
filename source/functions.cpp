#include "globals.h"
#include "functions.h"

/*H sinartisi afti pairnei san orisma enan akeraio pou einai ena evros timwn kai epistrefei mia tyxaia timi apo afto
to evros me tin xrisi tis rand() PROSOXH!: gia na einai kathe fora tyxaioi oi arithmoi pou paragontai tha prepei kapou
stin arxi tou programmatos mas na klithei i srand pou dinei ena diaforetiko kathe fora seed stin rand me vasi to opoio 
tha paragontai oi arithmoi.*/
int randomness(int range)
{
	int rand_num;
	/*H rand me vasi kapoion arithmo seed paragei tyxaious arithmous. To akeraio ypoloipo tis diairesis aftou tou arithmou
	me tin range mas dinei enan aritmo sto evros range. To +1 einai gia na ksekinaei to evros apo to 1 kai na teleiwnei sto
	range. Ekxwroume tin tyxaia timi sti meravliti rand_num*/
	rand_num = rand()%range +1;
	/*epistrefoume tin tyxaia timi pou ftiaksame */
	return rand_num;
}

//epistrefoume ton mikrotero akeraio. Se periptwsi isotitas epistrefoume ton deftero.
int minimum(int a, int b){ return (a<b) ? a : b; }

/*Epistrefei tin thesi pou exei sto monodiastato dianisma mia thesi me syntetagmenes x kai y*/
int convert_2d_to_1d(int x, int y, int grid_size){
    return x*grid_size+y;
}

/*Ypologizei tin apostasi manhattan metaksi dio simeiwn se enan kykliko xarti opou oi akres syndeontai metaksi tous*/
int getManhattanDistCirc(int current_x, int current_y, int target_x, int target_y, int grid_size){
    int dx = minimum(abs(current_x-target_x),grid_size-abs(current_x-target_x));
    int dy = minimum(abs(current_y-target_y),grid_size-abs(current_y-target_y));  
    return dx+dy;   
}
