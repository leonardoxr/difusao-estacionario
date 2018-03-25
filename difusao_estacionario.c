#include<stdio.h>
#include<math.h>
#include<string.h>
#include<stdlib.h>


void solve_tridiagonal_in_place_reusable ( double x[],double a,double b,double c, int N);


void main()
{

    FILE *arq;
    arq = fopen("difusao_est.txt", "w+");


    double a,b,c,estado_novo[101];
    int i,j,jmax;

    jmax = 101;


//condição inicial
    for (j = 1 ; j < jmax ; j++)
    {
        estado_novo[j] = 0;

    }

//condições de contorno
    estado_novo[0] = 1;
    estado_novo[jmax-1] = 0;






    a = 1;
    b = -2;
    c = 1;



    estado_novo[1] = estado_novo[1] -estado_novo[0];
    estado_novo[jmax-2] = estado_novo[jmax-2] -estado_novo[jmax-1];

    solve_tridiagonal_in_place_reusable(estado_novo,a,b,c,jmax);



    for(j = 0 ; j < jmax ; j++)
    {

        fprintf(arq, "%d %lf\n", j,estado_novo[j]);
    }



    fclose(arq);

}

void solve_tridiagonal_in_place_reusable (double x[],double a,double b,double c, int N)

{

    double m;
    int n;


    double *cfinal;
    cfinal = malloc ( N * sizeof ( double )  ) ;

    cfinal [1] = c/ b;
    x [1] = x [1] / b;

    /* loop de 2 a N - 2 inclusive */
    for ( n = 2; n < N-1 ; n ++)
    {
        m = 1.0 / ( b  - ( cfinal[ n - 1] * a ) );
        cfinal [ n ] = c * m ;


        x [ n ] = ( x [ n ] - a  * x [ n - 1]) * m ;
    }


    /* loop de N - 2 a 0 exclusive */
    for (n = (N - 2) ; n > 0; n--)
    {
        x [ n ] = x [ n ] - cfinal [ n ] * x [ n + 1];
    }


    free ( cfinal );

}
