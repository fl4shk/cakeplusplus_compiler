s64 main()
{
	//u8 six[6];
	s64 temp[3];

	//putn(sizeof(temp));

	//putn(clear_arr(temp));
	//return clear_arr(temp);

	//{
	//u64 i;
	//i = 0;

	//while (i < len(temp))
	//{
	//	temp[i] = i * 8;
	//	putn(temp[i]);

	//	i = i + 1;
	//}

	//}


	//if (temp[0] == temp[1])
	//{
	//	temp[2] = 7;
	//}
	//putn(get_size(temp));



	//return 9000;
	putn(len(temp));
	return get_size(temp);
}

u64 get_size(s64 a[])
{
	//return sizeof(a);
	return clear_arr(a);
	//return sizeof(a);
}

u64 clear_arr(s64 ret[])
{
	u64 i;
	i = 0;

	while (i < len(ret))
	{
		ret[i] = 0;
		i = i + 1;
	}

	return sizeof(ret);
}

//u64 add_u64(u64 a, u64 b)
//{
//	return (a + b);
//}
//
//s64 add_s64(s64 a, s64 b)
//{
//	return (a + b);
//}
