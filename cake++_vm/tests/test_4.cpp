s64 main()
{
	u8 buf[200];

	//getline(buf);

	//disp_str_as_numbers(buf);

	buf[0] = buf[1] * buf[2];

}

//u64 getline(u8 buf[])
//{
//	u64 buf_len;
//	buf_len = len(buf);
//
//
//	u64 i;
//	i = 0;
//
//	{
//
//	// You can indeed name a variable "char" in this language.
//	u8 char;
//	do
//	{
//		char = getchar();
//		// newline
//		if (char != 10)
//		{
//			buf[i] = char;
//		}
//
//		i += 1;
//
//	} while ((char != 10) && ((i + 1) < buf_len));
//
//	}
//
//	// Null terminate
//	buf[i] = 0;
//
//	return i;
//}
//
//u64 disp_str(u8 str[])
//{
//	u64 buf_len;
//	buf_len = len(str);
//
//	u64 i;
//	i = 0;
//
//	while ((i < buf_len) && (str[i] != 0))
//	{
//		putchar(str[i]);
//		i += 1;
//	}
//
//	//return len(str);
//	return i;
//}
//
//u64 disp_str_as_numbers(u8 str[])
//{
//	u64 buf_len;
//	buf_len = len(str);
//	u64 i;
//	i = 0;
//
//	while ((i < buf_len) && (str[i] != 0))
//	{
//		putn(str[i]);
//
//
//		i += 1;
//
//		if ((i < buf_len) && (str[i] != 0))
//		{
//			disp_comma();
//			disp_space();
//		}
//	}
//	disp_newline();
//
//	return i;
//}
//
//u8 disp_newline()
//{
//	// Ther really should be 
//	putchar(10);
//}
//u8 disp_space()
//{
//	putchar(32);
//}
//
//u8 disp_comma()
//{
//	putchar(44);
//}
//
//u64 fun_func_a(s64 arr[])
//{
//	u64 i;
//	i = 0;
//
//	while (i < len(arr))
//	{
//		arr[i] = i * 8;
//		i += 1;
//	}
//
//	return i;
//}
//
//u64 fun_func_b(s64 arr[])
//{
//	u64 i;
//	i = 0;
//
//	while (i < len(arr))
//	{
//		arr[i] += arr[i];
//		i += 1;
//	}
//
//
//}
//
//u64 disp_arr_s64(s64 arr[])
//{
//	u64 i;
//	i = 0;
//	while (i < len(arr))
//	{
//		putn(arr[i]);
//
//		//if ((i + 1) < len(arr))
//		//{
//		//}
//
//		i += 1;
//
//		if (i < len(arr))
//		{
//			disp_comma();
//			disp_space();
//		}
//	}
//	disp_newline();
//
//	return sizeof(arr);
//}
//
//u64 get_size_s64(s64 a[])
//{
//	return sizeof(a);
//}
//
//u64 clear_arr_s64(s64 to_clear[])
//{
//	u64 i;
//	i = 0;
//
//	while (i < len(to_clear))
//	{
//		to_clear[i] = 0;
//		i += 1;
//	}
//
//	return sizeof(to_clear);
//}
