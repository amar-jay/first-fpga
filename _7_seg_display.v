//https://cdn.testbook.com/1725519575423-MULTIPLEXER_3.png/1725519574.png
/* verilator lint_off MULTITOP */
module _7_seg_display (
    input [3:0] Inputs,
    output reg [6:0] Output
);
  //Out = I[0]*A'B' + I[1]*A'B + I[2]*AB' + I[3]*AB

  always @(Inputs) begin
    case (Inputs)
      4'h0: Output = 7'b1111110;
      4'h1: Output = 7'b0110000;
      4'h2: Output = 7'b1101101;
      4'h3: Output = 7'b1111001;
      4'h4: Output = 7'b0110011;
      4'h5: Output = 7'b1011011;
      4'h6: Output = 7'b1011111;
      4'h7: Output = 7'b1110000;
      4'h8: Output = 7'b1111111;
      4'h9: Output = 7'b1110011;
      default: Output = 7'b0000001;
    endcase
  end
endmodule

