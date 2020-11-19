#ifndef __IMMEDIATE
#define __IMMEDIATE

#include "rv32i_npp_ip.h"

i_immediate_t i_immediate(decoded_instruction_t d_i);
s_immediate_t s_immediate(decoded_instruction_t d_i);
b_immediate_t b_immediate(decoded_instruction_t d_i);
u_immediate_t u_immediate(decoded_instruction_t d_i);
j_immediate_t j_immediate(decoded_instruction_t d_i);

#endif
