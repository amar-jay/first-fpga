nothing much here!! Just trying out Verilog for the first time.

- Using `verilator`
- gtkwave for waveform visualization
- Setup lsp and treesitter for Neovim.


### HOW TO
To run a file, use the below command
```
make RUN_ONLY=full_adder #make RUN=<filename_without_extension>
```

However some modules rely on other modules. in such instances

```
make RUN=full_adder
```

to use the testbench for a specific module. copy it to the testbench file from `functions.h`. I couldn't figure out a more cleaner way of writing it, but this method will do for now.

## TODO
- [x] counter
- [x] half adder
- [x] full adder
- [x] full adder from half adder
- [x] ripple adder - (3_bit_adder)
- [x] 1bit/2bit comparator
- [x] 3bit/n-bit comparator
- [x] Multiplexer (4x1)
- [x] 7 segment display decoder

      
