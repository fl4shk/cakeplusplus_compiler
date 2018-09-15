 
# Cake++ Virtual Machine Details
* This is a stack machine that uses byte addressing.
* Basic data types supported for arithmetic are
	* `uint64_t`, `int64_t`
* 8 integer types are supported for loads and stores:
	* `uint8_t`, `int8_t`, `uint16_t`, `int16_t`,  `uint32_t`,
	`int32_t`, `uint64_t`, `int64_t`
* Registers:
	* <code><b>pc</b></code>:  program counter
	* <code><b>sp</b></code>:  stack pointer
	* <code><b>fp</b></code>:  frame pointer (points to the start of the stack frame)
* Stack frame:
	* <code><b>fp</b> - <b>arg\_space</b> - 8</code>:  return value
	* <code><b>fp</b> - <b>arg\_space</b></code>:  arguments to this specific call of the
	function, in reverse order.
		* Example:  for a function with two arguments, the first argument
		to the function is at (<code><b>fp</b> - 8</code>), and the second argument to
		the function is at (<code><b>fp</b> - 16</code>)
	* <code><b>fp</b></code>:  return address
	* <code><b>fp</b> + 8</code>:  old <b>fp</b>
	* <code><b>fp</b> + 16</code>:  local variables of this specific call of the
	function
	* <code><b>fp</b> + 16 + <b>var\_space</b></code>:  temporaries (basically just stuff on
	the stack)
