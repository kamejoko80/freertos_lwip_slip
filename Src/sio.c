#include "netif/slipif.h"
#include "lwip/sio.h"

extern UART_HandleTypeDef huart1;

/**
 * Opens a serial device for communication.
 *
 * @param devnum device number
 * @return handle to serial device if successful, NULL otherwise
 */
sio_fd_t sio_open(u8_t devnum)
{
  sio_fd_t sd;

  sd = &huart1;

  return sd;
}

/**
 * Sends a single character to the serial device.
 *
 * @param c character to send
 * @param fd serial device handle
 *
 * @note This function will block until the character can be sent.
 */
void sio_send(u8_t c, sio_fd_t fd)
{
    HAL_UART_Transmit(&huart1, (uint8_t *)&c, 1, 1000);
    printf("sio_send\n");
}

/**
 * Reads from the serial device.
 *
 * @param fd serial device handle
 * @param data pointer to data buffer for receiving
 * @param len maximum length (in bytes) of data to receive
 * @return number of bytes actually received - may be 0 if aborted by sio_read_abort
 *
 * @note This function will block until data can be received. The blocking
 * can be cancelled by calling sio_read_abort().
 */
u32_t sio_read(sio_fd_t fd, u8_t *data, u32_t len)
{
  u32_t recved_bytes;

/* USER CODE BEGIN 9 */
  HAL_StatusTypeDef ret;

  ret = HAL_UART_Receive(&huart1, (uint8_t *)data, (uint16_t)len, 10000);

  if(ret == HAL_OK)
  {
    recved_bytes = len;
    //printf("recved_bytes = %d\n", recved_bytes);
    //printf("sio_read = %X\n", data[0]);
  }
  else
  {
    recved_bytes = 0;
  }

  return recved_bytes;
}

/**
 * Tries to read from the serial device. Same as sio_read but returns
 * immediately if no data is available and never blocks.
 *
 * @param fd serial device handle
 * @param data pointer to data buffer for receiving
 * @param len maximum length (in bytes) of data to receive
 * @return number of bytes actually received
 */
u32_t sio_tryread(sio_fd_t fd, u8_t *data, u32_t len)
{
  u32_t recved_bytes;

  HAL_StatusTypeDef ret;

  ret = HAL_UART_Receive(&huart1, (uint8_t *)data, (uint16_t)len, 200);

  if(ret == HAL_OK)
  {
      recved_bytes = len;
      //printf("data = %x\r\n", data[0]);
  }
  else
  {
      recved_bytes = 0;
  }

  return recved_bytes;
}
