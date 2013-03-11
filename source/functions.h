#ifndef FUNCTIONS_H
#define FUNCTIONS_H

/*epistrefei tyxaio arithmo sto evros 1-range*/
int randomness(int range);

/*epistrefei me vasi ta x,y se ena plegma ton arithmo pou astoixei stin thesi tous se monodiastato pinaka*/
int convert_2d_to_1d(int x, int y, int grid_size);

/*epistrefei ton mikrotero akeraio*/
int minimum(int a, int b);

/*epistrefei tin apostasi manhattan se metaksi 2 simeiwn se kikliko xarti*/
int getManhattanDistCirc(int current_x, int current_x, int target_x, int target_y, int grid_size);

#endif
