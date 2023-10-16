#data
a1 1
a2 3
b1 4
#code
LOAD R1, a1
LOAD R2, a2
ADD R3, R1, R2
STORE a1, R3
LOAD R1, a1
LOAD R2, b1
ADD R3, R1, R2
STORE a1, R3
#output
CPU_printf(a1)
