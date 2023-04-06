#include "mex.h"
double iir2 ( double x_n, double *w, double *b, double *a, int n){
	double y_n,w_n;
	int k;
	w_n=x_n;
/*Cálculo de w[n]*/
	for (k=n-1; k>=1; k--)
		w_n -= a [k]*w[k];
/*w_n actual*/
	w[0]=w_n;
	y_n=0;
/*Cálculo de la rama de salida*/
	for (k=n-1; k>=0; k--) {
		y_n +=b[k]*w[k];
		w[k] = w[k-1];
	}
	return y_n;
}
void mexFunction( int nlhs, mxArray *plhs[],int nrhs, const mxArray *prhs[]){
	double *xn,*y,*b,*a;
	int p,nx;
	if(nrhs!=3) {
		mexErrMsgIdAndTxt("irr2:nrhs","Se requieren dos entradas.");
	}
/*Verifica que haya un argumento de salida*/
	if(nlhs!=1) {
		mexErrMsgIdAndTxt("irr2:nlhs","Se requiere una salida");
	}
	p=mxGetN(prhs[0]);
	xn=mxGetPr(prhs[2]);
	nx=mxGetM(prhs[2]);
	b=mxGetPr(prhs[0]);
	a=mxGetPr(prhs[1]);
/* Crea la matriz de salida */
	plhs[0] = mxCreateDoubleMatrix((mwSize)nx,1,mxREAL);
/* Puntero a la matriz de salida */
	y = mxGetPr(plhs[0]);
	double w[(mwSize)p]={0.0};
	
	for (int i=0;i<nx;i++){
		y[i]=iir2(xn[i],w,b,a,(mwSize)p);
	}
}
