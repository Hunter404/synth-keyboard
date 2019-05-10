#include <Arduino.h>
#include "filters.h"
short low_pass[NUM_COEFFS] = {
#include "lopass_44100.h"
};

short band_pass[NUM_COEFFS] = {
#include "hipass_44100.h"
};

float N[101] = {
	-50, -49, -48, -47, -46, -45, -44, -43, -42, -41, -40, -39, -38, -37,
	 -36, -35, -34, -33, -32, -31, -30, -29, -28, -27, -26, -25, -24, -23,
	 -22, -21, -20, -19, -18, -17, -16, -15, -14, -13, -12, -11, -10,  -9,
	  -8,  -7,  -6,  -5,  -4,  -3,  -2,  -1,   0,   1,   2,   3,   4,   5,
	   6,   7,   8,   9,  10,  11,  12,  13,  14,  15,  16,  17,  18,  19,
	  20,  21,  22,  23,  24,  25,  26,  27,  28,  29,  30,  31,  32,  33,
	  34,  35,  36,  37,  38,  39,  40,  41,  42,  43,  44,  45,  46,  47,
	  48,  49,  50,
};

float inter[101];

float blackman[101] = {-0.00000000, 0.00035581, 0.00142930, 0.00323849, 0.00581295, 0.00919310,
		0.01342925, 0.01858039, 0.02471280, 0.03189838, 0.04021286, 0.04973388, 0.06053893,
		0.07270321, 0.08629750, 0.10138601, 0.11802426, 0.13625702, 0.15611644,
		0.17762023, 0.20077014, 0.22555052, 0.25192722, 0.27984673, 0.30923556,
		0.34000000, 0.37202608, 0.40517996, 0.43930854, 0.47424041, 0.50978714,
		0.54574479, 0.58189573, 0.61801069, 0.65385105, 0.68917127, 0.72372149,
		0.75725031, 0.78950756, 0.82024713, 0.84922986, 0.87622631, 0.90101948,
		0.92340745, 0.94320573, 0.96024962, 0.97439611, 0.98552574, 0.99354400,
		0.99838254, 1.00000000, 0.99838254, 0.99354400, 0.98552574, 0.97439611,
		0.96024962, 0.94320573, 0.92340745, 0.90101948, 0.87622631, 0.84922986,
		0.82024713, 0.78950756, 0.75725031, 0.72372149, 0.68917127, 0.65385105,
		0.61801069, 0.58189573, 0.54574479, 0.50978714, 0.47424041, 0.43930854,
		0.40517996, 0.37202608, 0.34000000, 0.30923556, 0.27984673, 0.25192722,
		0.22555052, 0.20077014, 0.17762023, 0.15611644, 0.13625702, 0.11802426,
		0.10138601, 0.08629750, 0.07270321, 0.06053893, 0.04973388, 0.04021286,
		0.03189838, 0.02471280, 0.01858039, 0.01342925, 0.00919310, 0.00581295,
		0.00323849, 0.00142930, 0.00035581, -0.00000000 };

void calculateLPF(float fl)
{
	float total = 0;
	for(int i=0; i<101; i++){
		if(i == 50) inter[i] = .9999;
		else{
			inter[i] = 2 * fl / float(44100) * N[i];
			inter[i] = sin(PI*inter[i])/(PI*inter[i]) * blackman[i];
		}
		total += inter[i];
	}
	for(int i=0; i<100; i++){
		low_pass[i] = (inter[i]/total) * ((1<<15)-1);
	}
}

void calculateHPF(float fl)
{
	float total = 0;
	for(int i=0; i<101; i++){
		if(i == 50) inter[i] = .9999;
		else{
			inter[i] = 2 * fl / float(44100) * N[i];
			inter[i] = sin(PI*inter[i])/(PI*inter[i]) * blackman[i];
		}
		total += inter[i];
	}
	for(int i=0; i<100; i++){
		band_pass[i] = (-1*(inter[i]/total) * ((1<<15)-1));
	}
	band_pass[50] += ((1<<15)-1);
}
