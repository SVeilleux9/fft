#ifndef FFT_H_
#define FFT_H_


typedef struct double_complex{
	double r;
	double i;
} dcomp;

dcomp comp_add (dcomp a, dcomp b);
dcomp comp_sub (dcomp a, dcomp b);
dcomp comp_mul (dcomp a, dcomp b);
double comp_abs(dcomp a);

int reverseBits (int num, int size);
void fft (dcomp *data, int len);


#endif /* FFT_H_ */