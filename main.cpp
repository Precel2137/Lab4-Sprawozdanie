#include "rk4.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define lambda 4.0


double MetEulera(double T,double Y,double H,double (*fun)(double,double))
{
		Y+=H*fun(T,Y);
		return Y;
}
double fun(double T, double Y)
{
	return lambda*Y;
}
double analityczna(double T0,double T,double Y0)
{
	return Y0*exp(lambda*(T-T0));
}

void main()
{
	double tk,t0,y0,h,t,rozmiarPrzedzialu,N,WynikEu,WynikRK,bladEu,bladRK,WynikAn;
	printf("Podaj wartosci poczatkowe i koncowe przedzialu:\n");
	scanf("%lf",&t0);
	scanf("%lf",&tk);
	printf("Podaj wartosc poczatkowa y0:\n");
	scanf("%lf",&y0);
	rozmiarPrzedzialu = tk - t0;
	FILE* f;
	f=fopen("wyniki.txt","w");
	for(int i=0; i<7; i++)
	{
		N=pow(2.,i);
		h = rozmiarPrzedzialu/N;
		WynikEu = WynikRK = y0;
		t = t0;
		for(int j=0; j<N; j++)
		{
			t+=h;
			WynikAn = analityczna(t0,t,y0);
			WynikEu = MetEulera(t,WynikEu,h,fun);
			bladEu = abs(WynikEu - WynikAn)/abs(WynikAn);
			WynikRK = rk4(t,WynikRK,h,fun);
			bladRK = abs(WynikRK - WynikAn)/abs(WynikAn);
			if(i==6){printf("t: %lf\n (metoda eulera) y: %lf\t Blad wzgledny: %lf\n (metoda RK) y: %lf\t Blad wzgledny: %lf\n",t,WynikEu,bladEu,WynikRK,bladRK);}
			if(j == N-1)
			{
				fprintf(f,"%lf\t%lf\t%lf\t%lf\n",N,h,bladEu,bladRK);
			}
		}
	}
	fclose(f);
	scanf("%lf",&h);
	
}

