/*********************************************************
'*                   SIMPLEX METHOD                      *
'*                   --------------                      *
'*                                                       *
'* LIST OF MAIN VARIABLES:                               *
'*                                                       *
'*  R:          MAXIMIZE = Y, MINIMIZE = N               *
'*  NV:         NUMBER OF VARIABLES OF ECONOMIC FUNCTION *
'*              (TO MAXIMIZE OR MINIMIZE).               *
'*  NC:         NUMBER OF CONSTRAINTS                    *
'*  TS:         SIMPLEX TABLE OF SIZE NC+1 x NV+1        *
'*  R1:         =1 TO MAXIMIZE, =-1 TO MINIMIZE          *
'*  R2:         AUXILIARY VARIABLE FOR INPUTS            *
'* NOPTIMAL     BOOLEAN IF FALSE, CONTINUE ITERATIONS    *
'*  XMAX:       STORES GREATER COEFFICIENT OF ECONOMIC   *
'*              FUNCTION.                                *
'*  RAP         STORES SMALLEST RATIO > 0                *
'*  V:          AUXILIARY VARIABLE                       *
'*  P1,P2:      LINE, COLUMN INDEX OF PIVOT              *
'*  XERR:       BOOLEAN IF TRUE, NO SOLUTION.            *
'* ----------------------------------------------------- *
'* PROBLEM DESCRIPTION:                                  *
'* A builder of houses can make 3 kinds of them with     *
'* various profits: 15000$, 17000$ and 20000$.           *
'* Each kind must respect following conditions:          *
'* 1) for supply reasons, the number of houses of kind 2 *
'*    built each month must not exceed the number of     *
'*    kind 3 by more than two.                           *
'* 2) for staff reasons, the buider can make each month  *
'*    up to 5, 5 and 3, respectively of kinds 1, 2 and 3.*
'* 3) for organisation reasons, the builder can make up  *
'*    to 8 houses monthly of kinds 1,2 and 3, respecti-  *
'*    vely in the proportions of 3, 2 and 1.             *
'* The builder, having these data, wants to maximize his *
'* monthly profit by knowing the number oh houses of     *
'* each kind to build monthly.                           *
'* ----------------------------------------------------- *
'* SAMPLE RUN:                                           *
'* (Maximize 15 X1 + 17 X2 + 20 X3 with conditions:      *
'*                    X2 -   X3 <= 2                     *
'*           3 X1 + 3 X2 + 5 X3 <= 15                    *
'*           3 X1 + 2 X2 +   X3 <= 8     )               *
'*                                                       *
'* LINEAR PROGRAMMING                                    *
'*                                                       *
'* MAXIMIZE ? Y                                          *
'*                                                       *
'* NUMBER OF VARIABLES OF ECONOMIC FUNCTION ? 3          *
'*                                                       *
'* NUMBER OF CONSTRAINTS ? 3                             *
'*                                                       *
'* INPUT COEFFICIENTS OF ECONOMIC FUNCTION:              *
'*       #1 ? 15                                         *
'*       #2 ? 17                                         *
'*       #3 ? 20                                         *
'*       Right hand side ? 0                             *
'*                                                       *
'* CONSTRAINT #1:                                        *
'*       #1 ? 0                                          *
'*       #2 ? 1                                          *
'*       #3 ? -1                                         *
'*       Right hand side ? 2                             *
'*                                                       *
'* CONSTRAINT #2:                                        *
'*       #1 ? 3                                          *
'*       #2 ? 3                                          *
'*       #3 ? 5                                          *
'*       Right hand side ? 15                            *
'*                                                       *
'* CONSTRAINT #3:                                        *
'*       #1 ? 3                                          *
'*       #2 ? 2                                          *
'*       #3 ? 1                                          *
'*       Right hand side ? 8                             *
'*                                                       *
'* RESULTS:                                              *
'*                                                       *
'*       VARIABLE #1: 0.333333                           *
'*       VARIABLE #2: 3.000000                           *
'*       VARIABLE #3: 1.000000                           *
'*                                                       *
'*       ECONOMIC FUNCTION: 76.000000                    *
'*                                                       *
'* (Building monthly 1/3, 3 and 1 house(s) of kinds 1,2, *
'*  3, the builder can make a monthly profit of 76000$). *
'* ----------------------------------------------------- *
'* REFERENCE:                                            *
'* Modèles pratiques de décision Tome 2, By Jean-Pierre  *
'* Blanger, PSI Editions, France, 1982.                  *
'*                                                       *
'*                C++ Release 1.0 By J-P Moreau, Paris.  *
*                          (www.jpmoreau.fr)             *
'********************************************************/
#include <stdio.h>
#include <math.h>

