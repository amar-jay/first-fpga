/* verilator lint_off MULTITOP */
module full_adder (
    input  A,
    input  B,
    input  Cin,
    output Sum,
    output Cout
);

  /* verilator lint_off UNOPTFLAT */
  wire s1, Net1, Net2;

  assign s1   = A ^ B;
  assign Net1 = A & B;
  assign Sum  = s1 ^ Cin;
  assign Net2 = s1 & Cin;
  assign Cout = Net1 | Net2;

endmodule

