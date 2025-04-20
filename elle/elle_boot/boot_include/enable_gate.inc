enable_gate:
    pusha
    in al, 0x92
    or al, 2
    out 0x92, al                           
    popa
    ret