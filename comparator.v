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

  assign Gt = ~B[0] & (A[0] | A[1] ^ B[1]);
  assign Eq = (A[0] ~^ B[0]) | (A[1] ~^ B[1]);
  assign Lt = B[0] & (~A[0] | A[1] ^ B[1]);

endmodule


module comparator (
    input [2:0] A,
    input [2:0] B,
    output Gt,  //A>B
    output Eq,  //A==B
    output Lt  //A<B
);

  assign Gt = (~B[2] & ~B[1] & ~B[0] & A[0]) | (~B[2] & ~B[1] & A[1]) | (~B[2] & A[2]) |
    (~B[2] & ~B[0] & A[1] & A[0]) | (~B[1] & ~B[0] & A[2] & A[0]) | (~B[1] & A[2] & A[1]) |
    (~B[0] & A[2] & A[1] & A[0]);

  assign Lt = (B[0] & ~A[2] & ~A[1] & ~A[0]) | (B[1] & ~A[2] & ~A[1]) |
    (B[1] & B[0] & ~A[2] & ~A[0]) | (B[2] & ~A[2]) | (B[2] & B[0] & ~A[1] & ~A[0]) |
    (B[2] & B[1] & ~A[1]) | (B[2] & B[1] & B[0] & ~A[0]);

  assign Eq = (A[0] ^~ B[0]) & (A[1] ^~ B[1]) & (A[2] ^~ B[2]);
endmodule

