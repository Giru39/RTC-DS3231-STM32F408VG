/*
 * RTC-DS3231.c
 *
 *  Utiliza la  libreria I2C1 de mikrokontroller
 *
 */
#include "RTC-DS3231.h"

void RTC_INIT(void)
{
	//UB_I2C1_Init(); ESTA COMENTADO XQ YA INICIE EL I2C CON EL LCD..,
	UB_I2C1_WriteByte(ADDRESS , REG_SEG , 0x00);
	UB_I2C1_WriteByte(ADDRESS , REG_MIN , 0x00);
	UB_I2C1_WriteByte(ADDRESS , REG_HOR , 0x00);
	UB_I2C1_WriteByte(ADDRESS , REG_CONTROL , 0x00);
	UB_I2C1_WriteByte(ADDRESS , REG_CONTROL_STATUS , 0x00);
}
BYTE RTC_PAUSE(void) //pausa el oscilador del rtc (devuelve el registro de status para saber si se detuvo correctamente
{
	uint8_t aux;
	UB_I2C1_WriteByte(ADDRESS , REG_CONTROL_STATUS , 0x00);
	UB_I2C1_WriteByte(ADDRESS , REG_CONTROL , 0x00);
	aux=UB_I2C1_ReadByte(ADDRESS, REG_CONTROL_STATUS);
	return aux;

}
void RTC_START(reloj_t rolex) //inicia el oscilador desde la hora indicada
{
	uint8_t uni=0,dec=0,aux=0;
	dec=rolex.seg/10;
	uni=rolex.seg-dec*10;
	aux=(dec<<4)|uni;
	UB_I2C1_WriteByte(ADDRESS , REG_SEG , aux);
	dec=rolex.min/10;
	uni=rolex.min-dec*10;
	aux=(dec<<4)|uni;
	UB_I2C1_WriteByte(ADDRESS , REG_MIN , aux);
	dec=rolex.hora/10;
	uni=rolex.hora-dec*10;
	aux=(dec<<4)|uni;
	UB_I2C1_WriteByte(ADDRESS , REG_HOR , aux);
	UB_I2C1_WriteByte(ADDRESS , REG_CONTROL_STATUS , 0x00);
	UB_I2C1_WriteByte(ADDRESS , REG_CONTROL , 0x00);
}
reloj_t read_time(void) 
{

	BYTE aux,aux2=0;
	reloj_t reloj={0,0,0};
	aux=UB_I2C1_ReadByte(ADDRESS, REG_SEG);
	aux2=(aux>>4)*10+(aux&READ_UNIT);
	reloj.seg=aux2;
	aux=UB_I2C1_ReadByte(ADDRESS, REG_MIN);
	aux2=(aux>>4)*10+(aux&READ_UNIT);
	reloj.min=aux2;
	aux=UB_I2C1_ReadByte(ADDRESS, REG_HOR);
	aux2=(aux>>4)*10+(aux&READ_UNIT);
	reloj.hora=aux2;
	return reloj;
}
/* conviene que devuelva un puntero..
fecha_t *read_fecha(void)
{
	uint8_t aux,aux2;
	fecha_t fech;
	uint8_t masc=0x7f;// mascara para quitarle el bit del siglo..
	aux=UB_I2C1_ReadByte(ADDRESS, REG_DATE);
	aux2=(aux>>4)*10+(aux&READ_UNIT);
	fech.dia=aux2;
	aux=UB_I2C1_ReadByte(ADDRESS, REG_MONTH);
	aux2=((aux&masc)>>4)*10+(aux&READ_UNIT);
	fech.mes=aux2;
	aux=UB_I2C1_ReadByte(ADDRESS, REG_YEAR);
	aux2=(aux>>4)*10+(aux&READ_UNIT);
	fech.year=aux2;
	// si queres usar el bit de siglo descomenta este bloque
// 		aux=UB_I2C1_ReadByte(ADDRESS, REG_MONTH);
//		aux2=aux>>7; //solo puede ser 0 o 1
//		fech.siglo=aux2;

	return fech;
}
 */
