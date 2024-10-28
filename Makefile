${FILE}: 
	verilator --cc --exe --trace $(wildcard *.v) testbench.cpp --top-module ${FILE}
	make -C obj_dir -f V${FILE}.mk V${FILE} && \
	./obj_dir/V${FILE}
	gtkwave waveform.vcd 
	echo "\n---" 

another:
	verilator --cc full_adder.v testbench.cpp --trace --exe && \
	make -C obj_dir -f Vfull_adder.mk Vfull_adder && \
	./obj_dir/Vfull_adder
	gtkwave waveform.vcd 
	echo "\n---" 

counter_run:
	verilator -Wall --cc --exe --trace counter.v testbench.cpp && \
  cd obj_dir && make -f Vcounter.mk && \
  ./Vcounter && \
  echo "" && \
  echo "---"  

