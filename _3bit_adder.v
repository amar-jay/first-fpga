module _3bit_adder (
    input  [2:0] A,
    input  [2:0] B,
    output [3:0] Sum
);

  function automatic [1:0] adder;  // [Sum , Carry]
    input A, B, Cin;
    begin
      adder[0] = A ^ B ^ Cin;
      adder[1] = (A & B) | (Cin & (A ^ B));
    end
  endfunction

  wire carry0, carry1;
  assign {carry0, Sum[0]} = adder(A[0], B[0], 1'b0);
  assign {carry1, Sum[1]} = adder(A[1], B[1], carry0);
  assign {Sum[3], Sum[2]} = adder(A[2], B[2], carry1);
endmodule


