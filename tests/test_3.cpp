s64 main()
{
	s64 temp[3];

	//putn(len(temp));
	return get_size_s64(temp);
}

u64 get_size_s64(s64 a[])
{
	//return clear_arr_s64(a);
	return sizeof(a);
}

//u64 clear_arr_s64(s64 to_clear[])
//{
//	u32 i;
//	i = 0;
//
//	u64 ret;
//	ret = 0;
//	//ret = ret + sizeof(ret);
//	{
//	u64 temp;
//	temp = sizeof(ret);
//	ret = add_u64(ret, temp);
//	}
//
//	while (i < len(to_clear))
//	{
//		to_clear[i] = 0;
//		//i = i + 1;
//		putn(i);
//
//		{
//		u32 one;
//		one = 1;
//		i = add_u32(i, one);
//		}
//
//		//ret += sizeof(ret);
//		//ret = add(ret, sizeof(ret));
//		{
//		u64 temp;
//		temp = sizeof(ret);
//		ret = add_u64(ret, temp);
//		}
//	}
//
//	//return sizeof(ret);
//	return ret;
//}

//u64 add_u64(u64 a, u64 b)
//{
//	return (a + b);
//}
//
//s64 add_s64(s64 a, s64 b)
//{
//	return (a + b);
//}

u32 add_u32(u32 a, u32 b)
{
	//return (a + b);
	u32 ret;
	ret = a + b;
	return ret;
}
