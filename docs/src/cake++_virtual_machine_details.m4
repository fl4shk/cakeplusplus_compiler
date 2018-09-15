include(src/include/misc_defines.m4)dnl
define(`OPCODE', `Opcode:  _CODE($1)')dnl
define(`PUSH', `_BOLD(push)($1)')dnl
define(`POP', `_BOLD(pop)($1)')dnl
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
* Instructions:
	* Group 0:  Non-immediate Arithmetic/Logic instructions,
	Non-immediate-indexed loads and stores
		* Encoding:  _CODE(0000 0000  oooo oooo)
			* o:  opcode
		* List:
			* _BOLD(add)
				* OPCODE(0x00)
				* Effect:  _CODE(PUSH(POP() + POP()))
			* _BOLD(sub)
				* OPCODE(0x01)
				* Effect:  _CODE(PUSH(POP() - POP()))
			* _BOLD(mul)
				* OPCODE(0x02)
				* Effect:  _CODE(PUSH(POP() * POP()))
			* _BOLD(udiv)
				* OPCODE(0x03)
				* Note:  divide unsigned
				* Effect:  _CODE(PUSH(POP() udiv POP()))
			* _BOLD(sdiv)
				* OPCODE(0x04)
				* Note:  divide signed
				* Effect:  _CODE(PUSH(POP() sdiv POP()))
			* _BOLD(umod)
				* OPCODE(0x05)
				* Note:  modulo unsigned
				* Effect:  _CODE(PUSH(POP() umod POP()))
			* _BOLD(smod)
				* OPCODE(0x05)
				* Note:  modulo signed
				* Effect:  _CODE(PUSH(POP() smod POP()))
			* _BOLD(uslt)
				* OPCODE(0x06)
				* Note:  set less than unsigned
				* Effect:  _CODE(PUSH(POP() uslt POP()))
			* _BOLD(sslt)
				* OPCODE(0x06)
				* Note:  set less than signed
				* Effect:  _CODE(PUSH(POP() sslt POP()))
			* _BOLD(and)
				* OPCODE(0x07)
				* Note:  bitwise and
				* Effect:  _CODE(PUSH(POP() & POP()))
			* _BOLD(or)
				* OPCODE(0x08)
				* Note:  bitwise or
				* Effect:  _CODE(PUSH(POP() | POP()))
			* _BOLD(xor)
				* OPCODE(0x09)
				* Note:  bitwise xor
				* Effect:  _CODE(PUSH(POP() ^ POP()))
			* _BOLD(lsl)
				* OPCODE(0x0a)
				* Note:  logical shift left
				* Effect:  _CODE(PUSH(POP() << POP()))
			* _BOLD(lsr)
				* OPCODE(0x0b)
				* Note:  logical shift right
				* Effect:  _CODE(PUSH(POP() lsr POP()))
			* _BOLD(asr)
				* OPCODE(0x0c)
				* Note:  arithmetic shift right
				* Effect:  _CODE(PUSH(POP() asr POP()))
			* _BOLD(ldux8)
				* OPCODE(0x0d)
				* Effect:  _CODE(PUSH(_ZERO_EXTEND_TO_64(MEM8(POP()
				\+ POP()))))
			* _BOLD(ldsx8)
				* OPCODE(0x0e)
				* Effect:  _CODE(PUSH(_SIGN_EXTEND_TO_64(MEM8(POP()
				\+ POP()))))
			* _BOLD(ldux16)
				* OPCODE(0x0f)
				* Effect:  _CODE(PUSH(_ZERO_EXTEND_TO_64(MEM16(POP()
				\+ POP()))))
			* _BOLD(ldsx16)
				* OPCODE(0x10)
				* Effect:  _CODE(PUSH(_SIGN_EXTEND_TO_64(MEM16(POP()
				\+ POP()))))
			* _BOLD(ldux32)
				* OPCODE(0x11)
				* Effect:  _CODE(PUSH(_ZERO_EXTEND_TO_64(MEM32(POP()
				\+ POP()))))
			* _BOLD(ldsx32)
				* OPCODE(0x12)
				* Effect:  _CODE(PUSH(_SIGN_EXTEND_TO_64(MEM32(POP()
				\+ POP()))))
			* _BOLD(ldx64)
				* OPCODE(0x13)
				* Effect:  _CODE(PUSH(MEM64(POP() + POP())))
			* _BOLD(stx8)
				* OPCODE(0x14)
				* Effect:  _CODE(MEM8(POP() + POP()) = (POP()[7:0]))
			* _BOLD(stx16)
				* OPCODE(0x15)
				* Effect:  _CODE(MEM16(POP() + POP()) = (POP()[15:0]))
			* _BOLD(stx32)
				* OPCODE(0x16)
				* Effect:  _CODE(MEM32(POP() + POP()) = (POP()[31:0]))
			* _BOLD(stx64)
				* OPCODE(0x17)
				* Effect:  _CODE(MEM64(POP() + POP()) = POP())
	* Group 1:  Immediate arithmetic/logic instructions, immediate-indexed
	loads and stores, 
		* Encoding:  _CODE(0000 0001  oooo oooo  iiii iiii  iiii iiii)
			* o:  opcode
			* i:  sign-extended 16-bit immediate
		* List:
			* _BOLD(addi simm16)
				* OPCODE(0x00)
				* Effect:  _CODE(PUSH(POP()
				\+ _SIGN_EXTEND_TO_64(simm16)))
			* _BOLD(subi simm16)
				* OPCODE(0x01)
				* Effect:  _CODE(PUSH(POP()
				\- _SIGN_EXTEND_TO_64(simm16)))
			* _BOLD(muli simm16)
				* OPCODE(0x02)
				* Effect:  _CODE(PUSH(POP()
				\* _SIGN_EXTEND_TO_64(simm16)))
			* _BOLD(udivi simm16)
				* OPCODE(0x03)
				* Note:  divide unsigned
				* Effect:  _CODE(PUSH(POP()
				udiv _SIGN_EXTEND_TO_64(simm16)))
			* _BOLD(sdivi simm16)
				* OPCODE(0x04)
				* Note:  divide signed
				* Effect:  _CODE(PUSH(POP()
				sdiv _SIGN_EXTEND_TO_64(simm16)))
			* _BOLD(umodi simm16)
				* OPCODE(0x05)
				* Note:  modulo unsigned
				* Effect:  _CODE(PUSH(POP()
				umod _SIGN_EXTEND_TO_64(simm16)))
			* _BOLD(smodi simm16)
				* OPCODE(0x05)
				* Note:  modulo signed
				* Effect:  _CODE(PUSH(POP()
				smod _SIGN_EXTEND_TO_64(simm16)))
			* _BOLD(uslti simm16)
				* OPCODE(0x06)
				* Note:  set less than unsigned
				* Effect:  _CODE(PUSH(POP()
				uslt _SIGN_EXTEND_TO_64(simm16)))
			* _BOLD(sslti simm16)
				* OPCODE(0x06)
				* Note:  set less than signed
				* Effect:  _CODE(PUSH(POP() sslt POP()))
			* _BOLD(andi simm16)
				* OPCODE(0x07)
				* Note:  bitwise and
				* Effect:  _CODE(PUSH(POP() & POP()))
			* _BOLD(ori simm16)
				* OPCODE(0x08)
				* Note:  bitwise or
				* Effect:  _CODE(PUSH(POP() | POP()))
			* _BOLD(xori simm16)
				* OPCODE(0x09)
				* Note:  bitwise xor
				* Effect:  _CODE(PUSH(POP() ^ POP()))
			* _BOLD(lsli simm16)
				* OPCODE(0x0a)
				* Note:  logical shift left
				* Effect:  _CODE(PUSH(POP() << POP()))
			* _BOLD(lsri simm16)
				* OPCODE(0x0b)
				* Note:  logical shift right
				* Effect:  _CODE(PUSH(POP() lsr POP()))
			* _BOLD(asri simm16)
				* OPCODE(0x0c)
				* Note:  arithmetic shift right
				* Effect:  _CODE(PUSH(POP() asr POP()))
			* _BOLD(ldux8i simm16)
				* OPCODE(0x0d)
				* Effect:  _CODE(PUSH(_ZERO_EXTEND_TO_64(MEM8(POP()
				+ _SIGN_EXTEND_TO_64(simm16)))))
			* _BOLD(ldsx8i simm16)
				* OPCODE(0x0e)
				* Effect:  _CODE(PUSH(_SIGN_EXTEND_TO_64(MEM8(POP()
				+ _SIGN_EXTEND_TO_64(simm16)))))
			* _BOLD(ldux16i simm16)
				* OPCODE(0x0f)
				* Effect:  _CODE(PUSH(_ZERO_EXTEND_TO_64(MEM16(POP()
				+ _SIGN_EXTEND_TO_64(simm16)))))
			* _BOLD(ldsx16 simm16)
				* OPCODE(0x10)
				* Effect:  _CODE(PUSH(_SIGN_EXTEND_TO_64(MEM16(POP()
				+ POP()))))
			* _BOLD(ldux32i simm16)
				* OPCODE(0x11)
				* Effect:  _CODE(PUSH(_ZERO_EXTEND_TO_64(MEM32(POP()
				+ _SIGN_EXTEND_TO_64(simm16)))))
			* _BOLD(ldsx32i simm16)
				* OPCODE(0x12)
				* Effect:  _CODE(PUSH(_SIGN_EXTEND_TO_64(MEM32(POP()
				+ _SIGN_EXTEND_TO_64(simm16)))))
			* _BOLD(ldx64i simm16)
				* OPCODE(0x13)
				* Effect:  _CODE(PUSH(MEM64(POP()
				\+ _SIGN_EXTEND_TO_64(simm16))))
			* _BOLD(stx8i simm16)
				* OPCODE(0x14)
				* Effect:  _CODE(MEM8(POP()
				\+ _SIGN_EXTEND_TO_64(simm16)) = (POP()[7:0]))
			* _BOLD(stx16i simm16)
				* OPCODE(0x15)
				* Effect:  _CODE(MEM16(POP()
				\+ _SIGN_EXTEND_TO_64(simm16)) = (POP()[15:0]))
			* _BOLD(stx32i simm16)
				* OPCODE(0x16)
				* Effect:  _CODE(MEM32(POP()
				\+ _SIGN_EXTEND_TO_64(simm16)) = (POP()[31:0]))
			* _BOLD(stx64i simm16)
				* OPCODE(0x17)
				* Effect:  _CODE(MEM64(POP()
				\+ _SIGN_EXTEND_TO_64(simm16)) = POP())
