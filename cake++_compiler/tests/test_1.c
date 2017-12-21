main()
{
	s64 i;
	s64 temp[3];

	func(temp);


	i = 0;

	while (i < 3)
	{
		putn(temp[i]);
		i = i + 1;
	}
}

add(s64 ret[], s64 a, s64 b)
{
	ret[0] = a + b;
}


func(s64 ret[])
{
	s64 z;

	z = 9000;

	s64 i;
	i = 0;

	{
	s64 temp[1];

	s64 one;
	one = 1;

	while (i < len(ret))
	{
		ret[i] = z;
		//i = i + 1;

		add(temp, i, one);
		i = temp[0];
	}
	}
}
