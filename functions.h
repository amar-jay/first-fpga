#include <V_4x1_mux.h>
#include <Vcounter.h>    // Generated module header from Verilator
#include <Vfull_adder.h> // Generated module header from Verilator
#include <Vhalf_adder.h> // Generated module header from Verilator
#include <bitset>
#include <iostream>
#include <verilated.h>
#include <verilated_vcd_c.h> // Verilator VCD header for waveform output

#define WAVEFORM_PATH "waveform.vcd"

void _3bit_adder(VerilatedVcdC *tfp) {
  V_3bit_adder *top = new V_3bit_adder;
  top->trace(tfp, 5); // Trace level
  tfp->open(WAVEFORM_PATH);

  unsigned char inputs[]{
      0b000, 0b001, 0b010, 0b011, 0b100, 0b101, 0b110, 0b111,
  };
  int len = sizeof(inputs) / sizeof(unsigned char);

  for (size_t i = 0; i < len; i++) {
    for (size_t j = 0; j < len; j++) {
      top->A = inputs[i];
      top->B = inputs[j];
      top->eval();

      std::cout << std::bitset<3>(top->A & 0xF) << " + "
                << std::bitset<3>(top->B & 0xF) << " = "
                << std::bitset<4>(top->Sum & 0xF) << " |\t";

      tfp->dump((i * len) + j);
    }
    std::cout << std::endl;
  }

  tfp->dump(len * len);
  tfp->close();
  delete top;
  return;
}
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
void _2bit_comparator(VerilatedVcdC *tfp) {
  V_2bit_comparator *top = new V_2bit_comparator;
  top->trace(tfp, 5); // Trace level
  tfp->open(WAVEFORM_PATH);

  unsigned char inputs[]{
      0b00,
      0b01,
      0b10,
      0b11,
  };
  int len = sizeof(inputs) / sizeof(unsigned char);

  for (size_t i = 0; i < len; i++) {
    for (size_t j = 0; j < len; j++) {
      top->A = i;
      top->B = j;
      top->eval();

      if (top->Gt) {
        std::cout << std::bitset<2>(top->A) << " " << std::bitset<2>(top->B)
                  << " - A > B" << std::endl;
      } else if (top->Eq) {
        std::cout << std::bitset<2>(top->A) << " " << std::bitset<2>(top->B)
                  << " - A == B" << std::endl;
      } else if (top->Lt) {
        std::cout << std::bitset<2>(top->A) << " " << std::bitset<2>(top->B)
                  << " - A < B" << std::endl;
      } else {
        std::cout << "An error occured:  " << top->Gt << " " << top->Eq << " "
                  << top->Lt << std::endl;
      }

      tfp->dump((i * len) + j);
    }
  }

  tfp->dump(len * len);
  tfp->close();
  delete top;
  return;
}
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
