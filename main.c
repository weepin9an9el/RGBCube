#define F_CPU 20000000UL

#include <avr/io.h>
#include <util/delay.h>

#define srclockPin PC3
#define srlatchPin PC4
#define dataPin PC5

/*This array is merely turning on each color of each LED plane by plane.  Basically just mapping all the possible 1's and 0's to make 
//sure each LED gets a turn to come on.
*/
	uint32_t testarray[] =   {0x8000000C, 0x4000000C, 0x2000000C, 0x1000000C,
				  0x0800000C, 0x0400000C, 0x0200000C, 0x0100000C,
				  0x0080000C, 0x0040000C, 0x0020000C, 0x0010000C,
				  0x0008000C, 0x0004000C, 0x0002000C, 0x0001000C,
				  0x0000800C, 0x0000400C, 0x0000200C, 0x0000100C,
				  0x0000080C, 0x0000040C, 0x0000020C, 0x0000010C,
				  0x0000008C, 0x0000004C, 0x0000002C,  //end of first level

				  0x80000014, 0x40000014, 0x20000014, 0x10000014,
				  0x08000014, 0x04000014, 0x02000014, 0x01000014,
				  0x00800014, 0x00400014, 0x00200014, 0x00100014,
				  0x00080014, 0x00040014, 0x00020014, 0x00010014,
				  0x00008014, 0x00004014, 0x00002014, 0x00001014,
				  0x00000814, 0x00000414, 0x00000214, 0x00000114,
				  0x00000094, 0x00000054, 0x00000034, //end of second level

				  0x80000018, 0x40000018, 0x20000018, 0x10000018,
				  0x08000018, 0x04000018, 0x02000018, 0x01000018,
				  0x00800018, 0x00400018, 0x00200018, 0x00100018,
				  0x00080018, 0x00040018, 0x00020018, 0x00010018,
				  0x00008018, 0x00004018, 0x00002018, 0x00001018,
				  0x00000818, 0x00000418, 0x00000218, 0x00000118,
				  0x00000098, 0x00000058, 0x00000038}; //end of third level


void latch(void)
{
	PORTC &= ~(1<<srlatchPin);
	PORTC |= (1<<srlatchPin);
} //end of latch function


void shiftval(uint32_t value, uint8_t delaytime, uint8_t dtype)
{
	uint8_t j;

	for (j=0; j<32; j++) //this loop checks each of the 32 bits to see which is set
	{
		if (value & 0x01)
			PORTC |= (1<<dataPin); //value is a 1, so shift a 1
		else
			PORTC &= ~(1<<dataPin); //value is a 0, so shift a 0
		PORTC |= (1<<srclockPin);
		PORTC &= ~(1<<srclockPin);
		value >>= 1;
	} //end of "j" for loop
	latch();

	if (dtype == 1)
	{
		while (delaytime>0)
		{	
			_delay_ms(1);
			delaytime--;
		}
	}
	else
	{
		while (delaytime>0)
		{
			_delay_us(1);
			delaytime--;
		}
	}

} //end of shiftval function



void setup()
{
	DDRC |= (1<<srclockPin) | (1<<srlatchPin) | (1<<dataPin); //set shift register pins to outputs
	PORTC = 0X00;
} //end of setup function

void seqorder()
{
	uint8_t i, dt=150, dtype=1;

	for (i=0; i<81; i++)
	{ //this loop goes through each of the 81 values in the array
		shiftval(testarray[i], dt, dtype);
	} //end of "i" for loop cycling through the 81 possible values

}

void hor_wave()
{
	uint8_t i, dt=200, dtype=1;
	uint32_t testval = 0x00000000;

//bottom row red, left to right
	for (i=0; i<19; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

	for (i=3; i<22; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

	for (i=6; i<25; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

//middle row green, right to left
	for (i=34; i<53; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

	for (i=31; i<50; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

	for (i=28; i<47; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

//upper row blue, left to right
	for (i=56; i<75; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

	for (i=59; i<78; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

	for (i=62; i<81; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

//middle row green, right to left
	for (i=34; i<53; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

	for (i=31; i<50; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

	for (i=28; i<47; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

//bottom row red, left to right
	for (i=0; i<19; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

	for (i=3; i<22; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

	for (i=6; i<25; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

} //end of wave


void random()
{
	uint8_t i, dt=100, dtype=1;
//	uint32_t testval = 0x00000000;

//	i = (rand() % 82);
//	testval=testarray[i];

	for (i=0; i<26; i++)
	shiftval(testarray[(rand() %82)], dt, dtype);

}

void box()
{
	uint8_t i, dt, dtype;
	uint32_t testval = 0x00000000;

//front, left to right
	
	for (i=200; i>0; i--)
	{
		shiftval(testarray[0], 50, 2);
		shiftval(testarray[27], 50, 2);
		shiftval(testarray[54], 50, 2);
		_delay_ms(1);
	}

/*	testval = 0x00000000;

	for (i=3; i<22; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

	for (i=6; i<25; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

//middle row green, right to left
	for (i=34; i<53; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

	for (i=31; i<50; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

	for (i=28; i<47; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

//upper row blue, left to right
	for (i=56; i<75; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

	for (i=59; i<78; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

	for (i=62; i<81; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

//middle row green, right to left
	for (i=34; i<53; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

	for (i=31; i<50; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

	for (i=28; i<47; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

//bottom row red, left to right
	for (i=0; i<19; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

	for (i=3; i<22; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;

	for (i=6; i<25; i+=9)
		testval |= testarray[i];
	shiftval(testval, dt, dtype);

	testval = 0x00000000;
*/
} //end of box;

void main()
{
	setup();

	while (1) //infinite loop
	{
		hor_wave();
		random();
		box();
	} //end of while (1) loop


} //end of main function


