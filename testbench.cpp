#include <V_7_seg_display.h>
#include <bitset>
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <verilated.h>
#include <verilated_vcd_c.h> // Verilator VCD header for waveform output
#define WAVEFORM_PATH "waveform.vcd"

int _7_seg_display(VerilatedVcdC *tfp) {
  V_7_seg_display *top = new V_7_seg_display;

  top->trace(tfp, 5); // Trace level
  tfp->open(WAVEFORM_PATH);

  unsigned char inputs = 0b0110;
  unsigned char selectors[][2]{
      {0b00, 0},
      {0b01, 1},
      {0b10, 1},
      {0b11, 0},
  };

  unsigned char truth_table[10]{
      0b1111110, 0b0110000, 0b1101101, 0b1111001, 0b0110011,
      0b1011011, 0b1011111, 0b1110000, 0b1111111, 0b1110011,
  };

  // A, B, S, C
  for (int i = 0; i < 10; i++) {
    top->Inputs = i;
    top->eval(); // Evaluate with inputs
    std::cout << "Actual of (" << i << " | " << std::bitset<4>(i)
              << "): " << std::bitset<7>(truth_table[i])
              << "\tGot: " << std::bitset<7>(top->Output)
              << " \tCorrect: " << (truth_table[i] == top->Output) << std::endl;
    tfp->dump(i);
  }
  tfp->dump(10);
  tfp->close();

  delete top;
  return 0;
}
int main(int argc, char **argv, char **env) {
  Verilated::commandArgs(argc, argv);
  VerilatedVcdC *tfp = new VerilatedVcdC;
  Verilated::traceEverOn(true);

  _7_seg_display(tfp);
}
