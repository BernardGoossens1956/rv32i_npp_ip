#include "ap_cint.h"
#include "debug_rv32i_npp_ip.h"
#include "rv32i_npp_ip.h"
#include "fetch.h"
#include "decode.h"
#include "execute.h"
#ifndef __SYNTHESIS__
#ifdef DEBUG_DISASSEMBLE
#include "disassemble.h"
#endif
#ifdef DEBUG_REG_FILE
#include "print.h"
#endif
#endif

void rv32i_npp_ip(
  unsigned int  pc[2],
  unsigned int  code_mem  [CODE_MEM_SIZE/sizeof(int)],
  char          data_mem_0[DATA_MEM_SIZE/sizeof(int)],
  char          data_mem_1[DATA_MEM_SIZE/sizeof(int)],
  char          data_mem_2[DATA_MEM_SIZE/sizeof(int)],
  char          data_mem_3[DATA_MEM_SIZE/sizeof(int)],
  unsigned int *nb_instruction){
#pragma HLS INTERFACE s_axilite port=pc
#pragma HLS INTERFACE s_axilite port=code_mem
#pragma HLS INTERFACE s_axilite port=data_mem_0
#pragma HLS INTERFACE s_axilite port=data_mem_1
#pragma HLS INTERFACE s_axilite port=data_mem_2
#pragma HLS INTERFACE s_axilite port=data_mem_3
#pragma HLS INTERFACE s_axilite port=nb_instruction
#pragma HLS INTERFACE ap_ctrl_none port=return
  code_address_t        current_pc;
  code_address_t        next_pc;
  instruction_t         instruction;
  unsigned int          nbi;
  decoded_instruction_t d_i;
  int                   reg_file[NB_REGISTER];
#pragma HLS ARRAY_PARTITION variable=reg_file dim=1 complete
  uint6                 i;
  for (i = 0; i < NB_REGISTER; i++)
    reg_file[i] = 0;
  next_pc = pc[0];
  nbi = 0;

  do{
#pragma HLS PIPELINE off
    fetch(next_pc, &current_pc, code_mem, &instruction);
    decode(instruction, &d_i);
#ifndef __SYNTHESIS__
#ifdef DEBUG_DISASSEMBLE
    disassemble(current_pc, instruction, d_i);
#endif
#endif
    execute(reg_file, current_pc,
            data_mem_0,
            data_mem_1,
            data_mem_2,
            data_mem_3,
            d_i,
           &next_pc);
    nbi = nbi + 1;
  } while (instruction != RET || reg_file[RA] != 0);
  pc[1] = current_pc;
  *nb_instruction = nbi;
#ifndef __SYNTHESIS__
#ifdef DEBUG_REG_FILE
  print_reg(reg_file);
#endif
#endif
}
