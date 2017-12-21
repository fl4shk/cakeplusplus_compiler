//peanut_butter(s64 a, s64 b[], s64 aa[])
//{
//	s64 i;
//
//	i = 0;
//
//	while (i < len(b))
//	{
//		b[i] = 20;
//		i = i + 1;
//	}
//}

add(s64 a, s64 b, s64 ret[])
{
	s64 z;
	z = 7;

	s64 i;

	while (i < 3)
	{
		ret[i] = z;
		i = i + 1;
	}

	add(a, b, ret);
}
