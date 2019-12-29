#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

extern char M[];
extern int  cardM;
extern unsigned char *overlinedR;
extern int cardA;
extern int offset;
extern char verbose;

extern void printv();
extern void fprintv();
extern void err();

#include "perm.h"
#include "sc.h"
#include "sf.h"

long random_at_most(long max);
int initialize (char *s, int *sl, int *cl, int *offset);
int c3d(char *M, int x, int y, int z, int cardM, int cardA, int offset);
int conv(char *p, int base, int offset);
char* successor(char*v, int len);
long ptol(char *v, long *ret, long *dis);

#define PROLOGUE(a) \
       "\
                 #include \"colors.inc\" \n\
	         #include \"shapes.inc\" \n\
	         #include \"textures.inc\"\n\n\
                 camera {       \n\
                    location <%d, %d, %d>\n\
                    look_at <2, 0.7, 0>       \n\
                 }            \n\n\
                 light_source { <0, 0, 0> color White}\n\
                 light_source { <%d+2, %d+2, %d+2> color White}\n\n\
                  plane {      \n\
                    <0, 1, 0>, 0 \n\
	            } \n\
	         \n ", a,a,a,a,a,a

/*
                    pigment { LightGrey }\n\
#define pIGMENT "pigment {      \n \
	         checker        \n \
	           color Yellow \n \
	           color MidnightBlue  \n \
	         }                \n \
		normal { bumps 0.4 scale 0.2 } \n\
		finish { phong 1 }\n"
*/
#define pIGMENT "pigment {      \n \
	         // checker        \n \
	           // color White \n \
	           color Grey  \n \
	         }                \n \
		normal { bumps 0.4 scale 0.2 } \n\
		finish { phong 1 }\n\
		\n\
		\n"

#define PIGMENT "pigment { \n\
          DMFWood4      // Pre-defined from textures.inc \n\
          scale 4       // Scale by the same amount in all \n\
                        // directions \n\
	  }\n	normal { bumps 0.4 scale 0.2 } \n\
		finish { phong 1 }\n"

/*
#define PIGMENT " pigment { hexagon Green, White, Yellow } \n   normal { bumps 0.4 scale 0.2 } \n\
	      finish { phong 1 }\n"
	      */
void help(void);
void ferr(char*);

int analize;

static char *px, *py, *pz;

int main (int argc, char *argv[])
{	int   i, x, y, z;
	int   ix, iy, iz;
	char *pstr,
	     *ofile,
	      verbose;
	FILE *f;
	float side = 1.0;
	int max;
	char *prologue = NULL;
	char *pigment = NULL;
	int max_size = 1;
	long ltmp;


	ofile = "stdout";
	verbose = 0;
	pstr = NULL;
	x = y = z = 0;
	max = 10;

	for (i=1; i<argc; i++)
	{	if (strcmp(argv[i], "--help")==0)
		{	help();
			return 0;
		}
		else if (strncmp(argv[i], "--string=", 9)==0)
		{	pstr = strdup(argv[i] + 9);
		}
		else if (strncmp(argv[i], "--input=", 8)==0)
		{	pstr = strdup(argv[i] + 8);
		}
		else if (strncmp(argv[i], "--output=", 9)==0)
		{	ofile = argv[i] + 9;
		}
		else if (strncmp(argv[i], "--x=", 4)==0)
		{	x = atoi(argv[i] + 4);
		}
		else if (strncmp(argv[i], "--y=", 4)==0)
		{	y = atoi(argv[i] + 4);
		}
		else if (strncmp(argv[i], "--z=", 4)==0)
		{	z = atoi(argv[i] + 4);
		}
		else if (strcmp(argv[i], "--verbose")==0)
		{	verbose = 1;
		}
		else if (strncmp(argv[i], "--max=", 6)==0)
		{	max = atoi(argv[i] + 6);
		}
		else if (strncmp(argv[i], "--prologue=", 11)==0)
		{	prologue = argv[i] + 11;
		}
		else if (strncmp(argv[i], "--pigment=", 10)==0)
		{	pigment = argv[i] + 10;
		}
		else if (strncmp(argv[i], "--max-size=", 11)==0)
		{	max_size = atoi(argv[i] + 11);
		}
		else
		{	ferr("args");
		}
	}

	if (verbose)
	{	fprintf(stderr, "output file = %s\n", ofile);
	}

	f = (strcmp(ofile, "stdout"))?
		fopen(ofile, "w") 
	  :
		stdout;

	if (pstr==NULL)
	{	ferr("missing --input");
		help();
	}

	if (y == 0 || z == 0)
	{	ferr("missing --y and/or --z");
		help();
	}

/*	body
 *      ----
 */

	if (prologue != NULL) {
		int c; FILE *g;
		g = fopen(prologue, "r");
		if (g == NULL) {
			ferr("--prologue file can't be read");
			help();
		}
		while ( (c=fgetc(g)) != EOF ) fputc(c, f);
		fclose(g);
	} else
	fprintf(f, PROLOGUE(max));

	strcpy(M, pstr);

	initialize(M, &cardM, &cardA, &offset);

	if (verbose)
	{	fprintf(stderr, "card M == %d, cardA == %d, offset == %d\n",
			cardM, cardA, offset);
	}

	i = 1;
	do {	c3d(M, x, y, z, cardM, cardA, offset);
		/*
		if (verbose)
			printf("[%s][%s][%s] ", px, py, pz);
		 */
		ix = conv(px, cardA, offset);
		iy = conv(py, cardA, offset);
		iz = conv(pz, cardA, offset);
		if (verbose)
			printf("[%d][%d][%d]\n", ix, iy, iz);
#if BOXES
		fprintf(f, "\n// Box no. %d\n", i);
		fprintf(f, "box {\n");
		fprintf(f, "\t<%d,%d,%d>, <%f,%f,%f>\n", ix, iy, iz,
			ix + side, iy + side, iz + side);
#else
		fprintf(f, "sphere {\n");
		if (max_size <= 1)
			fprintf(f, "\t<%d,%d,%d>, 1\n", ix, iy, iz);
		else {
			ltmp = random_at_most( (long)max_size);
			if (ltmp == 0L) ltmp = 1L;
			fprintf(f, "\t<%d,%d,%d>, %ld\n", ix, iy, iz, ltmp);
		}
#endif
		//fprintf(f, "%s\n", pIGMENT);
		if (pigment) {
			fprintf(f, "%s\n", pigment);
		} else {
			fprintf(f, "%s\n", PIGMENT);
		}
		fprintf(f, "\trotate y*5\n}\n");
/*
		fprintf(f, "\trotate <0,0,-clock*360>\n");
		fprintf(f, "\ttranslate <-pi,1,0>\n");
		fprintf(f, "\ttranslate <2*pi*clock,0,0>\n}\n");
*/
		i++;

	}		while (successor(M, cardM));


/*	closings
 *	--------
 */

	if (strcmp(ofile, "stdout")!=0)
	{	fclose(f);
	}
	free(pstr);
}



