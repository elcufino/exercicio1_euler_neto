//#define EIGENLIB			// uncomment to use Eigen linear algebra library
//#define NO_POINTER_INIT	// uncomment to disable pointer checking

#include "fun_head_fast.h"

// do not add Equations in this area

MODELBEGIN


// X
EQUATION("X")
RESULT(VL("X",1)+uniform(0,1))


// SOMA
EQUATION("X_Sum")
	v[0]=0;
	CYCLE(cur, "FIRM")
		{
		v[1]=VS(cur,"X");
		v[0]=v[0]+v[1];
		}
RESULT(v[0])


// MÉDIA
EQUATION("X_Ave")
	v[0]=0;
	v[1]=0;
	v[2]=0;
	CYCLE(cur, "FIRM")
		{
		v[3]=VS(cur,"X");
		v[0]=v[0]+v[3];
		v[1]=v[1]+1;
		}
	if(v[1]==0)	v[2]=0; else v[2]=v[0]/v[1]
RESULT(v[2])


// MÁXIMO
EQUATION("X_Max")
	v[0]=0;
	CYCLE(cur, "FIRM")
		{
		v[1]=VS(cur,"X"); 
		if(v[1]>=v[0]) 	v[0]=v[1]; else v[0]=v[0];
		}
RESULT(v[0])


// MARKETSHARE
EQUATION("X_Share")
RESULT((V("X")/V("X_Sum"))) 


// SOMA DE MARKETSHARE
EQUATION("Share_Sum")
	v[0]=0;
	CYCLE(cur, "FIRM")
		{
		v[1]=VS(cur,"X_Share");
		v[0]=v[0]+v[1];
		}
RESULT(v[0])


// EMPRESA LÍDER
EQUATION("Leader")
/*	v[0]=0;
	v[1]=0;
	v[2]=1;
	CYCLE(cur, "FIRM")
		{
		v[3]=VS(cur,"X_Share");
		if(v[3]<v[0]) 
		{v[2]=v[2]+1;}
		else
		{v[0]=v[3] ; v[1]=v[1]+v[2] ; v[2]=1;}
		}
RESULT(v[1])
*/
RESULT(SEARCH_INST(SEARCH_CND("X", V("X_Max"))))

// RANKING
EQUATION("Rank") // for each Xi, how many X|(Xj >= Xi, i=j). If n Xi values equal, both will be rank n+1. Ex: {100, 50, 30, 30, 25} have ranks {1, 2, 5, 5, 3}.
	v[0]=0;
	CYCLE(cur, "FIRM")
		{
		v[1]=VS(cur, "X_Share");
		CYCLE(cur1, "FIRM")
			{
			v[2]=VS(cur1,"X_Share");
			if(v[2]>=v[1]) 	v[0]=v[0]+1; else v[0]=v[0];
			}
		WRITES(cur, "firm_rank", v[0]);
		v[0]=0;
		}
RESULT(1)


MODELEND

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}
