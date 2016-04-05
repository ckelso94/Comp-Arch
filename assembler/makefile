prog.bin: combined.s
	python asm.py combined.s -o prog.bin

test.out.s: test.s
	cpp test.s test.out.s
	sed -i -e 's/@/\n/g' test.out.s
	sed -i -e 's/@/\n/g' test.out.s

loader.out.s: loader.s
	cpp loader.s loader.out.s
	sed -i -e 's/@/\n/g' loader.out.s
	sed -i -e 's/@/\n/g' loader.out.s

combined.s: test.out.s loader.out.s
	cat loader.out.s > combined.s
	cat test.out.s >> combined.s
clean:
	rm *.out.s
	rm combined.s
