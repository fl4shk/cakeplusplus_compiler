u32 main()
{
	s64 temp[3];

	clear_arr(temp);

	//{
	//u64 a;
	//a = ~((5) + (9));
	//}


	u64 i;
	i = 0;

	while (i < len(temp))
	{
		putn(temp[i]);
		i = i + 1;
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

u32 add(s64 ret[], s64 a, s64 b)
{
	ret[0] = a + b;
}


u32 func(s64 ret[])
{
	s64 z;

	z = 9000;

	s64 i;
	i = 0;

	{
	s64 one;
	one = 1;

	while (i < len(ret))
	{
		ret[i] = z;
		//i = i + 1;
		
		{
		s64 temp[1];
		add(temp, i, one);
		i = temp[0];
		}
	}
	}

	u32 temp;

	i = 0;

	while (i < len(ret))
	{
		temp = ret[i];
		putn(temp);
		i = i + 1;
	}

	return u32(temp);
}
