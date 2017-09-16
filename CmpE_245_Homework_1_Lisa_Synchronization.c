/**************************************
*    Name: David Bui 006289491        *
*          Monica                     *
*		   Sarv                       *
*		   Sagar                      *
*    Date: 09/16/2017                 *
*    Class: CmpE-245                  *
*    Homework 1: Lisa Synchronization *
**************************************/

#include <stdio.h> 
//#include <string.h>

FILE *stream, *stream2;

#define BUFFER_SIZE 1024
//sync_field is 0x50 0x51 .. 0xae 0xaf 'Hello World!' in ascii
const char *sync_field ="0101000001010001010100100101001101010100010101010101011001010111010110000101100101011010010110110101110001011101010111100101111110100000101000011010001010100011101001001010010110100110101001111010100010101001101010101010101110101100101011011010111010101111010010000110010101101100011011000110111100100000010101110110111101110010011011000110100000100001";
const char hello_world [] = "010010000110010101101100011011000110111100100000010101110110111101110010011011000110010000100001";

void write_to_text_file();
char *copy_text_file();

int main(void) {
	printf("Hello World!\n");
	char *sync_buffer;
	
	char hello_world_string [97];
	char binary_buffer[8];

	strcpy(hello_world_string, hello_world);

	write_to_text_file();
	sync_buffer = copy_text_file();
	printf("SYNC BUFFER: %s\n", sync_buffer);

	printf("This is my hello world: %s\n", hello_world_string);
	for (int i = 0; i < strlen(hello_world_string); i++) {
		if (i >= 0 && i <= 7)
			binary_buffer[i] = hello_world_string[i];
		/*
		if (i >= 8 && i <= 15)
			binary_buffer[i - 8] = hello_world_string[i];
		if (i >= 16 && i <= 23)
			binary_buffer[i - 16] = hello_world_string[i];
		if (i >= 24 && i <= 31)
			binary_buffer[i - 24] = hello_world_string[i];
		if (i >= 32 && i <= 39)
			binary_buffer[i - 32] = hello_world_string[i];
		if (i >= 40 && i <= 47)
			binary_buffer[i - 40] = hello_world_string[i];
		*/
	}
	for (int i = 0; i < sizeof(binary_buffer); i++) {
		printf("HEX?: %x", binary_buffer[i]);
		printf("Binary Buffer: %c\n", binary_buffer[i]);
	}
	printf("Binary Buffer: %s\n", binary_buffer);
	printf("Size: %d\n", sizeof(hello_world_string));

	//FILE *fp = fopen_s("test.txt", "w+");
	//fprintf(fp, "This is testing for fprintf...\n");
	//fputs("This is testing for fputs...\n", fp);
	//fclose(fp);
}


/*This function creates a text file and writes the sync field
and payload to it.*/
void write_to_text_file() {
	errno_t err;
	//Open file for write
	err = fopen_s(&stream, "test.txt", "w+");
	if (err == 0)
		printf("The file 'text.txt' was opened. \n");
	else
		printf("The file 'test.txt' was not opened. \n");

	//fputs("This is or testing fputs\n", stream);
	fputs(sync_field, stream);

	//Close file
	if (stream) {
		err = fclose(stream);
		if (err == 0)
			printf("The file 'test.txt' was closed. \n");
		else
			printf("The file 'test.txt' was not closed. \n");
	}
	return;
}

/*This funciton parses a text file and saves it as a string. */
char *copy_text_file() {
	errno_t err;
	char buff[BUFFER_SIZE];
	//char buff[1024];
	//Open file for write
	err = fopen_s(&stream, "test.txt", "r");
	if (err == 0)
		printf("The file 'text.txt' was opened. \n");
	else
		printf("The file 'test.txt' was not opened. \n");

	fgets(buff, 1024, stream);
	//fgets(buff, 1024, stream);
	//printf("String read: %s\n", buff);

	//Close file
	if (stream) {
		err = fclose(stream);
		if (err == 0)
			printf("The file 'test.txt' was closed. \n");
		else
			printf("The file 'test.txt' was not closed. \n");
	}
	return buff;
}
