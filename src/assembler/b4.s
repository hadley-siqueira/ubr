    addi %10, %31, 128
    addi %12, %31, 128
    addi %11, %31, 208
    sub %9, %9, %9

L0:
    beq %10, %11, L1
    sw %9, 0(%10)
    addi %9, %9, 1
    addi %10, %10, 4
    beq %10, %10, L0

L1:
    beq %12, %10, L2
    lw %9, 0(%10)
    addi %9, %9, 1
    sw %9, 0(%10)
    addi %10, %10, -4
    beq %10, %10, L1

L2:
    beq %0, %0, L2
