
enable_gate:
    in  al, 0x92      ; switch a20 gate via fast a20 port 92
    or  al, 2         ; set a20_gate_bit (bit 1)
    out 0x92, al
    ret

    