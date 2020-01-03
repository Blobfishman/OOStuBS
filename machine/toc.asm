; $Id: toc.asm 9719 2018-12-05 09:57:29Z df $

;******************************************************************************
;* Betriebssysteme                                                            *
;*----------------------------------------------------------------------------*
;*                                                                            *
;*                               T O C . A S M                                *
;*                                                                            *
;*----------------------------------------------------------------------------*
;*
;******************************************************************************

%include "machine/toc.inc"

; EXPORTIERTE FUNKTIONEN

[GLOBAL toc_switch]
[GLOBAL toc_go]

; IMPLEMENTIERUNG DER FUNKTIONEN

[SECTION .text]

; TOC_GO : Startet den ersten Prozess ueberhaupt.
;
; C Prototyp: void toc_go (struct toc* regs);

toc_go:
MOV RBX,rdi
MOV R12,[rdi + r12_offset]
MOV R13,[rdi + r13_offset]
MOV R14,[rdi + r14_offset]
MOV R15,[rdi + r15_offset]
MOV RBP,[rdi + rbp_offset]
MOV RSP,[rdi + rsp_offset]
RET

; TOC_SWITCH : Prozessumschaltung. Der aktuelle Registersatz wird
;              gesichert und der Registersatz des neuen "thread of control"
;              wird in den Prozessor eingelesen.
;
; C Prototyp: void toc_switch (struct toc* regs_now,
;                              struct toc* reg_then);

toc_switch:
MOV rdi,rbx
MOV [rdi + r12_offset],r12
MOV [rdi + r13_offset],r13
MOV [rdi + r14_offset],r14
MOV [rdi + r15_offset],r15
MOV [rdi + rbp_offset],rbp
MOV [rdi + rsp_offset],rsp

MOV RBX,rsi
MOV R12,[rsi + r12_offset]
MOV R13,[rsi + r13_offset]
MOV R14,[rsi + r14_offset]
MOV R15,[rsi + r15_offset]
MOV RBP,[rsi + rbp_offset]
MOV RSP,[rsi + rsp_offset]
ret

