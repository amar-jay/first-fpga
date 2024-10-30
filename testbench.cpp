#include <Vfull_adder_from_half.h>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h> // Verilator VCD header for waveform output
#define WAVEFORM_PATH "waveform.vcd"

int main(int argc, char **argv, char **env) {
  Verilated::commandArgs(argc, argv);
  VerilatedVcdC *tfp = new VerilatedVcdC;
  Verilated::traceEverOn(true);

  full_adder_from_half(tfp);
}
