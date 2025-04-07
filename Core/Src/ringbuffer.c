/*
 * ringbuffer.c
 *
 *  Created on: Apr 7, 2025
 *      Author: Fatemeh
 */

#include "ringbuffer.h"
#include "cmsis_os2.h"
#include <stdbool.h>

#define BUFFER_SIZE 10

static rb_elem buffer[BUFFER_SIZE];
static uint32_t head = 0, tail = 0;

static osSemaphoreId_t sem_empty, sem_full;
static osMutexId_t mutex;

void Ringbuffer_Init(void) {
  sem_empty = osSemaphoreNew(BUFFER_SIZE, BUFFER_SIZE, NULL);
  sem_full = osSemaphoreNew(BUFFER_SIZE, 0, NULL);
  mutex = osMutexNew(NULL);
}

bool Ringbuffer_Put(rb_elem elem) {
  if (osSemaphoreAcquire(sem_empty, 0) != osOK) return false;
  osMutexAcquire(mutex, osWaitForever);
  buffer[head] = elem;
  head = (head + 1) % BUFFER_SIZE;
  osMutexRelease(mutex);
  osSemaphoreRelease(sem_full);
  return true;
}

bool Ringbuffer_Get(rb_elem *elem) {
  if (osSemaphoreAcquire(sem_full, 0) != osOK) return false;
  osMutexAcquire(mutex, osWaitForever);
  *elem = buffer[tail];
  tail = (tail + 1) % BUFFER_SIZE;
  osMutexRelease(mutex);
  osSemaphoreRelease(sem_empty);
  return true;
}
