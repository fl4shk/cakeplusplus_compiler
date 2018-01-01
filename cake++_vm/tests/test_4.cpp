s64 main()
{
	s64 arr[10];

	//arr[0] = 9 + sizeof(arr);
	//arr[1] = 8 + sizeof(arr);
	//arr[2] = 7 + sizeof(arr);
	//arr[3] = 6 + sizeof(arr);
	//arr[4] = 5 + sizeof(arr);
	//arr[5] = 4 + sizeof(arr);
	//arr[6] = 3 + sizeof(arr);
	//arr[7] = 2 + sizeof(arr);
	//arr[8] = 1 + sizeof(arr);
	//arr[9] = 0 + sizeof(arr);

	//{
	//u8 i;
	//i = 0;

	//u64 j;
	////j = len(arr) - 1;
	////j = len(arr);
	////j = j - 1;

	//while (i < len(arr))
	//{
	//	arr[i] = j;
	//	//j = j + 1;
	//	//j = (1 - j);
	//	//j = j - 1;
	//	//j = j - 1;
	//	//j = 5 - 6;
	//	//i = i + (-1);
	//}
	//}

	//return disp_arr_s64(arr);

	u8 i;
	i = 1;
	//i = i + (-1);
	//i = i - 1;
	//i = i + (-1);
	//i = (-i);
	//i = -i;
	//return i;
	//return - 1;
	putn(i);
	i = i - 1;
	putn(i);
	i = i - 1;
	//return i;
	putn(i);

	return -1;
}

u64 disp_arr_s64(s64 arr[])
{
	u64 i;
	i = 0;
	while (i < len(arr))
	{
		//putn(i);
		putn(arr[i]);
		i = i + 1;
	}

	return sizeof(arr);
}

//s64 main()
//{
//	//s64 arr[9000];
//	s64 arr[10];
//
//	clear_arr_s64(arr);
//
//	u64 i;
//	i = 0;
//
//	while (i < len(arr))
//	{
//		arr[i] = i * sizeof(arr);
//		putn(arr[i]);
//		i = i + 1;
//	}
//
//	clear_arr_s64(arr);
//	putn(-1);
//	putn(-1);
//
//	i = 0;
//	while (i < len(arr))
//	{
//		putn(arr[i]);
//		i = i + 1;
//	}
//
//
//
//
//	return 0;
//}
//
//u64 get_size_s64(s64 a[])
//{
//	//return clear_arr_s64(a);
//	return sizeof(a);
//}
//
//u64 clear_arr_s64(s64 to_clear[])
//{
//	u32 i;
//	//u64 i;
//	i = 0;
//
//	while (i < len(to_clear))
//	{
//		to_clear[i] = 0;
//		i = i + 1;
//	}
//
//	return sizeof(to_clear);
//}
