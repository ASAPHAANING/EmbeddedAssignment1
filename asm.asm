.data
RAM: .word 0, 0, 0, 0, 0, 0
li $t1 30
li $t2 0
li $t7 30
li $s1 RAM


.text
start:
sw $t1, 0($s1)
subi $t3, $s1, 30 
lw $t4, 0($t3)
add $t5, $t5, $t1
sub $t5, $t5, $t4
addi $t2, $t2, 1
div $t6, $t5, $t7