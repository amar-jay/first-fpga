`timescale 1ns / 1ps

module _1bit_comparator (
    input  A,
    input  B,
    output Gt,  //A>B
    output Eq,  //A==B
    output Lt   //A<B
);

  assign Gt = A & ~B;
  assign Eq = ~(A ^ B);
  assign Lt = ~A & B;

endmodule

module _2bit_comparator (
    input [1:0] A,
    input [1:0] B,
    output Gt,  //A>B
    output Eq,  //A==B
    output Lt  //A<B
);

  function automatic equal;
    input A, B;
    begin
      equal = ~(A ^ B);
    end
  endfunction

  function automatic lt;
    input A, B;
    begin
      lt = ~A & B;
    end
  endfunction

  function automatic gt;
    input A, B;
    begin
      gt = A & ~B;
    end
  endfunction

  assign Gt = gt(A[1], B[1]) | equal(A[1], B[1]) & gt(A[0], B[0]);
  assign Eq = equal(A[0], B[0]) | equal(A[0], B[0]);
  assign Lt = lt(A[1], B[1]) | equal(A[1], B[1]) & lt(A[0], B[0]);

endmodule


module _3bit_comparator (
    input [2:0] A,
    input [2:0] B,
    output Gt,  //A>B
    Eq,  //A==B
    Lt  //A<B
);
  // Define the full adder function
  function automatic equal;
    input A, B;
    begin
      equal = ~(A ^ B);
    end
  endfunction

  function automatic lt;
    input A, B;
    begin
      lt = ~A & B;
    end
  endfunction

  function automatic gt;
    input A, B;
    begin
      gt = A & ~B;
    end
  endfunction


  assign Eq = equal(A[0], B[0]) & equal(A[1], B[1]) & equal(A[2], B[2]);
  assign Lt = lt(
      A[2], B[2]
  ) | equal(
      A[2], B[2]
  ) & lt(
      A[1], B[1]
  ) | equal(
      A[2], B[2]
  ) & equal(
      A[1], B[1]
  ) & lt(
      A[0], B[0]
  );
  assign Gt = gt(
      A[2], B[2]
  ) | equal(
      A[2], B[2]
  ) & gt(
      A[1], B[1]
  ) | equal(
      A[2], B[2]
  ) & equal(
      A[1], B[1]
  ) & gt(
      A[0], B[0]
  );

endmodule



// a comparator can easily be done using the </>/= sign and leave verilog to
// handle the rest
module comparator (
    input [2:0] A,
    input [2:0] B,
    output wire Gt,  //A>B
    output wire Eq,  //A==B
    output wire Lt  //A<B
);

  assign Gt = (A > B) ? 1 : 0;
  assign Eq = (A == B) ? 1 : 0;
  assign Lt = (A < B) ? 1 : 0;

endmodule
