attack:
addi sp sp -12
sw ra 0(sp)
addi a6 a0 7
loop3: 
	bgt a0 a6 end3
    sw a0 4(sp)
    sw a1 8(sp)
	jal ra study_energy
    beq a5 zero end3
    lw a0 4(sp) 
    lw a1 8(sp)
	sb a5 0(a1)
    li a5 0
	addi a1 a1 1
	addi a0 a0 1
	j loop3 

end3:
sb zero 0(a1)
lw ra 0(sp)
addi sp sp 12
jr ra

