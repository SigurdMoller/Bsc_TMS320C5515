/*
 * SampleFilter.h
 *
 *  Created on: 31/03/2015
 *      Author: SimonBoelt
 */

#ifndef SAMPLEFILTER_H_
#define SAMPLEFILTER_H_

/*

FIR filter designed with
 http://t-filter.appspot.com

sampling frequency: 2000 Hz

fixed point precision: 16 bits

* 0 Hz - 400 Hz
  gain = 1
  desired ripple = 5 dB
  actual ripple = n/a

* 500 Hz - 1000 Hz
  gain = 0
  desired attenuation = -40 dB
  actual attenuation = n/a

*/

#define SAMPLEFILTER_TAP_NUM 96

#define FILTER_ORDER 3

// -- FIR --
 // LP TEST ORDER 30

//asm(" .bss DMA, 1");



short filter_taps[SAMPLEFILTER_TAP_NUM] = {
		-2,      2,     -2,     -1,      5,     -9,     10,     -5,     -6,
		       18,    -26,     23,     -5,    -23,     49,    -58,     40,      5,
		      -62,    105,   -107,     55,     39,   -140,    197,   -171,     53,
		      121,   -278,    337,   -244,      8,    289,   -517,    548,   -316,
		     -132,    637,   -966,    910,   -373,   -552,   1569,  -2233,   2031,
		     -405,  -3737,  19703,  19703,  -3737,   -405,   2031,  -2233,   1569,
		     -552,   -373,    910,   -966,    637,   -132,   -316,    548,   -517,
		      289,      8,   -244,    337,   -278,    121,     53,   -171,    197,
		     -140,     39,     55,   -107,    105,    -62,      5,     40,    -58,
		       49,    -23,     -5,     23,    -26,     18,     -6,     -5,     10,
		       -9,      5,     -1,     -2,      2,     -2
};


 // HP test filter ORDER 25
/*
short filter_taps[SAMPLEFILTER_TAP_NUM] = {
  		-344,   -509,   -694,   -894,  -1103,  -1314,  -1517,  -1707,  -1875,
		    -2013,  -2117,  -2181,  30833,  -2181,  -2117,  -2013,  -1875,  -1707,
		    -1517,  -1314,  -1103,   -894,   -694,   -509,   -344
};
*/

// -- IIR --

// ---- ØVERSTE BP ----

short b01c = 82,
      b11c = 0,
	  b21c = -82,

	  b02c = 16384,
	  b12c = -19235,
	  b22c = 16384,

	  b03c = 16384,
	  b13c = 31253,
	  b23c = 16384;

short a11c = 15809,
	  a21c = 13076,

	  a12c = 11480,
	  a22c = 14548,

	  a13c = 20929,
	  a23c = 14898;


// A WEIGHT
/*
short b01c = 3839,
      b11c = 7678,
	  b21c = 3839,

	  b02c = 16384,
	  b12c = -32768,
	  b22c = 16384,

	  b03c = 16384,
	  b13c = -32768,
	  b23c = 16384;

short a11c = -3679,
	  a21c = 207,

	  a12c = -31029,
	  a22c = 14666,

	  a13c = -32680,
	  a23c = 16296;
*/
// C WEIGHT
/*
short b01CW = 3242,
      b11CW = -6484,
	  b21CW = 3242,

	  b02CW = 16384,
	  b12CW = -32768,
	  b22CW = 16384;

short a11CW = -3679,
	  a21CW = 207,

	  a12CW = -32680,
	  a22CW = 16296;
*/

// ----MIDT BP----

short b01b = 55,
      b11b = 0,
	  b21b = -55,

	  b02b = 16384,
	  b12b = -22565,
	  b22b = 16384,

	  b03b = 16384,
	  b13b = 25484,
	  b23b = 16384;

short a11b = 2916,
	  a21b = 13744,

	  a12b = -1319,
	  a22b = 15040,

	  a13b = 7296,
	  a23b = 15074;



// ---- LAV BP -----

short b01a = 34,
      b11a = 0,
	  b21a = -34,

	  b02a = 16384,
	  b12a = 16656,
	  b22a = 16384,

	  b03a = 16384,
	  b13a = -25722,
	  b23a = 16384;

short a11a = -7463,
	  a21a = 14221,

	  a12a = -4205,
	  a22a = 15269,

	  a13a = -11061,
	  a23a = 15328;

short DS_table[1024] = {
	768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,520,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,516,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,520,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,514,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,520,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,516,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,520,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,513,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,520,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,516,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,520,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,514,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,520,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,516,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,520,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,512,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,520,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,516,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,520,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,514,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,520,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,516,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,520,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,513,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,520,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,516,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,520,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,514,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,520,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,516,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,520,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,528,768,640,768,576,768,640,768,544,768,640,768,576,768,640,768,512
};

long dB_table[37] = {
		1,8,17,27,42,60,86,110,137,195,290,348,430,540,730,900,
		1140,1420,1830,2300,3000,3600,4700,5700,9300,11200,14400,
		18000,23000,29000,36000,46000,58000,71000,88000,110000,131000

};
#pragma DATA_SECTION(adisplay, ".adisplay")
int adisplay[1536] = {
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,
			0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0

	};
/*
10th octave + X  ||   Bit Pattern    || Identifier
+2					 = 1100000000   =    768
+3 					 = 1010000000   =    640
+4 					 = 1001000000   =    576
+5 					 = 1000100000   =    544
+6 					 = 1000010000   =    528
+7 		   		     = 1000001000   =    520
+8 					 = 1000000100   =    516
+9 					 = 1000000010   =    514
+10			 		 = 1000000001   =    513
*/
#endif /* SAMPLEFILTER_H_ */
