#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FFT.h"




dcomp comp_add (dcomp a, dcomp b) {
	dcomp ans;
	ans.r = a.r + b.r;
	ans.i = a.i + b.i;
	return ans;
}
dcomp comp_sub (dcomp a, dcomp b) {
	dcomp ans;
	ans.r = a.r - b.r;
	ans.i = a.i - b.i;
	return ans;
}

dcomp comp_mul (dcomp a, dcomp b) {
	dcomp ans;
	ans.r = a.r*b.r - a.i*b.i;
	ans.i = a.i*b.r + a.r*b.i;
	return ans;
}

double comp_abs(dcomp a) {
	double ans;
	ans = sqrt(a.r*a.r + a.i*a.i);
	return ans;
}

int reverseBits (int num, int size) {
	int out = 0;

	for (int i = 0; i < size; i++){
		if((num & (1 << i)))
		out |= 1 << ((size - 1) - i);
	}
	return out;
}


void fft (dcomp *data, int len) {

	int s = log(len)/log(2);
	int i, j, k, m;
	dcomp wm, w, odd;
	double theta;

	for(i=0; i<len; i++){
		j = reverseBits(i, s);
		
		if(i < j){
			w.r = data[i].r;
			data[j].r = data[i].r;
			data[i].i = w.r;
		}
		
		
	}

	for(i=1; i<=s; i++){
		m = 0x01 << i;
		theta = 2*M_PI/m;
		
		wm.r = cos(theta);
		wm.i = sin(theta);

		for(j=0; j<len; j+=m){

			w.r = 1;
			w.i = 0;

			for(k=0; k<m/2; k++){
				odd = comp_mul(w,data[j+k+m/2]);

				w = comp_mul(w,wm);

				data[j+k+m/2] = comp_sub(data[j+k],odd);
				data[j+k] = comp_add(data[j+k],odd);

			}
		}
	}
	
	for(i=0; i<len; i++){
		data[i].r = comp_abs(data[i]);
	}
}

