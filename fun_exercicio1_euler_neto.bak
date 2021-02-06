//#define EIGENLIB			// uncomment to use Eigen linear algebra library
//#define NO_POINTER_INIT	// uncomment to disable pointer checking

#include "fun_head_fast.h"

// do not add Equations in this area

MODELBEGIN


// PREÇO dP% = a*dMS%
EQUATION("Price")
	v[0]=VL("X_Share",1);
	v[1]=VL("X_Share",2);
	v[2]=VL("Price",1);
	v[3]=V("elast_marketshare_price");
	if(v[1]!=0) v[4]=(v[0]-v[1]/v[1]); else v[4]=v[0];
	v[5]=v[2]*(1+v[3]*v[4]);
RESULT(v[5])


// QUALIDADE
EQUATION("Quality")
	v[0]=VL("Quality",1);
	v[1]=norm(0,1);
	if(v[1]>0) v[0]=v[0]+v[1]; v[0]=v[0]
RESULT(v[0])


// VENDAS v.1 - Vendas = A + B*Preço + C*Qualidade -> Vt = Vt-1 + B*delta preço + C*delta qualidade
EQUATION("X")
	v[0]=V("Price");
	v[1]=VL("Price",1);
	v[2]=V("Quality");
	v[3]=VL("Quality",1);
	v[4]=VL("X",1);
	v[5]=V("elast_price_demand")*(v[0]-v[1]) + V("elast_quality_demand")*(v[2]-v[3]) + v[4];
RESULT(v[5])


//VENDAS v.2 - Vendas a la Cobb-Douglas: X = P^epd*Qual^eqd - NUNCA ATIVE ESSE CÓDIGO, É HORRÍVEL DEMAIS PRA SER REAL
/*
EQUATION("X")
v[0]=V("Price");
v[1]=VL("Price",1);
v[2]=V("Quality");
v[3]=VL("Quality",1);
v[4]=VL("X",1);
v[5]=pow(v[0], V("elast_price_demand"));
v[6]=pow(v[2], V("elast_quality_demand"));
v[7]=pow(v[1], V("elast_price_demand"));
v[8]=pow(v[3], V("elast_quality_demand"));
v[9]=v[1]+v[5]*v[6]-v[7]*v[8];
RESULT(v[9])
*/


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
RESULT(SEARCH_INST(SEARCH_CND("X", V("X_Max"))))


// RANKING
EQUATION("Rank")
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


// HHI
EQUATION("HHI_inv")
	v[0]=0;
	CYCLE(cur, "FIRM")
		{
		v[1]=VS(cur, "X_Share");
		v[2]=pow(v[1],2);
		v[0]=v[0]+v[2];
		}
RESULT(1/v[0])

/*
Mudar número de objetos

EQUATION("EntryExit"
	v[0]=V("switch_entry");
	if(v[0]==1)
		{
		cur=SEARCH_CND("rank",10); //procure a ultima firma
		DELETE(cur); //MATE
		cur1=SEARCH_CND("rank", 5);
		ADDOBJ_EX("FIRM",cur1); //adicione uma firma tomando por exemplo cur1
		}
RESULT(1)
*/


MODELEND

// do not add Equations in this area

void close_sim( void )
{
	// close simulation special commands go here
}
