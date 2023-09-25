 string_compare:   

    li t0 0
    beq a0 t0 error
    beq a1 t0 error
    lb t1 0(a0)
    lb t2 0(a1)
    beq t1 t0 error
  	beq t2 t0 error
    loop: 
	lb t1 0(a0)
	lb t2 0(a1)
    beq t1 t0 end
	beq t1 t2 else1
	bne t1 t2 else2

    else2:
    li t3 0
	j end
    
	else1: 
	li t3 1
    addi a0 a0 1
    addi a1 a1 1
    j loop
    
    error:
       li t3 -1
       j end 
	
    end:
	mv a0 t3
    jr ra

