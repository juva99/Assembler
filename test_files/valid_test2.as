STAGEONE: add r1, DATA
STAGETWO: add r2, WORD
mov *r1, *r2
cmp r1, r2
END: stop
DATA: .data 7, 51, 40
WORD: .string "juvalele is sigma"