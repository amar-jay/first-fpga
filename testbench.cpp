#include "Vcomparator.h"
#include <bitset>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <verilated.h>
#include <verilated_vcd_c.h> // Verilator VCD header for waveform output
#define WAVEFORM_PATH "waveform.vcd"

void _3bit_comparator(VerilatedVcdC *tfp) {
  Vcomparator *top = new Vcomparator;
  top->trace(tfp, 5); // Trace level
  tfp->open(WAVEFORM_PATH);

  unsigned char inputs[]{
      0b000, 0b001, 0b010, 0b011, 0b100, 0b101, 0b110, 0b111,
  };
  int len = sizeof(inputs) / sizeof(unsigned char);

  for (size_t i = 0; i < len; i++) {
    for (size_t j = 0; j < len; j++) {
      top->A = i;
      top->B = j;
      top->eval();

      if (top->Gt) {
        std::cout << std::bitset<3>(top->A) << " " << std::bitset<3>(top->B)
                  << " - A > B" << " |\t";
      } else if (top->Eq) {
        std::cout << std::bitset<3>(top->A) << " " << std::bitset<3>(top->B)
                  << " - A = B" << " |\t";
      } else if (top->Lt) {
        std::cout << std::bitset<3>(top->A) << " " << std::bitset<3>(top->B)
                  << " - A < B" << " |\t";
      } else {
        std::cout << "An error occured:  " << top->Gt << " " << top->Eq << " "
                  << top->Lt << std::endl;
      }

      tfp->dump((i * len) + j);
    }
    std::cout << std::endl;
  }

  tfp->dump(16);
  tfp->close();
  delete top;
  return;
}
int main(int argc, char **argv, char **env) {
  Verilated::commandArgs(argc, argv);
  VerilatedVcdC *tfp = new VerilatedVcdC;
  Verilated::traceEverOn(true);

  _3bit_comparator(tfp);
}
