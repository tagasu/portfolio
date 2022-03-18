

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

//    printf("���l�v�Z���ʂ�ۑ�����t�@�C���̖�===>");  

//    scanf_s("%s", fname);

    fname = "result.csv";
    if ((fopen_s(&fp, fname, "w")) != 0) {   
        printf("�t�@�C�� %s ���I�[�v���ł��܂���B\n", fname);
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
    printf("�o�l�萔K,�����W��C,����M,�O��P,�O�͎��g��gam �̒l����͂��Ă��������B\n");
    printf("K  ===>"); scanf_s("%f", &K);
    printf("C  ===>"); scanf_s("%f", &C);
    printf("M  ===>"); scanf_s("%f", &M);
    printf("P  ===>"); scanf_s("%f", &P);
    printf("gam===>"); scanf_s("%f", &gam);

    printf("�����ψ�x0, �������xv0, �v�Z�Ő؎���tmax�C���ԑ���h �̒l����͂��Ă��������B\n");
    printf("x0  ===>"); scanf_s("%f", &x0);
    printf("v0  ===>"); scanf_s("%f", &v0);
    printf("tmax===>"); scanf_s("%f", &tmax);
    printf("h   ===>"); scanf_s("%f", &h);

    printf("�\�\�\�@���̓f�[�^�@�\�\�\\n");
    printf("�o�l�萔�@�@ K   =%f\n", K);
    printf("�����W���@�@ C   =%f\n", C);
    printf("���ʁ@�@�@�@ M   =%f\n", M);
    printf("�O�́@�@�@�@ P   =%f\n", P);
    printf("���g���@�@�@ gam =%f\n", gam);
    printf("�����ψʁ@�@ x0  =%f\n", x0);
    printf("�������x�@�@ v0  =%f\n", v0);
    printf("�v�Z�Ő؎��� tmax=%f\n", tmax);
    printf("���ԑ����@�@ h   =%f\n", h);
    printf("�\�\�\�\�\�\�\�\�\�\�\�\�\\n");

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