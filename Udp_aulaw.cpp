#include "Udp.h"

/*
 *  0- muLaw
 *  8 - ALaw ( best level for analog mode !!!)
 * 96 - Uncompress
 */

const qint16 MULAW_MAX = 0x1FFF;
const qint16 MULAW_BIAS = 33;
const quint16 ALAW_MAX = 0xFFF;

static quint16 mask;
static quint8  sign;
static quint8  position;
static quint8  lsb;
static qint16  decoded;
static qint16  temp;

qint8 Udp::MuLaw_Encode(qint16 number)
{
	//temp = number;
	//number = (temp << 8) | ((temp >> 8) & 0xFF); // inversion!!!
	mask = 0x1000;
	sign = 0;
	position = 12;
	lsb = 0;
	if (number < 0)
	{
		number = -number;
		sign = 0x80;
	}
	number += MULAW_BIAS;
	if (number > MULAW_MAX)
	{
		number = MULAW_MAX;
	}
	for (; ((number & mask) != mask && position >= 5); mask >>= 1, position--) ;
	lsb = (number >> (position - 4)) & 0x0f;
	return (~(sign | ((position - 5) << 4) | lsb));
}

qint16 Udp::MuLaw_Decode(qint8 number)
{
	sign = 0;
	position = 0;
	decoded = 0;
	number = ~number;
	if (number & 0x80)
	{
		number &= ~(1 << 7);
		sign = -1;
	}
	position = ((number & 0xF0) >> 4) + 5;
	decoded = ((1 << position) | ((number & 0x0F) << (position - 4))
	          | (1 << (position - 5))) - MULAW_BIAS;
	//return (sign == 0) ? (decoded) : (-(decoded));
	(sign == 0) ? (temp = decoded) : (temp = -(decoded));
	return temp;//(decoded = (temp << 8) | ((temp >> 8) & 0xFF));
}


qint8 Udp::ALaw_Encode(qint16 number)
{
	temp = number;
	number = (temp << 8) | ((temp >> 8) & 0xFF);
	mask = 0x800;
	sign = 0;
	position = 11;
	lsb = 0;
	if (number < 0)
	{
		number = -number;
		sign = 0x80;
	}
	if (number > ALAW_MAX)
	{
		number = ALAW_MAX;
	}
	for (; ((number & mask) != mask && position >= 5); mask >>= 1, position--) ;
	lsb = (number >> ((position == 4) ? (1) : (position - 4))) & 0x0f;
	return (sign | ((position - 4) << 4) | lsb) ^ 0x55;
}

qint16 Udp::ALaw_Decode(qint8 number)
{
	sign = 0x00;
	position = 0;
	decoded = 0;
	number ^= 0x55;
	if (number & 0x80)
	{
		number &= ~(1 << 7);
		sign = -1;
	}
	position = ((number & 0xF0) >> 4) + 4;
	if (position != 4)
	{
		decoded = ((1 << position) | ((number & 0x0F) << (position - 4))
		          | (1 << (position - 5)));
	}
	else
	{
		decoded = (number << 1) | 1;
	}
	//return (sign==0)?(decoded):(-decoded);
	(sign == 0) ? (temp = decoded) : (temp = -(decoded));
	return (decoded = (temp << 8) | ((temp >> 8) & 0xFF));
}
