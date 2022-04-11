.extern gpSystemFont__r13, __ct__8J2DPrintFP7JUTFontiiQ28JUtility6TColorQ28JUtility6TColor, PSMTXTrans, GXLoadPosMtxImm, J2DPrint_print_alpha_va

	.file	"draw.c"
	.machine ppc
	.section	".text"
	.align 2
	.globl drawText
	.type	drawText, @function
drawText:
	stwu 1,-296(1)
	mflr 0
	stmw 28,280(1)
	mr 31,3
	stw 0,300(1)
	mr 30,4
	stw 6,184(1)
	mr 29,5
	stw 7,188(1)
	mr 28,8
	stw 9,192(1)
	stw 10,196(1)
	bne- 1,.L3
	stfd 1,200(1)
	stfd 2,208(1)
	stfd 3,216(1)
	stfd 4,224(1)
	stfd 5,232(1)
	stfd 6,240(1)
	stfd 7,248(1)
	stfd 8,256(1)
.L3:
	li 9,0x600
	addi 8,1,188
	sth 9,160(1)
	addi 9,1,304
	stw 9,164(1)
	addi 9,1,168
	stw 9,168(1)
	lwz 4,gpSystemFont__r13(13)
	addi 7,1,184
	mr 6,29
	li 5,0
	addi 3,1,8
	xoris 30,30,0x8000
	bl __ct__8J2DPrintFP7JUTFontiiQ28JUtility6TColorQ28JUtility6TColor
	lis 9,0x4330
	stw 9,264(1)
	lis 10,.LC3@ha
	stw 30,268(1)
	xoris 31,31,0x8000
	lfs 0,.LC3@l(10)
	addi 3,1,112
	lfd 12,264(1)
	stw 9,272(1)
	lis 9,.LC1@ha
	stw 31,276(1)
	fsub 2,12,0
	lfs 3,.LC1@l(9)
	lfd 12,272(1)
	stw 29,100(1)
	fsub 1,12,0
	stw 29,96(1)
	bl PSMTXTrans
	li 4,0
	addi 3,1,112
	bl GXLoadPosMtxImm
	addi 6,1,160
	mr 5,28
	li 4,255
	addi 3,1,8
	bl J2DPrint_print_alpha_va
  lmw 28, 280(1)
  addi 1,1,296
  lwz 0,4(1)
  mtlr 0
  blr
	.size	drawText, .-drawText
	.section	.rodata.cst4,"aM",@progbits,4
	.align 2
.LC1:
	.long	0
	.align 2
.LC3:
	.long	1501560836
	.ident	"GCC: (devkitPPC release 40) 11.2.0"
	.gnu_attribute 4, 9