* Instructions:
	* Group 0:  Non-immediate Arithmetic/Logic instructions,
	Non-immediate-indexed loads and stores, non-immediate-indexed jumps
		* Encoding:  <code>0000 0000  oooo oooo</code>
			* o:  opcode
		* List:
			* <b>add</b>
				* Opcode:  <code>0x00</code>
				* Effect:  <code><b>push</b>(<b>pop</b>() + <b>pop</b>());</code>
			* <b>sub</b>
				* Opcode:  <code>0x01</code>
				* Effect:  <code><b>push</b>(<b>pop</b>() - <b>pop</b>());</code>
			* <b>mul</b>
				* Opcode:  <code>0x02</code>
				* Effect:  <code><b>push</b>(<b>pop</b>() * <b>pop</b>());</code>
			* <b>udiv</b>
				* Opcode:  <code>0x03</code>
				* Note:  divide unsigned
				* Effect:  <code><b>push</b>(<b>pop</b>() udiv <b>pop</b>());</code>
			* <b>sdiv</b>
				* Opcode:  <code>0x04</code>
				* Note:  divide signed
				* Effect:  <code><b>push</b>(<b>pop</b>() sdiv <b>pop</b>());</code>
			* <b>umod</b>
				* Opcode:  <code>0x05</code>
				* Note:  modulo unsigned
				* Effect:  <code><b>push</b>(<b>pop</b>() umod <b>pop</b>());</code>
			* <b>smod</b>
				* Opcode:  <code>0x05</code>
				* Note:  modulo signed
				* Effect:  <code><b>push</b>(<b>pop</b>() smod <b>pop</b>());</code>
			* <b>uslt</b>
				* Opcode:  <code>0x06</code>
				* Note:  set less than unsigned
				* Effect:  <code><b>push</b>(<b>pop</b>() uslt <b>pop</b>());</code>
			* <b>sslt</b>
				* Opcode:  <code>0x06</code>
				* Note:  set less than signed
				* Effect:  <code><b>push</b>(<b>pop</b>() sslt <b>pop</b>());</code>
			* <b>and</b>
				* Opcode:  <code>0x07</code>
				* Note:  bitwise and
				* Effect:  <code><b>push</b>(<b>pop</b>() & <b>pop</b>());</code>
			* <b>or</b>
				* Opcode:  <code>0x08</code>
				* Note:  bitwise or
				* Effect:  <code><b>push</b>(<b>pop</b>() | <b>pop</b>());</code>
			* <b>xor</b>
				* Opcode:  <code>0x09</code>
				* Note:  bitwise xor
				* Effect:  <code><b>push</b>(<b>pop</b>() ^ <b>pop</b>());</code>
			* <b>lsl</b>
				* Opcode:  <code>0x0a</code>
				* Note:  logical shift left
				* Effect:  <code><b>push</b>(<b>pop</b>() << <b>pop</b>());</code>
			* <b>lsr</b>
				* Opcode:  <code>0x0b</code>
				* Note:  logical shift right
				* Effect:  <code><b>push</b>(<b>pop</b>() lsr <b>pop</b>());</code>
			* <b>asr</b>
				* Opcode:  <code>0x0c</code>
				* Note:  arithmetic shift right
				* Effect:  <code><b>push</b>(<b>pop</b>() asr <b>pop</b>());</code>
			* <b>ldux8</b>
				* Opcode:  <code>0x0d</code>
				* Effect:  <code><b>push</b>(<b>zero\_extend\_to\_64</b>(<b>mem8</b>[<b>pop</b>()
				\+ <b>pop</b>()]));</code>
			* <b>ldsx8</b>
				* Opcode:  <code>0x0e</code>
				* Effect:  <code><b>push</b>(<b>sign\_extend\_to\_64</b>(<b>mem8</b>[<b>pop</b>()
				\+ <b>pop</b>()]));</code>
			* <b>ldux16</b>
				* Opcode:  <code>0x0f</code>
				* Effect:  <code><b>push</b>(<b>zero\_extend\_to\_64</b>(<b>mem16</b>[<b>pop</b>()
				\+ <b>pop</b>()]));</code>
			* <b>ldsx16</b>
				* Opcode:  <code>0x10</code>
				* Effect:  <code><b>push</b>(<b>sign\_extend\_to\_64</b>(<b>mem16</b>[<b>pop</b>()
				\+ <b>pop</b>()]));</code>
			* <b>ldux32</b>
				* Opcode:  <code>0x11</code>
				* Effect:  <code><b>push</b>(<b>zero\_extend\_to\_64</b>(<b>mem32</b>[<b>pop</b>()
				\+ <b>pop</b>()]));</code>
			* <b>ldsx32</b>
				* Opcode:  <code>0x12</code>
				* Effect:  <code><b>push</b>(<b>sign\_extend\_to\_64</b>(<b>mem32</b>[<b>pop</b>()
				\+ <b>pop</b>()]));</code>
			* <b>ldx64</b>
				* Opcode:  <code>0x13</code>
				* Effect:  <code><b>push</b>(<b>mem64</b>[<b>pop</b>() + <b>pop</b>()]);</code>
			* <b>stx8</b>
				* Opcode:  <code>0x14</code>
				* Effect:  <code><b>mem8</b>[<b>pop</b>() + <b>pop</b>()] = (<b>pop</b>()[7:0]);</code>
			* <b>stx16</b>
				* Opcode:  <code>0x15</code>
				* Effect:  <code><b>mem16</b>[<b>pop</b>() + <b>pop</b>()] = (<b>pop</b>()[15:0]);</code>
			* <b>stx32</b>
				* Opcode:  <code>0x16</code>
				* Effect:  <code><b>mem32</b>[<b>pop</b>() + <b>pop</b>()] = (<b>pop</b>()[31:0]);</code>
			* <b>stx64</b>
				* Opcode:  <code>0x17</code>
				* Effect:  <code><b>mem64</b>[<b>pop</b>() + <b>pop</b>()] = <b>pop</b>();</code>
			* <b>jmpx</b>
				* Opcode:  <code>0x18</code>
				* Effect:  <code><b>pc</b> = (<b>pop</b>() + <b>pop</b>());</code>
			* <b>jfal</b>
				* Opcode:  <code>0x19</code>
				* Effect:  <code>cond = <b>pop</b>(); temp = <b>pop</b>(); <br>
				if (cond == 0) { <b>pc</b> = temp; }</code>
			* <b>jtru</b>
				* Opcode:  <code>0x1a</code>
				* Effect:  <code>cond = <b>pop</b>(); temp = <b>pop</b>(); <br>
				if (cond != 0) { <b>pc</b> = temp; }</code>
	* Group 1:  Immediate arithmetic/logic instructions, immediate-indexed
	loads and stores, and jumps that use immediates
		* Encoding:  <code>0000 0001  oooo oooo  iiii iiii  iiii iiii</code>
			* o:  opcode
			* i:  sign-extended 16-bit immediate
		* List:
			* <b>addi simm16</b>
				* Opcode:  <code>0x00</code>
				* Effect:  <code><b>push</b>(<b>pop</b>() + <b>sign\_extend\_to\_64</b>(simm16));</code>
			* <b>subi simm16</b>
				* Opcode:  <code>0x01</code>
				* Effect:  <code><b>push</b>(<b>pop</b>() - <b>sign\_extend\_to\_64</b>(simm16));</code>
			* <b>muli simm16</b>
				* Opcode:  <code>0x02</code>
				* Effect:  <code><b>push</b>(<b>pop</b>() * <b>sign\_extend\_to\_64</b>(simm16));</code>
			* <b>udivi simm16</b>
				* Opcode:  <code>0x03</code>
				* Note:  divide unsigned
				* Effect:  <code><b>push</b>(<b>pop</b>()
				udiv <b>sign\_extend\_to\_64</b>(simm16));</code>
			* <b>sdivi simm16</b>
				* Opcode:  <code>0x04</code>
				* Note:  divide signed
				* Effect:  <code><b>push</b>(<b>pop</b>()
				sdiv <b>sign\_extend\_to\_64</b>(simm16));</code>
			* <b>umodi simm16</b>
				* Opcode:  <code>0x05</code>
				* Note:  modulo unsigned
				* Effect:  <code><b>push</b>(<b>pop</b>()
				umod <b>sign\_extend\_to\_64</b>(simm16));</code>
			* <b>smodi simm16</b>
				* Opcode:  <code>0x05</code>
				* Note:  modulo signed
				* Effect:  <code><b>push</b>(<b>pop</b>()
				smod <b>sign\_extend\_to\_64</b>(simm16));</code>
			* <b>uslti simm16</b>
				* Opcode:  <code>0x06</code>
				* Note:  set less than unsigned
				* Effect:  <code><b>push</b>(<b>pop</b>()
				uslt <b>sign\_extend\_to\_64</b>(simm16));</code>
			* <b>sslti simm16</b>
				* Opcode:  <code>0x06</code>
				* Note:  set less than signed
				* Effect:  <code><b>push</b>(<b>pop</b>()
				sslt <b>sign\_extend\_to\_64</b>(simm16));</code>
			* <b>andi simm16</b>
				* Opcode:  <code>0x07</code>
				* Note:  bitwise and
				* Effect:  <code><b>push</b>(<b>pop</b>() & <b>sign\_extend\_to\_64</b>(simm16));</code>
			* <b>ori simm16</b>
				* Opcode:  <code>0x08</code>
				* Note:  bitwise or
				* Effect:  <code><b>push</b>(<b>pop</b>() | <b>sign\_extend\_to\_64</b>(simm16));</code>
			* <b>xori simm16</b>
				* Opcode:  <code>0x09</code>
				* Note:  bitwise xor
				* Effect:  <code><b>push</b>(<b>pop</b>() ^ <b>sign\_extend\_to\_64</b>(simm16));</code>
			* <b>lsli simm16</b>
				* Opcode:  <code>0x0a</code>
				* Note:  logical shift left
				* Effect:  <code><b>push</b>(<b>pop</b>()
				<< <b>sign\_extend\_to\_64</b>(simm16));</code>
			* <b>lsri simm16</b>
				* Opcode:  <code>0x0b</code>
				* Note:  logical shift right
				* Effect:  <code><b>push</b>(<b>pop</b>()
				lsr <b>sign\_extend\_to\_64</b>(simm16));</code>
			* <b>asri simm16</b>
				* Opcode:  <code>0x0c</code>
				* Note:  arithmetic shift right
				* Effect:  <code><b>push</b>(<b>pop</b>()
				asr <b>sign\_extend\_to\_64</b>(simm16));</code>
			* <b>ldux8i simm16</b>
				* Opcode:  <code>0x0d</code>
				* Effect:  <code><b>push</b>(<b>zero\_extend\_to\_64</b>(<b>mem8</b>[<b>pop</b>()
				+ <b>sign\_extend\_to\_64</b>(simm16)]));</code>
			* <b>ldsx8i simm16</b>
				* Opcode:  <code>0x0e</code>
				* Effect:  <code><b>push</b>(<b>sign\_extend\_to\_64</b>(<b>mem8</b>[<b>pop</b>()
				+ <b>sign\_extend\_to\_64</b>(simm16)]));</code>
			* <b>ldux16i simm16</b>
				* Opcode:  <code>0x0f</code>
				* Effect:  <code><b>push</b>(<b>zero\_extend\_to\_64</b>(<b>mem16</b>[<b>pop</b>()
				+ <b>sign\_extend\_to\_64</b>(simm16)]));</code>
			* <b>ldsx16 simm16</b>
				* Opcode:  <code>0x10</code>
				* Effect:  <code><b>push</b>(<b>sign\_extend\_to\_64</b>(<b>mem16</b>[<b>pop</b>()
				+ <b>pop</b>()]));</code>
			* <b>ldux32i simm16</b>
				* Opcode:  <code>0x11</code>
				* Effect:  <code><b>push</b>(<b>zero\_extend\_to\_64</b>(<b>mem32</b>[<b>pop</b>()
				+ <b>sign\_extend\_to\_64</b>(simm16)]));</code>
			* <b>ldsx32i simm16</b>
				* Opcode:  <code>0x12</code>
				* Effect:  <code><b>push</b>(<b>sign\_extend\_to\_64</b>(<b>mem32</b>[<b>pop</b>()
				+ <b>sign\_extend\_to\_64</b>(simm16)]));</code>
			* <b>ldx64i simm16</b>
				* Opcode:  <code>0x13</code>
				* Effect:  <code><b>push</b>(<b>mem64</b>[<b>pop</b>()
				\+ <b>sign\_extend\_to\_64</b>(simm16)]);</code>
			* <b>stx8i simm16</b>
				* Opcode:  <code>0x14</code>
				* Effect:  <code><b>mem8</b>[<b>pop</b>()
				\+ <b>sign\_extend\_to\_64</b>(simm16)] = (<b>pop</b>()[7:0]);</code>
			* <b>stx16i simm16</b>
				* Opcode:  <code>0x15</code>
				* Effect:  <code><b>mem16</b>[<b>pop</b>()
				\+ <b>sign\_extend\_to\_64</b>(simm16)] = (<b>pop</b>()[15:0]);</code>
			* <b>stx32i simm16</b>
				* Opcode:  <code>0x16</code>
				* Effect:  <code><b>mem32</b>[<b>pop</b>()
				\+ <b>sign\_extend\_to\_64</b>(simm16)] = (<b>pop</b>()[31:0]);</code>
			* <b>stx64i simm16</b>
				* Opcode:  <code>0x17</code>
				* Effect:  <code><b>mem64</b>[<b>pop</b>()
				\+ <b>sign\_extend\_to\_64</b>(simm16)] = <b>pop</b>();</code>
			* <b>jmpxi simm16</b>
				* Opcode:  <code>0x18</code>
				* Effect:  <code><b>pc</b> = (<b>pop</b>()
				\+ <b>sign\_extend\_to\_64</b>(simm16));</code>
			* <b>bfal simm16</b>
				* Opcode:  <code>0x19</code>
				* Effect:  <code>if (<b>pop</b>() == 0) { <b>pc</b> = <b>pc</b>
				\+ <b>sign\_extend\_to\_64</b>(simm16); }</code>
			* <b>btru simm16</b>
				* Opcode:  <code>0x1a</code>
				* Effect:  <code>if (<b>pop</b>() != 0) { <b>pc</b> = <b>pc</b>
				\+ <b>sign\_extend\_to\_64</b>(simm16); }</code>
	* Group 2:  Constants
		* List:
			* <b>constu8 uimm8</b>
				* Encoding:  <code>0000 0010  0000 0000 iiii iiii</code>
				* Effect:  <code><b>push</b>(<b>zero\_extend\_to\_64</b>(uimm8));</code>
			* <b>consts8 simm8</b>
				* Encoding:  <code>0000 0010  0000 0001 iiii iiii</code>
				* Effect:  <code><b>push</b>(<b>sign\_extend\_to\_64</b>(simm8));</code>
			* <b>constu16 uimm16</b>
				* Encoding:  <code>0000 0010  0000 0010
				iiii iiii  iiii iiii</code>
				* Effect:  <code><b>push</b>(<b>zero\_extend\_to\_64</b>(uimm16));</code>
			* <b>consts16 simm16</b>
				* Encoding:  <code>0000 0010  0000 0011
				iiii iiii  iiii iiii</code>
				* Effect:  <code><b>push</b>(<b>sign\_extend\_to\_64</b>(simm16));</code>
			* <b>constu32 uimm32</b>
				* Encoding:  <code>0000 0010  0000 0100
				iiii iiii  iiii iiii  iiii iiii  iiii iiii</code>
				* Effect:  <code><b>push</b>(<b>zero\_extend\_to\_64</b>(uimm32));</code>
			* <b>consts32 simm32</b>
				* Encoding:  <code>0000 0010  0000 0101
				iiii iiii  iiii iiii  iiii iiii  iiii iiii</code>
				* Effect:  <code><b>push</b>(<b>sign\_extend\_to\_64</b>(simm32));</code>
			* <b>const imm64</b>
				* Encoding:  <code>0000 0010  0000 0110
				iiii iiii  iiii iiii  iiii iiii  iiii iiii
				iiii iiii  iiii iiii  iiii iiii  iiii iiii</code>
				* Effect:  <code><b>push</b>(imm64);</code>
	* Group 3:  <code>arg</code>, <code>var</code>, <code>get\_pc</code>
		* Encoding:  <code>0000 0011  oooo oooo</code>
			* o:  opcode
		* List:
			* <b>arg</b>
				* Opcode:  <code>0x00</code>
				* Effect:  <code><b>push</b>(<b>fp</b> - 8);</code>
			* <b>var</b>
				* Opcode:  <code>0x01</code>
				* Effect:  <code><b>push</b>(<b>fp</b> + 16);</code>
			* <b>get\_pc</b>
				* Opcode:  <code>0x02</code>
				* Effect:  <code><b>push</b>(<b>pc</b>);</code>
	* Group 4:  <code>argx</code>, <code>varx</code>, <code>add\_to\_sp</code>, <code>call</code>,
	<code>ret</code>
		* Encoding:  <code>0000 0100  oooo oooo</code>
			* o:  opcode
		* List:
			* <b>argx</b>
				* Opcode:  <code>0x00</code>
				* Effect:  <code><b>push</b>(<b>fp</b> - 8 + <b>pop</b>());</code>
			* <b>varx</b>
				* Opcode:  <code>0x01</code>
				* Effect:  <code><b>push</b>(<b>fp</b> + 16 + <b>pop</b>());</code>
			* <b>add\_to\_sp</b>
				* Opcode:  <code>0x02</code>
				* Effect:  <code><b>sp</b> = <b>sp</b> + <b>pop</b>();</code>
			* <b>call</b>
				* Opcode:  <code>0x03</code>
				* Effect:  
				<code>{<br>
				&emsp;&emsp;address = <b>pop</b>();<br>
				&emsp;&emsp;<b>push</b>(<b>pc</b>);<br>
				&emsp;&emsp;<b>old\_fp</b> = <b>fp</b>;<br>
				&emsp;&emsp;<b>fp</b> = <b>sp</b>;<br>
				&emsp;&emsp;<b>push</b>(<b>old\_fp</b>)<br>
				&emsp;&emsp;<b>pc</b> = address;<br>
				}</code>
			* <b>ret</b>
				* Opcode:  <code>0x04</code>
				* Effect:  <code><b>return\_sequence()</b>;</code>
			* <b>syscall</b>
				* Opcode:  <code>0x05</code>
				* Effect:  <code><b>exec\_syscall(<b>pop</b>())</b>;</code>
