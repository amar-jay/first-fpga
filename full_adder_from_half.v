/* verilator lint_off MULTITOP */
module full_adder_from_half (
    input  A,
    input  B,
    input  Cin,
    output Sum,
    output Cout
);

  /* verilator lint_off UNOPTFLAT */
  wire s1, c1, c2;

  half_adder half_1 (
      .A(A),
      .B(B),
      .Sum(s1),
      .Carry(c1)
  );

  half_adder half_2 (
      .A(s1),
      .B(Cin),
      .Sum(Sum),
      .Carry(c2)
  );

  assign Cout = c1 | c2;

endmodule
