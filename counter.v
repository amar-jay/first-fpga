// counter.v
/* verilator lint_off MULTITOP */
module counter(
    input  wire clk,
    input  wire rst,
    output wire [7:0] count
);

reg [7:0] count_reg;

initial begin
    $display("Simulation started");
end

always @ (posedge clk or posedge rst) begin
    if (rst) begin
        count_reg <= 8'd0;
    end else begin
        count_reg <= count_reg + 1;
    end
    $display("Tik : %0d", count_reg);
end

assign count = count_reg;

endmodule