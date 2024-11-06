#include "Vsimple_alu.h"
#include <bitset>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <verilated.h>
#include <verilated_vcd_c.h> // Verilator VCD header for waveform output
#define WAVEFORM_PATH "waveform.vcd"

void simple_alu(VerilatedVcdC *tfp) {
  Vsimple_alu *top = new Vsimple_alu;
  top->trace(tfp, 5); // Trace level
  tfp->open(WAVEFORM_PATH);

  unsigned char inputs[]{
      // opcodes are also in the same structure,
      0b000, 0b001, 0b010, 0b011, 0b100, 0b101, 0b110, 0b111,
  };

  unsigned char opcodes[]{'+', '-', '&', '|', '^', '<', '>', ' '};

  int len = sizeof(inputs) / sizeof(unsigned char);

  int count = 0;
  for (int i = 0; i < len; i++) {
    for (int j = 0; j < len; j++) {
      for (int opcode = 0; opcode < len; opcode++) {
        top->a = inputs[i];
        top->b = inputs[j];
        top->opcode = inputs[opcode];
        top->eval();

        std::cout << std::bitset<3>(top->a & 0xF) << ' ' << opcodes[opcode]
                  << ' ' << std::bitset<3>(top->b & 0xF) << " = "
                  << std::bitset<1>(top->carry & 0xF) << '-'
                  << std::bitset<3>(top->result & 0xF) << " |\t";
        tfp->dump(count);
        ++count;
      }
      std::cout << std::endl;
    }
  }
}

int main(int argc, char **argv, char **env) {
  Verilated::commandArgs(argc, argv);
  VerilatedVcdC *tfp = new VerilatedVcdC;
  Verilated::traceEverOn(true);

  simple_alu(tfp);
}
