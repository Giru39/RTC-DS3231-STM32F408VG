/*
 * RTC-DS3231.h
 *
 *  Created on: 29 oct. 2019
 */

#ifndef RTC_DS3231_H_
#define RTC_DS3231_H_

#include"stm32f4xx_gpio.h"
#include "math.h"
#include "integer.h"
#include "stm32f4xx.h"
#include "stm32_ub_i2c1.h"

#define ADDRESS 0xd0 //direccion q usa el modulo

#define REG_SEG 0x00 //registro de los seg... bits 6 a 4 son decenas de seg, bits 3 a 0 unidades de seg
#define REG_MIN 0x01 //registro de los min... bits 6 a 4 son decenas de MIN, bits 3 a 0 unidades de MIN
#define REG_HOR 0x02 //registro de las horas bit6=1 para formato de 12 horas y 0 para 24, si bit6=1 -> bit5=1 para PM y 0 para AM, si no bit5 es para las decenas de las horas
#define REG_CONTROL 0x0E
//registro de control, bit7 habilita con 0 al oscilador. bit6=1 habilita sqw para usar la bateria
//bit5=1 habilita la conv de temp. bit4 y 3 selecionan la frec de la sqw (ver datasheet).
//bit2=0 habilita la salida sqw. 1 para las salidas de las alarmas.(es el mismo pin)
//bit1=1 habilita la alarma 2, bit0 la alarma 1, trabajan de la misma forma.

#define REG_CONTROL_STATUS 0x0F //bit7 es para saber si el oscilador se para,
//bit 3 es para habilitar la salida de 32khz, bit 2 es el flag BSY
//para cuando esta conviertiendo temp, bit 1 es flag de A2, bit0 flag A1


/* COMENTO TODOS LOS DEMAS REGISTROS XQ NO LOS USO
 #define REG_DAY_WEEK 0x03 //es el registro de los dias de la semana... varia de forma ciclica entre 1-7 y el usuario debe de definir que valores de este registro sera tal dia
 #define REG_DATE 0x04 //registro de los dias del mes (0-31).. automaticamente cambia de mes para aquellos meses que tienen menos de 31 dias

 #define REG_MONTH 0x05 //registro de los meses, bit 7 del siglo para cuando cambia del año 99 a 00, bit4 para las decenas de meses, bit3 a 0 para las unidad de meses
 #define REG_YEAR 0x06 //registro de los años bit 7 a 4 para las decenas de años, y bits 3 a 0 para las unidad de años
 #define A1_SEG 0x07 //registro de la alarma 1 para segundos
 #define A1_MIN 0x08 //registro de la alarma 1 para minutos
 #define A1_HOR 0x09 //registro de la alarma 1 para horas
 #define A1_DATE 0x0A //registro de la alarma 1 para dias. bit6=1 para dia de la semana, 0 para dia del mes
 #define A2_MIN 0x0B //alarma 2
 #define A2_HOR 0x0C //alarma 2
 #define A2_DATE 0x0D //alarma 2

 #define REG_AGING_OFFSET 0x10 //no entendi lo q hace 

 #define REG_TEMP_MSB 0x11 //bit7 el signo, el resto es la temperatura a la que esta trabajando el cristal
 #define REG_TEMP_LSB 0x12 //solo se usan los bits7 y 6 de este registro.
*/

#define READ_UNIT 0X0F //mascara para leer unidades

typedef struct
{
	uint8_t seg;
	uint8_t min;
	uint8_t hora;
}reloj_t;
/*
typedef struct
{
	uint8_t dia;
	uint8_t mes;
	uint8_t year;//lo puse en ingles por que no se puede tener una var con ñ
//	uint8_t siglo;  //si queres manejar el siglo podes descomentar esto
}fecha_t;
*/

void RTC_INIT(void);
reloj_t read_time(void);
BYTE RTC_PAUSE(void);
void RTC_START(reloj_t rolex);
// fecha_t read_fecha(void);




#endif /* RTC_DS3231_H_ */
