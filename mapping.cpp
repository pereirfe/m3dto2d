#include <math.h>
#define DIM_F 4000
#define DIM_X 640
#define DIM_Y 480
#define SIZE_ROB_PX 200 // Size of the robot

#define END_VISION 5 // in meters
#define GRAY 194

#define SCALE_GMAP 36 // Scale used in the gray map. Pix/m

#define Y0 (DIM_Y - SIZE_ROB_PX) // Horizontal reference line for the robot 
#define X0 (DIM_X >> 1) // Vertical reference

#define GRID_OFFSET 10 // Distance between lines
#define GRID_UPPER DIM_Y/2  
#define GRID_LOWER 0


extern double __gamma; // Angle between the robot's line of sight and the 'compass'

class Mapping {

private:
  FILE* _map;
  double hash_dist[1<<11]; // distance in meters for each rawDisparity from 0 to 2048 

} ;


Mapping::Mapping(FILE* map){
  int i;
  const double k1 = 1.1863; // For numeric approximation
  const double k2 = 2842.5; // For numeric approximation
  const double k3 = 0.1236; // For numeric approximation
  this->_map = map;
  
  for ( i=0; i<2048; i++){
    this->hash_dist = k3 * tan(i/k2 + k1);
  }


}

void Mapping::process(FILE* image, int cx, int cy){ // figure, current x, current y
  char *map;
  char dist[DIM_X][DIM_Y];
  char block[DIM_X];
  int i, j;
  int sq_delta_y;
  int gx, gx; // x , y in the gray map

  double d_bar; // simulated distance in the horizontal reference (P_bar)
  double alpha; // Angle between (X0,Y0) and P_bar(x, Y0)

  // read image and put in img..
  // use mmap for accessing map

  for(i=0; i<DIM_X; i++){
    block[i] = 0;
  }

  for(i=GRID_LOWER; i<GRID_UPPER; i+=GRID_OFFSET){
    sq_delta_y = (i-Y0)*(i-Y0);
    for(j=0; j<DIM_X; j++){
      d_bar = sqrt((dist[j][i]*dist[j][i])-sq_delta_y);

      if(d_bar < block[j]) { 
	block[j] = d_bar; 
      } else { continue; }
    }
  }

  
  for(i=0; i<DIM_X; i++){
    d_bar = block[i];
    if(d_bar > END_VISION) continue;
    
    alpha = asin( (j-X0)/d_bar );
    d_bar*= SCALE_GMAP;

    gx = (int)(cx - d_bar*cos(__gamma+alpha));  
    gy = (int)(cy - d_bar*sin(__gamma+alpha));

    //put in the gray map
    map[gy*DIM_F + gx] =  GRAY;
  }
}
