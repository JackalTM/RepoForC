#ifdef _FUNCTION_DECLARATIONS_H

#include <stdint.h>

uint32_t LogicalAND(uint32_t inA, uint32_t inB);
uint32_t LogicalOR(uint32_t inA, uint32_t inB);
uint32_t LogicalXOR(uint32_t inA, uint32_t inB);
uint32_t LogicalNOT(uint32_t inA);

#define COMPARE_RESOULT_SAME    0x00
#define COMPARE_RESOULT_MORE    0x01
#define COMPARE_RESOULT_LESS    0xFF
uint8_t CompareBYTE(uint8_t inA, uint8_t inB);
uint8_t CompareDWORD(uint32_t inA, uint32_t inB);

#ifdef // _FUNCTION_DECLARATIONS_H


