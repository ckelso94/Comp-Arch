prog.bin: test.out.s
	python asm.py test.out.s -o prog.bin

test.out.s: test.s
	cpp test.s test.out.s
	sed -i -e 's/@/\n/g' test.out.s
	sed -i -e 's/~//g' test.out.s

clean:
	rm *.out.s
	rm prog.bin
