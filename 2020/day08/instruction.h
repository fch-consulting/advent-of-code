struct instruction {
	char *operation;
	signed int argument;
};

void print_instruction(struct instruction *input);

struct instruction *build_instruction(char *input);

struct instruction **copy_inst(struct instruction **input, size_t size);

void free_instructions(struct instruction **instructions, size_t size);

struct instruction **nop_jmp(struct instruction **instructions, size_t size, size_t next);