#define CMAX  10  //max. number of variables in economic function
#define VMAX  10  //max. number of constraints


int NC, NV, NOPTIMAL,P1,P2,XERR;
double TS[CMAX][VMAX];

void Data()
{
    double R1,R2;
    char R;
    int I,J;
    printf("\n LINEAR PROGRAMMING\n\n");
    printf(" MAXIMIZE (Y/N) ? ");
    scanf("%c", &R);
    printf("\n NUMBER OF VARIABLES OF ECONOMIC FUNCTION ? ");
    scanf("%d", &NV);
    printf("\n NUMBER OF CONSTRAINTS ? ");
    scanf("%d", &NC);
    if (R == 'Y' || R=='y')
        R1 = 1.0;
    else
        R1 = -1.0;
    printf("\n INPUT COEFFICIENTS OF ECONOMIC FUNCTION:\n");
    for (J = 1; J<=NV; J++)
    {
        printf("       #%d ? ", J);
        scanf("%lf", &R2);
        TS[1][J+1] = R2 * R1;
    }
    printf("       Right hand side ? ");
    scanf("%lf", &R2);
    TS[1][1] = R2 * R1;
    for (I = 1; I<=NC; I++)
    {
        printf("\n CONSTRAINT #%d:\n", I);
        for (J = 1; J<=NV; J++)
        {
            printf("       #%d ? ", J);
            scanf("%lf", &R2);
            TS[I + 1][J + 1] = -R2;
        }
        printf("       Right hand side ? ");
        scanf("%lf", &TS[I+1][1]);
    }
    printf("\n\n RESULTS:\n\n");
    for(J=1; J<=NV; J++)  TS[0][J+1] = J;
    for(I=NV+1; I<=NV+NC; I++)  TS[I-NV+1][0] = I;
}

void Pivot();
void Formula();
void Optimize();

void Simplex()
{
e10:
    Pivot();
    Formula();
    Optimize();
    if (NOPTIMAL == 1) goto e10;
}

void Pivot()
{

    double RAP,V,XMAX;
    int I,J;

    XMAX = 0.0;
    for(J=2; J<=NV+1; J++)
    {
        if (TS[1][J] > 0.0 && TS[1][J] > XMAX)
        {
            XMAX = TS[1][J];
            P2 = J;
        }
    }
    RAP = 999999.0;
    for (I=2; I<=NC+1; I++)
    {
        if (TS[I][P2] >= 0.0) goto e10;
        V = fabs(TS[I][1] / TS[I][P2]);
        if (V < RAP)
        {
            RAP = V;
            P1 = I;
        }
e10:
        ;
    }
    V = TS[0][P2];
    TS[0][P2] = TS[P1][0];
    TS[P1][0] = V;
}

void Formula()
{
    ;
    //Labels: e60,e70,e100,e110;
    int I,J;

    for (I=1; I<=NC+1; I++)
    {
        if (I == P1) goto e70;
        for (J=1; J<=NV+1; J++)
        {
            if (J == P2) goto e60;
            TS[I][J] -= TS[P1][J] * TS[I][P2] / TS[P1][P2];
e60:
            ;
        }
e70:
        ;
    }
    TS[P1][P2] = 1.0 / TS[P1][P2];
    for (J=1; J<=NV+1; J++)
    {
        if (J == P2) goto e100;
        TS[P1][J] *= fabs(TS[P1][P2]);
e100:
        ;
    }
    for (I=1; I<=NC+1; I++)
    {
        if (I == P1) goto e110;
        TS[I][P2] *= TS[P1][P2];
e110:
        ;
    }
}

void Optimize()
{
    int I,J;
    for (I=2; I<=NC+1; I++)
        if (TS[I][1] < 0.0)  XERR = 1;
    NOPTIMAL = 0;
    if (XERR == 1)  return;
    for (J=2; J<=NV+1; J++)
        if (TS[1][J] > 0.0)  NOPTIMAL = 1;
}

void Results()
{
    //Labels: e30,e70,e100;
    int I,J;

    if (XERR == 0) goto e30;
    printf(" NO SOLUTION.\n");
    goto e100;
e30:
    for (I=1; I<=NV; I++)
        for (J=2; J<=NC+1; J++)
        {
            if (TS[J][0] != 1.0*I) goto e70;
            printf("       VARIABLE #%d: %f\n", I, TS[J][1]);
e70:
            ;
        }
    printf("\n       ECONOMIC FUNCTION: %f\n", TS[1][1]);
e100:
    printf("\n");
}

int main()
{

    Data();
    Simplex();
    Results();
    return 0;

}

//end of file simplex.cpp

