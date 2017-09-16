/**************************************
*    Name: David Bui 006289491        *
*          Monica                     *
*		   Sarv                       *
*		   Sargay                     *
*    Date: 09/16/2017                 *
*    Class: CmpE-245                  *
*    Homework 1: Lisa Synchronization *
**************************************/

#include <stdio.h> 

FILE *stream, *stream2;

#define BUFFER_SIZE 1024
const char *sync_field ="0101000001010001010100100101001101010100010101010101011001010111010110000101100101011010010110110101110001011101010111100101111110100000101000011010001010100011101001001010010110100110101001111010100010101001101010101010101110101100101011011010111010101111010010000110010101101100011011000110111100100000010101110110111101110010011011000110100000100001";

void write_to_text_file();
char *parse_text_file();

int main(void) {
	printf("Hello World!\n");
	char *sync_buffer;

	write_to_text_file();
	sync_buffer = parse_text_file();
	printf("SYNC BUFFER: %s\n", sync_buffer);

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
char *parse_text_file() {
	errno_t err;
	char buff[BUFFER_SIZE];
	//Open file for write
	err = fopen_s(&stream, "test.txt", "r");
	if (err == 0)
		printf("The file 'text.txt' was opened. \n");
	else
		printf("The file 'test.txt' was not opened. \n");

	fgets(buff, 1024, stream);
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
