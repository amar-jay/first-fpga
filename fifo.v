/*
 *  FIFO (First-In-First-Out) buffer module
 *  A FIFO (First-In-First-Out) buffer module is a fundamental data structure used in
 *  digital systems and computer architecture to temporarily store and manage data.
 *  Its primary function is to ensure that the data items are processed in the order they
 *  were received, i.e., the first item added to the FIFO is the first one to be removed.
 *
 *  - maintains an internal buffer or queue to store the incoming data
 *  -  module keeps track of the read and write pointers
 *  - often used to bridge components operating at different clock frequencies or domains.
 *  - they allow for asynchronous communication
 */
module fifo #(
    parameter int WIDTH  = 8,
    parameter int DEPTH  = 4,
    parameter int ADDR_W = $clog2(DEPTH)  // Automatically calculate width for read/write pointers
) (
    input clk,
    input rst,
    input [WIDTH-1:0] data_in,
    input push,
    input pop,
    output [WIDTH-1:0] data_out,
    output full,
    output empty
);

  reg [WIDTH-1:0] mem[DEPTH-1:0];
  reg [31:0] count;
  reg [ADDR_W-1:0] read_ptr;
  reg [ADDR_W-1:0] write_ptr;

  always @(posedge clk or posedge rst) begin
    if (rst) begin
      for (int i = 0; i < DEPTH; i++) begin
        mem[i] <= 8'b0;
      end
      count <= 0;
      read_ptr <= 0;
      write_ptr <= 0;
    end else begin
      // Push Operation
      if (~full & push) begin
        mem[write_ptr] <= data_in;
        write_ptr <= write_ptr + 1;
        count <= count + 1;
      end

      // Pop Operation
      if (~empty & pop) begin
        read_ptr <= read_ptr + 1;
        count <= count - 1;
      end
    end
  end

  // Output data from the current read pointer
  assign data_out = mem[read_ptr];

  // FIFO status flags
  assign full = (count == DEPTH);
  assign empty = (count == 0);

endmodule

