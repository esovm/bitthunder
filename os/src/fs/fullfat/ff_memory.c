/*
 * FreeRTOS+FAT Labs Build 150406 (C) 2015 Real Time Engineers ltd.
 * Authors include James Walmsley, Hein Tibosch and Richard Barry
 *
 *******************************************************************************
 ***** NOTE ******* NOTE ******* NOTE ******* NOTE ******* NOTE ******* NOTE ***
 ***                                                                         ***
 ***                                                                         ***
 ***   FREERTOS+FAT IS STILL IN THE LAB:                                     ***
 ***                                                                         ***
 ***   This product is functional and is already being used in commercial    ***
 ***   products.  Be aware however that we are still refining its design,    ***
 ***   the source code does not yet fully conform to the strict coding and   ***
 ***   style standards mandated by Real Time Engineers ltd., and the         ***
 ***   documentation and testing is not necessarily complete.                ***
 ***                                                                         ***
 ***   PLEASE REPORT EXPERIENCES USING THE SUPPORT RESOURCES FOUND ON THE    ***
 ***   URL: http://www.FreeRTOS.org/contact  Active early adopters may, at   ***
 ***   the sole discretion of Real Time Engineers Ltd., be offered versions  ***
 ***   under a license other than that described below.                      ***
 ***                                                                         ***
 ***                                                                         ***
 ***** NOTE ******* NOTE ******* NOTE ******* NOTE ******* NOTE ******* NOTE ***
 *******************************************************************************
 *
 * - Open source licensing -
 * While FreeRTOS+FAT is in the lab it is provided only under version two of the
 * GNU General Public License (GPL) (which is different to the standard FreeRTOS
 * license).  FreeRTOS+FAT is free to download, use and distribute under the
 * terms of that license provided the copyright notice and this text are not
 * altered or removed from the source files.  The GPL V2 text is available on
 * the gnu.org web site, and on the following
 * URL: http://www.FreeRTOS.org/gpl-2.0.txt.  Active early adopters may, and
 * solely at the discretion of Real Time Engineers Ltd., be offered versions
 * under a license other then the GPL.
 *
 * FreeRTOS+FAT is distributed in the hope that it will be useful.  You cannot
 * use FreeRTOS+FAT unless you agree that you use the software 'as is'.
 * FreeRTOS+FAT is provided WITHOUT ANY WARRANTY; without even the implied
 * warranties of NON-INFRINGEMENT, MERCHANTABILITY or FITNESS FOR A PARTICULAR
 * PURPOSE. Real Time Engineers Ltd. disclaims all conditions and terms, be they
 * implied, expressed, or statutory.
 *
 * 1 tab == 4 spaces!
 *
 * http://www.FreeRTOS.org
 * http://www.FreeRTOS.org/plus
 * http://www.FreeRTOS.org/labs
 *
 */

/**
 *	@file		ff_memory.c
 *	@ingroup	MEMORY
 *
 *	@defgroup	MEMORY	FreeRTOS+FAT Memory Access Routines
 *	@brief		Handles memory access in a portable way.
 *
 *	Provides simple, fast, and portable access to memory routines.
 *	These are only used to read data from buffers. That are LITTLE ENDIAN
 *	due to the FAT specification.
 *
 *	These routines may need to be modified to your platform.
 *
 **/

#include "ff_headers.h"

/*
 * Here below 3 x 2 access functions that allow the code
 * not to worry about the endianness of the MCU.
 */


#if( ffconfigINLINE_MEMORY_ACCESS == 0 )

uint8_t FF_getChar( const uint8_t *pBuffer, uint32_t aOffset )
{
	return ( uint8_t ) ( pBuffer[ aOffset ] );
}

uint16_t FF_getShort( const uint8_t *pBuffer, uint32_t aOffset )
{
FF_T_UN16 u16;

	pBuffer += aOffset;
	u16.bytes.u8_1 = pBuffer[ 1 ];
	u16.bytes.u8_0 = pBuffer[ 0 ];

	return u16.u16;
}

uint32_t FF_getLong( const uint8_t *pBuffer, uint32_t aOffset )
{
FF_T_UN32 u32;

	pBuffer += aOffset;
	u32.bytes.u8_3 = pBuffer[ 3 ];
	u32.bytes.u8_2 = pBuffer[ 2 ];
	u32.bytes.u8_1 = pBuffer[ 1 ];
	u32.bytes.u8_0 = pBuffer[ 0 ];

	return u32.u32;
}

void FF_putChar( uint8_t *pBuffer, uint32_t aOffset, uint32_t Value )
{
	pBuffer[ aOffset ] = ( uint8_t ) Value;
}

void FF_putShort( uint8_t *pBuffer, uint32_t aOffset, uint32_t Value )
{
FF_T_UN16 u16;

	u16.u16 = ( uint16_t ) Value;
	pBuffer += aOffset;
	pBuffer[ 0 ] = u16.bytes.u8_0;
	pBuffer[ 1 ] = u16.bytes.u8_1;
}

void FF_putLong( uint8_t *pBuffer, uint32_t aOffset, uint32_t Value )
{
FF_T_UN32 u32;

	u32.u32 = Value;
	pBuffer += aOffset;
	pBuffer[ 0 ] = u32.bytes.u8_0;
	pBuffer[ 1 ] = u32.bytes.u8_1;
	pBuffer[ 2 ] = u32.bytes.u8_2;
	pBuffer[ 3 ] = u32.bytes.u8_3;
}

#endif
