/*
 * Copyright (c) 2020, Oracle and/or its affiliates. All rights reserved.
 * Copyright (c) 2020, 2021, Huawei Technologies Co., Ltd. All rights reserved.
 * DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.
 *
 * This code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 only, as
 * published by the Free Software Foundation.
 *
 * This code is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
 * FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * version 2 for more details (a copy is included in the LICENSE file that
 * accompanied this code).
 *
 * You should have received a copy of the GNU General Public License version
 * 2 along with this work; if not, write to the Free Software Foundation,
 * Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Please contact Oracle, 500 Oracle Parkway, Redwood Shores, CA 94065 USA
 * or visit www.oracle.com if you need additional information or have any
 * questions.
 *
 */

#ifndef CPU_RISCV64_C2_MACROASSEMBLER_RISCV64_HPP
#define CPU_RISCV64_C2_MACROASSEMBLER_RISCV64_HPP

// C2_MacroAssembler contains high-level macros for C2

 public:

  void string_compare(Register str1, Register str2,
                      Register cnt1, Register cnt2, Register result,
                      Register tmp1, Register tmp2, Register tmp3,
                      int ae);

  void string_indexof(Register str1, Register str2,
                      Register cnt1, Register cnt2,
                      Register tmp1, Register tmp2,
                      Register tmp3, Register tmp4,
                      Register tmp5, Register tmp6,
                      Register result, int ae);

  void string_indexof_linearscan(Register haystack, Register needle,
                                 Register haystack_len, Register needle_len,
                                 Register tmp1, Register tmp2,
                                 Register tmp3, Register tmp4,
                                 int needle_con_cnt, Register result, int ae);

  void arrays_equals(Register r1, Register r2,
                     Register tmp3, Register tmp4,
                     Register tmp5, Register tmp6,
                     Register result, Register cnt1,
                     int elem_size);

  void string_equals(Register r1, Register r2,
                     Register result, Register cnt1,
                     int elem_size);

  // refer to conditional_branches and float_conditional_branches
  static const int bool_test_bits = 3;
  static const int neg_cond_bits = 2;
  static const int unsigned_branch_mask = 1 << bool_test_bits;
  static const int double_branch_mask = 1 << bool_test_bits;

  // cmp
  void cmp_branch(int cmpFlag,
                  Register op1, Register op2,
                  Label& label, bool is_far = false);

  void float_cmp_branch(int cmpFlag,
                        FloatRegister op1, FloatRegister op2,
                        Label& label, bool is_far = false);

  void enc_cmpUEqNeLeGt_imm0_branch(int cmpFlag, Register op,
                                    Label& L, bool is_far = false);

  void enc_cmpEqNe_imm0_branch(int cmpFlag, Register op,
                               Label& L, bool is_far = false);

  void enc_cmove(int cmpFlag,
                 Register op1, Register op2,
                 Register dst, Register src);

  void spill(Register r, bool is64, int offset) {
    is64 ? sd(r, Address(sp, offset))
         : sw(r, Address(sp, offset));
  }

  void spill(FloatRegister f, bool is64, int offset) {
    is64 ? fsd(f, Address(sp, offset))
         : fsw(f, Address(sp, offset));
  }

  void unspill(Register r, bool is64, int offset) {
    is64 ? ld(r, Address(sp, offset))
         : lw(r, Address(sp, offset));
  }

  void unspillu(Register r, bool is64, int offset) {
    is64 ? ld(r, Address(sp, offset))
         : lwu(r, Address(sp, offset));
  }

  void unspill(FloatRegister f, bool is64, int offset) {
    is64 ? fld(f, Address(sp, offset))
         : flw(f, Address(sp, offset));
  }

  void minmax_FD(FloatRegister dst,
                 FloatRegister src1, FloatRegister src2,
                 bool is_double, bool is_min);


#endif // CPU_RISCV64_C2_MACROASSEMBLER_RISCV64_HPP