void help(void)
{
	fprintf(stderr, "feed-povray: creates a Povray script from a permutation file\n");
	fprintf(stderr, "Arguments: --input=string --output=filename\n");
	fprintf(stderr, "           --x=offset_x --y=offset_y --z=offset_z\n");
	fprintf(stderr, "           --max-size=max_radius --verbose\n");
	exit(-1);
}

void ferr(char* s)
{
	fprintf(stderr, "feed-povray: <%s>\n", s);
	exit(-2);
}

void fprintv(FILE*file,char*v){
	int i;
	long l,d,ord;

	ord= ptol(v,&l,&d);
#  ifdef QUANTUM
	if(ord%QUANTUM==0||ord%QUANTUM==1)
	{
#    endif

	fprintf(file,"%ld\t",ord);
	for(l= 0L,i= 0;i<cardM;i++)
	putc(v[i]+offset,file);
#       ifdef QUANTUM
	if(ord%QUANTUM==0)
#       endif
		putc('\n',file);
#       ifdef QUANTUM
	else
		putc('\t',file);
	}
#    endif
}

void printv(char*v){fprintv(stdout,v);}


int c3d(char *M, int x, int y, int z, int cardM, int cardA, int offset)
{
	int la, lb, lc;
	int a, b, c;
	int i;

	if (pz == NULL) 
	{
		px = strdup(M);
		py = strdup(M);
		pz = strdup(M);
	}

	la = y-x;
	lb = z-y;
	lc = cardM-z;

	memcpy(px, M+x, la); px[la] = '\0';
	memcpy(py, M+y, lb); px[lb] = '\0';
	memcpy(pz, M+z, lc); px[lc] = '\0';

	for (i=0; i<la; i++)
	{
		px[i] += offset;
	}
	for (i=0; i<lb; i++)
	{
		py[i] += offset;
	}
	for (i=0; i<lc; i++)
	{
		pz[i] += offset;
	}
}

int conv(char *p, int base, int offset)
{
	int n;
	int f;

	n = 0;
	f = 0;
	for(;;p++) {
		switch(*p) {
		case ' ':
		case '\t':
			continue;
		case '-':
			f++;
		case '+':
			p++;
		}
		break;
	}
	while(*p >= offset)
		n = n*base + *p++ - offset;
	return(f? -n: n);
}

// https://stackoverflow.com/questions/2509679/how-to-generate-a-random-integer-number-from-within-a-range
long random_at_most(long max) {
  unsigned long
    // max <= RAND_MAX < ULONG_MAX, so this is okay.
    num_bins = (unsigned long) max + 1,
    num_rand = (unsigned long) RAND_MAX + 1,
    bin_size = num_rand / num_bins,
    defect   = num_rand % num_bins;

  long x;

  srandom( time(0)+clock()+random() ); // added
  do {
   x = random();
  }
  // This is carefully written not to overflow
  while (num_rand - defect <= (unsigned long)x);

  // Truncated division is intentional
  return x/bin_size;
}


/*
      box {
        <-1,0  ,-1>,     // Near lower left corner
        < 1,0.5, 3>      // Far upper right corner
        rotate y*20     // Equivalent to "rotate <0,20,0>"
      }
*/
/* eof feedpovray.c */
/*
#define PROLOGUE(a) \
       "\
                 #include \"colors.inc\" \n\
	         #include \"shapes.inc\" \n\
	         #include \"textures.inc\"\n\n\
                 camera {       \n\
                    location <%d, %d, %d>\n\
                    look_at <2, 0.7, 0>       \n\
                 }            \n\n\
                 light_source { <0, 0, 0> color White}\n\
                 light_source { <%d+2, %d+2, %d+2> color White}\n\n\
                  plane {      \n\
                    <0, 1, 0>, 0 \n\
	            pigment { \n\
		      checker \n\
		        color Orange \n\
		        color Yellow \n\
	            } \n\
	         }\n ", a,a,a,a,a,a
*/
