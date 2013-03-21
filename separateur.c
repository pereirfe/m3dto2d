#include <stdio.h>
#include <stdlib.h>

#define FENTREE "img00.kin"
#define FA "a.kin"
#define FB "b.kin"
#define FPGMA "ga.pgm" 
#define FPGMB "gb.pgm"
#define FPGMO "go.pgm"

#define INSIZE 307200

void make_pgm(FILE*, FILE*);

int main(void){
  FILE* in1, *in2, *in3, *a, *b, *pgm;
  char c;
  int i = 0;

  if( !(in1 = fopen(FENTREE, "rb"))) {
      puts("Fichier Non trouvée");
    }

  a = fopen(FA, "wb");
  b = fopen(FB, "wb");
  
  while(i<INSIZE){
    fread(&c,1,1,in1);
    if(i%2) fwrite(&c,1,1,a);
    else  fwrite(&c,1,1,b);
    i++;
  }
    
  fclose(in1);
  fclose(a);
  fclose(b);

  in1 = fopen(FA, "rb");
  in2 = fopen(FB, "rb");
  in3 = fopen(FENTREE, "rb");

  pgm = fopen(FPGMA, "wb");
  make_pgm(in1, pgm);
  fclose(pgm);

  pgm = fopen(FPGMB, "wb");
  make_pgm(in2, pgm);
  fclose(pgm);

  pgm = fopen(FPGMO, "wb");
  make_pgm(in3, pgm);
  fclose(pgm);

}


void make_pgm(FILE* fin, FILE* fout){
  char c;
  int i;

  fprintf(fout, "P5\n640 480\n80\n");
  for(i=0; i<INSIZE/2; i++){
    fread(&c,1,1,fin);
    fwrite(&c,1,1,fout);
  }
}

void make_histogram(long long int* stream, int size_stream, int size_nod, int base, int top){ //works just in 64b...
  int range = top - base;
  int* hist = (int*)malloc(range*sizeof(int));
  int i;

  for(i=0; i<range; i++){
    hist[i] = 0;
  }




  
  
  

  
}    
  
   
