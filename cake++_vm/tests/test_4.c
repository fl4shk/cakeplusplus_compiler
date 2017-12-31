s64 main()
{
	//s64 temp[9000];
	s64 temp[10];
	//s64 temp[200];
	//s64 temp[3];

	//putn(len(temp));
	//return get_size_s64(temp);

	//u32 a[1], b[1];

	//a[0] = 3;
	//b[0] = 3;
	//return add_u32(a, b);

	putn(clear_arr_s64(temp));
	return 0;
}

u64 get_size_s64(s64 a[])
{
	//return clear_arr_s64(a);
	return sizeof(a);
}

u64 clear_arr_s64(s64 to_clear[])
{
	u32 i;
	//u64 i;
	i = 0;

	u64 ret;
	ret = 0;

	{
	u64 temp;
	temp = sizeof(temp);
	ret = add_u64(ret, temp);
	}

	while (i < len(to_clear))
	{
		to_clear[i] = 0;

		{
		u64 temp;
		temp = sizeof(temp);
		ret = add_u64(ret, temp);
		}

		{
		u32 one;
		one = 1;
		i = add_u32(i, one);
		}

	}

	//return sizeof(to_clear);
	//return 0;
	return ret;
}

u64 add_u64(u64 a, u64 b)
{
	return (a + b);
}

//s64 add_s64(s64 a, s64 b)
//{
//	return (a + b);
//}

//u32 add_u32(u32 a[], u32 b[])
//{
//	//return (a + b);
//	u32 ret;
//	ret = a[0] + b[0];
//	return ret;
//}

u64 add_u32(u32 a, u32 b)
{
	//putn(a);
	//putn(b);
	u32 ret;
	ret = (a + b);
	//putn(ret);
	return ret;
}
