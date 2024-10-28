// testbench.cpp
#include "Vcounter.h"
#include "Vfull_adder.h"
#include <iostream>
// #include "Vtestbench.h"
#include <verilated.h>
#include <verilated_vcd_c.h>

#define WAVEFORM_PATH "waveform.vcd"

/*
int counter() {
  Vcounter *top = new Vcounter;
  Verilated::traceEverOn(true);
  VerilatedVcdC *tfp = new VerilatedVcdC;
  top->trace(tfp, 99); // 99 is the trace depth

  tfp->open(WAVEFORM_PATH);

  // Simulation loop
  for (int i = 0; i < 100; i++) {
    top->clk = 0;
    top->eval();
    top->clk = 1;
    top->eval();
  }

  tfp->close();
  delete top;
  return 0;
}
*/

int full_adder() {
  // Instantiate the top Verilog module
  Vfull_adder *tb = new Vfull_adder;
  VerilatedVcdC *tfp = new VerilatedVcdC;

  Verilated::traceEverOn(true);
  tb->trace(tfp, 5); // Trace level
  tfp->open(WAVEFORM_PATH);

  // Test inputs
  tb->A = 0;
  tb->B = 1;
  tb->Cin = 1;
  tb->eval(); // Evaluate with inputs
  std::cout << tb->Cout << std::endl;

  // Test inputs
  tb->A = 1;
  tb->B = 1;
  tb->Cin = 0;
  tb->eval(); // Evaluate with inputs
  std::cout << tb->Cout << std::endl;

  // Test inputs
  tb->A = 0;
  tb->B = 0;
  tb->Cin = 1;
  tb->eval(); // Evaluate with inputs
  std::cout << tb->Cout << std::endl;

  // Test inputs
  tb->A = 1;
  tb->B = 1;
  tb->Cin = 1;
  tb->eval(); // Evaluate with inputs
  std::cout << tb->Cout << std::endl;

  tfp->dump(1); // Dump initial values
  tfp->close();

  delete tb;
  return 0;
}

int main(int argc, char **argv, char **env) {
  Verilated::commandArgs(argc, argv);

  counter();
  // full_adder();
}
