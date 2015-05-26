#include "usbstk5515.h"
#include "usbstk5515_gpio.h"
#include "usbstk5515_i2c.h"
#include "stdio.h"
#include "math.h"
#include "SampleFilter.h"
#include "register_dma.h"
#include "register_cpu.h"
#include "dma.h"
#define OSD9616_I2C_ADDR 0x3C
#define Rcv 0x08
#define Xmit 0x20
#define AIC3204_I2C_ADDR 0x18

Int16 AIC3204_rset( Uint16 regnum, Uint16 regval )
{
    Uint8 cmd[2];
    cmd[0] = regnum & 0x007F;       // 7-bit Register Address
    cmd[1] = regval;                // 8-bit Register Data

    return USBSTK5515_I2C_write( AIC3204_I2C_ADDR, cmd, 2 );
}



/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Int16 OSD9616_send( Uint16 comdat, Uint16 data )                        *
 *                                                                          *
 *      Sends 2 bytes of data to the OSD9616                                *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 OSD9616_send( Uint16 comdat, Uint16 data )
{
    Uint8 cmd[2];
    cmd[0] = comdat & 0x00FF;     // Specifies whether data is Command or Data
    cmd[1] = data;                // Command / Data

    return USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 2 );
}

/* ------------------------------------------------------------------------ *
 *                                                                          *
 *  Int16 OSD9616_multiSend( Uint16 comdat, Uint16 data )                   *
 *                                                                          *
 *      Sends multiple bytes of data to the OSD9616                         *
 *                                                                          *
 * ------------------------------------------------------------------------ */
Int16 OSD9616_multiSend( Uint8* data, Uint16 len )
{
    Uint16 x;
    Uint8 cmd[10];
    for(x=0;x<len;x++)               // Command / Data
    {
    	cmd[x] = data[x];
    }
    return USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, len );
}


int draw_1(int High_addr, int Low_addr)
{
    OSD9616_send(0x00,0xb0+1); // Set page for page 0 to page 5
    OSD9616_send(0x40,0x80);
    OSD9616_send(0x40,0x80);
    return 0;
}

int draw_2(int High_addr, int Low_addr)
{
    OSD9616_send(0x00,0xb0+1); // Set page for page 0 to page 5
    OSD9616_send(0x40,0xC0);
    OSD9616_send(0x40,0xC0);
    return 0;
}

int draw_3(int High_addr, int Low_addr)
{
    OSD9616_send(0x00,0xb0+1); // Set page for page 0 to page 5
    OSD9616_send(0x40,0xE0);
    OSD9616_send(0x40,0xE0);
    return 0;
}

int draw_4(int High_addr, int Low_addr)
{
    OSD9616_send(0x00,0xb0+1); // Set page for page 0 to page 5
    OSD9616_send(0x40,0xF0);
    OSD9616_send(0x40,0xF0);
    return 0;
}

int draw_5(int High_addr, int Low_addr)
{
    OSD9616_send(0x00,0xb0+1); // Set page for page 0 to page 5
    OSD9616_send(0x40,0xF8);
    OSD9616_send(0x40,0xF8);
    return 0;
}

int draw_6(int High_addr, int Low_addr)
{
    OSD9616_send(0x00,0xb0+1); // Set page for page 0 to page 5
    OSD9616_send(0x40,0xFC);
    OSD9616_send(0x40,0xFC);
    return 0;
}

int draw_7(int High_addr, int Low_addr)
{
    OSD9616_send(0x00,0xb0+1); // Set page for page 0 to page 5
    OSD9616_send(0x40,0xFE);
    OSD9616_send(0x40,0xFE);
    return 0;
}

int draw_8(int High_addr, int Low_addr)
{
    OSD9616_send(0x00,0xb0+1); // Set page for page 0 to page 5
    OSD9616_send(0x40,0xFF);
    OSD9616_send(0x40,0xFF);
    return 0;
}

int draw_9(int High_addr, int Low_addr)
{
    OSD9616_send(0x00,0xb0+1); // Set page for page 0 to page 5
    OSD9616_send(0x40,0xFF);
    OSD9616_send(0x40,0xFF);
    // on top:
    OSD9616_send(0x00,Low_addr);   // Set low column address
    OSD9616_send(0x00,High_addr);   // Set high column addres
    OSD9616_send(0x00,0xb0+0); // Set page for page 0 to page 5
    OSD9616_send(0x40,0x80);
    OSD9616_send(0x40,0x80);
    return 0;
}

int draw_10(int High_addr, int Low_addr)
{
    OSD9616_send(0x00,0xb0+1); // Set page for page 0 to page 5
    OSD9616_send(0x40,0xFF);
    OSD9616_send(0x40,0xFF);
    // on top:
    OSD9616_send(0x00,Low_addr);   // Set low column address
    OSD9616_send(0x00,High_addr);   // Set high column addres
    OSD9616_send(0x00,0xb0+0); // Set page for page 0 to page 5
    OSD9616_send(0x40,0xC0);
    OSD9616_send(0x40,0xC0);
    return 0;
}

int draw_11(int High_addr, int Low_addr)
{
    OSD9616_send(0x00,0xb0+1); // Set page for page 0 to page 5
    OSD9616_send(0x40,0xFF);
    OSD9616_send(0x40,0xFF);
    // on top:
    OSD9616_send(0x00,Low_addr);   // Set low column address
    OSD9616_send(0x00,High_addr);   // Set high column addres
    OSD9616_send(0x00,0xb0+0); // Set page for page 0 to page 5
    OSD9616_send(0x40,0xE0);
    OSD9616_send(0x40,0xE0);
    return 0;
}

int draw_12(int High_addr, int Low_addr)
{
    OSD9616_send(0x00,0xb0+1); // Set page for page 0 to page 5
    OSD9616_send(0x40,0xFF);
    OSD9616_send(0x40,0xFF);
    // on top:
    OSD9616_send(0x00,Low_addr);   // Set low column address
    OSD9616_send(0x00,High_addr);   // Set high column addres
    OSD9616_send(0x00,0xb0+0); // Set page for page 0 to page 5
    OSD9616_send(0x40,0xF0);
    OSD9616_send(0x40,0xF0);
    return 0;
}

int draw_13(int High_addr, int Low_addr)
{
    OSD9616_send(0x00,0xb0+1); // Set page for page 0 to page 5
    OSD9616_send(0x40,0xFF);
    OSD9616_send(0x40,0xFF);
    // on top:
    OSD9616_send(0x00,Low_addr);   // Set low column address
    OSD9616_send(0x00,High_addr);   // Set high column addres
    OSD9616_send(0x00,0xb0+0); // Set page for page 0 to page 5
    OSD9616_send(0x40,0xF8);
    OSD9616_send(0x40,0xF8);
    return 0;
}

int ChoosedB(int X, int High_addr, int Low_addr)
{
    if(X==1||X==2||X==3)
    {
        draw_1(High_addr, Low_addr);
    }

    if(X==4||X==5||X==6)
    {
        draw_2(High_addr, Low_addr);
    }

    if(X==7||X==8||X==9)
    {
        draw_3(High_addr, Low_addr);
    }

    if(X==10||X==11||X==12)
    {
        draw_4(High_addr, Low_addr);
    }

    if(X==13||X==14||X==15)
    {
        draw_5(High_addr, Low_addr);
    }

    if(X==16||X==17||X==18)
    {
        draw_6(High_addr, Low_addr);
    }

    if(X==19||X==20||X==21)
    {
        draw_7(High_addr, Low_addr);
    }

    if(X==22||X==23||X==24)
    {
        draw_8(High_addr, Low_addr);
    }

    if(X==25||X==26||X==27)
    {
        draw_9(High_addr, Low_addr);
    }

    if(X==28||X==29||X==30)
    {
        draw_10(High_addr, Low_addr);
    }

    if(X==31||X==32||X==33)
    {
        draw_11(High_addr, Low_addr);
    }

    if(X==34||X==35||X==36)
    {
        draw_12(High_addr, Low_addr);
    }

    if(X==37)
    {
        draw_13(High_addr, Low_addr);
    }



    return 0;
}

int old_dB1 = 0,old_dB2 = 0,old_dB3 = 0,old_dB4 = 0,old_dB5 = 0,old_dB6 = 0,old_dB7 = 0,old_dB8 = 0,old_dB9 = 0,old_dB10 = 0,
		  old_dB11 = 0,old_dB12 = 0,old_dB13 = 0,old_dB14 = 0,old_dB15 = 0,old_dB16 = 0,old_dB17 = 0,old_dB18 = 0,old_dB19 = 0,old_dB20 = 0,
		  old_dB21 = 0,old_dB22 = 0,old_dB23 = 0,old_dB24 = 0,old_dB25 = 0,old_dB26 = 0,old_dB27 = 0,old_dB28 = 0,old_dB29 = 0,old_dB30 = 0,bandcount = 0;

void WipeBand(int High_addr, int Low_addr)
{
	/*
    OSD9616_send(0x00,0xb0+1);
    OSD9616_send(0x00,Low_addr);   // Set low column address
    OSD9616_send(0x00,High_addr);   // Set high column addres
    OSD9616_send(0x40,0x00);
    OSD9616_send(0x40,0x00);
   */
    OSD9616_send(0x00,0xb0+0);
    OSD9616_send(0x00,Low_addr);   // Set low column address
    OSD9616_send(0x00,High_addr);   // Set high column addres
    OSD9616_send(0x40,0x00);
    OSD9616_send(0x40,0x00);
}

Int16 oled_test()
{
	int i = 0;
	Uint8 cmd[10];    // For multibyte commands

    /* Initialize I2C */
    USBSTK5515_I2C_init( );

    /* Initialize LCD power */
    USBSTK5515_GPIO_setDirection( 12, 1 );  // Output
    USBSTK5515_GPIO_setOutput( 12, 1 );     // Enable 13V



    /* Initialize OSD9616 display */
    OSD9616_send(0x00,0x00); // Set low column address
    OSD9616_send(0x00,0x10); // Set high column address
    OSD9616_send(0x00,0x40); // Set start line address

    cmd[0] = 0x00 & 0x00FF;  // Set contrast control register
    cmd[1] = 0x81;
    cmd[2] = 0x7f;
    USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 3 );


    OSD9616_send(0x00,0xa1); // Set segment re-map 95 to 0
    OSD9616_send(0x00,0xa6); // Set normal display

    cmd[0] = 0x00 & 0x00FF;  // Set multiplex ratio(1 to 16)
    cmd[1] = 0xa8;
    cmd[2] = 0x0f;
    USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 3 );

    OSD9616_send(0x00,0xd3); // Set display offset
    OSD9616_send(0x00,0x00); // Not offset
    OSD9616_send(0x00,0xd5); // Set display clock divide ratio/oscillator frequency
    OSD9616_send(0x00,0xf0); // Set divide ratio

    cmd[0] = 0x00 & 0x00FF;  // Set pre-charge period
    cmd[1] = 0xd9;
    cmd[2] = 0x22;
    USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 3 );

    cmd[0] = 0x00 & 0x00FF;  // Set com pins hardware configuration
    cmd[1] = 0xda;
    cmd[2] = 0x02;
    USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 3 );

    OSD9616_send(0x00,0xdb); // Set vcomh
    OSD9616_send(0x00,0x49); // 0.83*vref

    cmd[0] = 0x00 & 0x00FF;  //--set DC-DC enable
    cmd[1] = 0x8d;
    cmd[2] = 0x14;
    USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 3 );

    OSD9616_send(0x00, 0x2e);   //Stop scrolling text !

    cmd[0] = 0x00 & 0x00FF; // page start addr to end addr
	cmd[1] = 0x22;
	cmd[2] = 0x00;
	cmd[3] = 0x1;
	USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 4 );
	cmd[0] = 0x00 & 0x00FF; // column start addr to end addr
	cmd[1] = 0x21;
	cmd[2] = 0x00;
	cmd[3] = 0x5F;
	USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 4 );

	cmd[0] = 0x00 & 0x00FF;  //- HORIZ ADDR MODE
    cmd[1] = 0x20;
    cmd[2] = 0x00;
    USBSTK5515_I2C_write( OSD9616_I2C_ADDR, cmd, 3 );


    OSD9616_send(0x00,0xaf);   // Turn on oled panel



    //////////////(Clear the screen with spaces)///////////////////////
/*
    OSD9616_send(0x00,0x00);   // Set low column address
    OSD9616_send(0x00,0x10);   // Set high column address
    OSD9616_send(0x00,0xb0+0); // Set page for page 0 to page 5
    for(i=0;i<96;i++)
    {
        OSD9616_send(0x40,0x00);  // Spaces
    }
*/
    /* Fill page 1*/
/*
    OSD9616_send(0x00,0x00);   // Set low column address
    OSD9616_send(0x00,0x10);   // Set high column address
    OSD9616_send(0x00,0xb0+1); // Set page for page 0 to page 5
    for(i=0;i<96;i++)
    {
        OSD9616_send(0x40,0x00);  // Spaces
    }
*/
	USBSTK5515_I2C_close();



    return 0;

}

