/* Includes */
#include <stdio.h>
#include "stm32f4xx.h"
#include "stm32f4xx_hal.h"

extern UART_HandleTypeDef huart2;

/*----------------------------------------------------------------------------
  SendChar
  Write character to Serial Port.
 *----------------------------------------------------------------------------*/
unsigned char SendChar (unsigned char ch)
{
    char temp = '\r';

    if (ch=='\n')
    {
        HAL_UART_Transmit(&huart2, (uint8_t *)&temp, 1, 1000);
    }

    HAL_UART_Transmit(&huart2, (uint8_t *)&ch, 1, 1000);

  	return (ch);
}

/**
 * @brief         UART0_PutChar
 * @param[in]     void
 * @param[in,out] void
 * @return        void
 */
void UART_PutChar(char c)
{
    HAL_UART_Transmit(&huart2, (uint8_t *)&c, 1, 1000);
}

/**
 * @brief         UART0_GetChar
 * @param[in]     void
 * @param[in,out] void
 * @return        char
 */
char UART_GetChar(void)
{
    uint8_t c;

    HAL_UART_Receive(&huart2, &c, 1, 1000);

    return (char)c;
}

#if defined ( __CC_ARM )

/**
 * @brief file handle structure
 */
struct __FILE
{
	int handle;
};

FILE __stdout;
FILE __stdin;

/**
 * @brief         fputc
 * @param[in]     void
 * @param[in,out] void
 * @return        char
 */
int fputc(int ch, FILE *f)
{
  UART_PutChar((char)ch);
  return((int)ch);
}

/**
 * @brief         fgetc
 * @param[in]     void
 * @param[in,out] void
 * @return        char
 */
int fgetc(FILE *f) {

	char c;
	/* get key */
	c =  UART_GetChar();
	/* print echo */
	UART_PutChar(c);
  return (int)c;
}

#elif defined ( __GNUC__ )
/*----------------------------------------------------------------------------
  _read
  Read characters from Serial Port.
 *----------------------------------------------------------------------------*/
int _read (int fd, const void *buf, size_t count)
{
  return 0;
}

/*----------------------------------------------------------------------------
  _write
  Write characters to Serial Port.
 *----------------------------------------------------------------------------*/
int _write (int fd, const void *buf, size_t count)
{
  size_t CharCnt = 0x00;

  (void)fd;                            /* Parameter is not used, suppress unused argument warning */
   for (;count > 0x00; --count)
   {
     SendChar((unsigned char)*(uint8_t*)buf);
     (uint8_t*)buf++;
     CharCnt++;
   }
  return CharCnt; /* CORRECT */
}

#endif /* __GNUC__ */

