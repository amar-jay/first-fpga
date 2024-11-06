/**
 * a simple ALU just does
 *  - addition
 *  - subtraction
 *  - left shifting
 *  - right shifting
 *  opcodes
 *  000 - addition
 *  001 - subtraction
 *  010 - bitwise AND
 *  010 - bitwise OR
 *  011 - bitwise XOR
 *  100 - left shifting (logical)
 *  101 - right shifting (logical)
 *  111 - pass through
 */

module simple_alu #(
    parameter int SIZE = 4
) (
    input [SIZE-1:0] a,
    input [SIZE-1:0] b,
    input [2:0] opcode,
    output reg [SIZE-1:0] result,
    output carry
);

  always @(a or b) begin
    case (opcode)
      3'b000: begin
        {carry, result} = a + b;
      end
      3'b001: begin
        {carry, result} = a - b;
      end
      3'b010: begin
        result = a & b;
        carry  = 0;
      end

      3'b011: begin
        result = a | b;
        carry  = 0;
      end

      3'b100: begin
        result = a ^ b;
        carry  = 0;
      end

      3'b101: begin
        result = a << b;
        carry  = 0;
      end

      3'b110: begin
        result = a >> b;
        carry  = 0;
      end

      3'b111: begin
        result = a;
        carry  = 0;
      end
      default: begin
        result = {SIZE{1'0}};
        carry  = 0;
      end
    endcase
  end

endmodule
