${BUILD}: 
	verilator --cc --exe --trace $(wildcard *.v) testbench.cpp --top-module ${BUILD}
	make -C obj_dir -f V${BUILD}.mk V${BUILD} && \
	./obj_dir/V${BUILD}
	echo "built successfully"

${RUN}: 
	verilator --cc --exe --trace $(wildcard *.v) testbench.cpp --top-module ${RUN}
	make -C obj_dir -f V${RUN}.mk V${RUN} && \
	./obj_dir/V${RUN}
	gtkwave waveform.vcd 
	echo "Closing gtkwave..." 

${BUILD_ONLY}: 
	verilator --cc --exe --trace ${BUILD_ONLY}.v testbench.cpp --top-module ${BUILD_ONLY}
	make -C obj_dir -f V${BUILD_ONLY}.mk V${BUILD_ONLY} && \
	./obj_dir/V${BUILD}
	echo "built successfully"

${RUN_ONLY}: 
	verilator --cc --exe --trace ${RUN_ONLY}.v testbench.cpp --top-module ${RUN_ONLY}
	make -C obj_dir -f V${RUN_ONLY}.mk V${RUN_ONLY} && \
	./obj_dir/V${RUN_ONLY}
	gtkwave waveform.vcd 
	echo "Closing gtkwave..." 

counter_run:
	verilator -Wall --cc --exe --trace counter.v testbench.cpp && \
  cd obj_dir && make -f Vcounter.mk && \
  ./Vcounter && \
  echo "" && \
  echo "---"  

