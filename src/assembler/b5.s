    add %1, %0, %31
    addi %2, %0, 7
    addi %3, %0, -1
    sw %2, 164(%1)
    sw %3, 168(%1)

    sh %2, 172(%1)
    sh %3, 174(%1)

    sb %2, 176(%1)
    sb %3, 177(%1)

    sd %2, 180(%1)
    sd %3, 188(%1)

    lb %5, 177(%1)
    lbu %6, 177(%1)

    lh %7, 172(%1)
    lhu %8, 174(%1)

    lw %9, 168(%1)
    lwu %10, 168(%1)

L0:
    beq %0, %0, L0
