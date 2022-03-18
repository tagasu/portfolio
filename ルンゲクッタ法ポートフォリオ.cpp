

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void runge2(float*, float*, float*, float);
float fx(float, float, float);
float fy(float, float, float);

float alph, beta, gamm, delt;                   

void main(void)
{
    int   n, k;
    float t, x, y, x0, y0, tmax, h;
    //    char  fname[20];
    const char* fname;
    FILE* fp;

    alph = 1.0;                           
    gamm = 0.5;
    k = 1;
    beta = 0.1 * k;
    delt = 0.02 * k;

    x0 = 1.0;
    y0 = 1.0;
    tmax = 50;
    h = 0.05;
    h = 0.2;

    //    printf("数値計算結果を保存するファイルの名===>");  

    //    scanf_s("%s", fname);
    fname = "result.csv";
    if ((fopen_s(&fp, fname, "w")) != 0) {   
        printf("ファイル %s をオープンできません。\n", fname);
        exit(1);
    }
    
    x = x0; y = y0; t = 0.0;
    
    printf("   No.\tTime\t\t x \t\t y \n");
    printf("%5d\t%14.7e\t%14.7e\t%14.7e\n", n = 0, t, x, y);
   
    fprintf(fp, "%14.7e\t%14.7e\t%14.7e\n", t, x, y);

    
    for (n = 1; t < tmax; n++) {
        
        runge2(&t, &x, &y, h);
        
        printf("%5d\t%12.5e\t%12.5e\t%12.5e\n", n, t, x, y);
        
        fprintf(fp, "%14.7e\t%14.7e\t%14.7e\n", t, x, y);
    }
}


float fx(float t, float x, float y)
{
    return(x * (alph - beta * y));
}

float fy(float t, float x, float y)
{
    return(y * (-gamm + delt * x));
}


void runge2(float* tt, float* xx, float* yy, float h)
{
    float kx1, kx2, ky1, ky2;
    float t, x, y;

    x = *xx;
    y = *yy;
    t = *tt;

    kx1 = h * fx(t, x, y);
    ky1 = h * fy(t, x, y);
    kx2 = h * fx(t + h, x + kx1, y + ky1);
    ky2 = h * fy(t + h, x + kx1, y + ky1);

    *xx += (kx1 + kx2) / 2;
    *yy += (ky1 + ky2) / 2;
    *tt += h;
}