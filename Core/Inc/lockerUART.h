/*
 * lockerUART.h
 *
 *  Created on: Apr 17, 2024
 *      Author: josep
 */

#ifndef INC_LOCKERUART_H_
#define INC_LOCKERUART_H_

/*
   This function handles the "ping stream" message.

   The function accepts the upstream and downstream huart pointers
   and an already recieved message from upstream.

   The function will then send the downstream message,
   wait and then send the upstream message.
*/
void ping_stream_response(UART_HandleTypeDef *huart_up, UART_HandleTypeDef *huart_down, uint8_t message) {
    uint8_t buffer[1] = {(message - 4)};
    HAL_UART_Transmit(huart_down, buffer, 1, 100);
    int delay_time = 20 * message;
    HAL_StatusTypeDef receiveStatus = HAL_UART_Receive(huart_down, buffer, 1, delay_time);
    if( (receiveStatus == HAL_OK) && ((buffer[0] & 3) == 3)) {
        buffer[0] = buffer[0] + 4;
    } else {
        buffer[0] = 0b00000011;
    }
    // buffer[0] = 0b00000011;
    HAL_UART_Transmit(huart_up, buffer, 1, 1000);
    return;
}

// 0bXXXXXX11 * 20

#endif /* INC_LOCKERUART_H_ */
