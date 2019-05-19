    [BITS 32]
     
    section .data
     
    wsdll: db 'ws2_32.dll',0
    wsaddr: dd '0xFFFFFFFF'
    Getpc: dd '0xFFFFFFFF'
     
    WStp: db 'WSAStartup',0
    WSaddr: dd '0xFFFFFFFF'
    WSD: dd 'WSADATA',0
    saveWSA: dd '0xFFFFFFFF'
    soc: db 'socket',0
    soadd: dd '0xFFFFFFFF'
    conn: db 'connect', 0
    conaddr: dd '0xFFFFFFFF'
    sen: db 'send', 0
    sendadd: dd '0xFFFFFFFF'
     
    res1: db "WSAStartup %d", 10, 0
    res2: db "Socket %d", 10, 0
    res3: db "connect %d", 10, 0
    res4: db "send %d", 10 ,0
     
    sre: db "hola mundo",0
     
    section .bss
    sn resb 10
     
    section .text
     
    global _WinMain@16
    extern _ExitProcess@4
    extern _LoadLibraryA@4
    extern _GetProcAddress@8
    extern _printf
    extern _WSAStartup@8
     
    _WinMain@16:
     
    xor eax, eax
     
    push wsdll
    call _LoadLibraryA@4
    mov [wsaddr], eax
     
    push WStp
    push dword [wsaddr]
    call _GetProcAddress@8
    mov [Getpc], eax
     
    push WSD
    push 0x202
    call [Getpc]
    mov [saveWSA], eax
     
    cmp dword [saveWSA], -1
    jne mns1
    je erro
     
    mns1:
    push dword [saveWSA]
    push res1
    call _printf
     
    push soc
    push dword [wsaddr]
    call _GetProcAddress@8
    mov [Getpc], eax
     
    push 6
    push 1
    push 2
    call [Getpc]
    mov [soadd], eax
     
    push dword [soadd]
    push res2
    call _printf
     
    push conn
    push dword [wsaddr]
    call _GetProcAddress@8
    mov [conaddr], eax
     
    push dword [conaddr]
    push res3
    call _printf
     
    push 0x0100007F
    push 0xB9220002 
    mov esi, esp
    push byte 16
    push esi
    push dword [soadd]
    call [conaddr]
     
    erro:
    push 0
    call _ExitProcess@4
