#include <V_4x1_mux.h>
#include <cstring>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h> // Verilator VCD header for waveform output
#define WAVEFORM_PATH "waveform.vcd"

int _4x1_mux(VerilatedVcdC *tfp) {
  V_4x1_mux *top = new V_4x1_mux;

  top->trace(tfp, 5); // Trace level
  tfp->open(WAVEFORM_PATH);

  unsigned char inputs = 0b0110;
  unsigned char selectors[][2]{
      {0b00, 0},
      {0b01, 1},
      {0b10, 1},
      {0b11, 0},
  };

  // A, B, S, C
  for (int i = 0; i < 4; i++) {
    top->Inputs = inputs;
    top->Selector = selectors[i][0];
    top->eval(); // Evaluate with inputs
    std::cout << "Actual Sum for "
              << static_cast<unsigned char>(selectors[i][0]) << " : "
              << int(selectors[i][1]) << "\tGot: " << int(top->Out)
              << std::endl;
    tfp->dump(i);
  }
  tfp->dump(4);
  tfp->close();

  delete top;
  return 0;
}
int main(int argc, char **argv, char **env) {
  Verilated::commandArgs(argc, argv);
  VerilatedVcdC *tfp = new VerilatedVcdC;
  Verilated::traceEverOn(true);

  _4x1_mux(tfp);
}
