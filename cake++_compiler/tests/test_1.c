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
		//putn(func(temp));
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

u32 aaaa(s64 z, u32 b)
{
}

//add(s64 ret[], s64 a, s64 b)
//{
//	ret[0] = a + b;
//}
//
//
//func(s64 ret[])
//{
//	s64 z;
//
//	z = 9000;
//
//	s64 i;
//	i = 0;
//
//	{
//	s64 temp[1];
//
//	s64 one;
//	one = 1;
//
//	while (i < len(ret))
//	{
//		ret[i] = z;
//		//i = i + 1;
//
//		add(temp, i, one);
//		i = temp[0];
//	}
//	}
//}
