// xlldual.cpp - Dual numbers as vectors
// Copyright (c) 2011 KALX, LLC. All rights reserved. No warranty is made.
#include <iostream>
#include "dual.h"

void fms_test_dual(void);

int main()
{
	try {
		fms_test_dual();
	}
	catch (const std::exception& ex) {
		std::cerr << ex.what() << std::endl;

		return -1;
	}

	return 0;
}