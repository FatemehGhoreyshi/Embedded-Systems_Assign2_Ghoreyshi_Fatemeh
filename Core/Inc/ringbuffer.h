/*
 * ringbuffer.h
 *
 *  Created on: Apr 7, 2025
 *      Author: Fatemeh
 */

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "cmsis_os2.h"
#include <stdbool.h>

typedef struct {
  uint32_t data;
  osThreadId_t producer_id;
} rb_elem;

bool Ringbuffer_Put(rb_elem elem);
bool Ringbuffer_Get(rb_elem *elem);
void Ringbuffer_Init(void);

#endif /* INC_RINGBUFFER_H_ */
