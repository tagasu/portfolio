

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void input();                                  
void runge2(float*, float*, float*, float);
float fx(float, float, float);
float fv(float, float, float);

float K, M, C, P, gam, pi;                            
float x0, v0, tmax, h;

void main(void)
{
    int   n;
    float t, x, v;
    //    char  fname[20];
    const char* fname;
    FILE* fp;

    input();                                      

//    printf("数値計算結果を保存するファイルの名===>");  

//    scanf_s("%s", fname);

    fname = "result.csv";
    if ((fopen_s(&fp, fname, "w")) != 0) {   
        printf("ファイル %s をオープンできません。\n", fname);
        exit(1);
    }
    
    x = x0; v = v0; t = 0.0;
   
    printf("   No.\tTime\t\tPosition\t\tVelocity\n");
    printf("%5d\t%14.7e\t%14.7e\t%14.7e\n", n = 0, t, x, v);
    
    fprintf(fp, "%14.7e\t%14.7e\t%14.7e\n", t, x, v);

   
    for (n = 1; t < tmax; n++) {
       
        runge2(&t, &x, &v, h);
       
        printf("%5d\t%12.5e\t%12.5e\t%12.5e\n", n, t, x, v);
        
        fprintf(fp, "%14.7e\t%14.7e\t%14.7e\n", t, x, v);
    }
}


void input()
{
    printf("バネ定数K,減衰係数C,質量M,外力P,外力周波数gam の値を入力してください。\n");
    printf("K  ===>"); scanf_s("%f", &K);
    printf("C  ===>"); scanf_s("%f", &C);
    printf("M  ===>"); scanf_s("%f", &M);
    printf("P  ===>"); scanf_s("%f", &P);
    printf("gam===>"); scanf_s("%f", &gam);

    printf("初期変位x0, 初期速度v0, 計算打切時刻tmax，時間増分h の値を入力してください。\n");
    printf("x0  ===>"); scanf_s("%f", &x0);
    printf("v0  ===>"); scanf_s("%f", &v0);
    printf("tmax===>"); scanf_s("%f", &tmax);
    printf("h   ===>"); scanf_s("%f", &h);

    printf("―――　入力データ　―――\n");
    printf("バネ定数　　 K   =%f\n", K);
    printf("減衰係数　　 C   =%f\n", C);
    printf("質量　　　　 M   =%f\n", M);
    printf("外力　　　　 P   =%f\n", P);
    printf("周波数　　　 gam =%f\n", gam);
    printf("初期変位　　 x0  =%f\n", x0);
    printf("初期速度　　 v0  =%f\n", v0);
    printf("計算打切時刻 tmax=%f\n", tmax);
    printf("時間増分　　 h   =%f\n", h);
    printf("―――――――――――――\n");

    pi = atan2(0.0, -1.0);
    /*     printf("pi=%f\n",pi); */
}


float fx(float t, float x, float v)
{
    return(v);
}


float fv(float t, float x, float v)
{
    return(-(C / M) * v - (K / M) * x + (P / M) * sin(2 * pi * gam * t));
}


void runge2(float* tt, float* xx, float* vv, float h)
{
    float kx1, kx2, kv1, kv2;
    float t, x, v;

    x = *xx;
    v = *vv;
    t = *tt;

    kx1 = h * fx(t, x, v);
    kv1 = h * fv(t, x, v);
    kx2 = h * fx(t + h, x + kx1, v + kv1);
    kv2 = h * fv(t + h, x + kx1, v + kv1);

    *xx += (kx1 + kx2) / 2;
    *vv += (kv1 + kv2) / 2;
    *tt += h;
}