#include "mex.h"

double iir3 ( double x_n,double *v, double *b, double *a, int n) {
	int k;
/*Cálculo de la salida una vez se lee el ADC*/
	double y_n;
	y_n = b [0] * x_n + v[0];
/*Cálculo de v[n]*/
	for (k = 0; k < n - 2; k++)
		v[k] = b [k + 1] * x_n - a [k + 1] * y_n + v[k + 1];
/*Cálculo de v_{n-1}*/
	v[ n - 2] = b [ n - 1] * x_n - a [ n - 1] * y_n;

	return y_n;
}

//función pasarela
void mexFunction( int nlhs, mxArray *plhs[],int nrhs, const mxArray *prhs[]){
	
	double *xn,*y,*b,*a;
	int p,nx;
	if(nrhs!=3) {
		mexErrMsgIdAndTxt("irr3:nrhs","Se requieren tres entradas.");
	}
/*Verifica que haya un argumento de salida*/
	if(nlhs!=1) {
		mexErrMsgIdAndTxt("irr3:nlhs","Se requiere una salida");
	}
	
	p=mxGetM(prhs[0]); // longitud de a y b
	nx=mxGetM(prhs[2]); // longitud de x

// Obtencion de los punteros

	xn=mxGetPr(prhs[2]);	
	b=mxGetPr(prhs[0]);
	a=mxGetPr(prhs[1]);

/* Crea la matriz de salida */
	plhs[0] = mxCreateDoubleMatrix((mwSize)nx,1,mxREAL);
/* Puntero a la matriz de salida */
	y = mxGetPr(plhs[0]);

	double v[((mwSize)p)-1]={0.0};

	for (int i=0;i<(mwSize)nx;i++){
		y[i]=iir3(xn[i],v,b,a,(mwSize)p);
	}

	
}

