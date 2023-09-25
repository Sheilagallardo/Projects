
study_energy:

  addi sp, sp -4
  mv a4 ra
  li t4, 0
  mv a2 a0
  loop2:
	li t6 26
    li t5, 'a'
    bge t4, t6 end2
    add t5, t5 t4
    sb t5 0(sp)
    sb zero, 1(sp)
    mv a1 sp
    rdcycle t6
    jal ra string_compare
    rdcycle a3
    sub t6 a3 t6
    li a0 18
    ble t6 a0 else3
    mv a5 t5
    else3:
    mv a0 sp
    li a7 4
    ecall
    li a0 ':'
    li a7 11
    ecall
    mv a0 t6 
    li a7 1
    ecall
    li a0 '\n'
    li a7 11
    ecall
    mv a0 a2
    addi t4 t4 1
    j loop2

  end2:
  	addi sp, sp 4 
    mv ra a4
    jr ra
    
