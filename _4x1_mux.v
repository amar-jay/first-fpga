//https://cdn.testbook.com/1725519575423-MULTIPLEXER_3.png/1725519574.png
/* verilator lint_off MULTITOP */
module _4x1_mux (
    input [3:0] Inputs,
    input [1:0] Selector,

    output Out
);
  //Out = I[0]*A'B' + I[1]*A'B + I[2]*AB' + I[3]*AB

  assign Out = (Inputs[0] * ~Selector[0] * ~Selector[1]) + (Inputs[1] * ~Selector[0] * Selector[1])
  + (Inputs[2] * Selector[0] * ~Selector[1]) + (Inputs[3] * Selector[0] * Selector[1]);
endmodule
