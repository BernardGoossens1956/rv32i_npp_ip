#ifndef __FETCH
#define __FETCH

#include "rv32i_npp_ip.h"

void fetch(
  code_address_t next_pc,
  code_address_t *current_pc,
  instruction_t *code_mem,
  instruction_t *instruction);

#endif
