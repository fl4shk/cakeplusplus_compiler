main:
	[const(8)
	[const(9)
	[const(add)]
	[call]


	[const(0)]
	[quit]


add:
	[const_s8(-16)]
	[argx]

	[arg]
	[ld]

	[const_s8(-8)]
	[argx]
	[ld]

	[add]

	[st]

	[ret]
