s64 main()
{
	s64 arr[4];

	//arr[0] = arr[1];


	//fun_func_a(arr);
	//disp_arr_s64(arr);

	//return fun_func_b(arr);

	s64 x;
	x = getchar();
	//disp_newline();
	putchar(x);
	disp_newline();
}

u8 disp_newline()
{
	putchar(10);
}
u8 disp_space()
{
	putchar(32);
}

u8 disp_comma()
{
	putchar(44);
}

u64 fun_func_a(s64 arr[])
{
	u64 i;
	i = 0;

	while (i < len(arr))
	{
		arr[i] = i * 8;
		i += 1;
	}

	return i;
}

u64 fun_func_b(s64 arr[])
{
	u64 i;
	i = 0;

	while (i < len(arr))
	{
		arr[i] += arr[i];
		i += 1;
	}


}

u64 disp_arr_s64(s64 arr[])
{
	u64 i;
	i = 0;
	while (i < len(arr))
	{
		putn(arr[i]);

		//if ((i + 1) < len(arr))
		//{
		//}

		i += 1;

		if (i < len(arr))
		{
			disp_comma();
			disp_space();
		}
	}
	disp_newline();

	return sizeof(arr);
}

u64 get_size_s64(s64 a[])
{
	return sizeof(a);
}

u64 clear_arr_s64(s64 to_clear[])
{
	u64 i;
	i = 0;

	while (i < len(to_clear))
	{
		to_clear[i] = 0;
		i += 1;
	}

	return sizeof(to_clear);
}
