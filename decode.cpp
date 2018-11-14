void decode(string instruction) {
	int j = 4;
	for (int i = 0; i < 5; i++) {
		operand.at(i) = instruction.at(j)
		j--;
	}
	j = 2;
	for (int i = 0; i < 3; i++) {
		opcode.at(i) = instruction.at(12+j);
		j--;
	}
}