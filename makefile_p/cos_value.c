#include <stdio.h>
#define pi 3.14159
float angle;

void cos_value(void)
{
	float value;
	value = 100; // cos ( angle / 180. * pi );
	printf ("The Cos is: %5.2f\n",value);
}