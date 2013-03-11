#include "globals.h"
#include "functions.h"
#include "map_object.h"

/*Ypologizei tis syntetagmenes kapoias diplanis thesis kai epistefei to id pou antistoixei 
* se aftin tin thesi. Me orisma random i kinisi einai tyxaia,
* alliws ginetai i kinisi pros tin katefthinsi pou dilwnei to orisma LEFT,UP,DOWNLEFT klp.
* An to antikeimeno prospathisei na vgei eksw ap ton xarti pernaei stin apenanti plevra.
* Gia na xrisimopoihthei prepei to antikeimeno na gnwrizei to megethos tou xarti.*/
int Map_object::findNearbySlot(int type_of_move){

	int cur_x, cur_y, max_dim, moveto;
	cur_x=getPositionX();
	cur_y=getPositionY();
	max_dim=getMaxDim();
	if(type_of_move==RANDOM)
	   moveto=randomness(8);
	else
	   moveto=type_of_move;

	switch (moveto){
	   case UP:
			cur_x--;
			if(cur_x<0)cur_x=max_dim-1;	
			break;		   	
		case DOWN:
			cur_x++;
			if(cur_x==max_dim)cur_x=0;
			break;	
		case LEFT:
			cur_y--;
			if(cur_y<0)cur_y=max_dim-1;
			break;	
		case RIGHT:
			cur_y++;
			if(cur_y==max_dim)cur_y=0;
			break;	   
	   case UPLEFT:
			cur_x--,cur_y--;
			if(cur_x<0)cur_x=max_dim-1;
			if(cur_y<0)cur_y=max_dim-1;	
			break;		   	
		case DOWNLEFT:
			cur_x++,cur_y--;
			if(cur_x==max_dim)cur_x=0;
			if(cur_y<0)cur_y=max_dim-1;
			break;	
		case UPRIGHT:
			cur_x--,cur_y++;
			if(cur_x<0)cur_x=max_dim-1;
			if(cur_y==max_dim)cur_y=0;
			break;	
		case DOWNRIGHT:
			cur_x++,cur_y++;
			if(cur_x==max_dim)cur_x=0;
			if(cur_y==max_dim)cur_y=0;
			break;		   
 		   
	}

    return convert_2d_to_1d(cur_x,cur_y,getMaxDim());
}

/*Epistrefei tin thesi pou exei sto monodiastato dianisma to antikeimeno me vasi tis x kai y syntetagmenes*/
int Map_object::getMapSlotID(void){
    return convert_2d_to_1d(m_pos_x, m_pos_y,getMaxDim());
}
