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
PUSH RBP
MOV RBP,RSP
MOV RBX,[RBP + 16]
MOV R12,[RBP + 16 + r12_offset]
MOV R13,[RBP + 16 + r13_offset]
MOV R14,[RBP + 16 + r14_offset]
MOV R15,[RBP + 16 + r15_offset]
MOV RBP,[RBP + 16 + rbp_offset]
MOV RSP,[RBP + 16 + rsp_offset]
POP RBP
RET

; TOC_SWITCH : Prozessumschaltung. Der aktuelle Registersatz wird
;              gesichert und der Registersatz des neuen "thread of control"
;              wird in den Prozessor eingelesen.
;
; C Prototyp: void toc_switch (struct toc* regs_now,
;                              struct toc* reg_then);

toc_switch:
PUSH RBP
MOV RBP,RSP
MOV [RBP + 16],RBX
MOV [RBP + 16 + r12_offset],R12
MOV [RBP + 16 + r13_offset],R13
MOV [RBP + 16 + r14_offset],R14
MOV [RBP + 16 + r15_offset],R15
MOV [RBP + 16 + rbp_offset],RBP
MOV [RBP + 16 + rsp_offset],RSP
MOV RBX,[RBP + 936]
MOV R12,[RBP + 936 + r12_offset]
MOV R13,[RBP + 936 + r13_offset]
MOV R14,[RBP + 936 + r14_offset]
MOV R15,[RBP + 936 + r15_offset]
MOV RBP,[RBP + 936 + rbp_offset]
MOV RSP,[RBP + 936 + rsp_offset]
POP RBP

