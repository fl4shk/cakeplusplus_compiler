s64 main()
{
	//s64 arr[9000];
	s64 arr[10];

	clear_arr_s64(arr);

	u64 i;
	i = 0;

	while (i < len(arr))
	{
		arr[i] = i * sizeof(arr);
		putn(arr[i]);
		i = i + 1;
	}

	clear_arr_s64(arr);
	putn(-1);
	putn(-1);

	i = 0;
	while (i < len(arr))
	{
		putn(arr[i]);
		i = i + 1;
	}




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

	while (i < len(to_clear))
	{
		to_clear[i] = 0;
		i = i + 1;
	}

	return sizeof(to_clear);
}
