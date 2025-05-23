int compute_number(int sample_value, int temp_value, int dist_value)
{
    int ulong_a = sample_value;

	ulong_a = ((ulong_a >> 16u) ^ temp_value) * 0x45d9f3b;
    ulong_a = (ulong_a >> 16u) ^ ulong_a;
	ulong_a = ((ulong_a >> 16u) ^ dist_value) * 0x45d9f3b;

	return ulong_a;
}
