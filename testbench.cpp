#include "Vfifo.h"
#include <cstring>
#include <iostream>
#include <sys/types.h>
#include <verilated.h>
#include <verilated_vcd_c.h> // Verilator VCD header for waveform output

#define WAVEFORM_PATH "waveform.vcd"
#define TOGGLE_CLK(top, tfp, cycle)                                            \
  top->clk = !top->clk;                                                        \
  top->eval();                                                                 \
  tfp->dump(cycle);                                                            \
  cycle++

void fifo(VerilatedVcdC *tfp) {
#define MAX_FIFO_DEPTH 4

  Vfifo *top = new Vfifo;
  top->trace(tfp, 5); // Trace level
  tfp->open(WAVEFORM_PATH);

  unsigned char inputs[]{
      0b000,
      0b001,
      0b010,
      0b011,
  };

  // Initialize signals
  top->clk = 0;
  top->rst = 1; // Start with reset high
  int cycle = 0;

  // Reset sequence
  TOGGLE_CLK(top, tfp, cycle);
  top->rst = 0;
  TOGGLE_CLK(top, tfp, cycle);

  // Test 1: Push data until full
  std::cout << "[1]: Pushing data until full...\n";
  for (int i = 0; i < MAX_FIFO_DEPTH; i++) {
    top->data_in = inputs[i];
    top->push = 1;
    top->pop = 0;

    TOGGLE_CLK(top, tfp, cycle);
    TOGGLE_CLK(top, tfp, cycle);

    // Check for premature full condition
    if (top->full && i < MAX_FIFO_DEPTH - 1) {
      std::cout << "Error: FIFO full too early at iteration " << i << "\n";
      return;
    }
  }

  // Test 2: Verify full condition
  std::cout << "[2]: Verifying full condition...\n";
  if (!top->full) {
    std::cout << "Error: FIFO should be full\n";
    return;
  }

  // Test 3: Reset FIFO and verify empty condition
  std::cout << "[3]: Reset FIFO and verify empty condition...\n";
  top->rst = 1;
  TOGGLE_CLK(top, tfp, cycle);
  top->rst = 0;
  TOGGLE_CLK(top, tfp, cycle);

  if (!top->empty) {
    std::cout << "Error: FIFO should be empty after reset\n";
    return;
  }

  // Test 4: Testing concurrent push and pop
  std::cout << "[4]: Testing concurrent push and pop...\n";
  for (int i = 0; i < 2; i++) {
    top->data_in = inputs[i];
    top->push = 1;
    top->pop = 0;

    TOGGLE_CLK(top, tfp, cycle);
    TOGGLE_CLK(top, tfp, cycle);
  }

  for (int i = 0; i < 10; i++) {
    top->data_in = inputs[i % MAX_FIFO_DEPTH];
    top->push = 1;
    top->pop = 1;

    TOGGLE_CLK(top, tfp, cycle);
    TOGGLE_CLK(top, tfp, cycle);

    if (top->empty && top->full) {
      std::cout << "Error: FIFO state inconsistency detected\n";
      return;
    }
  }

  tfp->close(); // Close waveform file
}

int main(int argc, char **argv, char **env) {
  Verilated::commandArgs(argc, argv);
  VerilatedVcdC *tfp = new VerilatedVcdC;
  Verilated::traceEverOn(true);

  fifo(tfp);
}
