#ifndef __EXECUTE
#define __EXECUTE

#include "rv32i_npp_ip.h"

void execute(
  int *reg_file,
  code_address_t current_pc,
  char *data_mem_0,
  char *data_mem_1,
  char *data_mem_2,
  char *data_mem_3,
  decoded_instruction_t d_i,
  code_address_t *next_pc);

#endif
