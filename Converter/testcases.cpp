void TestCase0()
{
	// Test case: dynamic reallocation with fixed size array
	// Init Alloc
	const int size = 8;
	char* block = new char[size];

	// Create temp ptr to original block
	char* temp = block;

	// ALloc
	const int new_size = size * 2;
	block = new char[new_size];

	// Copy from old to new block
	// Only copy what is actually part of the old block
	for (int i = 0; i < size; ++i)
		block[i] = temp[i];

	// Free
	delete[] temp;
	temp = nullptr;
}