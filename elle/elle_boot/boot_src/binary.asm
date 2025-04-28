%macro IncBin 2
section .rodata
global %1
%1:
  incbin %2
  db 0
  %1_size: dq %1_size - %1
%endmacro

IncBin Test, "bin.txt"