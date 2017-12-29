u32 main()
{
	u8 six[6];
	s64 temp[3];

	clear_arr(temp);

	//{
	//u64 a;
	//a = ~((5) + (9));
	//}


	{
	u64 i;
	i = 0;

	while (i < len(temp))
	{
		temp[i] = i * 8;
		putn(temp[i]);

		{
		u64 one;
		one = 1;

		i = add_u64(i, one);
		}
	}

	}
}

u32 clear_arr(s64 ret[])
{
	u64 i;
	i = 0;

	while (i < len(ret))
	{
		ret[i] = 0;
		i = i + 1;
	}
}

u64 add_u64(u64 a, u64 b)
{
	return (a + b);
}

s64 add_s64(s64 a, s64 b)
{
	return (a + b);
}
