.name "tester"
.comment "test limit"

live %2147483647
ld %3825205505, r2
ld 3825205505, r3
add r2, r3, r4
sub r2, r3, r4
and r2, r3, r4
or r2, r3, r4
xor r2, r3, r4
st r4, 53
st r5, 3825205505
ldi 3825205505, %3825205505, r5
sti r5, 3825205505, %3825205505
lld 3825205505, r5
st r5, %0
lldi 3825205505, %3825205505, r5
fork %3825205505
# lfork %3825205505
zjmp %3825205505
