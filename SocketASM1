    option casemap:none
     
    extern ExitProcess:PROC
    extern WSAStartup:PROC
    extern socket:PROC
    extern connect:PROC
    extern send:PROC
     
    WSADATA STRUCT 8
        wVersion        WORD    ?
        wHighVersion    WORD    ?
        iMaxSockets     WORD    ?
        iMaxUdpDg       WORD    ?
        lpVendorInfo    QWORD   ?
        szDescription   SBYTE   257 dup (?)
        szSystemStatus  SBYTE   129 dup (?)
    WSADATA ENDS
     
    sockaddr STRUCT 
        sa_family   SWORD   ?
        sa_port     WORD    ?
        sa_addr     DWORD   ?
                    BYTE 8 dup (?)
    sockaddr ENDS
     
    .const
        align 8
        address     sockaddr <2, 0B922h, 0100007Fh>
        sz1         BYTE "hola mundo",0
    .data?
        align 8
        Socket  QWORD ?
        wsadata WSADATA <>
    .code
    main proc
        and rsp,-16
        sub rsp,4*8
     
        lea rdx, wsadata
        mov rcx, 2h
        call WSAStartup
     
        mov r8, 0h
        mov rdx, 1h
        mov rcx, 2h
        call socket
        mov Socket, rax
     
        mov r8, 16h
        lea rdx, address
        mov rcx, Socket
        call connect
     
        mov r9, 0h
        mov r8, SIZEOF sz1
        mov rdx, offset sz1
        mov rcx, Socket
        call send
     
        xor ecx, ecx
        call ExitProcess
     
    main endp
    End
