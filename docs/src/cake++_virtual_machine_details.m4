include(src/include/misc_defines.m4)dnl
define(`OPCODE', `Opcode:  _CODE($1)')dnl
define(`PUSH', `_BOLD(push)($1)')dnl
define(`POP', `_BOLD(pop)($1)')dnl
define(`PC', `_BOLD(pc)')dnl
define(`SP', `_BOLD(sp)')dnl
define(`FP', `_BOLD(fp)')dnl
define(`OLD_FP', `_BOLD(old\_fp)')dnl
define(`ARG_SPACE', `_BOLD(arg\_space)')dnl
define(`VAR_SPACE', `_BOLD(var\_space)')dnl
define(`MEM8', `_BOLD(mem8)[$1]')dnl
define(`MEM16', `_BOLD(mem16)[$1]')dnl
define(`MEM32', `_BOLD(mem32)[$1]')dnl
define(`MEM64', `_BOLD(mem64)[$1]')dnl

# Cake++ Virtual Machine Details
* This is a stack machine that uses byte addressing.
* Basic data types supported for arithmetic are
	* _UINT64_T(), _INT64_T()
* 8 integer types are supported for loads and stores:
	* _UINT8_T(), _INT8_T(), _UINT16_T(), _INT16_T(),  _UINT32_T(),
	_INT32_T(), _UINT64_T(), _INT64_T()
* Registers:
	* _CODE(PC()):  program counter
	* _CODE(SP()):  stack pointer
	* _CODE(FP()):  frame pointer (points to the start of the stack frame)
* Stack frame:
	* _CODE(FP() - ARG_SPACE() - 8):  return value
	* _CODE(FP() - ARG_SPACE):  arguments to this specific call of the
	function, in reverse order.
		* Example:  for a function with two arguments, the first argument
		to the function is at (_CODE(FP() - 8)), and the second argument to
		the function is at (_CODE(FP() - 16))
	* _CODE(FP()):  return address
	* _CODE(FP() + 8):  old FP()
	* _CODE(FP() + 16):  local variables of this specific call of the
	function
	* _CODE(FP() + 16 + VAR_SPACE()):  temporaries (basically just stuff on
	the stack)
* Instructions:
	* Group 0:  Non-immediate Arithmetic/Logic instructions,
	Non-immediate-indexed loads and stores, non-immediate-indexed jumps
		* Encoding:  _CODE(0000 0000  oooo oooo)
			* o:  opcode
		* List:
			* _BOLD(add)
				* OPCODE(0x00)
				* Effect:  _CODE(PUSH(POP() + POP());)
			* _BOLD(sub)
				* OPCODE(0x01)
				* Effect:  _CODE(PUSH(POP() - POP());)
			* _BOLD(mul)
				* OPCODE(0x02)
				* Effect:  _CODE(PUSH(POP() * POP());)
			* _BOLD(udiv)
				* OPCODE(0x03)
				* Note:  divide unsigned
				* Effect:  _CODE(PUSH(POP() udiv POP());)
			* _BOLD(sdiv)
				* OPCODE(0x04)
				* Note:  divide signed
				* Effect:  _CODE(PUSH(POP() sdiv POP());)
			* _BOLD(umod)
				* OPCODE(0x05)
				* Note:  modulo unsigned
				* Effect:  _CODE(PUSH(POP() umod POP());)
			* _BOLD(smod)
				* OPCODE(0x05)
				* Note:  modulo signed
				* Effect:  _CODE(PUSH(POP() smod POP());)
			* _BOLD(uslt)
				* OPCODE(0x06)
				* Note:  set less than unsigned
				* Effect:  _CODE(PUSH(POP() uslt POP());)
			* _BOLD(sslt)
				* OPCODE(0x06)
				* Note:  set less than signed
				* Effect:  _CODE(PUSH(POP() sslt POP());)
			* _BOLD(and)
				* OPCODE(0x07)
				* Note:  bitwise and
				* Effect:  _CODE(PUSH(POP() & POP());)
			* _BOLD(or)
				* OPCODE(0x08)
				* Note:  bitwise or
				* Effect:  _CODE(PUSH(POP() | POP());)
			* _BOLD(xor)
				* OPCODE(0x09)
				* Note:  bitwise xor
				* Effect:  _CODE(PUSH(POP() ^ POP());)
			* _BOLD(lsl)
				* OPCODE(0x0a)
				* Note:  logical shift left
				* Effect:  _CODE(PUSH(POP() << POP());)
			* _BOLD(lsr)
				* OPCODE(0x0b)
				* Note:  logical shift right
				* Effect:  _CODE(PUSH(POP() lsr POP());)
			* _BOLD(asr)
				* OPCODE(0x0c)
				* Note:  arithmetic shift right
				* Effect:  _CODE(PUSH(POP() asr POP());)
			* _BOLD(ldux8)
				* OPCODE(0x0d)
				* Effect:  _CODE(PUSH(_ZERO_EXTEND_TO_64(MEM8(POP()
				\+ POP())));)
			* _BOLD(ldsx8)
				* OPCODE(0x0e)
				* Effect:  _CODE(PUSH(_SIGN_EXTEND_TO_64(MEM8(POP()
				\+ POP())));)
			* _BOLD(ldux16)
				* OPCODE(0x0f)
				* Effect:  _CODE(PUSH(_ZERO_EXTEND_TO_64(MEM16(POP()
				\+ POP())));)
			* _BOLD(ldsx16)
				* OPCODE(0x10)
				* Effect:  _CODE(PUSH(_SIGN_EXTEND_TO_64(MEM16(POP()
				\+ POP())));)
			* _BOLD(ldux32)
				* OPCODE(0x11)
				* Effect:  _CODE(PUSH(_ZERO_EXTEND_TO_64(MEM32(POP()
				\+ POP())));)
			* _BOLD(ldsx32)
				* OPCODE(0x12)
				* Effect:  _CODE(PUSH(_SIGN_EXTEND_TO_64(MEM32(POP()
				\+ POP())));)
			* _BOLD(ldx64)
				* OPCODE(0x13)
				* Effect:  _CODE(PUSH(MEM64(POP() + POP()));)
			* _BOLD(stx8)
				* OPCODE(0x14)
				* Effect:  _CODE(MEM8(POP() + POP()) = (POP()[7:0]);)
			* _BOLD(stx16)
				* OPCODE(0x15)
				* Effect:  _CODE(MEM16(POP() + POP()) = (POP()[15:0]);)
			* _BOLD(stx32)
				* OPCODE(0x16)
				* Effect:  _CODE(MEM32(POP() + POP()) = (POP()[31:0]);)
			* _BOLD(stx64)
				* OPCODE(0x17)
				* Effect:  _CODE(MEM64(POP() + POP()) = POP();)
			* _BOLD(jmpx)
				* OPCODE(0x18)
				* Effect:  _CODE(PC() = (POP() + POP());)
			* _BOLD(jfal)
				* OPCODE(0x19)
				* Effect:  _CODE(cond = POP(); temp = POP(); _NEWLINE()
				if (cond == 0) { PC() = temp; })
			* _BOLD(jtru)
				* OPCODE(0x1a)
				* Effect:  _CODE(cond = POP(); temp = POP(); _NEWLINE()
				if (cond != 0) { PC() = temp; })
	* Group 1:  Immediate arithmetic/logic instructions, immediate-indexed
	loads and stores, and jumps that use immediates
		* Encoding:  _CODE(0000 0001  oooo oooo  iiii iiii  iiii iiii)
			* o:  opcode
			* i:  sign-extended 16-bit immediate
		* List:
			* _BOLD(addi simm16)
				* OPCODE(0x00)
				* Effect:  _CODE(PUSH(POP() + _SIGN_EXTEND_TO_64(simm16));)
			* _BOLD(subi simm16)
				* OPCODE(0x01)
				* Effect:  _CODE(PUSH(POP() - _SIGN_EXTEND_TO_64(simm16));)
			* _BOLD(muli simm16)
				* OPCODE(0x02)
				* Effect:  _CODE(PUSH(POP() * _SIGN_EXTEND_TO_64(simm16));)
			* _BOLD(udivi simm16)
				* OPCODE(0x03)
				* Note:  divide unsigned
				* Effect:  _CODE(PUSH(POP()
				udiv _SIGN_EXTEND_TO_64(simm16));)
			* _BOLD(sdivi simm16)
				* OPCODE(0x04)
				* Note:  divide signed
				* Effect:  _CODE(PUSH(POP()
				sdiv _SIGN_EXTEND_TO_64(simm16));)
			* _BOLD(umodi simm16)
				* OPCODE(0x05)
				* Note:  modulo unsigned
				* Effect:  _CODE(PUSH(POP()
				umod _SIGN_EXTEND_TO_64(simm16));)
			* _BOLD(smodi simm16)
				* OPCODE(0x05)
				* Note:  modulo signed
				* Effect:  _CODE(PUSH(POP()
				smod _SIGN_EXTEND_TO_64(simm16));)
			* _BOLD(uslti simm16)
				* OPCODE(0x06)
				* Note:  set less than unsigned
				* Effect:  _CODE(PUSH(POP()
				uslt _SIGN_EXTEND_TO_64(simm16));)
			* _BOLD(sslti simm16)
				* OPCODE(0x06)
				* Note:  set less than signed
				* Effect:  _CODE(PUSH(POP()
				sslt _SIGN_EXTEND_TO_64(simm16));)
			* _BOLD(andi simm16)
				* OPCODE(0x07)
				* Note:  bitwise and
				* Effect:  _CODE(PUSH(POP() & _SIGN_EXTEND_TO_64(simm16));)
			* _BOLD(ori simm16)
				* OPCODE(0x08)
				* Note:  bitwise or
				* Effect:  _CODE(PUSH(POP() | _SIGN_EXTEND_TO_64(simm16));)
			* _BOLD(xori simm16)
				* OPCODE(0x09)
				* Note:  bitwise xor
				* Effect:  _CODE(PUSH(POP() ^ _SIGN_EXTEND_TO_64(simm16));)
			* _BOLD(lsli simm16)
				* OPCODE(0x0a)
				* Note:  logical shift left
				* Effect:  _CODE(PUSH(POP()
				<< _SIGN_EXTEND_TO_64(simm16));)
			* _BOLD(lsri simm16)
				* OPCODE(0x0b)
				* Note:  logical shift right
				* Effect:  _CODE(PUSH(POP()
				lsr _SIGN_EXTEND_TO_64(simm16));)
			* _BOLD(asri simm16)
				* OPCODE(0x0c)
				* Note:  arithmetic shift right
				* Effect:  _CODE(PUSH(POP()
				asr _SIGN_EXTEND_TO_64(simm16));)
			* _BOLD(ldux8i simm16)
				* OPCODE(0x0d)
				* Effect:  _CODE(PUSH(_ZERO_EXTEND_TO_64(MEM8(POP()
				+ _SIGN_EXTEND_TO_64(simm16))));)
			* _BOLD(ldsx8i simm16)
				* OPCODE(0x0e)
				* Effect:  _CODE(PUSH(_SIGN_EXTEND_TO_64(MEM8(POP()
				+ _SIGN_EXTEND_TO_64(simm16))));)
			* _BOLD(ldux16i simm16)
				* OPCODE(0x0f)
				* Effect:  _CODE(PUSH(_ZERO_EXTEND_TO_64(MEM16(POP()
				+ _SIGN_EXTEND_TO_64(simm16))));)
			* _BOLD(ldsx16 simm16)
				* OPCODE(0x10)
				* Effect:  _CODE(PUSH(_SIGN_EXTEND_TO_64(MEM16(POP()
				+ POP())));)
			* _BOLD(ldux32i simm16)
				* OPCODE(0x11)
				* Effect:  _CODE(PUSH(_ZERO_EXTEND_TO_64(MEM32(POP()
				+ _SIGN_EXTEND_TO_64(simm16))));)
			* _BOLD(ldsx32i simm16)
				* OPCODE(0x12)
				* Effect:  _CODE(PUSH(_SIGN_EXTEND_TO_64(MEM32(POP()
				+ _SIGN_EXTEND_TO_64(simm16))));)
			* _BOLD(ldx64i simm16)
				* OPCODE(0x13)
				* Effect:  _CODE(PUSH(MEM64(POP()
				\+ _SIGN_EXTEND_TO_64(simm16)));)
			* _BOLD(stx8i simm16)
				* OPCODE(0x14)
				* Effect:  _CODE(MEM8(POP()
				\+ _SIGN_EXTEND_TO_64(simm16)) = (POP()[7:0]);)
			* _BOLD(stx16i simm16)
				* OPCODE(0x15)
				* Effect:  _CODE(MEM16(POP()
				\+ _SIGN_EXTEND_TO_64(simm16)) = (POP()[15:0]);)
			* _BOLD(stx32i simm16)
				* OPCODE(0x16)
				* Effect:  _CODE(MEM32(POP()
				\+ _SIGN_EXTEND_TO_64(simm16)) = (POP()[31:0]);)
			* _BOLD(stx64i simm16)
				* OPCODE(0x17)
				* Effect:  _CODE(MEM64(POP()
				\+ _SIGN_EXTEND_TO_64(simm16)) = POP();)
			* _BOLD(jmpxi simm16)
				* OPCODE(0x18)
				* Effect:  _CODE(PC() = (POP()
				\+ _SIGN_EXTEND_TO_64(simm16));)
			* _BOLD(bfal simm16)
				* OPCODE(0x19)
				* Effect:  _CODE(if (POP() == 0) { PC() = PC()
				\+ _SIGN_EXTEND_TO_64(simm16); })
			* _BOLD(btru simm16)
				* OPCODE(0x1a)
				* Effect:  _CODE(if (POP() != 0) { PC() = PC()
				\+ _SIGN_EXTEND_TO_64(simm16); })
	* Group 2:  Constants
		* List:
			* _BOLD(constu8 uimm8)
				* Encoding:  _CODE(0000 0010  0000 0000 iiii iiii)
				* Effect:  _CODE(PUSH(_ZERO_EXTEND_TO_64(uimm8));)
			* _BOLD(consts8 simm8)
				* Encoding:  _CODE(0000 0010  0000 0001 iiii iiii)
				* Effect:  _CODE(PUSH(_SIGN_EXTEND_TO_64(simm8));)
			* _BOLD(constu16 uimm16)
				* Encoding:  _CODE(0000 0010  0000 0010
				iiii iiii  iiii iiii)
				* Effect:  _CODE(PUSH(_ZERO_EXTEND_TO_64(uimm16));)
			* _BOLD(consts16 simm16)
				* Encoding:  _CODE(0000 0010  0000 0011
				iiii iiii  iiii iiii)
				* Effect:  _CODE(PUSH(_SIGN_EXTEND_TO_64(simm16));)
			* _BOLD(constu32 uimm32)
				* Encoding:  _CODE(0000 0010  0000 0100
				iiii iiii  iiii iiii  iiii iiii  iiii iiii)
				* Effect:  _CODE(PUSH(_ZERO_EXTEND_TO_64(uimm32));)
			* _BOLD(consts32 simm32)
				* Encoding:  _CODE(0000 0010  0000 0101
				iiii iiii  iiii iiii  iiii iiii  iiii iiii)
				* Effect:  _CODE(PUSH(_SIGN_EXTEND_TO_64(simm32));)
			* _BOLD(const imm64)
				* Encoding:  _CODE(0000 0010  0000 0110
				iiii iiii  iiii iiii  iiii iiii  iiii iiii
				iiii iiii  iiii iiii  iiii iiii  iiii iiii)
				* Effect:  _CODE(PUSH(imm64);)
	* Group 3:  _CODE(arg), _CODE(var), _CODE(get\_pc)
		* Encoding:  _CODE(0000 0011  oooo oooo)
			* o:  opcode
		* List:
			* _BOLD(arg)
				* OPCODE(0x00)
				* Effect:  _CODE(PUSH(FP() - 8);)
			* _BOLD(var)
				* OPCODE(0x01)
				* Effect:  _CODE(PUSH(FP() + 16);)
			* _BOLD(get\_pc)
				* OPCODE(0x02)
				* Effect:  _CODE(PUSH(PC());)
	* Group 4:  _CODE(argx), _CODE(varx), _CODE(add\_to\_sp), _CODE(call),
	_CODE(ret)
		* Encoding:  _CODE(0000 0100  oooo oooo)
			* o:  opcode
		* List:
			* _BOLD(argx)
				* OPCODE(0x00)
				* Effect:  _CODE(PUSH(FP() - 8 + POP());)
			* _BOLD(varx)
				* OPCODE(0x01)
				* Effect:  _CODE(PUSH(FP() + 16 + POP());)
			* _BOLD(add\_to\_sp)
				* OPCODE(0x02)
				* Effect:  _CODE(SP() = SP() + POP();)
			* _BOLD(call)
				* OPCODE(0x03)
				* Effect:  
				_CODE({_NEWLINE()
				_TAB()_TAB()address = POP();_NEWLINE()
				_TAB()_TAB()PUSH(PC());_NEWLINE()
				_TAB()_TAB()OLD_FP() = FP();_NEWLINE()
				_TAB()_TAB()FP() = SP();_NEWLINE()
				_TAB()_TAB()PUSH(OLD_FP())_NEWLINE()
				_TAB()_TAB()PC() = address;_NEWLINE()
				})
			* _BOLD(ret)
				* OPCODE(0x04)
				* Effect:  _CODE(_BOLD(return\_sequence());)
			* _BOLD(syscall)
				* OPCODE(0x05)
				* Effect:  _CODE(_BOLD(exec\_syscall(POP()));)
