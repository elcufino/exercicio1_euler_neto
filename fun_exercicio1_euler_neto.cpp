//#define EIGENLIB			// uncomment to use Eigen linear algebra library
//#define NO_POINTER_INIT	// uncomment to disable pointer checking

#include "fun_head_fast.h"

// do not add Equations in this area

MODELBEGIN

// insert your equations here, between the MODELBEGIN and MODELEND words

EQUATION("X") //X
RESULT(VL("X",1)+uniform(0,1))


EQUATION("X_Sum") //Soma
v[0]=0;
CYCLE(cur, "FIRM")
{
	v[1]=VS(cur,"X");
	v[0]=v[0]+v[1];
}
RESULT(v[0])


EQUATION("X_Ave") //Média
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


EQUATION("X_Max") //Máximo
v[0]=0;
CYCLE(cur, "FIRM")
{
	v[1]=VS(cur,"X");
	if(v[1]>=v[0]) 	v[0]=v[1]; else v[0]=v[0];
}
RESULT(v[0])


EQUATION("X_Share") //Marketshare
RESULT((V("X")/V("X_Sum")))


EQUATION("Share_Sum") //Soma de Marketshare
v[0]=0;
CYCLE(cur, "FIRM")
{
	v[1]=VS(cur,"X_Share");
	v[0]=v[0]+v[1];
}
RESULT(v[0])


EQUATION("Leader") //Who is the boss?
v[0]=0; //Share do campeão
v[1]=0; //Token de posição
v[2]=1; //Token de campeão
CYCLE(cur, "FIRM")
{
	v[3]=VS(cur,"X_Share");
	if(v[3]<v[0]) 
	{v[2]=v[2]+1;} //Challenger perde e aumenta token do campeão
	else
	{v[0]=v[3] ; v[1]=v[1]+v[2] ; v[2]=1;} //Challenger ganha, vira novo campeão, transfere tokens do campeão para posição e reinicia o streak de vitórias
}
RESULT(v[1])


MODELEND

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}
