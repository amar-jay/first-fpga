#include "verilated.h"
#include <Vcounter.h>    // Generated module header from Verilator
#include <Vfull_adder.h> // Generated module header from Verilator
#include <Vhalf_adder.h> // Generated module header from Verilator
#include <bitset>
#include <iostream>
#include <verilated_vcd_c.h> // Verilator VCD header for waveform output

#define WAVEFORM_PATH "waveform.vcd"


int counter(VerilatedVcdC *tfp) {
  Vcounter *top = new Vcounter;
  Verilated::traceEverOn(true);
  top->trace(tfp, 99); // 99 is the trace depth
  tfp->open(WAVEFORM_PATH);
  // Simulation loop
  for (int i = 0; i < 254; i++) {
    top->clk = 0;
    top->eval();
    tfp->dump(i * 2); // Dump at each clock edge
    top->clk = 1;
    top->eval();
    tfp->dump(i * 2 + 1); // Dump at each clock edge
    std::cout << "* Tik: ";
    std::cout << std::bitset<8>(top->count) << "\t" << long(top->count)
              << std::endl;
  }
  tfp->close();
  delete top;
  return 0;
}

int full_adder_from_half(VerilatedVcdC *tfp) {
  // Instantiate the top Verilog module
  Vfull_adder *top = new Vfull_adder_from_half;
  top->trace(tfp, 10); // Trace level
  tfp->open(WAVEFORM_PATH);

  int truth_table[8][3]{
      // A, B, Cin
      {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
      {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1},
  };

  for (size_t i = 0; i < 8; i++) {
    top->A = truth_table[i][0];
    top->B = truth_table[i][1];
    top->Cin = truth_table[i][2];
    top->eval();
    tfp->dump(i);
    std::cout << "Actual Sum: " << top->Sum << " Got: " << top->Sum
              << std::endl;
    std::cout << "Actual Carry: " << top->Cout << " Got: " << top->Cout
              << std::endl;
  }

  tfp->close();
  delete top;
  return 0;
}

int full_adder(VerilatedVcdC *tfp) {
  // Instantiate the top Verilog module
  Vfull_adder *top = new Vfull_adder;
  top->trace(tfp, 10); // Trace level
  tfp->open(WAVEFORM_PATH);

  int truth_table[8][3]{
      // A, B, Cin
      {0, 0, 0}, {0, 0, 1}, {0, 1, 0}, {0, 1, 1},
      {1, 0, 0}, {1, 0, 1}, {1, 1, 0}, {1, 1, 1},
  };

  for (size_t i = 0; i < 8; i++) {
    top->A = truth_table[i][0];
    top->B = truth_table[i][1];
    top->Cin = truth_table[i][2];
    top->eval();
    tfp->dump(i);
    std::cout << "Actual Sum: " << top->Sum << " Got: " << top->Sum
              << std::endl;
    std::cout << "Actual Carry: " << top->Cout << " Got: " << top->Cout
              << std::endl;
  }

  // tfp->dump(80);
  tfp->close();
  delete top;
  return 0;
}
int half_adder(VerilatedVcdC *tfp) {
  Vhalf_adder *top = new Vhalf_adder;

  top->trace(tfp, 5); // Trace level
  tfp->open(WAVEFORM_PATH);

  int vals[][4]{{0, 0, 0, 0}, {0, 1, 1, 0}, {1, 0, 1, 0}, {1, 1, 0, 1}};
  // A, B, S, C
  for (int i = 0; i < 4; i++) {
    top->A = vals[i][0];
    top->B = vals[i][1];
    top->eval(); // Evaluate with inputs
    std::cout << "Actual Sum: " << vals[i][2] << vals[i][2] << "  "
              << vals[i][2] << "\tGot: " << long(top->Sum) << std::endl;
    std::cout << "Actual Carry: " << vals[i][3] << "\tGot: " << long(top->Carry)
              << std::endl
              << std::endl;
    tfp->dump((i) * 10);
  }
  tfp->close();

  delete top;
  return 0;
}
