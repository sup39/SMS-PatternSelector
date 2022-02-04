.globl _restgpr_28_x
.globl _restgpr_29_x
.globl _restgpr_30_x
.globl _restgpr_31_x
_restgpr_28_x: lwz 28,-16(11)
_restgpr_29_x: lwz 29,-12(11)
_restgpr_30_x: lwz 30,-8(11)
_restgpr_31_x:
  lwz 0,4(11)
  lwz 31,-4(11)
  mtlr 0
  mr  1,11
  blr
