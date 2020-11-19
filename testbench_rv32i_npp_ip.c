#include <stdio.h>
#include "rv32i_npp_ip.h"

//#include "test_branch.h"
//#include "test_jal_jalr.h"
#include "test_load_store.h"
//#include "test_lui_auipc.h"
//#include "test_mem.h"
//#include "test_op.h"
//#include "test_op_imm.h"
//#include "test_sum.h"

char data_mem_0[DATA_MEM_SIZE/4];
char data_mem_1[DATA_MEM_SIZE/4];
char data_mem_2[DATA_MEM_SIZE/4];
char data_mem_3[DATA_MEM_SIZE/4];

int main() {
  unsigned int i;
  unsigned int pc[2];
  unsigned int nbi;
  unsigned char b0, b1, b2, b3;
  int w;
  pc[0] = 0;
  rv32i_npp_ip(pc, code_mem, data_mem_0, data_mem_1, data_mem_2, data_mem_3, &nbi);
  printf("%d fetched and decoded instructions\n", nbi);
  printf("last pc %d\n", pc[1]);
  for (i=0; i<DATA_MEM_SIZE/4; i++){
    b0 = data_mem_0[i];
    b1 = data_mem_1[i];
    b2 = data_mem_2[i];
    b3 = data_mem_3[i];
    w = (b3<<24) | (b2<<16) | (b1<<8) | b0;
    if (w != 0)
      printf("m[%4d] = %16d (%8x)\n", i, w, (unsigned int)w);
  }
  return 0;
}
