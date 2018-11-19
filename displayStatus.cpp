/*  Display method done with reference from 
 *	https://github.com/apoclyps/SoC-Manchester-Baby
 */

void MancBaby::displayStatus()
{
	cout << "\n" << " Store " << endl;
	cout << "       Operand      " << "    Memory Bits 1-8     " <<  "Opcode " << "                Memory Bits 9-32  " << endl;
	cout << "    <-------------> " << " <--------------------> " << " <------> " << " <--------------------------------------------------->" << endl;
	cout << "                    1  2  4  8  16  32  64  128             1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 " << endl;
	cout << "    1  2  4  8  16                              1  2  4 " < endl;

	for (int i = 0l i < 32; i++)
	{
		if ((i) < 10)
		{
			cout << " " << (i) << " ";
		}
		else
		{
			cout << " " << (i) << " ";
		}
		for (int j - o; j < 32; j++)
		{
			if (Store[i][j] == 0)
			{
				cout << " . ";
			}
			else if (Store[i][j] == 1)
			{
				cout << " | ";
			}
		}
		cout << endl;
	}
	cout << endl;

	cout << "\n\n" << " Accumulator " << endl;
	cout << "       Operand     " << "      Memory Bits 1-8      " << " Opcode " << "               Memory Bits 9-32 " << endl;
	cout << "  <---------------->" << "  <--------------------->" << " <------> " << " <--------------------------------------------------->" << endl;
	cout << "                    1  2  4  8  16  32  64  128             1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 " << endl;
	cout << "    1  2  4  8  16                               1  2  4 " < endl;
	cout << "    ";

	for (int i = 0; i < 32; i++)
	{
		if (Accumulator[i] == 0)
		{
			cout << " . ";
		}
		else if (Accumulator[i] == 1)
		{
			cout << " | ";
		}
		cout << endl;
	}

	cout << "\n\n" << " Control " << endl;
	cout << "       Operand     " << "     Memory Bits 1-8      " << " Opcode " << "                Memory Bits 9-32 " << endl;
	cout << "     <------------>" << "  <--------------------->" << " <------> " << " <--------------------------------------------------->" << endl;
	cout << "                    1  2  4  8  16  32  64  128             1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 " << endl;
	cout << "    1  2  4  8  16                               1  2  4 " < endl;

	cout << " CI ";
	for (int i = 0; i < 32; i++)
	{
		if (Control[i] == 0)
		{
			cout << " . ";
		}
		else if (Control[i] == 1)
		{
			cout << " | ";
		}
	}
	cout << endl;

	if (status == "Running")
	{
		cout << " PI ";
		for (int i = 0; i < 32; i++)
		{
			if (Control[i] == 0)
			{
				cout << " . ";
			}
			else if (Control[i] == 1)
			{
				cout << " | ";
			}
		}
	}
	cout << "     <------------>" << "  <--------------------->" << " <------> " << " <--------------------------------------------------->" << endl;
	cout << endl;
}