int i,j,samplecount = 0,RMScount = 0,RMScount1 = 0,RMScount2 = 0,RMScount3 = 0,RMScount4 = 0,RMScount5 = 0,RMScount6 = 0,RMScount7 = 0,RMScount8 = 0,RMScount9 = 0;
int main(void) {

/*

	long Result1a_ds1,Result2a_ds1,Result3a_ds1,
		 Result1b_ds1,Result2b_ds1,Result3b_ds1,
		 Result1c_ds1,Result2c_ds1,Result3c_ds1,

		 Result1a_ds2,Result2a_ds2,Result3a_ds2,
		 Result1b_ds2,Result2b_ds2,Result3b_ds2,
		 Result1c_ds2,Result2c_ds2,Result3c_ds2,

		 Result1a_ds3,Result2a_ds3,Result3a_ds3,
		 Result1b_ds3,Result2b_ds3,Result3b_ds3,
		 Result1c_ds3,Result2c_ds3,Result3c_ds3,

		 Result1a_ds4,Result2a_ds4,Result3a_ds4,
		 Result1b_ds4,Result2b_ds4,Result3b_ds4,
		 Result1c_ds4,Result2c_ds4,Result3c_ds4,

		 Result1a_ds5,Result2a_ds5,Result3a_ds5,
		 Result1b_ds5,Result2b_ds5,Result3b_ds5,
		 Result1c_ds5,Result2c_ds5,Result3c_ds5,

		 Result1a_ds6,Result2a_ds6,Result3a_ds6,
		 Result1b_ds6,Result2b_ds6,Result3b_ds6,
		 Result1c_ds6,Result2c_ds6,Result3c_ds6,

		 Result1a_ds7,Result2a_ds7,Result3a_ds7,
		 Result1b_ds7,Result2b_ds7,Result3b_ds7,
		 Result1c_ds7,Result2c_ds7,Result3c_ds7,

		 Result1a_ds8,Result2a_ds8,Result3a_ds8,
		 Result1b_ds8,Result2b_ds8,Result3b_ds8,
		 Result1c_ds8,Result2c_ds8,Result3c_ds8,

		 Result1a_ds9,Result2a_ds9,Result3a_ds9,
		 Result1b_ds9,Result2b_ds9,Result3b_ds9,
		 Result1c_ds9,Result2c_ds9,Result3c_ds9,

		 Result1a,Result2a,Result3a, //ResultCW1, ResultCW2,
		 		 Result1b,Result2b,Result3b,
		 		 Result1c,Result2c,Result3c,

		 DSResult1,DSResult2,DSResult3,
		 DSResult4,DSResult5,DSResult6,
		 DSResult7,DSResult8,DSResult9;
*/
/*
		 RMS1,RMS2,RMS3,
		 RMS4,RMS5,RMS6,
		 RMS7,RMS8,RMS9,
		 RMS10,RMS11,RMS12,
		 RMS13,RMS14,RMS15,
		 RMS16,RMS17,RMS18,
		 RMS19,RMS20,RMS21,
		 RMS22,RMS23,RMS24,
		 RMS25,RMS26,RMS27,
		 RMS28,RMS29,RMS30,
*/
//		 LResult;
/*
    long tempRMS_band1,tempRMS_band2,tempRMS_band3,tempRMS_band4,tempRMS_band5,tempRMS_band6,
	 tempRMS_band7,tempRMS_band8,tempRMS_band9,tempRMS_band10,tempRMS_band11,tempRMS_band12,
	 tempRMS_band13,tempRMS_band14,tempRMS_band15,tempRMS_band16,tempRMS_band17,tempRMS_band18,
	 tempRMS_band19,tempRMS_band20,tempRMS_band21,tempRMS_band22,tempRMS_band23,tempRMS_band24,
	 tempRMS_band25,tempRMS_band26,tempRMS_band27,tempRMS_band28,tempRMS_band29,tempRMS_band30;
*/



    short input_ds1[FILTER_ORDER],input2a_ds1[FILTER_ORDER],input3a_ds1[FILTER_ORDER],
	      input2b_ds1[FILTER_ORDER],input3b_ds1[FILTER_ORDER],
		  input2c_ds1[FILTER_ORDER],input3c_ds1[FILTER_ORDER],
		  NSe1a_ds1[2],NSe2a_ds1[2],NSe3a_ds1[2],
		  NSe1b_ds1[2],NSe2b_ds1[2],NSe3b_ds1[2],
		  NSe1c_ds1[2],NSe2c_ds1[2],NSe3c_ds1[2],

		  input_ds2[FILTER_ORDER],input2a_ds2[FILTER_ORDER],input3a_ds2[FILTER_ORDER],
		  input2b_ds2[FILTER_ORDER],input3b_ds2[FILTER_ORDER],
		  input2c_ds2[FILTER_ORDER],input3c_ds2[FILTER_ORDER],
		  NSe1a_ds2[2],NSe2a_ds2[2],NSe3a_ds2[2],
		  NSe1b_ds2[2],NSe2b_ds2[2],NSe3b_ds2[2],
		  NSe1c_ds2[2],NSe2c_ds2[2],NSe3c_ds2[2],

		  input_ds3[FILTER_ORDER],input2a_ds3[FILTER_ORDER],input3a_ds3[FILTER_ORDER],
		  input2b_ds3[FILTER_ORDER],input3b_ds3[FILTER_ORDER],
		  input2c_ds3[FILTER_ORDER],input3c_ds3[FILTER_ORDER],
		  NSe1a_ds3[2],NSe2a_ds3[2],NSe3a_ds3[2],
		  NSe1b_ds3[2],NSe2b_ds3[2],NSe3b_ds3[2],
		  NSe1c_ds3[2],NSe2c_ds3[2],NSe3c_ds3[2],

		  input_ds4[FILTER_ORDER],input2a_ds4[FILTER_ORDER],input3a_ds4[FILTER_ORDER],
		  input2b_ds4[FILTER_ORDER],input3b_ds4[FILTER_ORDER],
		  input2c_ds4[FILTER_ORDER],input3c_ds4[FILTER_ORDER],
		  NSe1a_ds4[2],NSe2a_ds4[2],NSe3a_ds4[2],
		  NSe1b_ds4[2],NSe2b_ds4[2],NSe3b_ds4[2],
		  NSe1c_ds4[2],NSe2c_ds4[2],NSe3c_ds4[2],

		  input_ds5[FILTER_ORDER],input2a_ds5[FILTER_ORDER],input3a_ds5[FILTER_ORDER],
		  input2b_ds5[FILTER_ORDER],input3b_ds5[FILTER_ORDER],
		  input2c_ds5[FILTER_ORDER],input3c_ds5[FILTER_ORDER],
		  NSe1a_ds5[2],NSe2a_ds5[2],NSe3a_ds5[2],
		  NSe1b_ds5[2],NSe2b_ds5[2],NSe3b_ds5[2],
		  NSe1c_ds5[2],NSe2c_ds5[2],NSe3c_ds5[2],

		  input_ds6[FILTER_ORDER],input2a_ds6[FILTER_ORDER],input3a_ds6[FILTER_ORDER],
		  input2b_ds6[FILTER_ORDER],input3b_ds6[FILTER_ORDER],
		  input2c_ds6[FILTER_ORDER],input3c_ds6[FILTER_ORDER],
		  NSe1a_ds6[2],NSe2a_ds6[2],NSe3a_ds6[2],
		  NSe1b_ds6[2],NSe2b_ds6[2],NSe3b_ds6[2],
		  NSe1c_ds6[2],NSe2c_ds6[2],NSe3c_ds6[2],

		  input_ds7[FILTER_ORDER],input2a_ds7[FILTER_ORDER],input3a_ds7[FILTER_ORDER],
		  input2b_ds7[FILTER_ORDER],input3b_ds7[FILTER_ORDER],
		  input2c_ds7[FILTER_ORDER],input3c_ds7[FILTER_ORDER],
		  NSe1a_ds7[2],NSe2a_ds7[2],NSe3a_ds7[2],
		  NSe1b_ds7[2],NSe2b_ds7[2],NSe3b_ds7[2],
		  NSe1c_ds7[2],NSe2c_ds7[2],NSe3c_ds7[2],

		  input_ds8[FILTER_ORDER],input2a_ds8[FILTER_ORDER],input3a_ds8[FILTER_ORDER],
		  input2b_ds8[FILTER_ORDER],input3b_ds8[FILTER_ORDER],
		  input2c_ds8[FILTER_ORDER],input3c_ds8[FILTER_ORDER],
		  NSe1a_ds8[2],NSe2a_ds8[2],NSe3a_ds8[2],
		  NSe1b_ds8[2],NSe2b_ds8[2],NSe3b_ds8[2],
		  NSe1c_ds8[2],NSe2c_ds8[2],NSe3c_ds8[2],

		  input_ds9[FILTER_ORDER],input2a_ds9[FILTER_ORDER],input3a_ds9[FILTER_ORDER],
		  input2b_ds9[FILTER_ORDER],input3b_ds9[FILTER_ORDER],
		  input2c_ds9[FILTER_ORDER],input3c_ds9[FILTER_ORDER],
		  NSe1a_ds9[2],NSe2a_ds9[2],NSe3a_ds9[2],
		  NSe1b_ds9[2],NSe2b_ds9[2],NSe3b_ds9[2],
		  NSe1c_ds9[2],NSe2c_ds9[2],NSe3c_ds9[2],

		  input1[FILTER_ORDER],input2a[FILTER_ORDER],input3a[FILTER_ORDER],
		  input2b[FILTER_ORDER],input3b[FILTER_ORDER],
		  input2c[FILTER_ORDER],input3c[FILTER_ORDER],// inputCW2[FILTER_ORDER],

		  NSe1a[2],NSe2a[2],NSe3a[2],
		  NSe1b[2],NSe2b[2],NSe3b[2],
		  NSe1c[2],NSe2c[2],NSe3c[2],

		  l_buffer[SAMPLEFILTER_TAP_NUM],

		  DSbuffer1[SAMPLEFILTER_TAP_NUM],DSbuffer2[SAMPLEFILTER_TAP_NUM],DSbuffer3[SAMPLEFILTER_TAP_NUM],
		  DSbuffer4[SAMPLEFILTER_TAP_NUM],DSbuffer5[SAMPLEFILTER_TAP_NUM],DSbuffer6[SAMPLEFILTER_TAP_NUM],
		  DSbuffer7[SAMPLEFILTER_TAP_NUM],DSbuffer8[SAMPLEFILTER_TAP_NUM],DSbuffer9[SAMPLEFILTER_TAP_NUM];

	short Output1a_ds1[FILTER_ORDER],Output2a_ds1[FILTER_ORDER],Output3a_ds1[FILTER_ORDER],
	      Output1b_ds1[FILTER_ORDER],Output2b_ds1[FILTER_ORDER],Output3b_ds1[FILTER_ORDER],
	      Output1c_ds1[FILTER_ORDER],Output2c_ds1[FILTER_ORDER],Output3c_ds1[FILTER_ORDER],

		  Output1a_ds2[FILTER_ORDER],Output2a_ds2[FILTER_ORDER],Output3a_ds2[FILTER_ORDER],
		  Output1b_ds2[FILTER_ORDER],Output2b_ds2[FILTER_ORDER],Output3b_ds2[FILTER_ORDER],
		  Output1c_ds2[FILTER_ORDER],Output2c_ds2[FILTER_ORDER],Output3c_ds2[FILTER_ORDER],

		  Output1a_ds3[FILTER_ORDER],Output2a_ds3[FILTER_ORDER],Output3a_ds3[FILTER_ORDER],
		  Output1b_ds3[FILTER_ORDER],Output2b_ds3[FILTER_ORDER],Output3b_ds3[FILTER_ORDER],
		  Output1c_ds3[FILTER_ORDER],Output2c_ds3[FILTER_ORDER],Output3c_ds3[FILTER_ORDER],

		  Output1a_ds4[FILTER_ORDER],Output2a_ds4[FILTER_ORDER],Output3a_ds4[FILTER_ORDER],
		  Output1b_ds4[FILTER_ORDER],Output2b_ds4[FILTER_ORDER],Output3b_ds4[FILTER_ORDER],
		  Output1c_ds4[FILTER_ORDER],Output2c_ds4[FILTER_ORDER],Output3c_ds4[FILTER_ORDER],

		  Output1a_ds5[FILTER_ORDER],Output2a_ds5[FILTER_ORDER],Output3a_ds5[FILTER_ORDER],
		  Output1b_ds5[FILTER_ORDER],Output2b_ds5[FILTER_ORDER],Output3b_ds5[FILTER_ORDER],
		  Output1c_ds5[FILTER_ORDER],Output2c_ds5[FILTER_ORDER],Output3c_ds5[FILTER_ORDER],

		  Output1a_ds6[FILTER_ORDER],Output2a_ds6[FILTER_ORDER],Output3a_ds6[FILTER_ORDER],
		  Output1b_ds6[FILTER_ORDER],Output2b_ds6[FILTER_ORDER],Output3b_ds6[FILTER_ORDER],
		  Output1c_ds6[FILTER_ORDER],Output2c_ds6[FILTER_ORDER],Output3c_ds6[FILTER_ORDER],

		  Output1a_ds7[FILTER_ORDER],Output2a_ds7[FILTER_ORDER],Output3a_ds7[FILTER_ORDER],
		  Output1b_ds7[FILTER_ORDER],Output2b_ds7[FILTER_ORDER],Output3b_ds7[FILTER_ORDER],
		  Output1c_ds7[FILTER_ORDER],Output2c_ds7[FILTER_ORDER],Output3c_ds7[FILTER_ORDER],

		  Output1a_ds8[FILTER_ORDER],Output2a_ds8[FILTER_ORDER],Output3a_ds8[FILTER_ORDER],
		  Output1b_ds8[FILTER_ORDER],Output2b_ds8[FILTER_ORDER],Output3b_ds8[FILTER_ORDER],
		  Output1c_ds8[FILTER_ORDER],Output2c_ds8[FILTER_ORDER],Output3c_ds8[FILTER_ORDER],

		  Output1a_ds9[FILTER_ORDER],Output2a_ds9[FILTER_ORDER],Output3a_ds9[FILTER_ORDER],
		  Output1b_ds9[FILTER_ORDER],Output2b_ds9[FILTER_ORDER],Output3b_ds9[FILTER_ORDER],
		  Output1c_ds9[FILTER_ORDER],Output2c_ds9[FILTER_ORDER],Output3c_ds9[FILTER_ORDER],

		  Output1a[FILTER_ORDER],Output2a[FILTER_ORDER],Output3a[FILTER_ORDER], //OutputCW1[FILTER_ORDER],OutputCW2[FILTER_ORDER],
		  Output1b[FILTER_ORDER],Output2b[FILTER_ORDER],Output3b[FILTER_ORDER],
		  Output1c[FILTER_ORDER],Output2c[FILTER_ORDER],Output3c[FILTER_ORDER],




		  DSOutput1,DSOutput2,DSOutput3,
		  DSOutput4,DSOutput5,DSOutput6,
		  DSOutput7,DSOutput8,DSOutput9;

	short data1,data2,data3,data4,j;
	//long rawrms;



	//short l_buffer[SAMPLEFILTER_TAP_NUM],r_buffer[SAMPLEFILTER_TAP_NUM];
	//long Lresult, Rresult;
    USBSTK5515_init( );
    SYS_EXBUSSEL = 0x6100;         // Enable I2C bus
    USBSTK5515_I2C_init( );        // Initialize I2C

		AIC3204_rset( 0, 0 );          // Select page 0
	    AIC3204_rset( 1, 1 );          // Reset codec
	    AIC3204_rset( 0, 1 );          // Select page 1
	    AIC3204_rset( 1, 8 );          // Disable crude AVDD generation from DVDD
	    AIC3204_rset( 2, 1 );          // Enable Analog Blocks, use LDO power
	    AIC3204_rset( 0, 0 );          // Select page 0
	    /* PLL and Clocks config and Power Up  */
	    AIC3204_rset( 27, 0x0d );      // BCLK and WCLK is set as o/p to AIC3204(Master)
	    AIC3204_rset( 28, 0x00 );      // Data ofset = 0
	    AIC3204_rset( 4, 3 );          // PLL setting: PLLCLK <- MCLK, CODEC_CLKIN <-PLL CLK
	    AIC3204_rset( 6, 7 );          // PLL setting: J=7
	    AIC3204_rset( 7, 0x06 );       // PLL setting: HI_BYTE(D=1680)
	    AIC3204_rset( 8, 0x90 );       // PLL setting: LO_BYTE(D=1680)
	    AIC3204_rset( 30, 0x88 );      // For 32 bit clocks per frame in Master mode ONLY
	                                   // BCLK=DAC_CLK/N =(12288000/8) = 1.536MHz = 32*fs
	    AIC3204_rset( 5, 0x91 );       // PLL setting: Power up PLL, P=1 and R=1
	    AIC3204_rset( 13, 0 );         // Hi_Byte(DOSR) for DOSR = 128 decimal or 0x0080 DAC oversamppling
	    AIC3204_rset( 14, 0x80 );      // Lo_Byte(DOSR) for DOSR = 128 decimal or 0x0080
	    AIC3204_rset( 20, 0x80 );      // AOSR for AOSR = 128 decimal or 0x0080 for decimation filters 1 to 6
	    AIC3204_rset( 11, 0x82 );      // Power up NDAC and set NDAC value to 2
	    AIC3204_rset( 12, 0x87 );      // Power up MDAC and set MDAC value to 7
	    AIC3204_rset( 18, 0x87 );      // Power up NADC and set NADC value to 7
	    AIC3204_rset( 19, 0x82 );      // Power up MADC and set MADC value to 2
	    /* DAC ROUTING and Power Up */
	    AIC3204_rset(  0, 0x01 );      // Select page 1
	    AIC3204_rset( 12, 0x08 );      // LDAC AFIR routed to HPL
	    AIC3204_rset( 13, 0x08 );      // RDAC AFIR routed to HPR
	    AIC3204_rset(  0, 0x00 );      // Select page 0
	    AIC3204_rset( 64, 0x02 );      // Left vol=right vol
	    AIC3204_rset( 65, 0x20 );      // Left DAC gain to 0dB VOL; Right tracks Left
	    AIC3204_rset( 63, 0xd4 );      // Power up left,right data paths and set channel
	    AIC3204_rset(  0, 0x01 );      // Select page 1
	    AIC3204_rset( 16, 0x00 );      // Unmute HPL , 0dB gain
	    AIC3204_rset( 17, 0x00 );      // Unmute HPR , 0dB gain
	    AIC3204_rset(  9, 0x30 );      // Power up HPL,HPR
	    AIC3204_rset(  0, 0x00 );      // Select page 0
	    USBSTK5515_wait( 500 );        // Wait

	    /* ADC ROUTING and Power Up */
	    AIC3204_rset( 0, 1 );          // Select page 1
	    AIC3204_rset( 0x34, 0x30 );    // STEREO 1 Jack
			                           // IN2_L to LADC_P through 40 kohm
	    AIC3204_rset( 0x37, 0x30 );    // IN2_R to RADC_P through 40 kohmm
	    AIC3204_rset( 0x36, 3 );       // CM_1 (common mode) to LADC_M through 40 kohm
	    AIC3204_rset( 0x39, 0xc0 );    // CM_1 (common mode) to RADC_M through 40 kohm
	    AIC3204_rset( 0x3b, 0 );       // MIC_PGA_L unmute
	    AIC3204_rset( 0x3c, 0 );       // MIC_PGA_R unmute
	    AIC3204_rset( 0, 0 );          // Select page 0
	    AIC3204_rset( 0x51, 0xc0 );    // Powerup Left and Right ADC
	    AIC3204_rset( 0x52, 0 );       // Unmute Left and Right ADC

	    AIC3204_rset( 0, 0 );
	    USBSTK5515_wait( 200 );        // Wait
	    /* I2S settings */
	    I2S0_SRGR = 0x0;
	    I2S0_CR = 0x8010;    // 16-bit word, slave, enable I2C
	    I2S0_ICMR = 0x3f;    // Enable interrupts
	    USBSTK5515_I2C_close( );

	    oled_test();

	    I2CREG = 0x6620;
		I2CREG2 = 1;

	    while((I2CREG3 & 0x10) == 0);

		I2CREG4 = 0x40;
		DMA2_CH10_EVENT_SRC = 1;
		I2CREG = 0x66A0;
		DMA2_CH0_SRC_LSW  = 0x0C00;			// DMA2 Channel 0 Source LSW Address
		DMA2_CH0_SRC_MSW = 0x1;				// DMA2 Channel 0 Source MSW Address
		DMA2_CH0_DST_LSW = 0x1A20;			// DMA2 Channel 0 Destination LSW Address
		DMA2_CH0_DST_MSW = 0x0;				// DMA2 Channel 0 Destination MSW Address
		DMA2_CH0_TC_LSW = 768;				// DMA2 Channel 0 Length / Transfer Control LSW Register
		DMA2_CH0_TC_MSW = 0x0D204;			// DMA2 Channel 0 Transfer Control MSW Register




	    while ( 1 )
	    	{
	    			// Read Digital audio */



	    	asm(" AMOV #000600h, XAR6");


	    	asm(" MOV #00FFh, *AR6+");
	    	asm(" MOV #00FFh, *AR6+");
	    	asm(" MOV #00FFh, *AR6+");
	    	asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #00FFh, *AR6+");
			asm(" MOV #00FFh, *AR6+");
			asm(" MOV #00FFh, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
			asm(" MOV #0000h, *AR6+");
	            	while((Rcv & I2S0_IR) == 0);// Wait for interrupt pending flag

	            	//asm(" bset XF");

	            	l_buffer[0] = I2S0_W0_MSW_R;// 16 bit left channel received audio data

	            	data1 = I2S0_W0_LSW_R;

	            	data4 = I2S0_W1_MSW_R;  // 16 bit right channel received audio data

	            	data2 = I2S0_W1_LSW_R;


/*
	            	if(DS_table[samplecount] == 768){  // M = 2



	            		DSbuffer1[0] = l_buffer[0];
	            		DSResult1 = (long)DSbuffer1[0] * filter_taps[0] + (long)DSbuffer1[1] * filter_taps[1] + (long)DSbuffer1[2] * filter_taps[2] + (long)DSbuffer1[3] * filter_taps[3] + (long)DSbuffer1[4] * filter_taps[4] + (long)DSbuffer1[5] * filter_taps[5] + (long)DSbuffer1[6] * filter_taps[6] + (long)DSbuffer1[7] * filter_taps[7] + (long)DSbuffer1[8] * filter_taps[8] + (long)DSbuffer1[9] * filter_taps[9] +
	            			   	  (long)DSbuffer1[10] * filter_taps[10] + (long)DSbuffer1[11] * filter_taps[11] + (long)DSbuffer1[12] * filter_taps[12] + (long)DSbuffer1[13] * filter_taps[13] + (long)DSbuffer1[14] * filter_taps[14] + (long)DSbuffer1[15] * filter_taps[15] + (long)DSbuffer1[16] * filter_taps[16] + (long)DSbuffer1[17] * filter_taps[17] + (long)DSbuffer1[18] * filter_taps[18] + (long)DSbuffer1[19] * filter_taps[19] +
	            			   	  (long)DSbuffer1[20] * filter_taps[20] + (long)DSbuffer1[21] * filter_taps[21] + (long)DSbuffer1[22] * filter_taps[22] + (long)DSbuffer1[23] * filter_taps[23] + (long)DSbuffer1[24] * filter_taps[24] + (long)DSbuffer1[25] * filter_taps[25] + (long)DSbuffer1[26] * filter_taps[26] + (long)DSbuffer1[27] * filter_taps[27] + (long)DSbuffer1[28] * filter_taps[28] + (long)DSbuffer1[29] * filter_taps[29] +
	            			      (long)DSbuffer1[30] * filter_taps[30] + (long)DSbuffer1[31] * filter_taps[31] + (long)DSbuffer1[32] * filter_taps[32] + (long)DSbuffer1[33] * filter_taps[33] + (long)DSbuffer1[34] * filter_taps[34] + (long)DSbuffer1[35] * filter_taps[35] + (long)DSbuffer1[36] * filter_taps[36] + (long)DSbuffer1[37] * filter_taps[37] + (long)DSbuffer1[38] * filter_taps[38] + (long)DSbuffer1[39] * filter_taps[39] +
								  (long)DSbuffer1[40] * filter_taps[40] + (long)DSbuffer1[41] * filter_taps[41] + (long)DSbuffer1[42] * filter_taps[42] + (long)DSbuffer1[43] * filter_taps[43] + (long)DSbuffer1[44] * filter_taps[44] + (long)DSbuffer1[45] * filter_taps[45] + (long)DSbuffer1[46] * filter_taps[46] + (long)DSbuffer1[47] * filter_taps[47] + (long)DSbuffer1[48] * filter_taps[48] + (long)DSbuffer1[49] * filter_taps[49] +
    							  (long)DSbuffer1[50] * filter_taps[50] + (long)DSbuffer1[51] * filter_taps[51] + (long)DSbuffer1[52] * filter_taps[52] + (long)DSbuffer1[53] * filter_taps[53] + (long)DSbuffer1[54] * filter_taps[54] + (long)DSbuffer1[55] * filter_taps[55] + (long)DSbuffer1[56] * filter_taps[56] + (long)DSbuffer1[57] * filter_taps[57] + (long)DSbuffer1[58] * filter_taps[58] + (long)DSbuffer1[59] * filter_taps[59] +
	            		          (long)DSbuffer1[60] * filter_taps[60] + (long)DSbuffer1[61] * filter_taps[61] + (long)DSbuffer1[62] * filter_taps[62] + (long)DSbuffer1[63] * filter_taps[63] + (long)DSbuffer1[64] * filter_taps[64] + (long)DSbuffer1[65] * filter_taps[65] + (long)DSbuffer1[66] * filter_taps[66] + (long)DSbuffer1[67] * filter_taps[67] + (long)DSbuffer1[68] * filter_taps[68] + (long)DSbuffer1[69] * filter_taps[69] +
	            			      (long)DSbuffer1[70] * filter_taps[70] + (long)DSbuffer1[71] * filter_taps[71] + (long)DSbuffer1[72] * filter_taps[72] + (long)DSbuffer1[73] * filter_taps[73] + (long)DSbuffer1[74] * filter_taps[74] + (long)DSbuffer1[75] * filter_taps[75] + (long)DSbuffer1[76] * filter_taps[76] + (long)DSbuffer1[77] * filter_taps[77] + (long)DSbuffer1[78] * filter_taps[78] + (long)DSbuffer1[79] * filter_taps[79] +
	            			      (long)DSbuffer1[80] * filter_taps[80] + (long)DSbuffer1[81] * filter_taps[81] + (long)DSbuffer1[82] * filter_taps[82] + (long)DSbuffer1[83] * filter_taps[83] + (long)DSbuffer1[84] * filter_taps[84] + (long)DSbuffer1[85] * filter_taps[85] + (long)DSbuffer1[86] * filter_taps[86] + (long)DSbuffer1[87] * filter_taps[87] + (long)DSbuffer1[88] * filter_taps[88] + (long)DSbuffer1[89] * filter_taps[89] +
	            		          (long)DSbuffer1[90] * filter_taps[90] + (long)DSbuffer1[91] * filter_taps[91] + (long)DSbuffer1[92] * filter_taps[92] + (long)DSbuffer1[93] * filter_taps[93] + (long)DSbuffer1[94] * filter_taps[94] + (long)DSbuffer1[95] * filter_taps[95];


						 DSbuffer1[95] = DSbuffer1[94];
						 DSbuffer1[94] = DSbuffer1[93];
						 DSbuffer1[93] = DSbuffer1[92];
						 DSbuffer1[92] = DSbuffer1[91];
						 DSbuffer1[91] = DSbuffer1[90];
						 DSbuffer1[90] = DSbuffer1[89];
						 DSbuffer1[89] = DSbuffer1[88];
						 DSbuffer1[88] = DSbuffer1[87];
						 DSbuffer1[87] = DSbuffer1[86];
						 DSbuffer1[86] = DSbuffer1[85];
						 DSbuffer1[85] = DSbuffer1[84];
						 DSbuffer1[84] = DSbuffer1[83];
						 DSbuffer1[83] = DSbuffer1[82];
						 DSbuffer1[82] = DSbuffer1[81];
						 DSbuffer1[81] = DSbuffer1[80];
						 DSbuffer1[80] = DSbuffer1[79];
						 DSbuffer1[79] = DSbuffer1[78];
						 DSbuffer1[78] = DSbuffer1[77];
						 DSbuffer1[77] = DSbuffer1[76];
						 DSbuffer1[76] = DSbuffer1[75];
						 DSbuffer1[75] = DSbuffer1[74];
						 DSbuffer1[74] = DSbuffer1[73];
						 DSbuffer1[73] = DSbuffer1[72];
						 DSbuffer1[72] = DSbuffer1[71];
						 DSbuffer1[71] = DSbuffer1[70];
						 DSbuffer1[70] = DSbuffer1[69];
						 DSbuffer1[69] = DSbuffer1[68];
						 DSbuffer1[68] = DSbuffer1[67];
						 DSbuffer1[67] = DSbuffer1[66];
						 DSbuffer1[66] = DSbuffer1[65];
						 DSbuffer1[65] = DSbuffer1[64];
						 DSbuffer1[64] = DSbuffer1[63];
						 DSbuffer1[63] = DSbuffer1[62];
						 DSbuffer1[62] = DSbuffer1[61];
						 DSbuffer1[61] = DSbuffer1[60];
						 DSbuffer1[60] = DSbuffer1[59];
						 DSbuffer1[59] = DSbuffer1[58];
						 DSbuffer1[58] = DSbuffer1[57];
						 DSbuffer1[57] = DSbuffer1[56];
						 DSbuffer1[56] = DSbuffer1[55];
						 DSbuffer1[55] = DSbuffer1[54];
						 DSbuffer1[54] = DSbuffer1[53];
						 DSbuffer1[53] = DSbuffer1[52];
						 DSbuffer1[52] = DSbuffer1[51];
						 DSbuffer1[51] = DSbuffer1[50];
						 DSbuffer1[50] = DSbuffer1[49];
						 DSbuffer1[49] = DSbuffer1[48];
						 DSbuffer1[48] = DSbuffer1[47];
						 DSbuffer1[47] = DSbuffer1[46];
						 DSbuffer1[46] = DSbuffer1[45];
						 DSbuffer1[45] = DSbuffer1[44];
						 DSbuffer1[44] = DSbuffer1[43];
						 DSbuffer1[43] = DSbuffer1[42];
						 DSbuffer1[42] = DSbuffer1[41];
						 DSbuffer1[41] = DSbuffer1[40];
						 DSbuffer1[40] = DSbuffer1[39];
						 DSbuffer1[39] = DSbuffer1[38];
						 DSbuffer1[38] = DSbuffer1[37];
						 DSbuffer1[37] = DSbuffer1[36];
						 DSbuffer1[36] = DSbuffer1[35];
						 DSbuffer1[35] = DSbuffer1[34];
						 DSbuffer1[34] = DSbuffer1[33];
						 DSbuffer1[33] = DSbuffer1[32];
						 DSbuffer1[32] = DSbuffer1[31];
						 DSbuffer1[31] = DSbuffer1[30];
						 DSbuffer1[30] = DSbuffer1[29];
						 DSbuffer1[29] = DSbuffer1[28];
						 DSbuffer1[28] = DSbuffer1[27];
						 DSbuffer1[27] = DSbuffer1[26];
						 DSbuffer1[26] = DSbuffer1[25];
						 DSbuffer1[25] = DSbuffer1[24];
						 DSbuffer1[24] = DSbuffer1[23];
						 DSbuffer1[23] = DSbuffer1[22];
						 DSbuffer1[22] = DSbuffer1[21];
						 DSbuffer1[21] = DSbuffer1[20];
						 DSbuffer1[20] = DSbuffer1[19];
						 DSbuffer1[19] = DSbuffer1[18];
						 DSbuffer1[18] = DSbuffer1[17];
						 DSbuffer1[17] = DSbuffer1[16];
						 DSbuffer1[16] = DSbuffer1[15];
						 DSbuffer1[15] = DSbuffer1[14];
						 DSbuffer1[14] = DSbuffer1[13];
						 DSbuffer1[13] = DSbuffer1[12];
						 DSbuffer1[12] = DSbuffer1[11];
						 DSbuffer1[11] = DSbuffer1[10];
						 DSbuffer1[10] = DSbuffer1[9];
						 DSbuffer1[9] = DSbuffer1[8];
						 DSbuffer1[8] = DSbuffer1[7];
						 DSbuffer1[7] = DSbuffer1[6];
						 DSbuffer1[6] = DSbuffer1[5];
						 DSbuffer1[5] = DSbuffer1[4];
						 DSbuffer1[4] = DSbuffer1[3];
						 DSbuffer1[3] = DSbuffer1[2];
						 DSbuffer1[2] = DSbuffer1[1];
						 DSbuffer1[1] = DSbuffer1[0];

						DSResult1 >>= 14;

						DSOutput1 = (short)(DSResult1);

						input_ds1[0] = DSOutput1;

		//				ResultCW1_ds1 = (long)input_ds1[0]*b01CW + (long)input_ds1[1]*b11CW + (long)input_ds1[2]*b21CW - (long)OutputCW1_ds1[1]*a11CW - (long)OutputCW1_ds1[2]*a21CW;

						Result1a_ds1 = (long)input_ds1[0]*b01a + (long)input_ds1[1]*b11a + (long)input_ds1[2]*b21a - (long)Output1a_ds1[1]*a11a - (long)Output1a_ds1[2]*a21a + NSe1a_ds1[1];

						Result1b_ds1 = (long)input_ds1[0]*b01b + (long)input_ds1[1]*b11b + (long)input_ds1[2]*b21b - (long)Output1b_ds1[1]*a11b - (long)Output1b_ds1[2]*a21b + NSe1b_ds1[1];

						Result1c_ds1 = (long)input_ds1[0]*b01c + (long)input_ds1[1]*b11c + (long)input_ds1[2]*b21c - (long)Output1c_ds1[1]*a11c - (long)Output1c_ds1[2]*a21c + NSe1c_ds1[1];

						NSe1a_ds1[0] = Result1a_ds1 & 16383;

						NSe1b_ds1[0] = Result1b_ds1 & 16383;

						NSe1c_ds1[0] = Result1c_ds1 & 16383;

			//			OutputCW1_ds1[0] = (short)(ResultCW1_ds1 >> 13);

						Output1a_ds1[0] = (short)(Result1a_ds1 >> 14);

						Output1b_ds1[0] = (short)(Result1b_ds1 >> 14);

						Output1c_ds1[0] = (short)(Result1c_ds1 >> 14);

				//		inputCW2_ds1[0] = OutputCW1_ds1[0];

						input2a_ds1[0] = Output1a_ds1[0];

						input2b_ds1[0] = Output1b_ds1[0];

						input2c_ds1[0] = Output1c_ds1[0];

			//			ResultCW2_ds1 = (long)inputCW2_ds1[0]*b02CW + (long)inputCW2_ds1[1]*b12CW + (long)inputCW2_ds1[2]*b22CW - (long)OutputCW2_ds1[1]*a12CW - (long)OutputCW2_ds1[2]*a22CW;

						Result2a_ds1 = (long)input2a_ds1[0]*b02a + (long)input2a_ds1[1]*b12a + (long)input2a_ds1[2]*b22a - (long)Output2a_ds1[1]*a12a - (long)Output2a_ds1[2]*a22a + NSe2a_ds1[1];

						Result2b_ds1 = (long)input2b_ds1[0]*b02b + (long)input2b_ds1[1]*b12b + (long)input2b_ds1[2]*b22b - (long)Output2b_ds1[1]*a12b - (long)Output2b_ds1[2]*a22b + NSe2b_ds1[1];

						Result2c_ds1 = (long)input2c_ds1[0]*b02c + (long)input2c_ds1[1]*b12c + (long)input2c_ds1[2]*b22c - (long)Output2c_ds1[1]*a12c - (long)Output2c_ds1[2]*a22c + NSe2c_ds1[1];

						NSe2a_ds1[0] = Result2a_ds1 & 16383;

						NSe2b_ds1[0] = Result2b_ds1 & 16383;

						NSe2c_ds1[0] = Result2c_ds1 & 16383;

			//			OutputCW2_ds1[0] = (short)(ResultCW2_ds1 >> 13);

						Output2a_ds1[0] = (short)(Result2a_ds1 >> 14);

						Output2b_ds1[0] = (short)(Result2b_ds1 >> 14);

						Output2c_ds1[0] = (short)(Result2c_ds1 >> 14);

						input3a_ds1[0] = Output2a_ds1[0];

						input3b_ds1[0] = Output2b_ds1[0];

						input3c_ds1[0] = Output2c_ds1[0];

						Result3a_ds1 = (long)input3a_ds1[0]*b03a + (long)input3a_ds1[1]*b13a + (long)input3a_ds1[2]*b23a - (long)Output3a_ds1[1]*a13a - (long)Output3a_ds1[2]*a23a + NSe3a_ds1[1];

						Result3b_ds1 = (long)input3b_ds1[0]*b03b + (long)input3b_ds1[1]*b13b + (long)input3b_ds1[2]*b23b - (long)Output3b_ds1[1]*a13b - (long)Output3b_ds1[2]*a23b + NSe3b_ds1[1];

						Result3c_ds1 = (long)input3c_ds1[0]*b03c + (long)input3c_ds1[1]*b13c + (long)input3c_ds1[2]*b23c - (long)Output3c_ds1[1]*a13c - (long)Output3c_ds1[2]*a23c + NSe3c_ds1[1];

						NSe3a_ds1[0] = Result3a_ds1 & 16383;

						NSe3b_ds1[0] = Result3b_ds1 & 16383;

						NSe3c_ds1[0] = Result3c_ds1 & 16383;

						Output3a_ds1[0] = (short)(Result3a_ds1 >> 14);

						Output3b_ds1[0] = (short)(Result3b_ds1 >> 14);

						Output3c_ds1[0] = (short)(Result3c_ds1 >> 14);

						NSe1a_ds1[1] = NSe1a_ds1[0];
						NSe2a_ds1[1] = NSe2a_ds1[0];
						NSe3a_ds1[1] = NSe3a_ds1[0];

						NSe1b_ds1[1] = NSe1b_ds1[0];
						NSe2b_ds1[1] = NSe2b_ds1[0];
						NSe3b_ds1[1] = NSe3b_ds1[0];

						NSe1c_ds1[1] = NSe1c_ds1[0];
						NSe2c_ds1[1] = NSe2c_ds1[0];
						NSe3c_ds1[1] = NSe3c_ds1[0];

						input_ds1[2] = input_ds1[1];
						input_ds1[1] = input_ds1[0];

			//			inputCW2_ds1[2] = inputCW2_ds1[1];
			//			inputCW2_ds1[1] = inputCW2_ds1[0];

						input2a_ds1[2] = input2a_ds1[1];
						input3a_ds1[2] = input3a_ds1[1];

						input2b_ds1[2] = input2b_ds1[1];
						input3b_ds1[2] = input3b_ds1[1];

						input2c_ds1[2] = input2c_ds1[1];
						input3c_ds1[2] = input3c_ds1[1];

						input2a_ds1[1] = input2a_ds1[0];
						input3a_ds1[1] = input3a_ds1[0];

						input2b_ds1[1] = input2b_ds1[0];
						input3b_ds1[1] = input3b_ds1[0];

						input2c_ds1[1] = input2c_ds1[0];
						input3c_ds1[1] = input3c_ds1[0];

			//			OutputCW1_ds1[2] = OutputCW1_ds1[1];
			//			OutputCW1_ds1[1] = OutputCW1_ds1[0];
			//			OutputCW2_ds1[2] = OutputCW2_ds1[1];
			//			OutputCW2_ds1[1] = OutputCW2_ds1[0];

						Output1a_ds1[2] = Output1a_ds1[1];
						Output2a_ds1[2] = Output2a_ds1[1];
						Output3a_ds1[2] = Output3a_ds1[1];

						Output1b_ds1[2] = Output1b_ds1[1];
						Output2b_ds1[2] = Output2b_ds1[1];
						Output3b_ds1[2] = Output3b_ds1[1];

						Output1c_ds1[2] = Output1c_ds1[1];
						Output2c_ds1[2] = Output2c_ds1[1];
						Output3c_ds1[2] = Output3c_ds1[1];

						Output1a_ds1[1] = Output1a_ds1[0];
						Output2a_ds1[1] = Output2a_ds1[0];
						Output3a_ds1[1] = Output3a_ds1[0];

						Output1b_ds1[1] = Output1b_ds1[0];
						Output2b_ds1[1] = Output2b_ds1[0];
						Output3b_ds1[1] = Output3b_ds1[0];

						Output1c_ds1[1] = Output1c_ds1[0];
						Output2c_ds1[1] = Output2c_ds1[0];
						Output3c_ds1[1] = Output3c_ds1[0];

						if(RMScount1 < 256){

							tempRMS_band25 += (long)Output3a_ds1[1] * Output3a_ds1[1]  >>  14;
							tempRMS_band26 += (long)Output3b_ds1[1] * Output3b_ds1[1]  >>  14;
							tempRMS_band27 += (long)Output3c_ds1[1] * Output3c_ds1[1]  >>  14;

							RMScount1++;

						}
						else if(RMScount1 >= 256){

							tempRMS_band25 /= 4;
							tempRMS_band26 /= 4;
							tempRMS_band27 /= 4;

							// OUTPUT HER
							if(tempRMS_band25 >= dB_table[old_dB25+1]){
								old_dB25++;
								if(old_dB25 > 36){
									old_dB25 = 36;
								}
							}
							else if(tempRMS_band25 <= dB_table[old_dB25-1]){
								old_dB25--;
								if(old_dB25 < 0){
									old_dB25 = 0;
								}
							}

							if(tempRMS_band26 >= dB_table[old_dB26+1]){
								old_dB26++;
								if(old_dB26 > 36){
									old_dB26 = 36;
								}
							}
							else if(tempRMS_band26 <= dB_table[old_dB26-1]){
								old_dB26--;
								if(old_dB26 < 0){
									old_dB26 = 0;
								}
							}

							if(tempRMS_band27 >= dB_table[old_dB27+1]){
								old_dB27++;
								if(old_dB27 > 36){
									old_dB27 = 36;
								}
							}
							else if(tempRMS_band27 <= dB_table[old_dB27-1]){
								old_dB27--;
								if(old_dB27 < 0){
									old_dB27 = 0;
								}
							}



							tempRMS_band25 = 0;
							tempRMS_band26 = 0;
							tempRMS_band27 = 0;
							RMScount1 = 0;
						}
	            	}
	            	if(DS_table[samplecount] == 640){  // M = 4


	            		DSbuffer2[0] = l_buffer[0];
					DSResult2 = (long)DSbuffer2[0] * filter_taps[0] + (long)DSbuffer2[1] * filter_taps[1] + (long)DSbuffer2[2] * filter_taps[2] + (long)DSbuffer2[3] * filter_taps[3] + (long)DSbuffer2[4] * filter_taps[4] + (long)DSbuffer2[5] * filter_taps[5] + (long)DSbuffer2[6] * filter_taps[6] + (long)DSbuffer2[7] * filter_taps[7] + (long)DSbuffer2[8] * filter_taps[8] + (long)DSbuffer2[9] * filter_taps[9] +
							  (long)DSbuffer2[10] * filter_taps[10] + (long)DSbuffer2[11] * filter_taps[11] + (long)DSbuffer2[12] * filter_taps[12] + (long)DSbuffer2[13] * filter_taps[13] + (long)DSbuffer2[14] * filter_taps[14] + (long)DSbuffer2[15] * filter_taps[15] + (long)DSbuffer2[16] * filter_taps[16] + (long)DSbuffer2[17] * filter_taps[17] + (long)DSbuffer2[18] * filter_taps[18] + (long)DSbuffer2[19] * filter_taps[19] +
							  (long)DSbuffer2[20] * filter_taps[20] + (long)DSbuffer2[21] * filter_taps[21] + (long)DSbuffer2[22] * filter_taps[22] + (long)DSbuffer2[23] * filter_taps[23] + (long)DSbuffer2[24] * filter_taps[24] + (long)DSbuffer2[25] * filter_taps[25] + (long)DSbuffer2[26] * filter_taps[26] + (long)DSbuffer2[27] * filter_taps[27] + (long)DSbuffer2[28] * filter_taps[28] + (long)DSbuffer2[29] * filter_taps[29] +
							  (long)DSbuffer2[30] * filter_taps[30] + (long)DSbuffer2[31] * filter_taps[31] + (long)DSbuffer2[32] * filter_taps[32] + (long)DSbuffer2[33] * filter_taps[33] + (long)DSbuffer2[34] * filter_taps[34] + (long)DSbuffer2[35] * filter_taps[35] + (long)DSbuffer2[36] * filter_taps[36] + (long)DSbuffer2[37] * filter_taps[37] + (long)DSbuffer2[38] * filter_taps[38] + (long)DSbuffer2[39] * filter_taps[39] +
							  (long)DSbuffer2[40] * filter_taps[40] + (long)DSbuffer2[41] * filter_taps[41] + (long)DSbuffer2[42] * filter_taps[42] + (long)DSbuffer2[43] * filter_taps[43] + (long)DSbuffer2[44] * filter_taps[44] + (long)DSbuffer2[45] * filter_taps[45] + (long)DSbuffer2[46] * filter_taps[46] + (long)DSbuffer2[47] * filter_taps[47] + (long)DSbuffer2[48] * filter_taps[48] + (long)DSbuffer2[49] * filter_taps[49] +
							  (long)DSbuffer2[50] * filter_taps[50] + (long)DSbuffer2[51] * filter_taps[51] + (long)DSbuffer2[52] * filter_taps[52] + (long)DSbuffer2[53] * filter_taps[53] + (long)DSbuffer2[54] * filter_taps[54] + (long)DSbuffer2[55] * filter_taps[55] + (long)DSbuffer2[56] * filter_taps[56] + (long)DSbuffer2[57] * filter_taps[57] + (long)DSbuffer2[58] * filter_taps[58] + (long)DSbuffer2[59] * filter_taps[59] +
							  (long)DSbuffer2[60] * filter_taps[60] + (long)DSbuffer2[61] * filter_taps[61] + (long)DSbuffer2[62] * filter_taps[62] + (long)DSbuffer2[63] * filter_taps[63] + (long)DSbuffer2[64] * filter_taps[64] + (long)DSbuffer2[65] * filter_taps[65] + (long)DSbuffer2[66] * filter_taps[66] + (long)DSbuffer2[67] * filter_taps[67] + (long)DSbuffer2[68] * filter_taps[68] + (long)DSbuffer2[69] * filter_taps[69] +
							  (long)DSbuffer2[70] * filter_taps[70] + (long)DSbuffer2[71] * filter_taps[71] + (long)DSbuffer2[72] * filter_taps[72] + (long)DSbuffer2[73] * filter_taps[73] + (long)DSbuffer2[74] * filter_taps[74] + (long)DSbuffer2[75] * filter_taps[75] + (long)DSbuffer2[76] * filter_taps[76] + (long)DSbuffer2[77] * filter_taps[77] + (long)DSbuffer2[78] * filter_taps[78] + (long)DSbuffer2[79] * filter_taps[79] +
							  (long)DSbuffer2[80] * filter_taps[80] + (long)DSbuffer2[81] * filter_taps[81] + (long)DSbuffer2[82] * filter_taps[82] + (long)DSbuffer2[83] * filter_taps[83] + (long)DSbuffer2[84] * filter_taps[84] + (long)DSbuffer2[85] * filter_taps[85] + (long)DSbuffer2[86] * filter_taps[86] + (long)DSbuffer2[87] * filter_taps[87] + (long)DSbuffer2[88] * filter_taps[88] + (long)DSbuffer2[89] * filter_taps[89] +
							  (long)DSbuffer2[90] * filter_taps[90] + (long)DSbuffer2[91] * filter_taps[91] + (long)DSbuffer2[92] * filter_taps[92] + (long)DSbuffer2[93] * filter_taps[93] + (long)DSbuffer2[94] * filter_taps[94] + (long)DSbuffer2[95] * filter_taps[95];


					 DSbuffer2[95] = DSbuffer2[94];
					 DSbuffer2[94] = DSbuffer2[93];
					 DSbuffer2[93] = DSbuffer2[92];
					 DSbuffer2[92] = DSbuffer2[91];
					 DSbuffer2[91] = DSbuffer2[90];
					 DSbuffer2[90] = DSbuffer2[89];
					 DSbuffer2[89] = DSbuffer2[88];
					 DSbuffer2[88] = DSbuffer2[87];
					 DSbuffer2[87] = DSbuffer2[86];
					 DSbuffer2[86] = DSbuffer2[85];
					 DSbuffer2[85] = DSbuffer2[84];
					 DSbuffer2[84] = DSbuffer2[83];
					 DSbuffer2[83] = DSbuffer2[82];
					 DSbuffer2[82] = DSbuffer2[81];
					 DSbuffer2[81] = DSbuffer2[80];
					 DSbuffer2[80] = DSbuffer2[79];
					 DSbuffer2[79] = DSbuffer2[78];
					 DSbuffer2[78] = DSbuffer2[77];
					 DSbuffer2[77] = DSbuffer2[76];
					 DSbuffer2[76] = DSbuffer2[75];
					 DSbuffer2[75] = DSbuffer2[74];
					 DSbuffer2[74] = DSbuffer2[73];
					 DSbuffer2[73] = DSbuffer2[72];
					 DSbuffer2[72] = DSbuffer2[71];
					 DSbuffer2[71] = DSbuffer2[70];
					 DSbuffer2[70] = DSbuffer2[69];
					 DSbuffer2[69] = DSbuffer2[68];
					 DSbuffer2[68] = DSbuffer2[67];
					 DSbuffer2[67] = DSbuffer2[66];
					 DSbuffer2[66] = DSbuffer2[65];
					 DSbuffer2[65] = DSbuffer2[64];
					 DSbuffer2[64] = DSbuffer2[63];
					 DSbuffer2[63] = DSbuffer2[62];
					 DSbuffer2[62] = DSbuffer2[61];
					 DSbuffer2[61] = DSbuffer2[60];
					 DSbuffer2[60] = DSbuffer2[59];
					 DSbuffer2[59] = DSbuffer2[58];
					 DSbuffer2[58] = DSbuffer2[57];
					 DSbuffer2[57] = DSbuffer2[56];
					 DSbuffer2[56] = DSbuffer2[55];
					 DSbuffer2[55] = DSbuffer2[54];
					 DSbuffer2[54] = DSbuffer2[53];
					 DSbuffer2[53] = DSbuffer2[52];
					 DSbuffer2[52] = DSbuffer2[51];
					 DSbuffer2[51] = DSbuffer2[50];
					 DSbuffer2[50] = DSbuffer2[49];
					 DSbuffer2[49] = DSbuffer2[48];
					 DSbuffer2[48] = DSbuffer2[47];
					 DSbuffer2[47] = DSbuffer2[46];
					 DSbuffer2[46] = DSbuffer2[45];
					 DSbuffer2[45] = DSbuffer2[44];
					 DSbuffer2[44] = DSbuffer2[43];
					 DSbuffer2[43] = DSbuffer2[42];
					 DSbuffer2[42] = DSbuffer2[41];
					 DSbuffer2[41] = DSbuffer2[40];
					 DSbuffer2[40] = DSbuffer2[39];
					 DSbuffer2[39] = DSbuffer2[38];
					 DSbuffer2[38] = DSbuffer2[37];
					 DSbuffer2[37] = DSbuffer2[36];
					 DSbuffer2[36] = DSbuffer2[35];
					 DSbuffer2[35] = DSbuffer2[34];
					 DSbuffer2[34] = DSbuffer2[33];
					 DSbuffer2[33] = DSbuffer2[32];
					 DSbuffer2[32] = DSbuffer2[31];
					 DSbuffer2[31] = DSbuffer2[30];
					 DSbuffer2[30] = DSbuffer2[29];
					 DSbuffer2[29] = DSbuffer2[28];
					 DSbuffer2[28] = DSbuffer2[27];
					 DSbuffer2[27] = DSbuffer2[26];
					 DSbuffer2[26] = DSbuffer2[25];
					 DSbuffer2[25] = DSbuffer2[24];
					 DSbuffer2[24] = DSbuffer2[23];
					 DSbuffer2[23] = DSbuffer2[22];
					 DSbuffer2[22] = DSbuffer2[21];
					 DSbuffer2[21] = DSbuffer2[20];
					 DSbuffer2[20] = DSbuffer2[19];
					 DSbuffer2[19] = DSbuffer2[18];
					 DSbuffer2[18] = DSbuffer2[17];
					 DSbuffer2[17] = DSbuffer2[16];
					 DSbuffer2[16] = DSbuffer2[15];
					 DSbuffer2[15] = DSbuffer2[14];
					 DSbuffer2[14] = DSbuffer2[13];
					 DSbuffer2[13] = DSbuffer2[12];
					 DSbuffer2[12] = DSbuffer2[11];
					 DSbuffer2[11] = DSbuffer2[10];
					 DSbuffer2[10] = DSbuffer2[9];
					 DSbuffer2[9] = DSbuffer2[8];
					 DSbuffer2[8] = DSbuffer2[7];
					 DSbuffer2[7] = DSbuffer2[6];
					 DSbuffer2[6] = DSbuffer2[5];
					 DSbuffer2[5] = DSbuffer2[4];
					 DSbuffer2[4] = DSbuffer2[3];
					 DSbuffer2[3] = DSbuffer2[2];
					 DSbuffer2[2] = DSbuffer2[1];
					 DSbuffer2[1] = DSbuffer2[0];

					DSResult2 >>= 14;
					DSOutput2 = (short)(DSResult2);


					input_ds2[0] = DSOutput2;

		//			ResultCW1_ds2 = (long)input_ds2[0]*b01CW + (long)input_ds2[1]*b11CW + (long)input_ds2[2]*b21CW - (long)OutputCW1_ds2[1]*a11CW - (long)OutputCW1_ds2[2]*a21CW;

					Result1a_ds2 = (long)input_ds2[0]*b01a + (long)input_ds2[1]*b11a + (long)input_ds2[2]*b21a - (long)Output1a_ds2[1]*a11a - (long)Output1a_ds2[2]*a21a + NSe1a_ds2[1];

					Result1b_ds2 = (long)input_ds2[0]*b01b + (long)input_ds2[1]*b11b + (long)input_ds2[2]*b21b - (long)Output1b_ds2[1]*a11b - (long)Output1b_ds2[2]*a21b + NSe1b_ds2[1];

					Result1c_ds2 = (long)input_ds2[0]*b01c + (long)input_ds2[1]*b11c + (long)input_ds2[2]*b21c - (long)Output1c_ds2[1]*a11c - (long)Output1c_ds2[2]*a21c + NSe1c_ds2[1];

					NSe1a_ds2[0] = Result1a_ds2 & 16383;

					NSe1b_ds2[0] = Result1b_ds2 & 16383;

					NSe1c_ds2[0] = Result1c_ds2 & 16383;

			//		OutputCW1_ds2[0] = (short)(ResultCW1_ds2 >> 13);

					Output1a_ds2[0] = (short)(Result1a_ds2 >> 14);

					Output1b_ds2[0] = (short)(Result1b_ds2 >> 14);

					Output1c_ds2[0] = (short)(Result1c_ds2 >> 14);

			//		inputCW2_ds2[0] = OutputCW1_ds2[0];

					input2a_ds2[0] = Output1a_ds2[0];

					input2b_ds2[0] = Output1b_ds2[0];

					input2c_ds2[0] = Output1c_ds2[0];

		//			ResultCW2_ds2 = (long)inputCW2_ds2[0]*b02CW + (long)inputCW2_ds2[1]*b12CW + (long)inputCW2_ds2[2]*b22CW - (long)OutputCW2_ds2[1]*a12CW - (long)OutputCW2_ds2[2]*a22CW;

					Result2a_ds2 = (long)input2a_ds2[0]*b02a + (long)input2a_ds2[1]*b12a + (long)input2a_ds2[2]*b22a - (long)Output2a_ds2[1]*a12a - (long)Output2a_ds2[2]*a22a + NSe2a_ds2[1];

					Result2b_ds2 = (long)input2b_ds2[0]*b02b + (long)input2b_ds2[1]*b12b + (long)input2b_ds2[2]*b22b - (long)Output2b_ds2[1]*a12b - (long)Output2b_ds2[2]*a22b + NSe2b_ds2[1];

					Result2c_ds2 = (long)input2c_ds2[0]*b02c + (long)input2c_ds2[1]*b12c + (long)input2c_ds2[2]*b22c - (long)Output2c_ds2[1]*a12c - (long)Output2c_ds2[2]*a22c + NSe2c_ds2[1];

					NSe2a_ds2[0] = Result2a_ds2 & 16383;

					NSe2b_ds2[0] = Result2b_ds2 & 16383;

					NSe2c_ds2[0] = Result2c_ds2 & 16383;

			//		OutputCW2_ds2[0] = (short)(ResultCW2_ds2 >> 13);

					Output2a_ds2[0] = (short)(Result2a_ds2 >> 14);

					Output2b_ds2[0] = (short)(Result2b_ds2 >> 14);

					Output2c_ds2[0] = (short)(Result2c_ds2 >> 14);

					input3a_ds2[0] = Output2a_ds2[0];

					input3b_ds2[0] = Output2b_ds2[0];

					input3c_ds2[0] = Output2c_ds2[0];

					Result3a_ds2 = (long)input3a_ds2[0]*b03a + (long)input3a_ds2[1]*b13a + (long)input3a_ds2[2]*b23a - (long)Output3a_ds2[1]*a13a - (long)Output3a_ds2[2]*a23a + NSe3a_ds2[1];

					Result3b_ds2 = (long)input3b_ds2[0]*b03b + (long)input3b_ds2[1]*b13b + (long)input3b_ds2[2]*b23b - (long)Output3b_ds2[1]*a13b - (long)Output3b_ds2[2]*a23b + NSe3b_ds2[1];

					Result3c_ds2 = (long)input3c_ds2[0]*b03c + (long)input3c_ds2[1]*b13c + (long)input3c_ds2[2]*b23c - (long)Output3c_ds2[1]*a13c - (long)Output3c_ds2[2]*a23c + NSe3c_ds2[1];

					NSe3a_ds2[0] = Result3a_ds2 & 16383;

					NSe3b_ds2[0] = Result3b_ds2 & 16383;

					NSe3c_ds2[0] = Result3c_ds2 & 16383;

					Output3a_ds2[0] = (short)(Result3a_ds2 >> 14);

					Output3b_ds2[0] = (short)(Result3b_ds2 >> 14);

					Output3c_ds2[0] = (short)(Result3c_ds2 >> 14);

					NSe1a_ds2[1] = NSe1a_ds2[0];
					NSe2a_ds2[1] = NSe2a_ds2[0];
					NSe3a_ds2[1] = NSe3a_ds2[0];

					NSe1b_ds2[1] = NSe1b_ds2[0];
					NSe2b_ds2[1] = NSe2b_ds2[0];
					NSe3b_ds2[1] = NSe3b_ds2[0];

					NSe1c_ds2[1] = NSe1c_ds2[0];
					NSe2c_ds2[1] = NSe2c_ds2[0];
					NSe3c_ds2[1] = NSe3c_ds2[0];

					input_ds2[2] = input_ds2[1];
					input_ds2[1] = input_ds2[0];

			//		inputCW2_ds2[2] = inputCW2_ds2[1];
			//		inputCW2_ds2[1] = inputCW2_ds2[0];

					input2a_ds2[2] = input2a_ds2[1];
					input3a_ds2[2] = input3a_ds2[1];

					input2b_ds2[2] = input2b_ds2[1];
					input3b_ds2[2] = input3b_ds2[1];

					input2c_ds2[2] = input2c_ds2[1];
					input3c_ds2[2] = input3c_ds2[1];

					input2a_ds2[1] = input2a_ds2[0];
					input3a_ds2[1] = input3a_ds2[0];

					input2b_ds2[1] = input2b_ds2[0];
					input3b_ds2[1] = input3b_ds2[0];

					input2c_ds2[1] = input2c_ds2[0];
					input3c_ds2[1] = input3c_ds2[0];

		//			OutputCW1_ds2[2] = OutputCW1_ds2[1];
		//			OutputCW1_ds2[1] = OutputCW1_ds2[0];
		//			OutputCW2_ds2[2] = OutputCW2_ds2[1];
		//			OutputCW2_ds2[1] = OutputCW2_ds2[0];

					Output1a_ds2[2] = Output1a_ds2[1];
					Output2a_ds2[2] = Output2a_ds2[1];
					Output3a_ds2[2] = Output3a_ds2[1];

					Output1b_ds2[2] = Output1b_ds2[1];
					Output2b_ds2[2] = Output2b_ds2[1];
					Output3b_ds2[2] = Output3b_ds2[1];

					Output1c_ds2[2] = Output1c_ds2[1];
					Output2c_ds2[2] = Output2c_ds2[1];
					Output3c_ds2[2] = Output3c_ds2[1];

					Output1a_ds2[1] = Output1a_ds2[0];
					Output2a_ds2[1] = Output2a_ds2[0];
					Output3a_ds2[1] = Output3a_ds2[0];

					Output1b_ds2[1] = Output1b_ds2[0];
					Output2b_ds2[1] = Output2b_ds2[0];
					Output3b_ds2[1] = Output3b_ds2[0];

					Output1c_ds2[1] = Output1c_ds2[0];
					Output2c_ds2[1] = Output2c_ds2[0];
					Output3c_ds2[1] = Output3c_ds2[0];

					if(RMScount2 < 256){

						tempRMS_band22 += (long)Output3a_ds2[1] * Output3a_ds2[1]  >>  14;
						tempRMS_band23 += (long)Output3b_ds2[1] * Output3b_ds2[1]  >>  14;
						tempRMS_band24 += (long)Output3c_ds2[1] * Output3c_ds2[1]  >>  14;

						RMScount2++;

					}
					else if(RMScount2 >= 256){

						tempRMS_band22 /= 4;
						tempRMS_band23 /= 4;
						tempRMS_band24 /= 4;

						// OUTPUT HER
						if(tempRMS_band22 >= dB_table[old_dB22+1]){
							old_dB22++;
							if(old_dB22 > 36){
								old_dB22 = 36;
							}
						}
						else if(tempRMS_band22 <= dB_table[old_dB22-1]){
							old_dB22--;
							if(old_dB22 < 0){
								old_dB22 = 0;
							}
						}

						if(tempRMS_band23 >= dB_table[old_dB23+1]){
							old_dB23++;
							if(old_dB23 > 36){
								old_dB23 = 36;
							}
						}
						else if(tempRMS_band23 <= dB_table[old_dB23-1]){
							old_dB23--;
							if(old_dB23 < 0){
								old_dB23 = 0;
							}
						}

						if(tempRMS_band24 >= dB_table[old_dB24+1]){
							old_dB24++;
							if(old_dB24 > 36){
								old_dB24 = 36;
							}
						}
						else if(tempRMS_band24 <= dB_table[old_dB24-1]){
							old_dB24--;
							if(old_dB24 < 0){
								old_dB24 = 0;
							}
						}


						tempRMS_band22 = 0;
						tempRMS_band23 = 0;
						tempRMS_band24 = 0;
						RMScount2 = 0;
					}

	            	}
	            	if(DS_table[samplecount] == 576){  // M = 8


	            		DSbuffer3[0] = l_buffer[0];
					DSResult3 = (long)DSbuffer3[0] * filter_taps[0] + (long)DSbuffer3[1] * filter_taps[1] + (long)DSbuffer3[2] * filter_taps[2] + (long)DSbuffer3[3] * filter_taps[3] + (long)DSbuffer3[4] * filter_taps[4] + (long)DSbuffer3[5] * filter_taps[5] + (long)DSbuffer3[6] * filter_taps[6] + (long)DSbuffer3[7] * filter_taps[7] + (long)DSbuffer3[8] * filter_taps[8] + (long)DSbuffer3[9] * filter_taps[9] +
							  (long)DSbuffer3[10] * filter_taps[10] + (long)DSbuffer3[11] * filter_taps[11] + (long)DSbuffer3[12] * filter_taps[12] + (long)DSbuffer3[13] * filter_taps[13] + (long)DSbuffer3[14] * filter_taps[14] + (long)DSbuffer3[15] * filter_taps[15] + (long)DSbuffer3[16] * filter_taps[16] + (long)DSbuffer3[17] * filter_taps[17] + (long)DSbuffer3[18] * filter_taps[18] + (long)DSbuffer3[19] * filter_taps[19] +
							  (long)DSbuffer3[20] * filter_taps[20] + (long)DSbuffer3[21] * filter_taps[21] + (long)DSbuffer3[22] * filter_taps[22] + (long)DSbuffer3[23] * filter_taps[23] + (long)DSbuffer3[24] * filter_taps[24] + (long)DSbuffer3[25] * filter_taps[25] + (long)DSbuffer3[26] * filter_taps[26] + (long)DSbuffer3[27] * filter_taps[27] + (long)DSbuffer3[28] * filter_taps[28] + (long)DSbuffer3[29] * filter_taps[29] +
							  (long)DSbuffer3[30] * filter_taps[30] + (long)DSbuffer3[31] * filter_taps[31] + (long)DSbuffer3[32] * filter_taps[32] + (long)DSbuffer3[33] * filter_taps[33] + (long)DSbuffer3[34] * filter_taps[34] + (long)DSbuffer3[35] * filter_taps[35] + (long)DSbuffer3[36] * filter_taps[36] + (long)DSbuffer3[37] * filter_taps[37] + (long)DSbuffer3[38] * filter_taps[38] + (long)DSbuffer3[39] * filter_taps[39] +
							  (long)DSbuffer3[40] * filter_taps[40] + (long)DSbuffer3[41] * filter_taps[41] + (long)DSbuffer3[42] * filter_taps[42] + (long)DSbuffer3[43] * filter_taps[43] + (long)DSbuffer3[44] * filter_taps[44] + (long)DSbuffer3[45] * filter_taps[45] + (long)DSbuffer3[46] * filter_taps[46] + (long)DSbuffer3[47] * filter_taps[47] + (long)DSbuffer3[48] * filter_taps[48] + (long)DSbuffer3[49] * filter_taps[49] +
							  (long)DSbuffer3[50] * filter_taps[50] + (long)DSbuffer3[51] * filter_taps[51] + (long)DSbuffer3[52] * filter_taps[52] + (long)DSbuffer3[53] * filter_taps[53] + (long)DSbuffer3[54] * filter_taps[54] + (long)DSbuffer3[55] * filter_taps[55] + (long)DSbuffer3[56] * filter_taps[56] + (long)DSbuffer3[57] * filter_taps[57] + (long)DSbuffer3[58] * filter_taps[58] + (long)DSbuffer3[59] * filter_taps[59] +
							  (long)DSbuffer3[60] * filter_taps[60] + (long)DSbuffer3[61] * filter_taps[61] + (long)DSbuffer3[62] * filter_taps[62] + (long)DSbuffer3[63] * filter_taps[63] + (long)DSbuffer3[64] * filter_taps[64] + (long)DSbuffer3[65] * filter_taps[65] + (long)DSbuffer3[66] * filter_taps[66] + (long)DSbuffer3[67] * filter_taps[67] + (long)DSbuffer3[68] * filter_taps[68] + (long)DSbuffer3[69] * filter_taps[69] +
							  (long)DSbuffer3[70] * filter_taps[70] + (long)DSbuffer3[71] * filter_taps[71] + (long)DSbuffer3[72] * filter_taps[72] + (long)DSbuffer3[73] * filter_taps[73] + (long)DSbuffer3[74] * filter_taps[74] + (long)DSbuffer3[75] * filter_taps[75] + (long)DSbuffer3[76] * filter_taps[76] + (long)DSbuffer3[77] * filter_taps[77] + (long)DSbuffer3[78] * filter_taps[78] + (long)DSbuffer3[79] * filter_taps[79] +
							  (long)DSbuffer3[80] * filter_taps[80] + (long)DSbuffer3[81] * filter_taps[81] + (long)DSbuffer3[82] * filter_taps[82] + (long)DSbuffer3[83] * filter_taps[83] + (long)DSbuffer3[84] * filter_taps[84] + (long)DSbuffer3[85] * filter_taps[85] + (long)DSbuffer3[86] * filter_taps[86] + (long)DSbuffer3[87] * filter_taps[87] + (long)DSbuffer3[88] * filter_taps[88] + (long)DSbuffer3[89] * filter_taps[89] +
							  (long)DSbuffer3[90] * filter_taps[90] + (long)DSbuffer3[91] * filter_taps[91] + (long)DSbuffer3[92] * filter_taps[92] + (long)DSbuffer3[93] * filter_taps[93] + (long)DSbuffer3[94] * filter_taps[94] + (long)DSbuffer3[95] * filter_taps[95];


					 DSbuffer3[95] = DSbuffer3[94];
					 DSbuffer3[94] = DSbuffer3[93];
					 DSbuffer3[93] = DSbuffer3[92];
					 DSbuffer3[92] = DSbuffer3[91];
					 DSbuffer3[91] = DSbuffer3[90];
					 DSbuffer3[90] = DSbuffer3[89];
					 DSbuffer3[89] = DSbuffer3[88];
					 DSbuffer3[88] = DSbuffer3[87];
					 DSbuffer3[87] = DSbuffer3[86];
					 DSbuffer3[86] = DSbuffer3[85];
					 DSbuffer3[85] = DSbuffer3[84];
					 DSbuffer3[84] = DSbuffer3[83];
					 DSbuffer3[83] = DSbuffer3[82];
					 DSbuffer3[82] = DSbuffer3[81];
					 DSbuffer3[81] = DSbuffer3[80];
					 DSbuffer3[80] = DSbuffer3[79];
					 DSbuffer3[79] = DSbuffer3[78];
					 DSbuffer3[78] = DSbuffer3[77];
					 DSbuffer3[77] = DSbuffer3[76];
					 DSbuffer3[76] = DSbuffer3[75];
					 DSbuffer3[75] = DSbuffer3[74];
					 DSbuffer3[74] = DSbuffer3[73];
					 DSbuffer3[73] = DSbuffer3[72];
					 DSbuffer3[72] = DSbuffer3[71];
					 DSbuffer3[71] = DSbuffer3[70];
					 DSbuffer3[70] = DSbuffer3[69];
					 DSbuffer3[69] = DSbuffer3[68];
					 DSbuffer3[68] = DSbuffer3[67];
					 DSbuffer3[67] = DSbuffer3[66];
					 DSbuffer3[66] = DSbuffer3[65];
					 DSbuffer3[65] = DSbuffer3[64];
					 DSbuffer3[64] = DSbuffer3[63];
					 DSbuffer3[63] = DSbuffer3[62];
					 DSbuffer3[62] = DSbuffer3[61];
					 DSbuffer3[61] = DSbuffer3[60];
					 DSbuffer3[60] = DSbuffer3[59];
					 DSbuffer3[59] = DSbuffer3[58];
					 DSbuffer3[58] = DSbuffer3[57];
					 DSbuffer3[57] = DSbuffer3[56];
					 DSbuffer3[56] = DSbuffer3[55];
					 DSbuffer3[55] = DSbuffer3[54];
					 DSbuffer3[54] = DSbuffer3[53];
					 DSbuffer3[53] = DSbuffer3[52];
					 DSbuffer3[52] = DSbuffer3[51];
					 DSbuffer3[51] = DSbuffer3[50];
					 DSbuffer3[50] = DSbuffer3[49];
					 DSbuffer3[49] = DSbuffer3[48];
					 DSbuffer3[48] = DSbuffer3[47];
					 DSbuffer3[47] = DSbuffer3[46];
					 DSbuffer3[46] = DSbuffer3[45];
					 DSbuffer3[45] = DSbuffer3[44];
					 DSbuffer3[44] = DSbuffer3[43];
					 DSbuffer3[43] = DSbuffer3[42];
					 DSbuffer3[42] = DSbuffer3[41];
					 DSbuffer3[41] = DSbuffer3[40];
					 DSbuffer3[40] = DSbuffer3[39];
					 DSbuffer3[39] = DSbuffer3[38];
					 DSbuffer3[38] = DSbuffer3[37];
					 DSbuffer3[37] = DSbuffer3[36];
					 DSbuffer3[36] = DSbuffer3[35];
					 DSbuffer3[35] = DSbuffer3[34];
					 DSbuffer3[34] = DSbuffer3[33];
					 DSbuffer3[33] = DSbuffer3[32];
					 DSbuffer3[32] = DSbuffer3[31];
					 DSbuffer3[31] = DSbuffer3[30];
					 DSbuffer3[30] = DSbuffer3[29];
					 DSbuffer3[29] = DSbuffer3[28];
					 DSbuffer3[28] = DSbuffer3[27];
					 DSbuffer3[27] = DSbuffer3[26];
					 DSbuffer3[26] = DSbuffer3[25];
					 DSbuffer3[25] = DSbuffer3[24];
					 DSbuffer3[24] = DSbuffer3[23];
					 DSbuffer3[23] = DSbuffer3[22];
					 DSbuffer3[22] = DSbuffer3[21];
					 DSbuffer3[21] = DSbuffer3[20];
					 DSbuffer3[20] = DSbuffer3[19];
					 DSbuffer3[19] = DSbuffer3[18];
					 DSbuffer3[18] = DSbuffer3[17];
					 DSbuffer3[17] = DSbuffer3[16];
					 DSbuffer3[16] = DSbuffer3[15];
					 DSbuffer3[15] = DSbuffer3[14];
					 DSbuffer3[14] = DSbuffer3[13];
					 DSbuffer3[13] = DSbuffer3[12];
					 DSbuffer3[12] = DSbuffer3[11];
					 DSbuffer3[11] = DSbuffer3[10];
					 DSbuffer3[10] = DSbuffer3[9];
					 DSbuffer3[9] = DSbuffer3[8];
					 DSbuffer3[8] = DSbuffer3[7];
					 DSbuffer3[7] = DSbuffer3[6];
					 DSbuffer3[6] = DSbuffer3[5];
					 DSbuffer3[5] = DSbuffer3[4];
					 DSbuffer3[4] = DSbuffer3[3];
					 DSbuffer3[3] = DSbuffer3[2];
					 DSbuffer3[2] = DSbuffer3[1];
					 DSbuffer3[1] = DSbuffer3[0];

					DSResult3 >>= 14;
					DSOutput3 = (short)(DSResult3);

					input_ds3[0] = DSOutput3;

			//		ResultCW1_ds3 = (long)input_ds3[0]*b01CW + (long)input_ds3[1]*b11CW + (long)input_ds3[2]*b21CW - (long)OutputCW1_ds3[1]*a11CW - (long)OutputCW1_ds3[2]*a21CW;

					Result1a_ds3 = (long)input_ds3[0]*b01a + (long)input_ds3[1]*b11a + (long)input_ds3[2]*b21a - (long)Output1a_ds3[1]*a11a - (long)Output1a_ds3[2]*a21a + NSe1a_ds3[1];

					Result1b_ds3 = (long)input_ds3[0]*b01b + (long)input_ds3[1]*b11b + (long)input_ds3[2]*b21b - (long)Output1b_ds3[1]*a11b - (long)Output1b_ds3[2]*a21b + NSe1b_ds3[1];

					Result1c_ds3 = (long)input_ds3[0]*b01c + (long)input_ds3[1]*b11c + (long)input_ds3[2]*b21c - (long)Output1c_ds3[1]*a11c - (long)Output1c_ds3[2]*a21c + NSe1c_ds3[1];

					NSe1a_ds3[0] = Result1a_ds3 & 16383;

					NSe1b_ds3[0] = Result1b_ds3 & 16383;

					NSe1c_ds3[0] = Result1c_ds3 & 16383;

		//			OutputCW1_ds3[0] = (short)(ResultCW1_ds3 >> 13);

					Output1a_ds3[0] = (short)(Result1a_ds3 >> 14);

					Output1b_ds3[0] = (short)(Result1b_ds3 >> 14);

					Output1c_ds3[0] = (short)(Result1c_ds3 >> 14);

		//			inputCW2_ds3[0] = OutputCW1_ds3[0];

					input2a_ds3[0] = Output1a_ds3[0];

					input2b_ds3[0] = Output1b_ds3[0];

					input2c_ds3[0] = Output1c_ds3[0];

		//			ResultCW2_ds3 = (long)inputCW2_ds3[0]*b02CW + (long)inputCW2_ds3[1]*b12CW + (long)inputCW2_ds3[2]*b22CW - (long)OutputCW2_ds3[1]*a12CW - (long)OutputCW2_ds3[2]*a22CW;

					Result2a_ds3 = (long)input2a_ds3[0]*b02a + (long)input2a_ds3[1]*b12a + (long)input2a_ds3[2]*b22a - (long)Output2a_ds3[1]*a12a - (long)Output2a_ds3[2]*a22a + NSe2a_ds3[1];

					Result2b_ds3 = (long)input2b_ds3[0]*b02b + (long)input2b_ds3[1]*b12b + (long)input2b_ds3[2]*b22b - (long)Output2b_ds3[1]*a12b - (long)Output2b_ds3[2]*a22b + NSe2b_ds3[1];

					Result2c_ds3 = (long)input2c_ds3[0]*b02c + (long)input2c_ds3[1]*b12c + (long)input2c_ds3[2]*b22c - (long)Output2c_ds3[1]*a12c - (long)Output2c_ds3[2]*a22c + NSe2c_ds3[1];

					NSe2a_ds3[0] = Result2a_ds3 & 16383;

					NSe2b_ds3[0] = Result2b_ds3 & 16383;

					NSe2c_ds3[0] = Result2c_ds3 & 16383;

		//			OutputCW2_ds3[0] = (short)(ResultCW2_ds3 >> 13);

					Output2a_ds3[0] = (short)(Result2a_ds3 >> 14);

					Output2b_ds3[0] = (short)(Result2b_ds3 >> 14);

					Output2c_ds3[0] = (short)(Result2c_ds3 >> 14);

					input3a_ds3[0] = Output2a_ds3[0];

					input3b_ds3[0] = Output2b_ds3[0];

					input3c_ds3[0] = Output2c_ds3[0];

					Result3a_ds3 = (long)input3a_ds3[0]*b03a + (long)input3a_ds3[1]*b13a + (long)input3a_ds3[2]*b23a - (long)Output3a_ds3[1]*a13a - (long)Output3a_ds3[2]*a23a + NSe3a_ds3[1];

					Result3b_ds3 = (long)input3b_ds3[0]*b03b + (long)input3b_ds3[1]*b13b + (long)input3b_ds3[2]*b23b - (long)Output3b_ds3[1]*a13b - (long)Output3b_ds3[2]*a23b + NSe3b_ds3[1];

					Result3c_ds3 = (long)input3c_ds3[0]*b03c + (long)input3c_ds3[1]*b13c + (long)input3c_ds3[2]*b23c - (long)Output3c_ds3[1]*a13c - (long)Output3c_ds3[2]*a23c + NSe3c_ds3[1];

					NSe3a_ds3[0] = Result3a_ds3 & 16383;

					NSe3b_ds3[0] = Result3b_ds3 & 16383;

					NSe3c_ds3[0] = Result3c_ds3 & 16383;

					Output3a_ds3[0] = (short)(Result3a_ds3 >> 14);

					Output3b_ds3[0] = (short)(Result3b_ds3 >> 14);

					Output3c_ds3[0] = (short)(Result3c_ds3 >> 14);

					NSe1a_ds3[1] = NSe1a_ds3[0];
					NSe2a_ds3[1] = NSe2a_ds3[0];
					NSe3a_ds3[1] = NSe3a_ds3[0];

					NSe1b_ds3[1] = NSe1b_ds3[0];
					NSe2b_ds3[1] = NSe2b_ds3[0];
					NSe3b_ds3[1] = NSe3b_ds3[0];

					NSe1c_ds3[1] = NSe1c_ds3[0];
					NSe2c_ds3[1] = NSe2c_ds3[0];
					NSe3c_ds3[1] = NSe3c_ds3[0];

					input_ds3[2] = input_ds3[1];
					input_ds3[1] = input_ds3[0];

		//			inputCW2_ds3[2] = inputCW2_ds3[1];
		//			inputCW2_ds3[1] = inputCW2_ds3[0];

					input2a_ds3[2] = input2a_ds3[1];
					input3a_ds3[2] = input3a_ds3[1];

					input2b_ds3[2] = input2b_ds3[1];
					input3b_ds3[2] = input3b_ds3[1];

					input2c_ds3[2] = input2c_ds3[1];
					input3c_ds3[2] = input3c_ds3[1];

					input2a_ds3[1] = input2a_ds3[0];
					input3a_ds3[1] = input3a_ds3[0];

					input2b_ds3[1] = input2b_ds3[0];
					input3b_ds3[1] = input3b_ds3[0];

					input2c_ds3[1] = input2c_ds3[0];
					input3c_ds3[1] = input3c_ds3[0];

		//			OutputCW1_ds3[2] = OutputCW1_ds3[1];
		//			OutputCW1_ds3[1] = OutputCW1_ds3[0];
		//			OutputCW2_ds3[2] = OutputCW2_ds3[1];
		//			OutputCW2_ds3[1] = OutputCW2_ds3[0];

					Output1a_ds3[2] = Output1a_ds3[1];
					Output2a_ds3[2] = Output2a_ds3[1];
					Output3a_ds3[2] = Output3a_ds3[1];

					Output1b_ds3[2] = Output1b_ds3[1];
					Output2b_ds3[2] = Output2b_ds3[1];
					Output3b_ds3[2] = Output3b_ds3[1];

					Output1c_ds3[2] = Output1c_ds3[1];
					Output2c_ds3[2] = Output2c_ds3[1];
					Output3c_ds3[2] = Output3c_ds3[1];

					Output1a_ds3[1] = Output1a_ds3[0];
					Output2a_ds3[1] = Output2a_ds3[0];
					Output3a_ds3[1] = Output3a_ds3[0];

					Output1b_ds3[1] = Output1b_ds3[0];
					Output2b_ds3[1] = Output2b_ds3[0];
					Output3b_ds3[1] = Output3b_ds3[0];

					Output1c_ds3[1] = Output1c_ds3[0];
					Output2c_ds3[1] = Output2c_ds3[0];
					Output3c_ds3[1] = Output3c_ds3[0];

					if(RMScount3 < 256){

							tempRMS_band19 += (long)Output3a_ds3[1] * Output3a_ds3[1]  >>  14;
							tempRMS_band20 += (long)Output3b_ds3[1] * Output3b_ds3[1]  >>  14;
							tempRMS_band21 += (long)Output3c_ds3[1] * Output3c_ds3[1]  >>  14;

							RMScount3++;

					}
					else if(RMScount3 >= 256){

						tempRMS_band19 /= 4;
						tempRMS_band20 /= 4;
						tempRMS_band21 /= 4;

						// OUTPUT HER
						if(tempRMS_band19 >= dB_table[old_dB19+1]){
							old_dB19++;
							if(old_dB19 > 36){
								old_dB19 = 36;
							}

						}
						else if(tempRMS_band19 <= dB_table[old_dB19-1]){
							old_dB19--;
							if(old_dB19 < 0){
								old_dB19 = 0;
							}
						}


						if(tempRMS_band20 >= dB_table[old_dB20+1]){
							old_dB20++;
							if(old_dB20 > 36){
								old_dB20 = 36;
							}
						}
						else if(tempRMS_band20 <= dB_table[old_dB20-1]){
							old_dB20--;
							if(old_dB20 < 0){
								old_dB20 = 0;
							}
						}

						if(tempRMS_band21 >= dB_table[old_dB21+1]){
							old_dB21++;
							if(old_dB21 > 36){
								old_dB21 = 36;
							}
						}
						else if(tempRMS_band21 <= dB_table[old_dB21-1]){
							old_dB21--;
							if(old_dB21 < 0){
								old_dB21 = 0;
							}
						}




						tempRMS_band19 = 0;
						tempRMS_band20 = 0;
						tempRMS_band21 = 0;
						RMScount3 = 0;
					}
	    			}
	            	if(DS_table[samplecount] == 544){  // M = 16



	            		DSbuffer4[0] = l_buffer[0];
					DSResult4 = (long)DSbuffer4[0] * filter_taps[0] + (long)DSbuffer4[1] * filter_taps[1] + (long)DSbuffer4[2] * filter_taps[2] + (long)DSbuffer4[3] * filter_taps[3] + (long)DSbuffer4[4] * filter_taps[4] + (long)DSbuffer4[5] * filter_taps[5] + (long)DSbuffer4[6] * filter_taps[6] + (long)DSbuffer4[7] * filter_taps[7] + (long)DSbuffer4[8] * filter_taps[8] + (long)DSbuffer4[9] * filter_taps[9] +
							  (long)DSbuffer4[10] * filter_taps[10] + (long)DSbuffer4[11] * filter_taps[11] + (long)DSbuffer4[12] * filter_taps[12] + (long)DSbuffer4[13] * filter_taps[13] + (long)DSbuffer4[14] * filter_taps[14] + (long)DSbuffer4[15] * filter_taps[15] + (long)DSbuffer4[16] * filter_taps[16] + (long)DSbuffer4[17] * filter_taps[17] + (long)DSbuffer4[18] * filter_taps[18] + (long)DSbuffer4[19] * filter_taps[19] +
							  (long)DSbuffer4[20] * filter_taps[20] + (long)DSbuffer4[21] * filter_taps[21] + (long)DSbuffer4[22] * filter_taps[22] + (long)DSbuffer4[23] * filter_taps[23] + (long)DSbuffer4[24] * filter_taps[24] + (long)DSbuffer4[25] * filter_taps[25] + (long)DSbuffer4[26] * filter_taps[26] + (long)DSbuffer4[27] * filter_taps[27] + (long)DSbuffer4[28] * filter_taps[28] + (long)DSbuffer4[29] * filter_taps[29] +
							  (long)DSbuffer4[30] * filter_taps[30] + (long)DSbuffer4[31] * filter_taps[31] + (long)DSbuffer4[32] * filter_taps[32] + (long)DSbuffer4[33] * filter_taps[33] + (long)DSbuffer4[34] * filter_taps[34] + (long)DSbuffer4[35] * filter_taps[35] + (long)DSbuffer4[36] * filter_taps[36] + (long)DSbuffer4[37] * filter_taps[37] + (long)DSbuffer4[38] * filter_taps[38] + (long)DSbuffer4[39] * filter_taps[39] +
							  (long)DSbuffer4[40] * filter_taps[40] + (long)DSbuffer4[41] * filter_taps[41] + (long)DSbuffer4[42] * filter_taps[42] + (long)DSbuffer4[43] * filter_taps[43] + (long)DSbuffer4[44] * filter_taps[44] + (long)DSbuffer4[45] * filter_taps[45] + (long)DSbuffer4[46] * filter_taps[46] + (long)DSbuffer4[47] * filter_taps[47] + (long)DSbuffer4[48] * filter_taps[48] + (long)DSbuffer4[49] * filter_taps[49] +
							  (long)DSbuffer4[50] * filter_taps[50] + (long)DSbuffer4[51] * filter_taps[51] + (long)DSbuffer4[52] * filter_taps[52] + (long)DSbuffer4[53] * filter_taps[53] + (long)DSbuffer4[54] * filter_taps[54] + (long)DSbuffer4[55] * filter_taps[55] + (long)DSbuffer4[56] * filter_taps[56] + (long)DSbuffer4[57] * filter_taps[57] + (long)DSbuffer4[58] * filter_taps[58] + (long)DSbuffer4[59] * filter_taps[59] +
							  (long)DSbuffer4[60] * filter_taps[60] + (long)DSbuffer4[61] * filter_taps[61] + (long)DSbuffer4[62] * filter_taps[62] + (long)DSbuffer4[63] * filter_taps[63] + (long)DSbuffer4[64] * filter_taps[64] + (long)DSbuffer4[65] * filter_taps[65] + (long)DSbuffer4[66] * filter_taps[66] + (long)DSbuffer4[67] * filter_taps[67] + (long)DSbuffer4[68] * filter_taps[68] + (long)DSbuffer4[69] * filter_taps[69] +
							  (long)DSbuffer4[70] * filter_taps[70] + (long)DSbuffer4[71] * filter_taps[71] + (long)DSbuffer4[72] * filter_taps[72] + (long)DSbuffer4[73] * filter_taps[73] + (long)DSbuffer4[74] * filter_taps[74] + (long)DSbuffer4[75] * filter_taps[75] + (long)DSbuffer4[76] * filter_taps[76] + (long)DSbuffer4[77] * filter_taps[77] + (long)DSbuffer4[78] * filter_taps[78] + (long)DSbuffer4[79] * filter_taps[79] +
							  (long)DSbuffer4[80] * filter_taps[80] + (long)DSbuffer4[81] * filter_taps[81] + (long)DSbuffer4[82] * filter_taps[82] + (long)DSbuffer4[83] * filter_taps[83] + (long)DSbuffer4[84] * filter_taps[84] + (long)DSbuffer4[85] * filter_taps[85] + (long)DSbuffer4[86] * filter_taps[86] + (long)DSbuffer4[87] * filter_taps[87] + (long)DSbuffer4[88] * filter_taps[88] + (long)DSbuffer4[89] * filter_taps[89] +
							  (long)DSbuffer4[90] * filter_taps[90] + (long)DSbuffer4[91] * filter_taps[91] + (long)DSbuffer4[92] * filter_taps[92] + (long)DSbuffer4[93] * filter_taps[93] + (long)DSbuffer4[94] * filter_taps[94] + (long)DSbuffer4[95] * filter_taps[95];


					 DSbuffer4[95] = DSbuffer4[94];
					 DSbuffer4[94] = DSbuffer4[93];
					 DSbuffer4[93] = DSbuffer4[92];
					 DSbuffer4[92] = DSbuffer4[91];
					 DSbuffer4[91] = DSbuffer4[90];
					 DSbuffer4[90] = DSbuffer4[89];
					 DSbuffer4[89] = DSbuffer4[88];
					 DSbuffer4[88] = DSbuffer4[87];
					 DSbuffer4[87] = DSbuffer4[86];
					 DSbuffer4[86] = DSbuffer4[85];
					 DSbuffer4[85] = DSbuffer4[84];
					 DSbuffer4[84] = DSbuffer4[83];
					 DSbuffer4[83] = DSbuffer4[82];
					 DSbuffer4[82] = DSbuffer4[81];
					 DSbuffer4[81] = DSbuffer4[80];
					 DSbuffer4[80] = DSbuffer4[79];
					 DSbuffer4[79] = DSbuffer4[78];
					 DSbuffer4[78] = DSbuffer4[77];
					 DSbuffer4[77] = DSbuffer4[76];
					 DSbuffer4[76] = DSbuffer4[75];
					 DSbuffer4[75] = DSbuffer4[74];
					 DSbuffer4[74] = DSbuffer4[73];
					 DSbuffer4[73] = DSbuffer4[72];
					 DSbuffer4[72] = DSbuffer4[71];
					 DSbuffer4[71] = DSbuffer4[70];
					 DSbuffer4[70] = DSbuffer4[69];
					 DSbuffer4[69] = DSbuffer4[68];
					 DSbuffer4[68] = DSbuffer4[67];
					 DSbuffer4[67] = DSbuffer4[66];
					 DSbuffer4[66] = DSbuffer4[65];
					 DSbuffer4[65] = DSbuffer4[64];
					 DSbuffer4[64] = DSbuffer4[63];
					 DSbuffer4[63] = DSbuffer4[62];
					 DSbuffer4[62] = DSbuffer4[61];
					 DSbuffer4[61] = DSbuffer4[60];
					 DSbuffer4[60] = DSbuffer4[59];
					 DSbuffer4[59] = DSbuffer4[58];
					 DSbuffer4[58] = DSbuffer4[57];
					 DSbuffer4[57] = DSbuffer4[56];
					 DSbuffer4[56] = DSbuffer4[55];
					 DSbuffer4[55] = DSbuffer4[54];
					 DSbuffer4[54] = DSbuffer4[53];
					 DSbuffer4[53] = DSbuffer4[52];
					 DSbuffer4[52] = DSbuffer4[51];
					 DSbuffer4[51] = DSbuffer4[50];
					 DSbuffer4[50] = DSbuffer4[49];
					 DSbuffer4[49] = DSbuffer4[48];
					 DSbuffer4[48] = DSbuffer4[47];
					 DSbuffer4[47] = DSbuffer4[46];
					 DSbuffer4[46] = DSbuffer4[45];
					 DSbuffer4[45] = DSbuffer4[44];
					 DSbuffer4[44] = DSbuffer4[43];
					 DSbuffer4[43] = DSbuffer4[42];
					 DSbuffer4[42] = DSbuffer4[41];
					 DSbuffer4[41] = DSbuffer4[40];
					 DSbuffer4[40] = DSbuffer4[39];
					 DSbuffer4[39] = DSbuffer4[38];
					 DSbuffer4[38] = DSbuffer4[37];
					 DSbuffer4[37] = DSbuffer4[36];
					 DSbuffer4[36] = DSbuffer4[35];
					 DSbuffer4[35] = DSbuffer4[34];
					 DSbuffer4[34] = DSbuffer4[33];
					 DSbuffer4[33] = DSbuffer4[32];
					 DSbuffer4[32] = DSbuffer4[31];
					 DSbuffer4[31] = DSbuffer4[30];
					 DSbuffer4[30] = DSbuffer4[29];
					 DSbuffer4[29] = DSbuffer4[28];
					 DSbuffer4[28] = DSbuffer4[27];
					 DSbuffer4[27] = DSbuffer4[26];
					 DSbuffer4[26] = DSbuffer4[25];
					 DSbuffer4[25] = DSbuffer4[24];
					 DSbuffer4[24] = DSbuffer4[23];
					 DSbuffer4[23] = DSbuffer4[22];
					 DSbuffer4[22] = DSbuffer4[21];
					 DSbuffer4[21] = DSbuffer4[20];
					 DSbuffer4[20] = DSbuffer4[19];
					 DSbuffer4[19] = DSbuffer4[18];
					 DSbuffer4[18] = DSbuffer4[17];
					 DSbuffer4[17] = DSbuffer4[16];
					 DSbuffer4[16] = DSbuffer4[15];
					 DSbuffer4[15] = DSbuffer4[14];
					 DSbuffer4[14] = DSbuffer4[13];
					 DSbuffer4[13] = DSbuffer4[12];
					 DSbuffer4[12] = DSbuffer4[11];
					 DSbuffer4[11] = DSbuffer4[10];
					 DSbuffer4[10] = DSbuffer4[9];
					 DSbuffer4[9] = DSbuffer4[8];
					 DSbuffer4[8] = DSbuffer4[7];
					 DSbuffer4[7] = DSbuffer4[6];
					 DSbuffer4[6] = DSbuffer4[5];
					 DSbuffer4[5] = DSbuffer4[4];
					 DSbuffer4[4] = DSbuffer4[3];
					 DSbuffer4[3] = DSbuffer4[2];
					 DSbuffer4[2] = DSbuffer4[1];
					 DSbuffer4[1] = DSbuffer4[0];

					DSResult4 >>= 16;

					DSOutput4 = (short)(DSResult4);

					input_ds4[0] = DSOutput4;

			//		ResultCW1_ds4 = (long)input_ds4[0]*b01CW + (long)input_ds4[1]*b11CW + (long)input_ds4[2]*b21CW - (long)OutputCW1_ds4[1]*a11CW - (long)OutputCW1_ds4[2]*a21CW;

					Result1a_ds4 = (long)input_ds4[0]*b01a + (long)input_ds4[1]*b11a + (long)input_ds4[2]*b21a - (long)Output1a_ds4[1]*a11a - (long)Output1a_ds4[2]*a21a + NSe1a_ds4[1];

					Result1b_ds4 = (long)input_ds4[0]*b01b + (long)input_ds4[1]*b11b + (long)input_ds4[2]*b21b - (long)Output1b_ds4[1]*a11b - (long)Output1b_ds4[2]*a21b + NSe1b_ds4[1];

					Result1c_ds4 = (long)input_ds4[0]*b01c + (long)input_ds4[1]*b11c + (long)input_ds4[2]*b21c - (long)Output1c_ds4[1]*a11c - (long)Output1c_ds4[2]*a21c + NSe1c_ds4[1];

					NSe1a_ds4[0] = Result1a_ds4 & 16383;

					NSe1b_ds4[0] = Result1b_ds4 & 16383;

					NSe1c_ds4[0] = Result1c_ds4 & 16383;

			//		OutputCW1_ds4[0] = (short)(ResultCW1_ds4 >> 13);

					Output1a_ds4[0] = (short)(Result1a_ds4 >> 14);

					Output1b_ds4[0] = (short)(Result1b_ds4 >> 14);

					Output1c_ds4[0] = (short)(Result1c_ds4 >> 14);

			//		inputCW2_ds4[0] = OutputCW1_ds4[0];

					input2a_ds4[0] = Output1a_ds4[0];

					input2b_ds4[0] = Output1b_ds4[0];

					input2c_ds4[0] = Output1c_ds4[0];

			//		ResultCW2_ds4 = (long)inputCW2_ds4[0]*b02CW + (long)inputCW2_ds4[1]*b12CW + (long)inputCW2_ds4[2]*b22CW - (long)OutputCW2_ds4[1]*a12CW - (long)OutputCW2_ds4[2]*a22CW;

					Result2a_ds4 = (long)input2a_ds4[0]*b02a + (long)input2a_ds4[1]*b12a + (long)input2a_ds4[2]*b22a - (long)Output2a_ds4[1]*a12a - (long)Output2a_ds4[2]*a22a + NSe2a_ds4[1];

					Result2b_ds4 = (long)input2b_ds4[0]*b02b + (long)input2b_ds4[1]*b12b + (long)input2b_ds4[2]*b22b - (long)Output2b_ds4[1]*a12b - (long)Output2b_ds4[2]*a22b + NSe2b_ds4[1];

					Result2c_ds4 = (long)input2c_ds4[0]*b02c + (long)input2c_ds4[1]*b12c + (long)input2c_ds4[2]*b22c - (long)Output2c_ds4[1]*a12c - (long)Output2c_ds4[2]*a22c + NSe2c_ds4[1];

					NSe2a_ds4[0] = Result2a_ds4 & 16383;

					NSe2b_ds4[0] = Result2b_ds4 & 16383;

					NSe2c_ds4[0] = Result2c_ds4 & 16383;

			//		OutputCW2_ds4[0] = (short)(ResultCW2_ds4 >> 13);

					Output2a_ds4[0] = (short)(Result2a_ds4 >> 14);

					Output2b_ds4[0] = (short)(Result2b_ds4 >> 14);

					Output2c_ds4[0] = (short)(Result2c_ds4 >> 14);

					input3a_ds4[0] = Output2a_ds4[0];

					input3b_ds4[0] = Output2b_ds4[0];

					input3c_ds4[0] = Output2c_ds4[0];

					Result3a_ds4 = (long)input3a_ds4[0]*b03a + (long)input3a_ds4[1]*b13a + (long)input3a_ds4[2]*b23a - (long)Output3a_ds4[1]*a13a - (long)Output3a_ds4[2]*a23a + NSe3a_ds4[1];

					Result3b_ds4 = (long)input3b_ds4[0]*b03b + (long)input3b_ds4[1]*b13b + (long)input3b_ds4[2]*b23b - (long)Output3b_ds4[1]*a13b - (long)Output3b_ds4[2]*a23b + NSe3b_ds4[1];

					Result3c_ds4 = (long)input3c_ds4[0]*b03c + (long)input3c_ds4[1]*b13c + (long)input3c_ds4[2]*b23c - (long)Output3c_ds4[1]*a13c - (long)Output3c_ds4[2]*a23c + NSe3c_ds4[1];

					NSe3a_ds4[0] = Result3a_ds4 & 16383;

					NSe3b_ds4[0] = Result3b_ds4 & 16383;

					NSe3c_ds4[0] = Result3c_ds4 & 16383;

					Output3a_ds4[0] = (short)(Result3a_ds4 >> 14);

					Output3b_ds4[0] = (short)(Result3b_ds4 >> 14);

					Output3c_ds4[0] = (short)(Result3c_ds4 >> 14);

					NSe1a_ds4[1] = NSe1a_ds4[0];
					NSe2a_ds4[1] = NSe2a_ds4[0];
					NSe3a_ds4[1] = NSe3a_ds4[0];

					NSe1b_ds4[1] = NSe1b_ds4[0];
					NSe2b_ds4[1] = NSe2b_ds4[0];
					NSe3b_ds4[1] = NSe3b_ds4[0];

					NSe1c_ds4[1] = NSe1c_ds4[0];
					NSe2c_ds4[1] = NSe2c_ds4[0];
					NSe3c_ds4[1] = NSe3c_ds4[0];

					input_ds4[2] = input_ds4[1];
					input_ds4[1] = input_ds4[0];

			//		inputCW2_ds4[2] = inputCW2_ds4[1];
			//		inputCW2_ds4[1] = inputCW2_ds4[0];

					input2a_ds4[2] = input2a_ds4[1];
					input3a_ds4[2] = input3a_ds4[1];

					input2b_ds4[2] = input2b_ds4[1];
					input3b_ds4[2] = input3b_ds4[1];

					input2c_ds4[2] = input2c_ds4[1];
					input3c_ds4[2] = input3c_ds4[1];

					input2a_ds4[1] = input2a_ds4[0];
					input3a_ds4[1] = input3a_ds4[0];

					input2b_ds4[1] = input2b_ds4[0];
					input3b_ds4[1] = input3b_ds4[0];

					input2c_ds4[1] = input2c_ds4[0];
					input3c_ds4[1] = input3c_ds4[0];

			//		OutputCW1_ds4[2] = OutputCW1_ds4[1];
			//		OutputCW1_ds4[1] = OutputCW1_ds4[0];
			//		OutputCW2_ds4[2] = OutputCW2_ds4[1];
			//		OutputCW2_ds4[1] = OutputCW2_ds4[0];

					Output1a_ds4[2] = Output1a_ds4[1];
					Output2a_ds4[2] = Output2a_ds4[1];
					Output3a_ds4[2] = Output3a_ds4[1];

					Output1b_ds4[2] = Output1b_ds4[1];
					Output2b_ds4[2] = Output2b_ds4[1];
					Output3b_ds4[2] = Output3b_ds4[1];

					Output1c_ds4[2] = Output1c_ds4[1];
					Output2c_ds4[2] = Output2c_ds4[1];
					Output3c_ds4[2] = Output3c_ds4[1];

					Output1a_ds4[1] = Output1a_ds4[0];
					Output2a_ds4[1] = Output2a_ds4[0];
					Output3a_ds4[1] = Output3a_ds4[0];

					Output1b_ds4[1] = Output1b_ds4[0];
					Output2b_ds4[1] = Output2b_ds4[0];
					Output3b_ds4[1] = Output3b_ds4[0];

					Output1c_ds4[1] = Output1c_ds4[0];
					Output2c_ds4[1] = Output2c_ds4[0];
					Output3c_ds4[1] = Output3c_ds4[0];
					// M=0 OUTPUT ASSIGNMENTS


					if(RMScount4 < 256){

						tempRMS_band16 += (long)Output3a_ds4[1] * Output3a_ds4[1]  >>  14;
						tempRMS_band17 += (long)Output3b_ds4[1] * Output3b_ds4[1]  >>  14;
						tempRMS_band18 += (long)Output3c_ds4[1] * Output3c_ds4[1]  >>  14;

						RMScount4++;

					}
					else if(RMScount4 >= 256){

						tempRMS_band16 /= 4;
						tempRMS_band17 /= 4;
						tempRMS_band18 /= 4;

						// OUTPUT HER


						if(tempRMS_band16 >= dB_table[old_dB16+1]){
							old_dB16++;
							if(old_dB16 > 36){
								old_dB16 = 36;
							}
						}
						else if(tempRMS_band16 <= dB_table[old_dB16-1]){
							old_dB16--;
							if(old_dB16 < 0){
								old_dB16 = 0;
							}
						}

						if(tempRMS_band17 >= dB_table[old_dB17+1]){
							old_dB17++;
							if(old_dB17 > 36){
								old_dB17 = 36;
							}
						}
						else if(tempRMS_band17 <= dB_table[old_dB17-1]){
							old_dB17--;
							if(old_dB17 < 0){
								old_dB17 = 0;
							}
						}

						if(tempRMS_band18 >= dB_table[old_dB18+1]){
							old_dB18++;
							if(old_dB18 > 36){
								old_dB18 = 36;
							}
						}
						else if(tempRMS_band18 <= dB_table[old_dB18-1]){
							old_dB18--;
							if(old_dB18 < 0){
								old_dB18 = 0;
							}
						}

						tempRMS_band16 = 0;
						tempRMS_band17 = 0;
						tempRMS_band18 = 0;
						RMScount4 = 0;
					}



					}
	            	if(DS_table[samplecount] == 528){  // M = 32


	            		DSbuffer5[0] = l_buffer[0];
	            		DSResult5 = (long)DSbuffer5[0] * filter_taps[0] + (long)DSbuffer5[1] * filter_taps[1] + (long)DSbuffer5[2] * filter_taps[2] + (long)DSbuffer5[3] * filter_taps[3] + (long)DSbuffer5[4] * filter_taps[4] + (long)DSbuffer5[5] * filter_taps[5] + (long)DSbuffer5[6] * filter_taps[6] + (long)DSbuffer5[7] * filter_taps[7] + (long)DSbuffer5[8] * filter_taps[8] + (long)DSbuffer5[9] * filter_taps[9] +
							  (long)DSbuffer5[10] * filter_taps[10] + (long)DSbuffer5[11] * filter_taps[11] + (long)DSbuffer5[12] * filter_taps[12] + (long)DSbuffer5[13] * filter_taps[13] + (long)DSbuffer5[14] * filter_taps[14] + (long)DSbuffer5[15] * filter_taps[15] + (long)DSbuffer5[16] * filter_taps[16] + (long)DSbuffer5[17] * filter_taps[17] + (long)DSbuffer5[18] * filter_taps[18] + (long)DSbuffer5[19] * filter_taps[19] +
							  (long)DSbuffer5[20] * filter_taps[20] + (long)DSbuffer5[21] * filter_taps[21] + (long)DSbuffer5[22] * filter_taps[22] + (long)DSbuffer5[23] * filter_taps[23] + (long)DSbuffer5[24] * filter_taps[24] + (long)DSbuffer5[25] * filter_taps[25] + (long)DSbuffer5[26] * filter_taps[26] + (long)DSbuffer5[27] * filter_taps[27] + (long)DSbuffer5[28] * filter_taps[28] + (long)DSbuffer5[29] * filter_taps[29] +
							  (long)DSbuffer5[30] * filter_taps[30] + (long)DSbuffer5[31] * filter_taps[31] + (long)DSbuffer5[32] * filter_taps[32] + (long)DSbuffer5[33] * filter_taps[33] + (long)DSbuffer5[34] * filter_taps[34] + (long)DSbuffer5[35] * filter_taps[35] + (long)DSbuffer5[36] * filter_taps[36] + (long)DSbuffer5[37] * filter_taps[37] + (long)DSbuffer5[38] * filter_taps[38] + (long)DSbuffer5[39] * filter_taps[39] +
							  (long)DSbuffer5[40] * filter_taps[40] + (long)DSbuffer5[41] * filter_taps[41] + (long)DSbuffer5[42] * filter_taps[42] + (long)DSbuffer5[43] * filter_taps[43] + (long)DSbuffer5[44] * filter_taps[44] + (long)DSbuffer5[45] * filter_taps[45] + (long)DSbuffer5[46] * filter_taps[46] + (long)DSbuffer5[47] * filter_taps[47] + (long)DSbuffer5[48] * filter_taps[48] + (long)DSbuffer5[49] * filter_taps[49] +
							  (long)DSbuffer5[50] * filter_taps[50] + (long)DSbuffer5[51] * filter_taps[51] + (long)DSbuffer5[52] * filter_taps[52] + (long)DSbuffer5[53] * filter_taps[53] + (long)DSbuffer5[54] * filter_taps[54] + (long)DSbuffer5[55] * filter_taps[55] + (long)DSbuffer5[56] * filter_taps[56] + (long)DSbuffer5[57] * filter_taps[57] + (long)DSbuffer5[58] * filter_taps[58] + (long)DSbuffer5[59] * filter_taps[59] +
							  (long)DSbuffer5[60] * filter_taps[60] + (long)DSbuffer5[61] * filter_taps[61] + (long)DSbuffer5[62] * filter_taps[62] + (long)DSbuffer5[63] * filter_taps[63] + (long)DSbuffer5[64] * filter_taps[64] + (long)DSbuffer5[65] * filter_taps[65] + (long)DSbuffer5[66] * filter_taps[66] + (long)DSbuffer5[67] * filter_taps[67] + (long)DSbuffer5[68] * filter_taps[68] + (long)DSbuffer5[69] * filter_taps[69] +
							  (long)DSbuffer5[70] * filter_taps[70] + (long)DSbuffer5[71] * filter_taps[71] + (long)DSbuffer5[72] * filter_taps[72] + (long)DSbuffer5[73] * filter_taps[73] + (long)DSbuffer5[74] * filter_taps[74] + (long)DSbuffer5[75] * filter_taps[75] + (long)DSbuffer5[76] * filter_taps[76] + (long)DSbuffer5[77] * filter_taps[77] + (long)DSbuffer5[78] * filter_taps[78] + (long)DSbuffer5[79] * filter_taps[79] +
							  (long)DSbuffer5[80] * filter_taps[80] + (long)DSbuffer5[81] * filter_taps[81] + (long)DSbuffer5[82] * filter_taps[82] + (long)DSbuffer5[83] * filter_taps[83] + (long)DSbuffer5[84] * filter_taps[84] + (long)DSbuffer5[85] * filter_taps[85] + (long)DSbuffer5[86] * filter_taps[86] + (long)DSbuffer5[87] * filter_taps[87] + (long)DSbuffer5[88] * filter_taps[88] + (long)DSbuffer5[89] * filter_taps[89] +
							  (long)DSbuffer5[90] * filter_taps[90] + (long)DSbuffer5[91] * filter_taps[91] + (long)DSbuffer5[92] * filter_taps[92] + (long)DSbuffer5[93] * filter_taps[93] + (long)DSbuffer5[94] * filter_taps[94] + (long)DSbuffer5[95] * filter_taps[95];


					 DSbuffer5[95] = DSbuffer5[94];
					 DSbuffer5[94] = DSbuffer5[93];
					 DSbuffer5[93] = DSbuffer5[92];
					 DSbuffer5[92] = DSbuffer5[91];
					 DSbuffer5[91] = DSbuffer5[90];
					 DSbuffer5[90] = DSbuffer5[89];
					 DSbuffer5[89] = DSbuffer5[88];
					 DSbuffer5[88] = DSbuffer5[87];
					 DSbuffer5[87] = DSbuffer5[86];
					 DSbuffer5[86] = DSbuffer5[85];
					 DSbuffer5[85] = DSbuffer5[84];
					 DSbuffer5[84] = DSbuffer5[83];
					 DSbuffer5[83] = DSbuffer5[82];
					 DSbuffer5[82] = DSbuffer5[81];
					 DSbuffer5[81] = DSbuffer5[80];
					 DSbuffer5[80] = DSbuffer5[79];
					 DSbuffer5[79] = DSbuffer5[78];
					 DSbuffer5[78] = DSbuffer5[77];
					 DSbuffer5[77] = DSbuffer5[76];
					 DSbuffer5[76] = DSbuffer5[75];
					 DSbuffer5[75] = DSbuffer5[74];
					 DSbuffer5[74] = DSbuffer5[73];
					 DSbuffer5[73] = DSbuffer5[72];
					 DSbuffer5[72] = DSbuffer5[71];
					 DSbuffer5[71] = DSbuffer5[70];
					 DSbuffer5[70] = DSbuffer5[69];
					 DSbuffer5[69] = DSbuffer5[68];
					 DSbuffer5[68] = DSbuffer5[67];
					 DSbuffer5[67] = DSbuffer5[66];
					 DSbuffer5[66] = DSbuffer5[65];
					 DSbuffer5[65] = DSbuffer5[64];
					 DSbuffer5[64] = DSbuffer5[63];
					 DSbuffer5[63] = DSbuffer5[62];
					 DSbuffer5[62] = DSbuffer5[61];
					 DSbuffer5[61] = DSbuffer5[60];
					 DSbuffer5[60] = DSbuffer5[59];
					 DSbuffer5[59] = DSbuffer5[58];
					 DSbuffer5[58] = DSbuffer5[57];
					 DSbuffer5[57] = DSbuffer5[56];
					 DSbuffer5[56] = DSbuffer5[55];
					 DSbuffer5[55] = DSbuffer5[54];
					 DSbuffer5[54] = DSbuffer5[53];
					 DSbuffer5[53] = DSbuffer5[52];
					 DSbuffer5[52] = DSbuffer5[51];
					 DSbuffer5[51] = DSbuffer5[50];
					 DSbuffer5[50] = DSbuffer5[49];
					 DSbuffer5[49] = DSbuffer5[48];
					 DSbuffer5[48] = DSbuffer5[47];
					 DSbuffer5[47] = DSbuffer5[46];
					 DSbuffer5[46] = DSbuffer5[45];
					 DSbuffer5[45] = DSbuffer5[44];
					 DSbuffer5[44] = DSbuffer5[43];
					 DSbuffer5[43] = DSbuffer5[42];
					 DSbuffer5[42] = DSbuffer5[41];
					 DSbuffer5[41] = DSbuffer5[40];
					 DSbuffer5[40] = DSbuffer5[39];
					 DSbuffer5[39] = DSbuffer5[38];
					 DSbuffer5[38] = DSbuffer5[37];
					 DSbuffer5[37] = DSbuffer5[36];
					 DSbuffer5[36] = DSbuffer5[35];
					 DSbuffer5[35] = DSbuffer5[34];
					 DSbuffer5[34] = DSbuffer5[33];
					 DSbuffer5[33] = DSbuffer5[32];
					 DSbuffer5[32] = DSbuffer5[31];
					 DSbuffer5[31] = DSbuffer5[30];
					 DSbuffer5[30] = DSbuffer5[29];
					 DSbuffer5[29] = DSbuffer5[28];
					 DSbuffer5[28] = DSbuffer5[27];
					 DSbuffer5[27] = DSbuffer5[26];
					 DSbuffer5[26] = DSbuffer5[25];
					 DSbuffer5[25] = DSbuffer5[24];
					 DSbuffer5[24] = DSbuffer5[23];
					 DSbuffer5[23] = DSbuffer5[22];
					 DSbuffer5[22] = DSbuffer5[21];
					 DSbuffer5[21] = DSbuffer5[20];
					 DSbuffer5[20] = DSbuffer5[19];
					 DSbuffer5[19] = DSbuffer5[18];
					 DSbuffer5[18] = DSbuffer5[17];
					 DSbuffer5[17] = DSbuffer5[16];
					 DSbuffer5[16] = DSbuffer5[15];
					 DSbuffer5[15] = DSbuffer5[14];
					 DSbuffer5[14] = DSbuffer5[13];
					 DSbuffer5[13] = DSbuffer5[12];
					 DSbuffer5[12] = DSbuffer5[11];
					 DSbuffer5[11] = DSbuffer5[10];
					 DSbuffer5[10] = DSbuffer5[9];
					 DSbuffer5[9] = DSbuffer5[8];
					 DSbuffer5[8] = DSbuffer5[7];
					 DSbuffer5[7] = DSbuffer5[6];
					 DSbuffer5[6] = DSbuffer5[5];
					 DSbuffer5[5] = DSbuffer5[4];
					 DSbuffer5[4] = DSbuffer5[3];
					 DSbuffer5[3] = DSbuffer5[2];
					 DSbuffer5[2] = DSbuffer5[1];
					 DSbuffer5[1] = DSbuffer5[0];

					DSResult5 >>= 14;

					DSOutput5 = (short)(DSResult5);

					input_ds5[0] = DSOutput5;

		//			ResultCW1_ds5 = (long)input_ds5[0]*b01CW + (long)input_ds5[1]*b11CW + (long)input_ds5[2]*b21CW - (long)OutputCW1_ds5[1]*a11CW - (long)OutputCW1_ds5[2]*a21CW;

					Result1a_ds5 = (long)input_ds5[0]*b01a + (long)input_ds5[1]*b11a + (long)input_ds5[2]*b21a - (long)Output1a_ds5[1]*a11a - (long)Output1a_ds5[2]*a21a + NSe1a_ds5[1];

					Result1b_ds5 = (long)input_ds5[0]*b01b + (long)input_ds5[1]*b11b + (long)input_ds5[2]*b21b - (long)Output1b_ds5[1]*a11b - (long)Output1b_ds5[2]*a21b + NSe1b_ds5[1];

					Result1c_ds5 = (long)input_ds5[0]*b01c + (long)input_ds5[1]*b11c + (long)input_ds5[2]*b21c - (long)Output1c_ds5[1]*a11c - (long)Output1c_ds5[2]*a21c + NSe1c_ds5[1];

					NSe1a_ds5[0] = Result1a_ds5 & 16383;

					NSe1b_ds5[0] = Result1b_ds5 & 16383;

					NSe1c_ds5[0] = Result1c_ds5 & 16383;

		//			OutputCW1_ds5[0] = (short)(ResultCW1_ds5 >> 13);

					Output1a_ds5[0] = (short)(Result1a_ds5 >> 14);

					Output1b_ds5[0] = (short)(Result1b_ds5 >> 14);

					Output1c_ds5[0] = (short)(Result1c_ds5 >> 14);

		//			inputCW2_ds5[0] = OutputCW1_ds5[0];

					input2a_ds5[0] = Output1a_ds5[0];

					input2b_ds5[0] = Output1b_ds5[0];

					input2c_ds5[0] = Output1c_ds5[0];

		//			ResultCW2_ds5 = (long)inputCW2_ds5[0]*b02CW + (long)inputCW2_ds5[1]*b12CW + (long)inputCW2_ds5[2]*b22CW - (long)OutputCW2_ds5[1]*a12CW - (long)OutputCW2_ds5[2]*a22CW;

					Result2a_ds5 = (long)input2a_ds5[0]*b02a + (long)input2a_ds5[1]*b12a + (long)input2a_ds5[2]*b22a - (long)Output2a_ds5[1]*a12a - (long)Output2a_ds5[2]*a22a + NSe2a_ds5[1];

					Result2b_ds5 = (long)input2b_ds5[0]*b02b + (long)input2b_ds5[1]*b12b + (long)input2b_ds5[2]*b22b - (long)Output2b_ds5[1]*a12b - (long)Output2b_ds5[2]*a22b + NSe2b_ds5[1];

					Result2c_ds5 = (long)input2c_ds5[0]*b02c + (long)input2c_ds5[1]*b12c + (long)input2c_ds5[2]*b22c - (long)Output2c_ds5[1]*a12c - (long)Output2c_ds5[2]*a22c + NSe2c_ds5[1];

					NSe2a_ds5[0] = Result2a_ds5 & 16383;

					NSe2b_ds5[0] = Result2b_ds5 & 16383;

					NSe2c_ds5[0] = Result2c_ds5 & 16383;

		//			OutputCW2_ds5[0] = (short)(ResultCW2_ds5 >> 13);

					Output2a_ds5[0] = (short)(Result2a_ds5 >> 14);

					Output2b_ds5[0] = (short)(Result2b_ds5 >> 14);

					Output2c_ds5[0] = (short)(Result2c_ds5 >> 14);

					input3a_ds5[0] = Output2a_ds5[0];

					input3b_ds5[0] = Output2b_ds5[0];

					input3c_ds5[0] = Output2c_ds5[0];

					Result3a_ds5 = (long)input3a_ds5[0]*b03a + (long)input3a_ds5[1]*b13a + (long)input3a_ds5[2]*b23a - (long)Output3a_ds5[1]*a13a - (long)Output3a_ds5[2]*a23a + NSe3a_ds5[1];

					Result3b_ds5 = (long)input3b_ds5[0]*b03b + (long)input3b_ds5[1]*b13b + (long)input3b_ds5[2]*b23b - (long)Output3b_ds5[1]*a13b - (long)Output3b_ds5[2]*a23b + NSe3b_ds5[1];

					Result3c_ds5 = (long)input3c_ds5[0]*b03c + (long)input3c_ds5[1]*b13c + (long)input3c_ds5[2]*b23c - (long)Output3c_ds5[1]*a13c - (long)Output3c_ds5[2]*a23c + NSe3c_ds5[1];

					NSe3a_ds5[0] = Result3a_ds5 & 16383;

					NSe3b_ds5[0] = Result3b_ds5 & 16383;

					NSe3c_ds5[0] = Result3c_ds5 & 16383;

					Output3a_ds5[0] = (short)(Result3a_ds5 >> 14);

					Output3b_ds5[0] = (short)(Result3b_ds5 >> 14);

					Output3c_ds5[0] = (short)(Result3c_ds5 >> 14);

					NSe1a_ds5[1] = NSe1a_ds5[0];
					NSe2a_ds5[1] = NSe2a_ds5[0];
					NSe3a_ds5[1] = NSe3a_ds5[0];

					NSe1b_ds5[1] = NSe1b_ds5[0];
					NSe2b_ds5[1] = NSe2b_ds5[0];
					NSe3b_ds5[1] = NSe3b_ds5[0];

					NSe1c_ds5[1] = NSe1c_ds5[0];
					NSe2c_ds5[1] = NSe2c_ds5[0];
					NSe3c_ds5[1] = NSe3c_ds5[0];

					input_ds5[2] = input_ds5[1];
					input_ds5[1] = input_ds5[0];

		//			inputCW2_ds5[2] = inputCW2_ds5[1];
		//			inputCW2_ds5[1] = inputCW2_ds5[0];

					input2a_ds5[2] = input2a_ds5[1];
					input3a_ds5[2] = input3a_ds5[1];

					input2b_ds5[2] = input2b_ds5[1];
					input3b_ds5[2] = input3b_ds5[1];

					input2c_ds5[2] = input2c_ds5[1];
					input3c_ds5[2] = input3c_ds5[1];

					input2a_ds5[1] = input2a_ds5[0];
					input3a_ds5[1] = input3a_ds5[0];

					input2b_ds5[1] = input2b_ds5[0];
					input3b_ds5[1] = input3b_ds5[0];

					input2c_ds5[1] = input2c_ds5[0];
					input3c_ds5[1] = input3c_ds5[0];

		//			OutputCW1_ds5[2] = OutputCW1_ds5[1];
		//			OutputCW1_ds5[1] = OutputCW1_ds5[0];
		//			OutputCW2_ds5[2] = OutputCW2_ds5[1];
		//			OutputCW2_ds5[1] = OutputCW2_ds5[0];

					Output1a_ds5[2] = Output1a_ds5[1];
					Output2a_ds5[2] = Output2a_ds5[1];
					Output3a_ds5[2] = Output3a_ds5[1];

					Output1b_ds5[2] = Output1b_ds5[1];
					Output2b_ds5[2] = Output2b_ds5[1];
					Output3b_ds5[2] = Output3b_ds5[1];

					Output1c_ds5[2] = Output1c_ds5[1];
					Output2c_ds5[2] = Output2c_ds5[1];
					Output3c_ds5[2] = Output3c_ds5[1];

					Output1a_ds5[1] = Output1a_ds5[0];
					Output2a_ds5[1] = Output2a_ds5[0];
					Output3a_ds5[1] = Output3a_ds5[0];

					Output1b_ds5[1] = Output1b_ds5[0];
					Output2b_ds5[1] = Output2b_ds5[0];
					Output3b_ds5[1] = Output3b_ds5[0];

					Output1c_ds5[1] = Output1c_ds5[0];
					Output2c_ds5[1] = Output2c_ds5[0];
					Output3c_ds5[1] = Output3c_ds5[0];

					if(RMScount5 < 256){

						tempRMS_band13 += (long)Output3a_ds5[1] * Output3a_ds5[1]  >>  14;
						tempRMS_band14 += (long)Output3b_ds5[1] * Output3b_ds5[1]  >>  14;
						tempRMS_band15 += (long)Output3c_ds5[1] * Output3c_ds5[1]  >>  14;

						RMScount5++;

					}
					else if(RMScount5 >= 256){

						tempRMS_band13 /= 4;
						tempRMS_band14 /= 4;
						tempRMS_band15 /= 4;

						// OUTPUT HER

						if(tempRMS_band13 >= dB_table[old_dB13+1]){
							old_dB13++;
							if(old_dB13 > 36){
								old_dB13 = 36;
							}
						}
						else if(tempRMS_band13 <= dB_table[old_dB13-1]){
							old_dB13--;
						    if(old_dB13 < 0){
						    	old_dB13 = 0;
							}
						}

						if(tempRMS_band14 >= dB_table[old_dB14+1]){
							old_dB14++;
							if(old_dB13 > 36){
								old_dB13 = 36;
							}
						}
						else if(tempRMS_band14 <= dB_table[old_dB14-1]){
							old_dB14--;
							if(old_dB14 < 0){
								old_dB14 = 0;
							}
						}

						if(tempRMS_band15 >= dB_table[old_dB15+1]){
							old_dB15++;
							if(old_dB15 > 36){
								old_dB15 = 36;
							}
						}
						else if(tempRMS_band15 <= dB_table[old_dB15-1]){
							old_dB15--;
							if(old_dB15 < 0){
								old_dB15 = 0;
							}
						}


						tempRMS_band13 = 0;
						tempRMS_band14 = 0;
						tempRMS_band15 = 0;
						RMScount5 = 0;
					}

	            	}
	            	if(DS_table[samplecount] == 520){  // M = 64

	            		DSbuffer6[0] = l_buffer[0];
					DSResult6 = (long)DSbuffer6[0] * filter_taps[0] + (long)DSbuffer6[1] * filter_taps[1] + (long)DSbuffer6[2] * filter_taps[2] + (long)DSbuffer6[3] * filter_taps[3] + (long)DSbuffer6[4] * filter_taps[4] + (long)DSbuffer6[5] * filter_taps[5] + (long)DSbuffer6[6] * filter_taps[6] + (long)DSbuffer6[7] * filter_taps[7] + (long)DSbuffer6[8] * filter_taps[8] + (long)DSbuffer6[9] * filter_taps[9] +
							  (long)DSbuffer6[10] * filter_taps[10] + (long)DSbuffer6[11] * filter_taps[11] + (long)DSbuffer6[12] * filter_taps[12] + (long)DSbuffer6[13] * filter_taps[13] + (long)DSbuffer6[14] * filter_taps[14] + (long)DSbuffer6[15] * filter_taps[15] + (long)DSbuffer6[16] * filter_taps[16] + (long)DSbuffer6[17] * filter_taps[17] + (long)DSbuffer6[18] * filter_taps[18] + (long)DSbuffer6[19] * filter_taps[19] +
							  (long)DSbuffer6[20] * filter_taps[20] + (long)DSbuffer6[21] * filter_taps[21] + (long)DSbuffer6[22] * filter_taps[22] + (long)DSbuffer6[23] * filter_taps[23] + (long)DSbuffer6[24] * filter_taps[24] + (long)DSbuffer6[25] * filter_taps[25] + (long)DSbuffer6[26] * filter_taps[26] + (long)DSbuffer6[27] * filter_taps[27] + (long)DSbuffer6[28] * filter_taps[28] + (long)DSbuffer6[29] * filter_taps[29] +
							  (long)DSbuffer6[30] * filter_taps[30] + (long)DSbuffer6[31] * filter_taps[31] + (long)DSbuffer6[32] * filter_taps[32] + (long)DSbuffer6[33] * filter_taps[33] + (long)DSbuffer6[34] * filter_taps[34] + (long)DSbuffer6[35] * filter_taps[35] + (long)DSbuffer6[36] * filter_taps[36] + (long)DSbuffer6[37] * filter_taps[37] + (long)DSbuffer6[38] * filter_taps[38] + (long)DSbuffer6[39] * filter_taps[39] +
							  (long)DSbuffer6[40] * filter_taps[40] + (long)DSbuffer6[41] * filter_taps[41] + (long)DSbuffer6[42] * filter_taps[42] + (long)DSbuffer6[43] * filter_taps[43] + (long)DSbuffer6[44] * filter_taps[44] + (long)DSbuffer6[45] * filter_taps[45] + (long)DSbuffer6[46] * filter_taps[46] + (long)DSbuffer6[47] * filter_taps[47] + (long)DSbuffer6[48] * filter_taps[48] + (long)DSbuffer6[49] * filter_taps[49] +
							  (long)DSbuffer6[50] * filter_taps[50] + (long)DSbuffer6[51] * filter_taps[51] + (long)DSbuffer6[52] * filter_taps[52] + (long)DSbuffer6[53] * filter_taps[53] + (long)DSbuffer6[54] * filter_taps[54] + (long)DSbuffer6[55] * filter_taps[55] + (long)DSbuffer6[56] * filter_taps[56] + (long)DSbuffer6[57] * filter_taps[57] + (long)DSbuffer6[58] * filter_taps[58] + (long)DSbuffer6[59] * filter_taps[59] +
							  (long)DSbuffer6[60] * filter_taps[60] + (long)DSbuffer6[61] * filter_taps[61] + (long)DSbuffer6[62] * filter_taps[62] + (long)DSbuffer6[63] * filter_taps[63] + (long)DSbuffer6[64] * filter_taps[64] + (long)DSbuffer6[65] * filter_taps[65] + (long)DSbuffer6[66] * filter_taps[66] + (long)DSbuffer6[67] * filter_taps[67] + (long)DSbuffer6[68] * filter_taps[68] + (long)DSbuffer6[69] * filter_taps[69] +
							  (long)DSbuffer6[70] * filter_taps[70] + (long)DSbuffer6[71] * filter_taps[71] + (long)DSbuffer6[72] * filter_taps[72] + (long)DSbuffer6[73] * filter_taps[73] + (long)DSbuffer6[74] * filter_taps[74] + (long)DSbuffer6[75] * filter_taps[75] + (long)DSbuffer6[76] * filter_taps[76] + (long)DSbuffer6[77] * filter_taps[77] + (long)DSbuffer6[78] * filter_taps[78] + (long)DSbuffer6[79] * filter_taps[79] +
							  (long)DSbuffer6[80] * filter_taps[80] + (long)DSbuffer6[81] * filter_taps[81] + (long)DSbuffer6[82] * filter_taps[82] + (long)DSbuffer6[83] * filter_taps[83] + (long)DSbuffer6[84] * filter_taps[84] + (long)DSbuffer6[85] * filter_taps[85] + (long)DSbuffer6[86] * filter_taps[86] + (long)DSbuffer6[87] * filter_taps[87] + (long)DSbuffer6[88] * filter_taps[88] + (long)DSbuffer6[89] * filter_taps[89] +
							  (long)DSbuffer6[90] * filter_taps[90] + (long)DSbuffer6[91] * filter_taps[91] + (long)DSbuffer6[92] * filter_taps[92] + (long)DSbuffer6[93] * filter_taps[93] + (long)DSbuffer6[94] * filter_taps[94] + (long)DSbuffer6[95] * filter_taps[95];


					 DSbuffer6[95] = DSbuffer6[94];
					 DSbuffer6[94] = DSbuffer6[93];
					 DSbuffer6[93] = DSbuffer6[92];
					 DSbuffer6[92] = DSbuffer6[91];
					 DSbuffer6[91] = DSbuffer6[90];
					 DSbuffer6[90] = DSbuffer6[89];
					 DSbuffer6[89] = DSbuffer6[88];
					 DSbuffer6[88] = DSbuffer6[87];
					 DSbuffer6[87] = DSbuffer6[86];
					 DSbuffer6[86] = DSbuffer6[85];
					 DSbuffer6[85] = DSbuffer6[84];
					 DSbuffer6[84] = DSbuffer6[83];
					 DSbuffer6[83] = DSbuffer6[82];
					 DSbuffer6[82] = DSbuffer6[81];
					 DSbuffer6[81] = DSbuffer6[80];
					 DSbuffer6[80] = DSbuffer6[79];
					 DSbuffer6[79] = DSbuffer6[78];
					 DSbuffer6[78] = DSbuffer6[77];
					 DSbuffer6[77] = DSbuffer6[76];
					 DSbuffer6[76] = DSbuffer6[75];
					 DSbuffer6[75] = DSbuffer6[74];
					 DSbuffer6[74] = DSbuffer6[73];
					 DSbuffer6[73] = DSbuffer6[72];
					 DSbuffer6[72] = DSbuffer6[71];
					 DSbuffer6[71] = DSbuffer6[70];
					 DSbuffer6[70] = DSbuffer6[69];
					 DSbuffer6[69] = DSbuffer6[68];
					 DSbuffer6[68] = DSbuffer6[67];
					 DSbuffer6[67] = DSbuffer6[66];
					 DSbuffer6[66] = DSbuffer6[65];
					 DSbuffer6[65] = DSbuffer6[64];
					 DSbuffer6[64] = DSbuffer6[63];
					 DSbuffer6[63] = DSbuffer6[62];
					 DSbuffer6[62] = DSbuffer6[61];
					 DSbuffer6[61] = DSbuffer6[60];
					 DSbuffer6[60] = DSbuffer6[59];
					 DSbuffer6[59] = DSbuffer6[58];
					 DSbuffer6[58] = DSbuffer6[57];
					 DSbuffer6[57] = DSbuffer6[56];
					 DSbuffer6[56] = DSbuffer6[55];
					 DSbuffer6[55] = DSbuffer6[54];
					 DSbuffer6[54] = DSbuffer6[53];
					 DSbuffer6[53] = DSbuffer6[52];
					 DSbuffer6[52] = DSbuffer6[51];
					 DSbuffer6[51] = DSbuffer6[50];
					 DSbuffer6[50] = DSbuffer6[49];
					 DSbuffer6[49] = DSbuffer6[48];
					 DSbuffer6[48] = DSbuffer6[47];
					 DSbuffer6[47] = DSbuffer6[46];
					 DSbuffer6[46] = DSbuffer6[45];
					 DSbuffer6[45] = DSbuffer6[44];
					 DSbuffer6[44] = DSbuffer6[43];
					 DSbuffer6[43] = DSbuffer6[42];
					 DSbuffer6[42] = DSbuffer6[41];
					 DSbuffer6[41] = DSbuffer6[40];
					 DSbuffer6[40] = DSbuffer6[39];
					 DSbuffer6[39] = DSbuffer6[38];
					 DSbuffer6[38] = DSbuffer6[37];
					 DSbuffer6[37] = DSbuffer6[36];
					 DSbuffer6[36] = DSbuffer6[35];
					 DSbuffer6[35] = DSbuffer6[34];
					 DSbuffer6[34] = DSbuffer6[33];
					 DSbuffer6[33] = DSbuffer6[32];
					 DSbuffer6[32] = DSbuffer6[31];
					 DSbuffer6[31] = DSbuffer6[30];
					 DSbuffer6[30] = DSbuffer6[29];
					 DSbuffer6[29] = DSbuffer6[28];
					 DSbuffer6[28] = DSbuffer6[27];
					 DSbuffer6[27] = DSbuffer6[26];
					 DSbuffer6[26] = DSbuffer6[25];
					 DSbuffer6[25] = DSbuffer6[24];
					 DSbuffer6[24] = DSbuffer6[23];
					 DSbuffer6[23] = DSbuffer6[22];
					 DSbuffer6[22] = DSbuffer6[21];
					 DSbuffer6[21] = DSbuffer6[20];
					 DSbuffer6[20] = DSbuffer6[19];
					 DSbuffer6[19] = DSbuffer6[18];
					 DSbuffer6[18] = DSbuffer6[17];
					 DSbuffer6[17] = DSbuffer6[16];
					 DSbuffer6[16] = DSbuffer6[15];
					 DSbuffer6[15] = DSbuffer6[14];
					 DSbuffer6[14] = DSbuffer6[13];
					 DSbuffer6[13] = DSbuffer6[12];
					 DSbuffer6[12] = DSbuffer6[11];
					 DSbuffer6[11] = DSbuffer6[10];
					 DSbuffer6[10] = DSbuffer6[9];
					 DSbuffer6[9] = DSbuffer6[8];
					 DSbuffer6[8] = DSbuffer6[7];
					 DSbuffer6[7] = DSbuffer6[6];
					 DSbuffer6[6] = DSbuffer6[5];
					 DSbuffer6[5] = DSbuffer6[4];
					 DSbuffer6[4] = DSbuffer6[3];
					 DSbuffer6[3] = DSbuffer6[2];
					 DSbuffer6[2] = DSbuffer6[1];
					 DSbuffer6[1] = DSbuffer6[0];

					DSResult6 >>= 14;

					DSOutput6  = (short)(DSResult6);

					input_ds6[0] = DSOutput6;

		//			ResultCW1_ds6 = (long)input_ds6[0]*b01CW + (long)input_ds6[1]*b11CW + (long)input_ds6[2]*b21CW - (long)OutputCW1_ds6[1]*a11CW - (long)OutputCW1_ds6[2]*a21CW;

					Result1a_ds6 = (long)input_ds6[0]*b01a + (long)input_ds6[1]*b11a + (long)input_ds6[2]*b21a - (long)Output1a_ds6[1]*a11a - (long)Output1a_ds6[2]*a21a + NSe1a_ds6[1];

					Result1b_ds6 = (long)input_ds6[0]*b01b + (long)input_ds6[1]*b11b + (long)input_ds6[2]*b21b - (long)Output1b_ds6[1]*a11b - (long)Output1b_ds6[2]*a21b + NSe1b_ds6[1];

					Result1c_ds6 = (long)input_ds6[0]*b01c + (long)input_ds6[1]*b11c + (long)input_ds6[2]*b21c - (long)Output1c_ds6[1]*a11c - (long)Output1c_ds6[2]*a21c + NSe1c_ds6[1];

					NSe1a_ds6[0] = Result1a_ds6 & 16383;

					NSe1b_ds6[0] = Result1b_ds6 & 16383;

					NSe1c_ds6[0] = Result1c_ds6 & 16383;

		//			OutputCW1_ds6[0] = (short)(ResultCW1_ds6 >> 13);

					Output1a_ds6[0] = (short)(Result1a_ds6 >> 14);

					Output1b_ds6[0] = (short)(Result1b_ds6 >> 14);

					Output1c_ds6[0] = (short)(Result1c_ds6 >> 14);

		//			inputCW2_ds6[0] = OutputCW1_ds6[0];

					input2a_ds6[0] = Output1a_ds6[0];

					input2b_ds6[0] = Output1b_ds6[0];

					input2c_ds6[0] = Output1c_ds6[0];

		//			ResultCW2_ds6 = (long)inputCW2_ds6[0]*b02CW + (long)inputCW2_ds6[1]*b12CW + (long)inputCW2_ds6[2]*b22CW - (long)OutputCW2_ds6[1]*a12CW - (long)OutputCW2_ds6[2]*a22CW;

					Result2a_ds6 = (long)input2a_ds6[0]*b02a + (long)input2a_ds6[1]*b12a + (long)input2a_ds6[2]*b22a - (long)Output2a_ds6[1]*a12a - (long)Output2a_ds6[2]*a22a + NSe2a_ds6[1];

					Result2b_ds6 = (long)input2b_ds6[0]*b02b + (long)input2b_ds6[1]*b12b + (long)input2b_ds6[2]*b22b - (long)Output2b_ds6[1]*a12b - (long)Output2b_ds6[2]*a22b + NSe2b_ds6[1];

					Result2c_ds6 = (long)input2c_ds6[0]*b02c + (long)input2c_ds6[1]*b12c + (long)input2c_ds6[2]*b22c - (long)Output2c_ds6[1]*a12c - (long)Output2c_ds6[2]*a22c + NSe2c_ds6[1];

					NSe2a_ds6[0] = Result2a_ds6 & 16383;

					NSe2b_ds6[0] = Result2b_ds6 & 16383;

					NSe2c_ds6[0] = Result2c_ds6 & 16383;

		//			OutputCW2_ds6[0] = (short)(ResultCW2_ds6 >> 13);

					Output2a_ds6[0] = (short)(Result2a_ds6 >> 14);

					Output2b_ds6[0] = (short)(Result2b_ds6 >> 14);

					Output2c_ds6[0] = (short)(Result2c_ds6 >> 14);

					input3a_ds6[0] = Output2a_ds6[0];

					input3b_ds6[0] = Output2b_ds6[0];

					input3c_ds6[0] = Output2c_ds6[0];

					Result3a_ds6 = (long)input3a_ds6[0]*b03a + (long)input3a_ds6[1]*b13a + (long)input3a_ds6[2]*b23a - (long)Output3a_ds6[1]*a13a - (long)Output3a_ds6[2]*a23a + NSe3a_ds6[1];

					Result3b_ds6 = (long)input3b_ds6[0]*b03b + (long)input3b_ds6[1]*b13b + (long)input3b_ds6[2]*b23b - (long)Output3b_ds6[1]*a13b - (long)Output3b_ds6[2]*a23b + NSe3b_ds6[1];

					Result3c_ds6 = (long)input3c_ds6[0]*b03c + (long)input3c_ds6[1]*b13c + (long)input3c_ds6[2]*b23c - (long)Output3c_ds6[1]*a13c - (long)Output3c_ds6[2]*a23c + NSe3c_ds6[1];

					NSe3a_ds6[0] = Result3a_ds6 & 16383;

					NSe3b_ds6[0] = Result3b_ds6 & 16383;

					NSe3c_ds6[0] = Result3c_ds6 & 16383;

					Output3a_ds6[0] = (short)(Result3a_ds6 >> 14);

					Output3b_ds6[0] = (short)(Result3b_ds6 >> 14);

					Output3c_ds6[0] = (short)(Result3c_ds6 >> 14);

					NSe1a_ds6[1] = NSe1a_ds6[0];
					NSe2a_ds6[1] = NSe2a_ds6[0];
					NSe3a_ds6[1] = NSe3a_ds6[0];

					NSe1b_ds6[1] = NSe1b_ds6[0];
					NSe2b_ds6[1] = NSe2b_ds6[0];
					NSe3b_ds6[1] = NSe3b_ds6[0];

					NSe1c_ds6[1] = NSe1c_ds6[0];
					NSe2c_ds6[1] = NSe2c_ds6[0];
					NSe3c_ds6[1] = NSe3c_ds6[0];

					input_ds6[2] = input_ds6[1];
					input_ds6[1] = input_ds6[0];

		//			inputCW2_ds6[2] = inputCW2_ds6[1];
		//			inputCW2_ds6[1] = inputCW2_ds6[0];

					input2a_ds6[2] = input2a_ds6[1];
					input3a_ds6[2] = input3a_ds6[1];

					input2b_ds6[2] = input2b_ds6[1];
					input3b_ds6[2] = input3b_ds6[1];

					input2c_ds6[2] = input2c_ds6[1];
					input3c_ds6[2] = input3c_ds6[1];

					input2a_ds6[1] = input2a_ds6[0];
					input3a_ds6[1] = input3a_ds6[0];

					input2b_ds6[1] = input2b_ds6[0];
					input3b_ds6[1] = input3b_ds6[0];

					input2c_ds6[1] = input2c_ds6[0];
					input3c_ds6[1] = input3c_ds6[0];

		//			OutputCW1_ds6[2] = OutputCW1_ds6[1];
		//			OutputCW1_ds6[1] = OutputCW1_ds6[0];
		//			OutputCW2_ds6[2] = OutputCW2_ds6[1];
		//			OutputCW2_ds6[1] = OutputCW2_ds6[0];

					Output1a_ds6[2] = Output1a_ds6[1];
					Output2a_ds6[2] = Output2a_ds6[1];
					Output3a_ds6[2] = Output3a_ds6[1];

					Output1b_ds6[2] = Output1b_ds6[1];
					Output2b_ds6[2] = Output2b_ds6[1];
					Output3b_ds6[2] = Output3b_ds6[1];

					Output1c_ds6[2] = Output1c_ds6[1];
					Output2c_ds6[2] = Output2c_ds6[1];
					Output3c_ds6[2] = Output3c_ds6[1];

					Output1a_ds6[1] = Output1a_ds6[0];
					Output2a_ds6[1] = Output2a_ds6[0];
					Output3a_ds6[1] = Output3a_ds6[0];

					Output1b_ds6[1] = Output1b_ds6[0];
					Output2b_ds6[1] = Output2b_ds6[0];
					Output3b_ds6[1] = Output3b_ds6[0];

					Output1c_ds6[1] = Output1c_ds6[0];
					Output2c_ds6[1] = Output2c_ds6[0];
					Output3c_ds6[1] = Output3c_ds6[0];

					if(RMScount6 < 256){

						tempRMS_band10 += (long)Output3a_ds6[1] * Output3a_ds6[1]  >>  14;
						tempRMS_band11 += (long)Output3b_ds6[1] * Output3b_ds6[1]  >>  14;
						tempRMS_band12 += (long)Output3c_ds6[1] * Output3c_ds6[1]  >>  14;

						RMScount6++;

					}
					else if(RMScount6 >= 256){

						tempRMS_band10 /= 4;
						tempRMS_band11 /= 4;
						tempRMS_band12 /= 4;

						// OUTPUT HER
						if(tempRMS_band10 >= dB_table[old_dB10+1]){
							old_dB10++;
							if(old_dB10 > 36){
								old_dB10 = 36;
							}
						}
						else if(tempRMS_band10 <= dB_table[old_dB10-1]){
							old_dB10--;
							if(old_dB10 < 0){
								old_dB10 = 0;
							}
						}

						if(tempRMS_band11 >= dB_table[old_dB11+1]){
							old_dB11++;
							if(old_dB11 > 36){
								old_dB11 = 36;
							}
						}
						else if(tempRMS_band11 <= dB_table[old_dB11-1]){
							old_dB11--;
							if(old_dB11 < 0){
								old_dB11 = 0;
							}
						}

						if(tempRMS_band12 >= dB_table[old_dB12+1]){
							old_dB12++;
							if(old_dB12 > 36){
								old_dB12 = 36;
							}
						}
						else if(tempRMS_band12 <= dB_table[old_dB12-1]){
							old_dB12--;
							if(old_dB12 < 0){
								old_dB12 = 0;
							}
						}


						tempRMS_band10 = 0;
						tempRMS_band11 = 0;
						tempRMS_band12 = 0;
						RMScount6 = 0;
					}

	            	}
	            	if(DS_table[samplecount] == 516){  // M = 128



					DSbuffer7[0] = l_buffer[0];
					DSResult7 = (long)DSbuffer7[0] * filter_taps[0] + (long)DSbuffer7[1] * filter_taps[1] + (long)DSbuffer7[2] * filter_taps[2] + (long)DSbuffer7[3] * filter_taps[3] + (long)DSbuffer7[4] * filter_taps[4] + (long)DSbuffer7[5] * filter_taps[5] + (long)DSbuffer7[6] * filter_taps[6] + (long)DSbuffer7[7] * filter_taps[7] + (long)DSbuffer7[8] * filter_taps[8] + (long)DSbuffer7[9] * filter_taps[9] +
							  (long)DSbuffer7[10] * filter_taps[10] + (long)DSbuffer7[11] * filter_taps[11] + (long)DSbuffer7[12] * filter_taps[12] + (long)DSbuffer7[13] * filter_taps[13] + (long)DSbuffer7[14] * filter_taps[14] + (long)DSbuffer7[15] * filter_taps[15] + (long)DSbuffer7[16] * filter_taps[16] + (long)DSbuffer7[17] * filter_taps[17] + (long)DSbuffer7[18] * filter_taps[18] + (long)DSbuffer7[19] * filter_taps[19] +
							  (long)DSbuffer7[20] * filter_taps[20] + (long)DSbuffer7[21] * filter_taps[21] + (long)DSbuffer7[22] * filter_taps[22] + (long)DSbuffer7[23] * filter_taps[23] + (long)DSbuffer7[24] * filter_taps[24] + (long)DSbuffer7[25] * filter_taps[25] + (long)DSbuffer7[26] * filter_taps[26] + (long)DSbuffer7[27] * filter_taps[27] + (long)DSbuffer7[28] * filter_taps[28] + (long)DSbuffer7[29] * filter_taps[29] +
							  (long)DSbuffer7[30] * filter_taps[30] + (long)DSbuffer7[31] * filter_taps[31] + (long)DSbuffer7[32] * filter_taps[32] + (long)DSbuffer7[33] * filter_taps[33] + (long)DSbuffer7[34] * filter_taps[34] + (long)DSbuffer7[35] * filter_taps[35] + (long)DSbuffer7[36] * filter_taps[36] + (long)DSbuffer7[37] * filter_taps[37] + (long)DSbuffer7[38] * filter_taps[38] + (long)DSbuffer7[39] * filter_taps[39] +
							  (long)DSbuffer7[40] * filter_taps[40] + (long)DSbuffer7[41] * filter_taps[41] + (long)DSbuffer7[42] * filter_taps[42] + (long)DSbuffer7[43] * filter_taps[43] + (long)DSbuffer7[44] * filter_taps[44] + (long)DSbuffer7[45] * filter_taps[45] + (long)DSbuffer7[46] * filter_taps[46] + (long)DSbuffer7[47] * filter_taps[47] + (long)DSbuffer7[48] * filter_taps[48] + (long)DSbuffer7[49] * filter_taps[49] +
							  (long)DSbuffer7[50] * filter_taps[50] + (long)DSbuffer7[51] * filter_taps[51] + (long)DSbuffer7[52] * filter_taps[52] + (long)DSbuffer7[53] * filter_taps[53] + (long)DSbuffer7[54] * filter_taps[54] + (long)DSbuffer7[55] * filter_taps[55] + (long)DSbuffer7[56] * filter_taps[56] + (long)DSbuffer7[57] * filter_taps[57] + (long)DSbuffer7[58] * filter_taps[58] + (long)DSbuffer7[59] * filter_taps[59] +
							  (long)DSbuffer7[60] * filter_taps[60] + (long)DSbuffer7[61] * filter_taps[61] + (long)DSbuffer7[62] * filter_taps[62] + (long)DSbuffer7[63] * filter_taps[63] + (long)DSbuffer7[64] * filter_taps[64] + (long)DSbuffer7[65] * filter_taps[65] + (long)DSbuffer7[66] * filter_taps[66] + (long)DSbuffer7[67] * filter_taps[67] + (long)DSbuffer7[68] * filter_taps[68] + (long)DSbuffer7[69] * filter_taps[69] +
							  (long)DSbuffer7[70] * filter_taps[70] + (long)DSbuffer7[71] * filter_taps[71] + (long)DSbuffer7[72] * filter_taps[72] + (long)DSbuffer7[73] * filter_taps[73] + (long)DSbuffer7[74] * filter_taps[74] + (long)DSbuffer7[75] * filter_taps[75] + (long)DSbuffer7[76] * filter_taps[76] + (long)DSbuffer7[77] * filter_taps[77] + (long)DSbuffer7[78] * filter_taps[78] + (long)DSbuffer7[79] * filter_taps[79] +
							  (long)DSbuffer7[80] * filter_taps[80] + (long)DSbuffer7[81] * filter_taps[81] + (long)DSbuffer7[82] * filter_taps[82] + (long)DSbuffer7[83] * filter_taps[83] + (long)DSbuffer7[84] * filter_taps[84] + (long)DSbuffer7[85] * filter_taps[85] + (long)DSbuffer7[86] * filter_taps[86] + (long)DSbuffer7[87] * filter_taps[87] + (long)DSbuffer7[88] * filter_taps[88] + (long)DSbuffer7[89] * filter_taps[89] +
							  (long)DSbuffer7[90] * filter_taps[90] + (long)DSbuffer7[91] * filter_taps[91] + (long)DSbuffer7[92] * filter_taps[92] + (long)DSbuffer7[93] * filter_taps[93] + (long)DSbuffer7[94] * filter_taps[94] + (long)DSbuffer7[95] * filter_taps[95];


					 DSbuffer7[95] = DSbuffer7[94];
					 DSbuffer7[94] = DSbuffer7[93];
					 DSbuffer7[93] = DSbuffer7[92];
					 DSbuffer7[92] = DSbuffer7[91];
					 DSbuffer7[91] = DSbuffer7[90];
					 DSbuffer7[90] = DSbuffer7[89];
					 DSbuffer7[89] = DSbuffer7[88];
					 DSbuffer7[88] = DSbuffer7[87];
					 DSbuffer7[87] = DSbuffer7[86];
					 DSbuffer7[86] = DSbuffer7[85];
					 DSbuffer7[85] = DSbuffer7[84];
					 DSbuffer7[84] = DSbuffer7[83];
					 DSbuffer7[83] = DSbuffer7[82];
					 DSbuffer7[82] = DSbuffer7[81];
					 DSbuffer7[81] = DSbuffer7[80];
					 DSbuffer7[80] = DSbuffer7[79];
					 DSbuffer7[79] = DSbuffer7[78];
					 DSbuffer7[78] = DSbuffer7[77];
					 DSbuffer7[77] = DSbuffer7[76];
					 DSbuffer7[76] = DSbuffer7[75];
					 DSbuffer7[75] = DSbuffer7[74];
					 DSbuffer7[74] = DSbuffer7[73];
					 DSbuffer7[73] = DSbuffer7[72];
					 DSbuffer7[72] = DSbuffer7[71];
					 DSbuffer7[71] = DSbuffer7[70];
					 DSbuffer7[70] = DSbuffer7[69];
					 DSbuffer7[69] = DSbuffer7[68];
					 DSbuffer7[68] = DSbuffer7[67];
					 DSbuffer7[67] = DSbuffer7[66];
					 DSbuffer7[66] = DSbuffer7[65];
					 DSbuffer7[65] = DSbuffer7[64];
					 DSbuffer7[64] = DSbuffer7[63];
					 DSbuffer7[63] = DSbuffer7[62];
					 DSbuffer7[62] = DSbuffer7[61];
					 DSbuffer7[61] = DSbuffer7[60];
					 DSbuffer7[60] = DSbuffer7[59];
					 DSbuffer7[59] = DSbuffer7[58];
					 DSbuffer7[58] = DSbuffer7[57];
					 DSbuffer7[57] = DSbuffer7[56];
					 DSbuffer7[56] = DSbuffer7[55];
					 DSbuffer7[55] = DSbuffer7[54];
					 DSbuffer7[54] = DSbuffer7[53];
					 DSbuffer7[53] = DSbuffer7[52];
					 DSbuffer7[52] = DSbuffer7[51];
					 DSbuffer7[51] = DSbuffer7[50];
					 DSbuffer7[50] = DSbuffer7[49];
					 DSbuffer7[49] = DSbuffer7[48];
					 DSbuffer7[48] = DSbuffer7[47];
					 DSbuffer7[47] = DSbuffer7[46];
					 DSbuffer7[46] = DSbuffer7[45];
					 DSbuffer7[45] = DSbuffer7[44];
					 DSbuffer7[44] = DSbuffer7[43];
					 DSbuffer7[43] = DSbuffer7[42];
					 DSbuffer7[42] = DSbuffer7[41];
					 DSbuffer7[41] = DSbuffer7[40];
					 DSbuffer7[40] = DSbuffer7[39];
					 DSbuffer7[39] = DSbuffer7[38];
					 DSbuffer7[38] = DSbuffer7[37];
					 DSbuffer7[37] = DSbuffer7[36];
					 DSbuffer7[36] = DSbuffer7[35];
					 DSbuffer7[35] = DSbuffer7[34];
					 DSbuffer7[34] = DSbuffer7[33];
					 DSbuffer7[33] = DSbuffer7[32];
					 DSbuffer7[32] = DSbuffer7[31];
					 DSbuffer7[31] = DSbuffer7[30];
					 DSbuffer7[30] = DSbuffer7[29];
					 DSbuffer7[29] = DSbuffer7[28];
					 DSbuffer7[28] = DSbuffer7[27];
					 DSbuffer7[27] = DSbuffer7[26];
					 DSbuffer7[26] = DSbuffer7[25];
					 DSbuffer7[25] = DSbuffer7[24];
					 DSbuffer7[24] = DSbuffer7[23];
					 DSbuffer7[23] = DSbuffer7[22];
					 DSbuffer7[22] = DSbuffer7[21];
					 DSbuffer7[21] = DSbuffer7[20];
					 DSbuffer7[20] = DSbuffer7[19];
					 DSbuffer7[19] = DSbuffer7[18];
					 DSbuffer7[18] = DSbuffer7[17];
					 DSbuffer7[17] = DSbuffer7[16];
					 DSbuffer7[16] = DSbuffer7[15];
					 DSbuffer7[15] = DSbuffer7[14];
					 DSbuffer7[14] = DSbuffer7[13];
					 DSbuffer7[13] = DSbuffer7[12];
					 DSbuffer7[12] = DSbuffer7[11];
					 DSbuffer7[11] = DSbuffer7[10];
					 DSbuffer7[10] = DSbuffer7[9];
					 DSbuffer7[9] = DSbuffer7[8];
					 DSbuffer7[8] = DSbuffer7[7];
					 DSbuffer7[7] = DSbuffer7[6];
					 DSbuffer7[6] = DSbuffer7[5];
					 DSbuffer7[5] = DSbuffer7[4];
					 DSbuffer7[4] = DSbuffer7[3];
					 DSbuffer7[3] = DSbuffer7[2];
					 DSbuffer7[2] = DSbuffer7[1];
					 DSbuffer7[1] = DSbuffer7[0];

					DSResult7 >>= 14;

					DSOutput7 = (short)(DSResult7);

					input_ds7[0] = DSOutput7;

		// 			ResultCW1_ds7 = (long)input_ds7[0]*b01CW + (long)input_ds7[1]*b11CW + (long)input_ds7[2]*b21CW - (long)OutputCW1_ds7[1]*a11CW - (long)OutputCW1_ds7[2]*a21CW;

					Result1a_ds7 = (long)input_ds7[0]*b01a + (long)input_ds7[1]*b11a + (long)input_ds7[2]*b21a - (long)Output1a_ds7[1]*a11a - (long)Output1a_ds7[2]*a21a + NSe1a_ds7[1];

					Result1b_ds7 = (long)input_ds7[0]*b01b + (long)input_ds7[1]*b11b + (long)input_ds7[2]*b21b - (long)Output1b_ds7[1]*a11b - (long)Output1b_ds7[2]*a21b + NSe1b_ds7[1];

					Result1c_ds7 = (long)input_ds7[0]*b01c + (long)input_ds7[1]*b11c + (long)input_ds7[2]*b21c - (long)Output1c_ds7[1]*a11c - (long)Output1c_ds7[2]*a21c + NSe1c_ds7[1];

					NSe1a_ds7[0] = Result1a_ds7 & 16383;

					NSe1b_ds7[0] = Result1b_ds7 & 16383;

					NSe1c_ds7[0] = Result1c_ds7 & 16383;

		//			OutputCW1_ds7[0] = (short)(ResultCW1_ds7 >> 13);

					Output1a_ds7[0] = (short)(Result1a_ds7 >> 14);

					Output1b_ds7[0] = (short)(Result1b_ds7 >> 14);

					Output1c_ds7[0] = (short)(Result1c_ds7 >> 14);

		//			inputCW2_ds7[0] = OutputCW1_ds7[0];

					input2a_ds7[0] = Output1a_ds7[0];

					input2b_ds7[0] = Output1b_ds7[0];

					input2c_ds7[0] = Output1c_ds7[0];

		//			ResultCW2_ds7 = (long)inputCW2_ds7[0]*b02CW + (long)inputCW2_ds7[1]*b12CW + (long)inputCW2_ds7[2]*b22CW - (long)OutputCW2_ds7[1]*a12CW - (long)OutputCW2_ds7[2]*a22CW;

					Result2a_ds7 = (long)input2a_ds7[0]*b02a + (long)input2a_ds7[1]*b12a + (long)input2a_ds7[2]*b22a - (long)Output2a_ds7[1]*a12a - (long)Output2a_ds7[2]*a22a + NSe2a_ds7[1];

					Result2b_ds7 = (long)input2b_ds7[0]*b02b + (long)input2b_ds7[1]*b12b + (long)input2b_ds7[2]*b22b - (long)Output2b_ds7[1]*a12b - (long)Output2b_ds7[2]*a22b + NSe2b_ds7[1];

					Result2c_ds7 = (long)input2c_ds7[0]*b02c + (long)input2c_ds7[1]*b12c + (long)input2c_ds7[2]*b22c - (long)Output2c_ds7[1]*a12c - (long)Output2c_ds7[2]*a22c + NSe2c_ds7[1];

					NSe2a_ds7[0] = Result2a_ds7 & 16383;

					NSe2b_ds7[0] = Result2b_ds7 & 16383;

					NSe2c_ds7[0] = Result2c_ds7 & 16383;

		//			OutputCW2_ds7[0] = (short)(ResultCW2_ds7 >> 13);

					Output2a_ds7[0] = (short)(Result2a_ds7 >> 14);

					Output2b_ds7[0] = (short)(Result2b_ds7 >> 14);

					Output2c_ds7[0] = (short)(Result2c_ds7 >> 14);

					input3a_ds7[0] = Output2a_ds7[0];

					input3b_ds7[0] = Output2b_ds7[0];

					input3c_ds7[0] = Output2c_ds7[0];

					Result3a_ds7 = (long)input3a_ds7[0]*b03a + (long)input3a_ds7[1]*b13a + (long)input3a_ds7[2]*b23a - (long)Output3a_ds7[1]*a13a - (long)Output3a_ds7[2]*a23a + NSe3a_ds7[1];

					Result3b_ds7 = (long)input3b_ds7[0]*b03b + (long)input3b_ds7[1]*b13b + (long)input3b_ds7[2]*b23b - (long)Output3b_ds7[1]*a13b - (long)Output3b_ds7[2]*a23b + NSe3b_ds7[1];

					Result3c_ds7 = (long)input3c_ds7[0]*b03c + (long)input3c_ds7[1]*b13c + (long)input3c_ds7[2]*b23c - (long)Output3c_ds7[1]*a13c - (long)Output3c_ds7[2]*a23c + NSe3c_ds7[1];

					NSe3a_ds7[0] = Result3a_ds7 & 16383;

					NSe3b_ds7[0] = Result3b_ds7 & 16383;

					NSe3c_ds7[0] = Result3c_ds7 & 16383;

					Output3a_ds7[0] = (short)(Result3a_ds7 >> 14);

					Output3b_ds7[0] = (short)(Result3b_ds7 >> 14);

					Output3c_ds7[0] = (short)(Result3c_ds7 >> 14);

					NSe1a_ds7[1] = NSe1a_ds7[0];
					NSe2a_ds7[1] = NSe2a_ds7[0];
					NSe3a_ds7[1] = NSe3a_ds7[0];

					NSe1b_ds7[1] = NSe1b_ds7[0];
					NSe2b_ds7[1] = NSe2b_ds7[0];
					NSe3b_ds7[1] = NSe3b_ds7[0];

					NSe1c_ds7[1] = NSe1c_ds7[0];
					NSe2c_ds7[1] = NSe2c_ds7[0];
					NSe3c_ds7[1] = NSe3c_ds7[0];

					input_ds7[2] = input_ds7[1];
					input_ds7[1] = input_ds7[0];

		//			inputCW2_ds7[2] = inputCW2_ds7[1];
		//			inputCW2_ds7[1] = inputCW2_ds7[0];

					input2a_ds7[2] = input2a_ds7[1];
					input3a_ds7[2] = input3a_ds7[1];

					input2b_ds7[2] = input2b_ds7[1];
					input3b_ds7[2] = input3b_ds7[1];

					input2c_ds7[2] = input2c_ds7[1];
					input3c_ds7[2] = input3c_ds7[1];

					input2a_ds7[1] = input2a_ds7[0];
					input3a_ds7[1] = input3a_ds7[0];

					input2b_ds7[1] = input2b_ds7[0];
					input3b_ds7[1] = input3b_ds7[0];

					input2c_ds7[1] = input2c_ds7[0];
					input3c_ds7[1] = input3c_ds7[0];

		//			OutputCW1_ds7[2] = OutputCW1_ds7[1];
		//			OutputCW1_ds7[1] = OutputCW1_ds7[0];
		//			OutputCW2_ds7[2] = OutputCW2_ds7[1];
		//			OutputCW2_ds7[1] = OutputCW2_ds7[0];

					Output1a_ds7[2] = Output1a_ds7[1];
					Output2a_ds7[2] = Output2a_ds7[1];
					Output3a_ds7[2] = Output3a_ds7[1];

					Output1b_ds7[2] = Output1b_ds7[1];
					Output2b_ds7[2] = Output2b_ds7[1];
					Output3b_ds7[2] = Output3b_ds7[1];

					Output1c_ds7[2] = Output1c_ds7[1];
					Output2c_ds7[2] = Output2c_ds7[1];
					Output3c_ds7[2] = Output3c_ds7[1];

					Output1a_ds7[1] = Output1a_ds7[0];
					Output2a_ds7[1] = Output2a_ds7[0];
					Output3a_ds7[1] = Output3a_ds7[0];

					Output1b_ds7[1] = Output1b_ds7[0];
					Output2b_ds7[1] = Output2b_ds7[0];
					Output3b_ds7[1] = Output3b_ds7[0];

					Output1c_ds7[1] = Output1c_ds7[0];
					Output2c_ds7[1] = Output2c_ds7[0];
					Output3c_ds7[1] = Output3c_ds7[0];

					if(RMScount7 < 256){

						tempRMS_band7 += (long)Output3a_ds7[1] * Output3a_ds7[1]  >>  14;
						tempRMS_band8 += (long)Output3b_ds7[1] * Output3b_ds7[1]  >>  14;
						tempRMS_band9 += (long)Output3c_ds7[1] * Output3c_ds7[1]  >>  14;

						RMScount7++;

					}
					else if(RMScount7 >= 256){

						tempRMS_band7 /= 4;
						tempRMS_band8 /= 4;
						tempRMS_band9 /= 4;

						// OUTPUT HER
						if(tempRMS_band7 >= dB_table[old_dB7+1]){
							old_dB7++;
							if(old_dB7 > 36){
								old_dB7 = 36;
							}
						}
						else if(tempRMS_band7 <= dB_table[old_dB7-1]){
							old_dB7--;
							if(old_dB7 < 0){
								old_dB7 = 0;
							}
						}

						if(tempRMS_band8 >= dB_table[old_dB8+1]){
							old_dB8++;
							if(old_dB8 > 36){
								old_dB8 = 36;
							}
						}
						else if(tempRMS_band8 <= dB_table[old_dB8-1]){
							old_dB8--;
							if(old_dB8 < 0){
								old_dB8 = 0;
							}
						}

						if(tempRMS_band9 >= dB_table[old_dB9+1]){
							old_dB9++;
							if(old_dB9 > 36){
								old_dB9 = 36;
							}
						}
						else if(tempRMS_band9 <= dB_table[old_dB9-1]){
							old_dB9--;
							if(old_dB9 < 0){
								old_dB9 = 0;
							}
						}


						tempRMS_band7 = 0;
						tempRMS_band8 = 0;
						tempRMS_band9 = 0;
						RMScount7 = 0;
					}

	            	}
	            	if(DS_table[samplecount] == 514){  // M = 256


	            		DSbuffer8[0] = l_buffer[0];
					DSResult8 = (long)DSbuffer8[0] * filter_taps[0] + (long)DSbuffer8[1] * filter_taps[1] + (long)DSbuffer8[2] * filter_taps[2] + (long)DSbuffer8[3] * filter_taps[3] + (long)DSbuffer8[4] * filter_taps[4] + (long)DSbuffer8[5] * filter_taps[5] + (long)DSbuffer8[6] * filter_taps[6] + (long)DSbuffer8[7] * filter_taps[7] + (long)DSbuffer8[8] * filter_taps[8] + (long)DSbuffer8[9] * filter_taps[9] +
							  (long)DSbuffer8[10] * filter_taps[10] + (long)DSbuffer8[11] * filter_taps[11] + (long)DSbuffer8[12] * filter_taps[12] + (long)DSbuffer8[13] * filter_taps[13] + (long)DSbuffer8[14] * filter_taps[14] + (long)DSbuffer8[15] * filter_taps[15] + (long)DSbuffer8[16] * filter_taps[16] + (long)DSbuffer8[17] * filter_taps[17] + (long)DSbuffer8[18] * filter_taps[18] + (long)DSbuffer8[19] * filter_taps[19] +
							  (long)DSbuffer8[20] * filter_taps[20] + (long)DSbuffer8[21] * filter_taps[21] + (long)DSbuffer8[22] * filter_taps[22] + (long)DSbuffer8[23] * filter_taps[23] + (long)DSbuffer8[24] * filter_taps[24] + (long)DSbuffer8[25] * filter_taps[25] + (long)DSbuffer8[26] * filter_taps[26] + (long)DSbuffer8[27] * filter_taps[27] + (long)DSbuffer8[28] * filter_taps[28] + (long)DSbuffer8[29] * filter_taps[29] +
							  (long)DSbuffer8[30] * filter_taps[30] + (long)DSbuffer8[31] * filter_taps[31] + (long)DSbuffer8[32] * filter_taps[32] + (long)DSbuffer8[33] * filter_taps[33] + (long)DSbuffer8[34] * filter_taps[34] + (long)DSbuffer8[35] * filter_taps[35] + (long)DSbuffer8[36] * filter_taps[36] + (long)DSbuffer8[37] * filter_taps[37] + (long)DSbuffer8[38] * filter_taps[38] + (long)DSbuffer8[39] * filter_taps[39] +
							  (long)DSbuffer8[40] * filter_taps[40] + (long)DSbuffer8[41] * filter_taps[41] + (long)DSbuffer8[42] * filter_taps[42] + (long)DSbuffer8[43] * filter_taps[43] + (long)DSbuffer8[44] * filter_taps[44] + (long)DSbuffer8[45] * filter_taps[45] + (long)DSbuffer8[46] * filter_taps[46] + (long)DSbuffer8[47] * filter_taps[47] + (long)DSbuffer8[48] * filter_taps[48] + (long)DSbuffer8[49] * filter_taps[49] +
							  (long)DSbuffer8[50] * filter_taps[50] + (long)DSbuffer8[51] * filter_taps[51] + (long)DSbuffer8[52] * filter_taps[52] + (long)DSbuffer8[53] * filter_taps[53] + (long)DSbuffer8[54] * filter_taps[54] + (long)DSbuffer8[55] * filter_taps[55] + (long)DSbuffer8[56] * filter_taps[56] + (long)DSbuffer8[57] * filter_taps[57] + (long)DSbuffer8[58] * filter_taps[58] + (long)DSbuffer8[59] * filter_taps[59] +
							  (long)DSbuffer8[60] * filter_taps[60] + (long)DSbuffer8[61] * filter_taps[61] + (long)DSbuffer8[62] * filter_taps[62] + (long)DSbuffer8[63] * filter_taps[63] + (long)DSbuffer8[64] * filter_taps[64] + (long)DSbuffer8[65] * filter_taps[65] + (long)DSbuffer8[66] * filter_taps[66] + (long)DSbuffer8[67] * filter_taps[67] + (long)DSbuffer8[68] * filter_taps[68] + (long)DSbuffer8[69] * filter_taps[69] +
							  (long)DSbuffer8[70] * filter_taps[70] + (long)DSbuffer8[71] * filter_taps[71] + (long)DSbuffer8[72] * filter_taps[72] + (long)DSbuffer8[73] * filter_taps[73] + (long)DSbuffer8[74] * filter_taps[74] + (long)DSbuffer8[75] * filter_taps[75] + (long)DSbuffer8[76] * filter_taps[76] + (long)DSbuffer8[77] * filter_taps[77] + (long)DSbuffer8[78] * filter_taps[78] + (long)DSbuffer8[79] * filter_taps[79] +
							  (long)DSbuffer8[80] * filter_taps[80] + (long)DSbuffer8[81] * filter_taps[81] + (long)DSbuffer8[82] * filter_taps[82] + (long)DSbuffer8[83] * filter_taps[83] + (long)DSbuffer8[84] * filter_taps[84] + (long)DSbuffer8[85] * filter_taps[85] + (long)DSbuffer8[86] * filter_taps[86] + (long)DSbuffer8[87] * filter_taps[87] + (long)DSbuffer8[88] * filter_taps[88] + (long)DSbuffer8[89] * filter_taps[89] +
							  (long)DSbuffer8[90] * filter_taps[90] + (long)DSbuffer8[91] * filter_taps[91] + (long)DSbuffer8[92] * filter_taps[92] + (long)DSbuffer8[93] * filter_taps[93] + (long)DSbuffer8[94] * filter_taps[94] + (long)DSbuffer8[95] * filter_taps[95];


					 DSbuffer8[95] = DSbuffer8[94];
					 DSbuffer8[94] = DSbuffer8[93];
					 DSbuffer8[93] = DSbuffer8[92];
					 DSbuffer8[92] = DSbuffer8[91];
					 DSbuffer8[91] = DSbuffer8[90];
					 DSbuffer8[90] = DSbuffer8[89];
					 DSbuffer8[89] = DSbuffer8[88];
					 DSbuffer8[88] = DSbuffer8[87];
					 DSbuffer8[87] = DSbuffer8[86];
					 DSbuffer8[86] = DSbuffer8[85];
					 DSbuffer8[85] = DSbuffer8[84];
					 DSbuffer8[84] = DSbuffer8[83];
					 DSbuffer8[83] = DSbuffer8[82];
					 DSbuffer8[82] = DSbuffer8[81];
					 DSbuffer8[81] = DSbuffer8[80];
					 DSbuffer8[80] = DSbuffer8[79];
					 DSbuffer8[79] = DSbuffer8[78];
					 DSbuffer8[78] = DSbuffer8[77];
					 DSbuffer8[77] = DSbuffer8[76];
					 DSbuffer8[76] = DSbuffer8[75];
					 DSbuffer8[75] = DSbuffer8[74];
					 DSbuffer8[74] = DSbuffer8[73];
					 DSbuffer8[73] = DSbuffer8[72];
					 DSbuffer8[72] = DSbuffer8[71];
					 DSbuffer8[71] = DSbuffer8[70];
					 DSbuffer8[70] = DSbuffer8[69];
					 DSbuffer8[69] = DSbuffer8[68];
					 DSbuffer8[68] = DSbuffer8[67];
					 DSbuffer8[67] = DSbuffer8[66];
					 DSbuffer8[66] = DSbuffer8[65];
					 DSbuffer8[65] = DSbuffer8[64];
					 DSbuffer8[64] = DSbuffer8[63];
					 DSbuffer8[63] = DSbuffer8[62];
					 DSbuffer8[62] = DSbuffer8[61];
					 DSbuffer8[61] = DSbuffer8[60];
					 DSbuffer8[60] = DSbuffer8[59];
					 DSbuffer8[59] = DSbuffer8[58];
					 DSbuffer8[58] = DSbuffer8[57];
					 DSbuffer8[57] = DSbuffer8[56];
					 DSbuffer8[56] = DSbuffer8[55];
					 DSbuffer8[55] = DSbuffer8[54];
					 DSbuffer8[54] = DSbuffer8[53];
					 DSbuffer8[53] = DSbuffer8[52];
					 DSbuffer8[52] = DSbuffer8[51];
					 DSbuffer8[51] = DSbuffer8[50];
					 DSbuffer8[50] = DSbuffer8[49];
					 DSbuffer8[49] = DSbuffer8[48];
					 DSbuffer8[48] = DSbuffer8[47];
					 DSbuffer8[47] = DSbuffer8[46];
					 DSbuffer8[46] = DSbuffer8[45];
					 DSbuffer8[45] = DSbuffer8[44];
					 DSbuffer8[44] = DSbuffer8[43];
					 DSbuffer8[43] = DSbuffer8[42];
					 DSbuffer8[42] = DSbuffer8[41];
					 DSbuffer8[41] = DSbuffer8[40];
					 DSbuffer8[40] = DSbuffer8[39];
					 DSbuffer8[39] = DSbuffer8[38];
					 DSbuffer8[38] = DSbuffer8[37];
					 DSbuffer8[37] = DSbuffer8[36];
					 DSbuffer8[36] = DSbuffer8[35];
					 DSbuffer8[35] = DSbuffer8[34];
					 DSbuffer8[34] = DSbuffer8[33];
					 DSbuffer8[33] = DSbuffer8[32];
					 DSbuffer8[32] = DSbuffer8[31];
					 DSbuffer8[31] = DSbuffer8[30];
					 DSbuffer8[30] = DSbuffer8[29];
					 DSbuffer8[29] = DSbuffer8[28];
					 DSbuffer8[28] = DSbuffer8[27];
					 DSbuffer8[27] = DSbuffer8[26];
					 DSbuffer8[26] = DSbuffer8[25];
					 DSbuffer8[25] = DSbuffer8[24];
					 DSbuffer8[24] = DSbuffer8[23];
					 DSbuffer8[23] = DSbuffer8[22];
					 DSbuffer8[22] = DSbuffer8[21];
					 DSbuffer8[21] = DSbuffer8[20];
					 DSbuffer8[20] = DSbuffer8[19];
					 DSbuffer8[19] = DSbuffer8[18];
					 DSbuffer8[18] = DSbuffer8[17];
					 DSbuffer8[17] = DSbuffer8[16];
					 DSbuffer8[16] = DSbuffer8[15];
					 DSbuffer8[15] = DSbuffer8[14];
					 DSbuffer8[14] = DSbuffer8[13];
					 DSbuffer8[13] = DSbuffer8[12];
					 DSbuffer8[12] = DSbuffer8[11];
					 DSbuffer8[11] = DSbuffer8[10];
					 DSbuffer8[10] = DSbuffer8[9];
					 DSbuffer8[9] = DSbuffer8[8];
					 DSbuffer8[8] = DSbuffer8[7];
					 DSbuffer8[7] = DSbuffer8[6];
					 DSbuffer8[6] = DSbuffer8[5];
					 DSbuffer8[5] = DSbuffer8[4];
					 DSbuffer8[4] = DSbuffer8[3];
					 DSbuffer8[3] = DSbuffer8[2];
					 DSbuffer8[2] = DSbuffer8[1];
					 DSbuffer8[1] = DSbuffer8[0];

					DSResult8 >>= 14;


					DSOutput8 = (short)(DSResult8);

					input_ds8[0] = DSOutput8;

		//			ResultCW1_ds8 = (long)input_ds8[0]*b01CW + (long)input_ds8[1]*b11CW + (long)input_ds8[2]*b21CW - (long)OutputCW1_ds8[1]*a11CW - (long)OutputCW1_ds8[2]*a21CW;

					Result1a_ds8 = (long)input_ds8[0]*b01a + (long)input_ds8[1]*b11a + (long)input_ds8[2]*b21a - (long)Output1a_ds8[1]*a11a - (long)Output1a_ds8[2]*a21a + NSe1a_ds8[1];

					Result1b_ds8 = (long)input_ds8[0]*b01b + (long)input_ds8[1]*b11b + (long)input_ds8[2]*b21b - (long)Output1b_ds8[1]*a11b - (long)Output1b_ds8[2]*a21b + NSe1b_ds8[1];

					Result1c_ds8 = (long)input_ds8[0]*b01c + (long)input_ds8[1]*b11c + (long)input_ds8[2]*b21c - (long)Output1c_ds8[1]*a11c - (long)Output1c_ds8[2]*a21c + NSe1c_ds8[1];

					NSe1a_ds8[0] = Result1a_ds8 & 16383;

					NSe1b_ds8[0] = Result1b_ds8 & 16383;

					NSe1c_ds8[0] = Result1c_ds8 & 16383;

		//			OutputCW1_ds8[0] = (short)(ResultCW1_ds8 >> 13);

					Output1a_ds8[0] = (short)(Result1a_ds8 >> 14);

					Output1b_ds8[0] = (short)(Result1b_ds8 >> 14);

					Output1c_ds8[0] = (short)(Result1c_ds8 >> 14);

		//			inputCW2_ds8[0] = OutputCW1_ds8[0];

					input2a_ds8[0] = Output1a_ds8[0];

					input2b_ds8[0] = Output1b_ds8[0];

					input2c_ds8[0] = Output1c_ds8[0];

		//			ResultCW2_ds8 = (long)inputCW2_ds8[0]*b02CW + (long)inputCW2_ds8[1]*b12CW + (long)inputCW2_ds8[2]*b22CW - (long)OutputCW2_ds8[1]*a12CW - (long)OutputCW2_ds8[2]*a22CW;

					Result2a_ds8 = (long)input2a_ds8[0]*b02a + (long)input2a_ds8[1]*b12a + (long)input2a_ds8[2]*b22a - (long)Output2a_ds8[1]*a12a - (long)Output2a_ds8[2]*a22a + NSe2a_ds8[1];

					Result2b_ds8 = (long)input2b_ds8[0]*b02b + (long)input2b_ds8[1]*b12b + (long)input2b_ds8[2]*b22b - (long)Output2b_ds8[1]*a12b - (long)Output2b_ds8[2]*a22b + NSe2b_ds8[1];

					Result2c_ds8 = (long)input2c_ds8[0]*b02c + (long)input2c_ds8[1]*b12c + (long)input2c_ds8[2]*b22c - (long)Output2c_ds8[1]*a12c - (long)Output2c_ds8[2]*a22c + NSe2c_ds8[1];

					NSe2a_ds8[0] = Result2a_ds8 & 16383;

					NSe2b_ds8[0] = Result2b_ds8 & 16383;

					NSe2c_ds8[0] = Result2c_ds8 & 16383;

		//			OutputCW2_ds8[0] = (short)(ResultCW2_ds8 >> 13);

					Output2a_ds8[0] = (short)(Result2a_ds8 >> 14);

					Output2b_ds8[0] = (short)(Result2b_ds8 >> 14);

					Output2c_ds8[0] = (short)(Result2c_ds8 >> 14);

					input3a_ds8[0] = Output2a_ds8[0];

					input3b_ds8[0] = Output2b_ds8[0];

					input3c_ds8[0] = Output2c_ds8[0];

					Result3a_ds8 = (long)input3a_ds8[0]*b03a + (long)input3a_ds8[1]*b13a + (long)input3a_ds8[2]*b23a - (long)Output3a_ds8[1]*a13a - (long)Output3a_ds8[2]*a23a + NSe3a_ds8[1];

					Result3b_ds8 = (long)input3b_ds8[0]*b03b + (long)input3b_ds8[1]*b13b + (long)input3b_ds8[2]*b23b - (long)Output3b_ds8[1]*a13b - (long)Output3b_ds8[2]*a23b + NSe3b_ds8[1];

					Result3c_ds8 = (long)input3c_ds8[0]*b03c + (long)input3c_ds8[1]*b13c + (long)input3c_ds8[2]*b23c - (long)Output3c_ds8[1]*a13c - (long)Output3c_ds8[2]*a23c + NSe3c_ds8[1];

					NSe3a_ds8[0] = Result3a_ds8 & 16383;

					NSe3b_ds8[0] = Result3b_ds8 & 16383;

					NSe3c_ds8[0] = Result3c_ds8 & 16383;

					Output3a_ds8[0] = (short)(Result3a_ds8 >> 14);

					Output3b_ds8[0] = (short)(Result3b_ds8 >> 14);

					Output3c_ds8[0] = (short)(Result3c_ds8 >> 14);

					NSe1a_ds8[1] = NSe1a_ds8[0];
					NSe2a_ds8[1] = NSe2a_ds8[0];
					NSe3a_ds8[1] = NSe3a_ds8[0];

					NSe1b_ds8[1] = NSe1b_ds8[0];
					NSe2b_ds8[1] = NSe2b_ds8[0];
					NSe3b_ds8[1] = NSe3b_ds8[0];

					NSe1c_ds8[1] = NSe1c_ds8[0];
					NSe2c_ds8[1] = NSe2c_ds8[0];
					NSe3c_ds8[1] = NSe3c_ds8[0];

					input_ds8[2] = input_ds8[1];
					input_ds8[1] = input_ds8[0];

		//			inputCW2_ds8[2] = inputCW2_ds8[1];
		//			inputCW2_ds8[1] = inputCW2_ds8[0];

					input2a_ds8[2] = input2a_ds8[1];
					input3a_ds8[2] = input3a_ds8[1];

					input2b_ds8[2] = input2b_ds8[1];
					input3b_ds8[2] = input3b_ds8[1];

					input2c_ds8[2] = input2c_ds8[1];
					input3c_ds8[2] = input3c_ds8[1];

					input2a_ds8[1] = input2a_ds8[0];
					input3a_ds8[1] = input3a_ds8[0];

					input2b_ds8[1] = input2b_ds8[0];
					input3b_ds8[1] = input3b_ds8[0];

					input2c_ds8[1] = input2c_ds8[0];
					input3c_ds8[1] = input3c_ds8[0];

		//			OutputCW1_ds8[2] = OutputCW1_ds8[1];
		//			OutputCW1_ds8[1] = OutputCW1_ds8[0];
		//			OutputCW2_ds8[2] = OutputCW2_ds8[1];
		//			OutputCW2_ds8[1] = OutputCW2_ds8[0];

					Output1a_ds8[2] = Output1a_ds8[1];
					Output2a_ds8[2] = Output2a_ds8[1];
					Output3a_ds8[2] = Output3a_ds8[1];

					Output1b_ds8[2] = Output1b_ds8[1];
					Output2b_ds8[2] = Output2b_ds8[1];
					Output3b_ds8[2] = Output3b_ds8[1];

					Output1c_ds8[2] = Output1c_ds8[1];
					Output2c_ds8[2] = Output2c_ds8[1];
					Output3c_ds8[2] = Output3c_ds8[1];

					Output1a_ds8[1] = Output1a_ds8[0];
					Output2a_ds8[1] = Output2a_ds8[0];
					Output3a_ds8[1] = Output3a_ds8[0];

					Output1b_ds8[1] = Output1b_ds8[0];
					Output2b_ds8[1] = Output2b_ds8[0];
					Output3b_ds8[1] = Output3b_ds8[0];

					Output1c_ds8[1] = Output1c_ds8[0];
					Output2c_ds8[1] = Output2c_ds8[0];
					Output3c_ds8[1] = Output3c_ds8[0];

					if(RMScount8 < 256){

						tempRMS_band4 += (long)Output3a_ds8[1] * Output3a_ds8[1]  >>  14;
						tempRMS_band5 += (long)Output3b_ds8[1] * Output3b_ds8[1]  >>  14;
						tempRMS_band6 += (long)Output3c_ds8[1] * Output3c_ds8[1]  >>  14;

						RMScount8++;

					}
					else if(RMScount8 >= 256){

						tempRMS_band4 /= 4;
						tempRMS_band5 /= 4;
						tempRMS_band6 /= 4;

						// OUTPUT HER
						if(tempRMS_band4 >= dB_table[old_dB4+1]){
							old_dB4++;
							if(old_dB4 > 36){
								old_dB4 = 36;
							}

						}
						else if(tempRMS_band4 <= dB_table[old_dB4-1]){
							old_dB4--;
							if(old_dB4 < 0){
								old_dB4 = 0;
							}
						}


						if(tempRMS_band5 >= dB_table[old_dB5+1]){
							old_dB5++;
							if(old_dB5 > 36){
								old_dB5 = 36;
							}
						}
						else if(tempRMS_band5 <= dB_table[old_dB5-1]){
							old_dB5--;
							if(old_dB5 < 0){
								old_dB5 = 0;
							}
						}

						if(tempRMS_band6 >= dB_table[old_dB6+1]){
							old_dB6++;
							if(old_dB6 > 36){
								old_dB6 = 36;
							}
						}
						else if(tempRMS_band6 <= dB_table[old_dB6-1]){
							old_dB6--;
							if(old_dB6 < 0){
								old_dB6 = 0;
							}
						}




						tempRMS_band4 = 0;
						tempRMS_band5 = 0;
						tempRMS_band6 = 0;
						RMScount8 = 0;
					}

	            	}
	            	if(DS_table[samplecount] == 513){  // M = 512


					DSbuffer9[0] = l_buffer[0];
					DSResult9 = (long)DSbuffer9[0] * filter_taps[0] + (long)DSbuffer9[1] * filter_taps[1] + (long)DSbuffer9[2] * filter_taps[2] + (long)DSbuffer9[3] * filter_taps[3] + (long)DSbuffer9[4] * filter_taps[4] + (long)DSbuffer9[5] * filter_taps[5] + (long)DSbuffer9[6] * filter_taps[6] + (long)DSbuffer9[7] * filter_taps[7] + (long)DSbuffer9[8] * filter_taps[8] + (long)DSbuffer9[9] * filter_taps[9] +
							  (long)DSbuffer9[10] * filter_taps[10] + (long)DSbuffer9[11] * filter_taps[11] + (long)DSbuffer9[12] * filter_taps[12] + (long)DSbuffer9[13] * filter_taps[13] + (long)DSbuffer9[14] * filter_taps[14] + (long)DSbuffer9[15] * filter_taps[15] + (long)DSbuffer9[16] * filter_taps[16] + (long)DSbuffer9[17] * filter_taps[17] + (long)DSbuffer9[18] * filter_taps[18] + (long)DSbuffer9[19] * filter_taps[19] +
							  (long)DSbuffer9[20] * filter_taps[20] + (long)DSbuffer9[21] * filter_taps[21] + (long)DSbuffer9[22] * filter_taps[22] + (long)DSbuffer9[23] * filter_taps[23] + (long)DSbuffer9[24] * filter_taps[24] + (long)DSbuffer9[25] * filter_taps[25] + (long)DSbuffer9[26] * filter_taps[26] + (long)DSbuffer9[27] * filter_taps[27] + (long)DSbuffer9[28] * filter_taps[28] + (long)DSbuffer9[29] * filter_taps[29] +
							  (long)DSbuffer9[30] * filter_taps[30] + (long)DSbuffer9[31] * filter_taps[31] + (long)DSbuffer9[32] * filter_taps[32] + (long)DSbuffer9[33] * filter_taps[33] + (long)DSbuffer9[34] * filter_taps[34] + (long)DSbuffer9[35] * filter_taps[35] + (long)DSbuffer9[36] * filter_taps[36] + (long)DSbuffer9[37] * filter_taps[37] + (long)DSbuffer9[38] * filter_taps[38] + (long)DSbuffer9[39] * filter_taps[39] +
							  (long)DSbuffer9[40] * filter_taps[40] + (long)DSbuffer9[41] * filter_taps[41] + (long)DSbuffer9[42] * filter_taps[42] + (long)DSbuffer9[43] * filter_taps[43] + (long)DSbuffer9[44] * filter_taps[44] + (long)DSbuffer9[45] * filter_taps[45] + (long)DSbuffer9[46] * filter_taps[46] + (long)DSbuffer9[47] * filter_taps[47] + (long)DSbuffer9[48] * filter_taps[48] + (long)DSbuffer9[49] * filter_taps[49] +
							  (long)DSbuffer9[50] * filter_taps[50] + (long)DSbuffer9[51] * filter_taps[51] + (long)DSbuffer9[52] * filter_taps[52] + (long)DSbuffer9[53] * filter_taps[53] + (long)DSbuffer9[54] * filter_taps[54] + (long)DSbuffer9[55] * filter_taps[55] + (long)DSbuffer9[56] * filter_taps[56] + (long)DSbuffer9[57] * filter_taps[57] + (long)DSbuffer9[58] * filter_taps[58] + (long)DSbuffer9[59] * filter_taps[59] +
							  (long)DSbuffer9[60] * filter_taps[60] + (long)DSbuffer9[61] * filter_taps[61] + (long)DSbuffer9[62] * filter_taps[62] + (long)DSbuffer9[63] * filter_taps[63] + (long)DSbuffer9[64] * filter_taps[64] + (long)DSbuffer9[65] * filter_taps[65] + (long)DSbuffer9[66] * filter_taps[66] + (long)DSbuffer9[67] * filter_taps[67] + (long)DSbuffer9[68] * filter_taps[68] + (long)DSbuffer9[69] * filter_taps[69] +
							  (long)DSbuffer9[70] * filter_taps[70] + (long)DSbuffer9[71] * filter_taps[71] + (long)DSbuffer9[72] * filter_taps[72] + (long)DSbuffer9[73] * filter_taps[73] + (long)DSbuffer9[74] * filter_taps[74] + (long)DSbuffer9[75] * filter_taps[75] + (long)DSbuffer9[76] * filter_taps[76] + (long)DSbuffer9[77] * filter_taps[77] + (long)DSbuffer9[78] * filter_taps[78] + (long)DSbuffer9[79] * filter_taps[79] +
							  (long)DSbuffer9[80] * filter_taps[80] + (long)DSbuffer9[81] * filter_taps[81] + (long)DSbuffer9[82] * filter_taps[82] + (long)DSbuffer9[83] * filter_taps[83] + (long)DSbuffer9[84] * filter_taps[84] + (long)DSbuffer9[85] * filter_taps[85] + (long)DSbuffer9[86] * filter_taps[86] + (long)DSbuffer9[87] * filter_taps[87] + (long)DSbuffer9[88] * filter_taps[88] + (long)DSbuffer9[89] * filter_taps[89] +
							  (long)DSbuffer9[90] * filter_taps[90] + (long)DSbuffer9[91] * filter_taps[91] + (long)DSbuffer9[92] * filter_taps[92] + (long)DSbuffer9[93] * filter_taps[93] + (long)DSbuffer9[94] * filter_taps[94] + (long)DSbuffer9[95] * filter_taps[95];


					 DSbuffer9[95] = DSbuffer9[94];
					 DSbuffer9[94] = DSbuffer9[93];
					 DSbuffer9[93] = DSbuffer9[92];
					 DSbuffer9[92] = DSbuffer9[91];
					 DSbuffer9[91] = DSbuffer9[90];
					 DSbuffer9[90] = DSbuffer9[89];
					 DSbuffer9[89] = DSbuffer9[88];
					 DSbuffer9[88] = DSbuffer9[87];
					 DSbuffer9[87] = DSbuffer9[86];
					 DSbuffer9[86] = DSbuffer9[85];
					 DSbuffer9[85] = DSbuffer9[84];
					 DSbuffer9[84] = DSbuffer9[83];
					 DSbuffer9[83] = DSbuffer9[82];
					 DSbuffer9[82] = DSbuffer9[81];
					 DSbuffer9[81] = DSbuffer9[80];
					 DSbuffer9[80] = DSbuffer9[79];
					 DSbuffer9[79] = DSbuffer9[78];
					 DSbuffer9[78] = DSbuffer9[77];
					 DSbuffer9[77] = DSbuffer9[76];
					 DSbuffer9[76] = DSbuffer9[75];
					 DSbuffer9[75] = DSbuffer9[74];
					 DSbuffer9[74] = DSbuffer9[73];
					 DSbuffer9[73] = DSbuffer9[72];
					 DSbuffer9[72] = DSbuffer9[71];
					 DSbuffer9[71] = DSbuffer9[70];
					 DSbuffer9[70] = DSbuffer9[69];
					 DSbuffer9[69] = DSbuffer9[68];
					 DSbuffer9[68] = DSbuffer9[67];
					 DSbuffer9[67] = DSbuffer9[66];
					 DSbuffer9[66] = DSbuffer9[65];
					 DSbuffer9[65] = DSbuffer9[64];
					 DSbuffer9[64] = DSbuffer9[63];
					 DSbuffer9[63] = DSbuffer9[62];
					 DSbuffer9[62] = DSbuffer9[61];
					 DSbuffer9[61] = DSbuffer9[60];
					 DSbuffer9[60] = DSbuffer9[59];
					 DSbuffer9[59] = DSbuffer9[58];
					 DSbuffer9[58] = DSbuffer9[57];
					 DSbuffer9[57] = DSbuffer9[56];
					 DSbuffer9[56] = DSbuffer9[55];
					 DSbuffer9[55] = DSbuffer9[54];
					 DSbuffer9[54] = DSbuffer9[53];
					 DSbuffer9[53] = DSbuffer9[52];
					 DSbuffer9[52] = DSbuffer9[51];
					 DSbuffer9[51] = DSbuffer9[50];
					 DSbuffer9[50] = DSbuffer9[49];
					 DSbuffer9[49] = DSbuffer9[48];
					 DSbuffer9[48] = DSbuffer9[47];
					 DSbuffer9[47] = DSbuffer9[46];
					 DSbuffer9[46] = DSbuffer9[45];
					 DSbuffer9[45] = DSbuffer9[44];
					 DSbuffer9[44] = DSbuffer9[43];
					 DSbuffer9[43] = DSbuffer9[42];
					 DSbuffer9[42] = DSbuffer9[41];
					 DSbuffer9[41] = DSbuffer9[40];
					 DSbuffer9[40] = DSbuffer9[39];
					 DSbuffer9[39] = DSbuffer9[38];
					 DSbuffer9[38] = DSbuffer9[37];
					 DSbuffer9[37] = DSbuffer9[36];
					 DSbuffer9[36] = DSbuffer9[35];
					 DSbuffer9[35] = DSbuffer9[34];
					 DSbuffer9[34] = DSbuffer9[33];
					 DSbuffer9[33] = DSbuffer9[32];
					 DSbuffer9[32] = DSbuffer9[31];
					 DSbuffer9[31] = DSbuffer9[30];
					 DSbuffer9[30] = DSbuffer9[29];
					 DSbuffer9[29] = DSbuffer9[28];
					 DSbuffer9[28] = DSbuffer9[27];
					 DSbuffer9[27] = DSbuffer9[26];
					 DSbuffer9[26] = DSbuffer9[25];
					 DSbuffer9[25] = DSbuffer9[24];
					 DSbuffer9[24] = DSbuffer9[23];
					 DSbuffer9[23] = DSbuffer9[22];
					 DSbuffer9[22] = DSbuffer9[21];
					 DSbuffer9[21] = DSbuffer9[20];
					 DSbuffer9[20] = DSbuffer9[19];
					 DSbuffer9[19] = DSbuffer9[18];
					 DSbuffer9[18] = DSbuffer9[17];
					 DSbuffer9[17] = DSbuffer9[16];
					 DSbuffer9[16] = DSbuffer9[15];
					 DSbuffer9[15] = DSbuffer9[14];
					 DSbuffer9[14] = DSbuffer9[13];
					 DSbuffer9[13] = DSbuffer9[12];
					 DSbuffer9[12] = DSbuffer9[11];
					 DSbuffer9[11] = DSbuffer9[10];
					 DSbuffer9[10] = DSbuffer9[9];
					 DSbuffer9[9] = DSbuffer9[8];
					 DSbuffer9[8] = DSbuffer9[7];
					 DSbuffer9[7] = DSbuffer9[6];
					 DSbuffer9[6] = DSbuffer9[5];
					 DSbuffer9[5] = DSbuffer9[4];
					 DSbuffer9[4] = DSbuffer9[3];
					 DSbuffer9[3] = DSbuffer9[2];
					 DSbuffer9[2] = DSbuffer9[1];
					 DSbuffer9[1] = DSbuffer9[0];

					DSResult9 >>= 14;
					DSOutput9 = (short)(DSResult9);

					input_ds9[0] = DSOutput9;

//					ResultCW1_ds9 = (long)input_ds9[0]*b01CW + (long)input_ds9[1]*b11CW + (long)input_ds9[2]*b21CW - (long)OutputCW1_ds9[1]*a11CW - (long)OutputCW1_ds9[2]*a21CW;

					Result1a_ds9 = (long)input_ds9[0]*b01a + (long)input_ds9[1]*b11a + (long)input_ds9[2]*b21a - (long)Output1a_ds9[1]*a11a - (long)Output1a_ds9[2]*a21a + NSe1a_ds9[1];

					Result1b_ds9 = (long)input_ds9[0]*b01b + (long)input_ds9[1]*b11b + (long)input_ds9[2]*b21b - (long)Output1b_ds9[1]*a11b - (long)Output1b_ds9[2]*a21b + NSe1b_ds9[1];

					Result1c_ds9 = (long)input_ds9[0]*b01c + (long)input_ds9[1]*b11c + (long)input_ds9[2]*b21c - (long)Output1c_ds9[1]*a11c - (long)Output1c_ds9[2]*a21c + NSe1c_ds9[1];

					NSe1a_ds9[0] = Result1a_ds9 & 16383;

					NSe1b_ds9[0] = Result1b_ds9 & 16383;

					NSe1c_ds9[0] = Result1c_ds9 & 16383;

//					OutputCW1_ds9[0] = (short)(ResultCW1_ds9 >> 13);

					Output1a_ds9[0] = (short)(Result1a_ds9 >> 14);

					Output1b_ds9[0] = (short)(Result1b_ds9 >> 14);

					Output1c_ds9[0] = (short)(Result1c_ds9 >> 14);

//					inputCW2_ds9[0] = OutputCW1_ds9[0];

					input2a_ds9[0] = Output1a_ds9[0];

					input2b_ds9[0] = Output1b_ds9[0];

					input2c_ds9[0] = Output1c_ds9[0];

		//			ResultCW2_ds9 = (long)inputCW2_ds9[0]*b02CW + (long)inputCW2_ds9[1]*b12CW + (long)inputCW2_ds9[2]*b22CW - (long)OutputCW2_ds9[1]*a12CW - (long)OutputCW2_ds9[2]*a22CW;

					Result2a_ds9 = (long)input2a_ds9[0]*b02a + (long)input2a_ds9[1]*b12a + (long)input2a_ds9[2]*b22a - (long)Output2a_ds9[1]*a12a - (long)Output2a_ds9[2]*a22a + NSe2a_ds9[1];

					Result2b_ds9 = (long)input2b_ds9[0]*b02b + (long)input2b_ds9[1]*b12b + (long)input2b_ds9[2]*b22b - (long)Output2b_ds9[1]*a12b - (long)Output2b_ds9[2]*a22b + NSe2b_ds9[1];

					Result2c_ds9 = (long)input2c_ds9[0]*b02c + (long)input2c_ds9[1]*b12c + (long)input2c_ds9[2]*b22c - (long)Output2c_ds9[1]*a12c - (long)Output2c_ds9[2]*a22c + NSe2c_ds9[1];

					NSe2a_ds9[0] = Result2a_ds9 & 16383;

					NSe2b_ds9[0] = Result2b_ds9 & 16383;

					NSe2c_ds9[0] = Result2c_ds9 & 16383;

			//		OutputCW2_ds9[0] = (short)(ResultCW2_ds9 >> 13);

					Output2a_ds9[0] = (short)(Result2a_ds9 >> 14);

					Output2b_ds9[0] = (short)(Result2b_ds9 >> 14);

					Output2c_ds9[0] = (short)(Result2c_ds9 >> 14);

					input3a_ds9[0] = Output2a_ds9[0];

					input3b_ds9[0] = Output2b_ds9[0];

					input3c_ds9[0] = Output2c_ds9[0];

					Result3a_ds9 = (long)input3a_ds9[0]*b03a + (long)input3a_ds9[1]*b13a + (long)input3a_ds9[2]*b23a - (long)Output3a_ds9[1]*a13a - (long)Output3a_ds9[2]*a23a + NSe3a_ds9[1];

					Result3b_ds9 = (long)input3b_ds9[0]*b03b + (long)input3b_ds9[1]*b13b + (long)input3b_ds9[2]*b23b - (long)Output3b_ds9[1]*a13b - (long)Output3b_ds9[2]*a23b + NSe3b_ds9[1];

					Result3c_ds9 = (long)input3c_ds9[0]*b03c + (long)input3c_ds9[1]*b13c + (long)input3c_ds9[2]*b23c - (long)Output3c_ds9[1]*a13c - (long)Output3c_ds9[2]*a23c + NSe3c_ds9[1];

					NSe3a_ds9[0] = Result3a_ds9 & 16383;

					NSe3b_ds9[0] = Result3b_ds9 & 16383;

					NSe3c_ds9[0] = Result3c_ds9 & 16383;

					Output3a_ds9[0] = (short)(Result3a_ds9 >> 14);

					Output3b_ds9[0] = (short)(Result3b_ds9 >> 14);

					Output3c_ds9[0] = (short)(Result3c_ds9 >> 14);

					NSe1a_ds9[1] = NSe1a_ds9[0];
					NSe2a_ds9[1] = NSe2a_ds9[0];
					NSe3a_ds9[1] = NSe3a_ds9[0];

					NSe1b_ds9[1] = NSe1b_ds9[0];
					NSe2b_ds9[1] = NSe2b_ds9[0];
					NSe3b_ds9[1] = NSe3b_ds9[0];

					NSe1c_ds9[1] = NSe1c_ds9[0];
					NSe2c_ds9[1] = NSe2c_ds9[0];
					NSe3c_ds9[1] = NSe3c_ds9[0];

					input_ds9[2] = input_ds9[1];
					input_ds9[1] = input_ds9[0];

				//	inputCW2_ds9[2] = inputCW2_ds9[1];
				//	inputCW2_ds9[1] = inputCW2_ds9[0];

					input2a_ds9[2] = input2a_ds9[1];
					input3a_ds9[2] = input3a_ds9[1];

					input2b_ds9[2] = input2b_ds9[1];
					input3b_ds9[2] = input3b_ds9[1];

					input2c_ds9[2] = input2c_ds9[1];
					input3c_ds9[2] = input3c_ds9[1];

					input2a_ds9[1] = input2a_ds9[0];
					input3a_ds9[1] = input3a_ds9[0];

					input2b_ds9[1] = input2b_ds9[0];
					input3b_ds9[1] = input3b_ds9[0];

					input2c_ds9[1] = input2c_ds9[0];
					input3c_ds9[1] = input3c_ds9[0];

			//		OutputCW1_ds9[2] = OutputCW1_ds9[1];
			//		OutputCW1_ds9[1] = OutputCW1_ds9[0];
			//		OutputCW2_ds9[2] = OutputCW2_ds9[1];
			//		OutputCW2_ds9[1] = OutputCW2_ds9[0];

					Output1a_ds9[2] = Output1a_ds9[1];
					Output2a_ds9[2] = Output2a_ds9[1];
					Output3a_ds9[2] = Output3a_ds9[1];

					Output1b_ds9[2] = Output1b_ds9[1];
					Output2b_ds9[2] = Output2b_ds9[1];
					Output3b_ds9[2] = Output3b_ds9[1];

					Output1c_ds9[2] = Output1c_ds9[1];
					Output2c_ds9[2] = Output2c_ds9[1];
					Output3c_ds9[2] = Output3c_ds9[1];

					Output1a_ds9[1] = Output1a_ds9[0];
					Output2a_ds9[1] = Output2a_ds9[0];
					Output3a_ds9[1] = Output3a_ds9[0];

					Output1b_ds9[1] = Output1b_ds9[0];
					Output2b_ds9[1] = Output2b_ds9[0];
					Output3b_ds9[1] = Output3b_ds9[0];

					Output1c_ds9[1] = Output1c_ds9[0];
					Output2c_ds9[1] = Output2c_ds9[0];
					Output3c_ds9[1] = Output3c_ds9[0];

					if(RMScount9 < 256){

						tempRMS_band1 += (long)Output3a_ds9[1] * Output3a_ds9[1]  >>  14;
						tempRMS_band2 += (long)Output3b_ds9[1] * Output3b_ds9[1]  >>  14;
						tempRMS_band3 += (long)Output3c_ds9[1] * Output3c_ds9[1]  >>  14;

						RMScount9++;

					}
					else if(RMScount9 >= 256){

						tempRMS_band1 /= 4;
						tempRMS_band2 /= 4;
						tempRMS_band3 /= 4;

						// OUTPUT HER
						if(tempRMS_band1 >= dB_table[old_dB1+1]){
							old_dB1++;
							if(old_dB1 > 36){
								old_dB1 = 36;
							}
						}
						else if(tempRMS_band1 <= dB_table[old_dB1-1]){
							old_dB1--;
							if(old_dB1 < 0){
								old_dB1 = 0;
														}
						}

						if(tempRMS_band2 >= dB_table[old_dB2+1]){
							old_dB2++;
							if(old_dB2 > 36){
								old_dB2 = 36;
							}
						}
						else if(tempRMS_band2 <= dB_table[old_dB2-1]){
							old_dB2--;
							if(old_dB2 < 0){
								old_dB2 = 0;
														}
						}

						if(tempRMS_band3 >= dB_table[old_dB3+1]){
							old_dB3++;
							if(old_dB3 > 36){
								old_dB3 = 36;
							}
						}
						else if(tempRMS_band3 <= dB_table[old_dB3-1]){
							old_dB3--;
							if(old_dB3 < 0){
								old_dB3 = 0;
														}
						}



						tempRMS_band1 = 0;
						tempRMS_band2 = 0;
						tempRMS_band3 = 0;
						RMScount9 = 0;
					}

	            	}

	            	if(DS_table[samplecount] == 514){

	            		if(bandcount == 0){


	            		}


	            		if(bandcount == 1){


	            		}

	            		if(bandcount == 2){


	            		}

	            		if(bandcount == 3){


	            		}

	            		if(bandcount == 4){


	            		}
		            	if(bandcount == 5){


		            	}
						if(bandcount == 6){


						}
						if(bandcount == 7){


						}
						if(bandcount == 8){


						}
						if(bandcount == 9){


						}
						if(bandcount == 10){


						}
						if(bandcount == 11){


						}
						if(bandcount == 12){


						}
						if(bandcount == 13){


						}
						if(bandcount == 14){


						}
						if(bandcount == 15){


						}
						if(bandcount == 16){


						}
						if(bandcount == 17){


						}
						if(bandcount == 18){


						}
						if(bandcount == 19){


						}
						if(bandcount == 20){


						}
						if(bandcount == 21){

						}
						if(bandcount == 22){


						}
						if(bandcount == 23){


						}
						if(bandcount == 24){


						}
						if(bandcount == 25){


						}
						if(bandcount == 26){


						}
						if(bandcount == 27){


						}
						if(bandcount == 28){


						}
						if(bandcount == 29){


						}


						bandcount++;

						if(bandcount > 29){
							bandcount = 0;
						}

	            	}

	            	//asm(" MOV #(0xFF), 0x1D63");
					input1[0] = l_buffer[0];

					//ResultCW1 = (long)input1[0]*b01CW + (long)input1[1]*b11CW + (long)input1[2]*b21CW - (long)OutputCW1[1]*a11CW - (long)OutputCW1[2]*a21CW;

					Result1a = (long)input1[0]*b01a + (long)input1[1]*b11a + (long)input1[2]*b21a - (long)Output1a[1]*a11a - (long)Output1a[2]*a21a + NSe1a[1];

					Result1b = (long)input1[0]*b01b + (long)input1[1]*b11b + (long)input1[2]*b21b - (long)Output1b[1]*a11b - (long)Output1b[2]*a21b + NSe1b[1];

					Result1c = (long)input1[0]*b01c + (long)input1[1]*b11c + (long)input1[2]*b21c - (long)Output1c[1]*a11c - (long)Output1c[2]*a21c + NSe1c[1];

					NSe1a[0] = Result1a & 16383;

					NSe1b[0] = Result1b & 16383;

					NSe1c[0] = Result1c & 16383;

					//OutputCW1[0] = (short)(ResultCW1 >> 13);

					Output1a[0] = (short)(Result1a >> 14);

					Output1b[0] = (short)(Result1b >> 14);

					Output1c[0] = (short)(Result1c >> 14);

					//inputCW2[0] = OutputCW1[0];

					input2a[0] = Output1a[0];

					input2b[0] = Output1b[0];

					input2c[0] = Output1c[0];

					//ResultCW2 = (long)inputCW2[0]*b02CW + (long)inputCW2[1]*b12CW + (long)inputCW2[2]*b22CW - (long)OutputCW2[1]*a12CW - (long)OutputCW2[2]*a22CW;

					Result2a = (long)input2a[0]*b02a + (long)input2a[1]*b12a + (long)input2a[2]*b22a - (long)Output2a[1]*a12a - (long)Output2a[2]*a22a + NSe2a[1];

					Result2b = (long)input2b[0]*b02b + (long)input2b[1]*b12b + (long)input2b[2]*b22b - (long)Output2b[1]*a12b - (long)Output2b[2]*a22b + NSe2b[1];

					Result2c = (long)input2c[0]*b02c + (long)input2c[1]*b12c + (long)input2c[2]*b22c - (long)Output2c[1]*a12c - (long)Output2c[2]*a22c + NSe2c[1];

					NSe2a[0] = Result2a & 16383;

					NSe2b[0] = Result2b & 16383;

					NSe2c[0] = Result2c & 16383;

					//OutputCW2[0] = (short)(ResultCW2 >> 13);

					Output2a[0] = (short)(Result2a >> 14);

					Output2b[0] = (short)(Result2b >> 14);

					Output2c[0] = (short)(Result2c >> 14);

					input3a[0] = Output2a[0];

					input3b[0] = Output2b[0];

					input3c[0] = Output2c[0];

					Result3a = (long)input3a[0]*b03a + (long)input3a[1]*b13a + (long)input3a[2]*b23a - (long)Output3a[1]*a13a - (long)Output3a[2]*a23a + NSe3a[1];

					Result3b = (long)input3b[0]*b03b + (long)input3b[1]*b13b + (long)input3b[2]*b23b - (long)Output3b[1]*a13b - (long)Output3b[2]*a23b + NSe3b[1];

					Result3c = (long)input3c[0]*b03c + (long)input3c[1]*b13c + (long)input3c[2]*b23c - (long)Output3c[1]*a13c - (long)Output3c[2]*a23c + NSe3c[1];

					NSe3a[0] = Result3a & 16383;

					NSe3b[0] = Result3b & 16383;

					NSe3c[0] = Result3c & 16383;

					Output3a[0] = (short)(Result3a >> 14);

					Output3b[0] = (short)(Result3b >> 14);

					Output3c[0] = (short)(Result3c >> 14);

					NSe1a[1] = NSe1a[0];
					NSe2a[1] = NSe2a[0];
					NSe3a[1] = NSe3a[0];

					NSe1b[1] = NSe1b[0];
					NSe2b[1] = NSe2b[0];
					NSe3b[1] = NSe3b[0];

					NSe1c[1] = NSe1c[0];
					NSe2c[1] = NSe2c[0];
					NSe3c[1] = NSe3c[0];

					input1[2] = input1[1];
					input1[1] = input1[0];

					//inputCW2[2] = inputCW2[1];
					//inputCW2[1] = inputCW2[0];

					input2a[2] = input2a[1];
					input3a[2] = input3a[1];

					input2b[2] = input2b[1];
					input3b[2] = input3b[1];

					input2c[2] = input2c[1];
					input3c[2] = input3c[1];

					input2a[1] = input2a[0];
					input3a[1] = input3a[0];

					input2b[1] = input2b[0];
					input3b[1] = input3b[0];

					input2c[1] = input2c[0];
					input3c[1] = input3c[0];

					//OutputCW1[2] = OutputCW1[1];
					//OutputCW1[1] = OutputCW1[0];
					//OutputCW2[2] = OutputCW2[1];
					//OutputCW2[1] = OutputCW2[0];

					Output1a[2] = Output1a[1];
					Output2a[2] = Output2a[1];
					Output3a[2] = Output3a[1];

					Output1b[2] = Output1b[1];
					Output2b[2] = Output2b[1];
					Output3b[2] = Output3b[1];

					Output1c[2] = Output1c[1];
					Output2c[2] = Output2c[1];
					Output3c[2] = Output3c[1];

					Output1a[1] = Output1a[0];
					Output2a[1] = Output2a[0];
					Output3a[1] = Output3a[0];

					Output1b[1] = Output1b[0];
					Output2b[1] = Output2b[0];
					Output3b[1] = Output3b[0];

					Output1c[1] = Output1c[0];
					Output2c[1] = Output2c[0];
					Output3c[1] = Output3c[0];

					if(RMScount < 256){

						tempRMS_band28 += (long)Output3a[1] * Output3a[1]  >>  14;
						tempRMS_band29 += (long)Output3b[1] * Output3b[1]  >>  14;
						tempRMS_band30 += (long)Output3c[1] * Output3c[1]  >>  14;

						RMScount++;

					}
					else if(RMScount >= 256){

						tempRMS_band28 /= 4;
						tempRMS_band29 /= 4;
						tempRMS_band30 /= 4;

						// OUTPUT HER
						if(tempRMS_band28 >= dB_table[old_dB28+1]){
							old_dB28++;
							if(old_dB28 > 36){
								old_dB28 = 36;
							}
						}
						else if(tempRMS_band28 <= dB_table[old_dB28-1]){
							old_dB28--;
							if(old_dB28 < 0){
								old_dB28 = 0;
														}
						}

						if(tempRMS_band29 >= dB_table[old_dB29+1]){
							old_dB29++;
							if(old_dB29 > 36){
								old_dB29 = 36;
							}
						}
						else if(tempRMS_band29 <= dB_table[old_dB29-1]){
							old_dB29--;
							if(old_dB29 < 0){
								old_dB29 = 0;
														}
						}

						if(tempRMS_band30 >= dB_table[old_dB30+1]){
							old_dB30++;
							if(old_dB30 > 36){
								old_dB30 = 36;
							}
						}
						else if(tempRMS_band30 <= dB_table[old_dB30-1]){
							old_dB30--;
							if(old_dB30 < 0){
								old_dB30 = 0;
														}
						}


						tempRMS_band28 = 0;
						tempRMS_band29 = 0;
						tempRMS_band30 = 0;
						RMScount = 0;
					}

*/
					//asm(" bclr XF");
	            	/* Write Digital audio */

	            	while((Xmit & I2S0_IR) == 0);// Wait for interrupt pending flag

	            	I2S0_W0_MSW_W = 0;  // 16 bit left channel transmit audio data

	            	I2S0_W0_LSW_W = 0;

	            	I2S0_W1_MSW_W = 0;  // 16 bit right channel transmit audio data

	            	I2S0_W1_LSW_W = 0;

	            	samplecount++;

	            	if(samplecount == 1024){
	            	samplecount = 0;
	            	}

	        }

}
