/**************************************
*    Name: David Bui 006289491        *
*          Monica                     *
*		   Sarv                       *
*		   Sagar                      *
*    Date: 09/16/2017                 *
*    Class: CmpE-245                  *
*    Homework 1: Lisa Synchronization *
**************************************/

/*Assumptions
Confidence level is based on consecutive kernels
Must have starting 0x50 in order to gather confidence level
Must be consecutive 0x50 0x51 in order to pass, even if 0xa0 to 0xaf pass. */

#include <stdio.h> 
//#include <string.h>
#include <stdlib.h>

FILE *stream, *stream2;

#define BUFFER_SIZE 1024
//sync_field is 0x50 0x51 .. 0xae 0xaf 'Hello World!' in ascii
const char sync_field [] =	"01010000"
							"01010001"
							"01010010"
							"0101001101010100010101010101011001010111010110000101100101011010010110110101110001011101010111100101111110100000101000011010001010100011101001001010010110100110101001111010100010101001101010101010101110101100101011011010111010101111010010000110010101101100011011000110111100100000010101110110111101110010011011000110100000100001";
const char hello_world [] = "010010000110010101101100011011000110111100100000010101110110111101110010011011000110010000100001";
const char sync_kernel[] = "01010000"; //0x50

void write_to_text_file();
char *copy_text_file();

int main(void) {
	printf("Hello World!\n");
	char *sync_buffer_input;
	char sync_buffer[1024];

	char sync_field_1[] =	"00000000" //FAKE
							"00010001" //FAKE
							"01010000" //0x50
							"01010001" //0x51
							"01010010" //0x52
							"01010011" //0x53
							"01010100" //0x54
							"01010101" //0x55
							"01010110" //0x56
							"01010111" //0x57
							"01011000" //0x58
							"01011001" //0x59
							"01011010" //0x5a
							"01011011" //0x5b
							"01011100" //0x5c
							"01011101" //0x5d
							"01011110" //0x5e
							"01011111" //0x5f
							"10100000" //0xa0
							"10100001" //0xa1
							"10100010" //0xa2
							"10100011" //0xa3
							"10100100" //0xa4
							"10100101" //0xa5
							"10100110" //0xa6
							"10100111" //0xa7
							"10101000" //0xa8
							"10101001" //0xa9
							"10101010" //0xaa
							"10101011" //0xab
							"10101100" //0xac
							"10101101" //0xad
							"10101110" //0xae
							"10101111" //0xaf
							"010010000110010101101100011011000110111100100000010101110110111101110010011011000110100000100001";
	char hello_world_1[] = "010010000110010101101100011011000110111100100000010101110110111101110010011011000110010000100001";
	char sync_kernel_0[] = "01010000"; //0x50
	char sync_kernel_1[] = "01010001"; //0x51
	char sync_kernel_2[] = "01010010"; //0x52
	char sync_kernel_3[] = "01010011"; //0x53
	char sync_kernel_4[] = "01010100"; //0x54
	char sync_kernel_5[] = "01010101"; //0x55
	char sync_kernel_6[] = "01010110"; //0x56
	char sync_kernel_7[] = "01010111"; //0x57
	char sync_kernel_8[] = "01011000"; //0x58
	char sync_kernel_9[] = "01011001"; //0x59
	char sync_kernel_10[] = "01011010"; //0x5a
	char sync_kernel_11[] = "01011011"; //0x5b
	char sync_kernel_12[] = "01011100"; //0x5c
	char sync_kernel_13[] = "01011101"; //0x5d
	char sync_kernel_14[] = "01011110"; //0x5e
	char sync_kernel_15[] = "01011111"; //0x5f
	char sync_kernel_16[] = "10100000"; //0xa0
	char sync_kernel_17[] = "10100001"; //0xa1
	char sync_kernel_18[] = "10100010"; //0xa2
	char sync_kernel_19[] = "10100011"; //0xa3
	char sync_kernel_20[] = "10100100"; //0xa4
	char sync_kernel_21[] = "10100101"; //0xa5
	char sync_kernel_22[] = "10100110"; //0xa6
	char sync_kernel_23[] = "10100111"; //0xa7
	char sync_kernel_24[] = "10101000"; //0xa8
	char sync_kernel_25[] = "10101001"; //0xa9
	char sync_kernel_26[] = "10101010"; //0xaa
	char sync_kernel_27[] = "10101011"; //0xab
	char sync_kernel_28[] = "10101100"; //0xac
	char sync_kernel_29[] = "10101101"; //0xad
	char sync_kernel_30[] = "10101110"; //0xae
	char sync_kernel_31[] = "10101111"; //0xaf
	
	char hello_world_string [97];
	char binary_buffer[8];

	strcpy(hello_world_string, hello_world);

	write_to_text_file();
	sync_buffer_input = copy_text_file();
	printf("SYNC BUFFER: %s\n", sync_buffer_input);
	printf("adsfasfd: %c\n", sync_buffer_input[1]);

	for (int i = 0; i < 1024; i++)
		sync_buffer[i] = sync_buffer_input[i];

	/*
	printf("Size of sync_field: %d\n", sizeof(sync_field));
	printf("Size of hello_world: %d\n", sizeof(hello_world));
	printf("Size of sync_kernel: %d\n", sizeof(sync_kernel));

	printf("Size of sync_field_1: %d\n", sizeof(sync_field_1));
	printf("Size of hello_world_1: %d\n", sizeof(hello_world_1));
	printf("Size of sync_kernel_0: %d\n", sizeof(sync_kernel_0));
	*/
	int confidence_level = '0';
	printf("Ask user for confidence level\n");
	scanf_s("%d", &confidence_level, 1);
	
	//scanf("%d", &confidence_level);

	//printf("This is the confidence level: %d\n", confidence_level);
	
	int confidence_level_count = 0;
	int payload_start = 0;
	int payload_start_count = 0;
	int success_count = 0;
	int sync_field_iterator_1 = 0;
	int sync_field_iterator = 0;
	int sync_field_iterator_find = 0;
	int stop = 0;

	/*
	//Find start of sync field
	//Save payload start position
	for (sync_field_iterator_find = 0; sync_field_iterator_find < sizeof(sync_field_1); sync_field_iterator_find++) {
		//Confidence Level 0
		for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_0); sync_kernel_iterator++) {
			if (sync_kernel_0[sync_kernel_iterator] == sync_field_1[sync_field_iterator_find + sync_kernel_iterator]) {
				//printf("match\n");
				if (stop != 1)
					success_count++;
			}
			else {
				//printf("NONONONONNONON MATCH\n");
				success_count = 0;
			}
			if (success_count == 8) {
				printf("MATCH 0x50 "); //0xA0 and 0xA1 will cause a match with 0x50
										//0x50 = 01010000
										//0xA0 0xA1 = 1010000'0 1010000'1
				printf("%d\n", sync_field_iterator_find);
				sync_field_iterator = sync_field_iterator_find;
				stop = 1;
				success_count = 0;
				//success_count = 0;
				//break;
				//sync_field_iterator = sync_field_iterator_find;

			}
		}
		if (success_count == 8)
			break;
	}

	//sync_field_iterator = sync_field_iterator_find;
	sync_field_iterator_1 = sync_field_iterator;
	for (sync_field_iterator = sync_field_iterator_1; sync_field_iterator < sizeof(sync_field_1); sync_field_iterator++) {
		//Confidence Level 0
		if (confidence_level_count < confidence_level && sync_field_iterator == sync_field_iterator_1) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_0); sync_kernel_iterator++) {
				if (sync_kernel_0[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x50 "); //0xA0 and 0xA1 will cause a match with 0x50
									 //0x50 = 01010000
									 //0xA0 0xA1 = 1010000'0 1010000'1
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 256;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 1
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 8)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_1); sync_kernel_iterator++) {
				if (sync_kernel_1[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x51 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 248;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 2
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 16)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_2); sync_kernel_iterator++) {
				if (sync_kernel_2[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x52 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 240;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 3
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 24)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_3); sync_kernel_iterator++) {
				if (sync_kernel_3[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x53 "); 
					//printf("MATCH Sync Kernel 3: ");
					//for (int i = 0; i < 8; i++)
					//	printf("%c", sync_kernel_3[i]);
					//printf("\n");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 232;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 4
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 32)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_4); sync_kernel_iterator++) {
				if (sync_kernel_4[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x54 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 224;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 5
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 40)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_5); sync_kernel_iterator++) {
				if (sync_kernel_5[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x55 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 216;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 6
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 48)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_6); sync_kernel_iterator++) {
				if (sync_kernel_6[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x56 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 208;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 7
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 56)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_7); sync_kernel_iterator++) {
				if (sync_kernel_7[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x57 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 200;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 8
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 64)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_8); sync_kernel_iterator++) {
				if (sync_kernel_8[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x58 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 192;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 9
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1+ 72)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_9); sync_kernel_iterator++) {
				if (sync_kernel_9[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x59 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 184;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 10
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 80)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_10); sync_kernel_iterator++) {
				if (sync_kernel_10[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x5a ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 176;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 11
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 88)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_11); sync_kernel_iterator++) {
				if (sync_kernel_11[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x5b ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 168;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 12
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 96)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_12); sync_kernel_iterator++) {
				if (sync_kernel_12[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x5c ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 160;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 13
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 104)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_13); sync_kernel_iterator++) {
				if (sync_kernel_13[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x5d ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 152;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 14
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 112)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_14); sync_kernel_iterator++) {
				if (sync_kernel_14[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x5e ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 144;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 15
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 120)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_15); sync_kernel_iterator++) {
				if (sync_kernel_15[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x5f ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 136;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 16
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 128)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_16); sync_kernel_iterator++) {
				if (sync_kernel_16[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xa0 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 128;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 17
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 136)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_17); sync_kernel_iterator++) {
				if (sync_kernel_17[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xa1 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 120;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 18
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 144)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_18); sync_kernel_iterator++) {
				if (sync_kernel_18[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xa2 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 112;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 19
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 152)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_19); sync_kernel_iterator++) {
				if (sync_kernel_19[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xa3 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 104;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 20
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 160)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_20); sync_kernel_iterator++) {
				if (sync_kernel_20[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xa4 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 96;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 21
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 168)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_21); sync_kernel_iterator++) {
				if (sync_kernel_21[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xa5 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 88;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 22
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 176)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_22); sync_kernel_iterator++) {
				if (sync_kernel_22[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xa6 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 80;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 23
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 184)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_23); sync_kernel_iterator++) {
				if (sync_kernel_23[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xa7 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 72;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 24
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 192)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_24); sync_kernel_iterator++) {
				if (sync_kernel_24[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xa8 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 64;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 25
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 200)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_25); sync_kernel_iterator++) {
				if (sync_kernel_25[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xa9 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 56;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 26
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 208)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_26); sync_kernel_iterator++) {
				if (sync_kernel_26[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xaa ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 48;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 27
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 216)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_27); sync_kernel_iterator++) {
				if (sync_kernel_27[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xab ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 40;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 28
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 224)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_28); sync_kernel_iterator++) {
				if (sync_kernel_28[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xac ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 32;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 29
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 232)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_29); sync_kernel_iterator++) {
				if (sync_kernel_29[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xad ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 24;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 30
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 240)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_30); sync_kernel_iterator++) {
				if (sync_kernel_30[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xae ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 16;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 31
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 248)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_31); sync_kernel_iterator++) {
				if (sync_kernel_31[sync_kernel_iterator] == sync_field_1[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xaf ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 8;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
	}
	*/
	printf("asdfsadfasfd %c\n", sync_buffer[1]);
	//Find start of sync field
	//Save payload start position
	for (sync_field_iterator_find = 0; sync_field_iterator_find < sizeof(sync_buffer); sync_field_iterator_find++) {
		//Confidence Level 0
		for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_0); sync_kernel_iterator++) {
			if (sync_kernel_0[sync_kernel_iterator] == sync_buffer[sync_field_iterator_find + sync_kernel_iterator]) {
				//printf("match\n");
				if (stop != 1)
					success_count++;
			}
			else {
				//printf("NONONONONNONON MATCH\n");
				success_count = 0;
			}
			if (success_count == 8) {
				printf("MATCH 0x50 "); //0xA0 and 0xA1 will cause a match with 0x50
									   //0x50 = 01010000
									   //0xA0 0xA1 = 1010000'0 1010000'1
				printf("%d\n", sync_field_iterator_find);
				sync_field_iterator = sync_field_iterator_find;
				stop = 1;
				success_count = 0;
				//success_count = 0;
				//break;
				//sync_field_iterator = sync_field_iterator_find;

			}
		}
		if (success_count == 8)
			break;
	}

	//sync_field_iterator = sync_field_iterator_find;
	sync_field_iterator_1 = sync_field_iterator;
	for (sync_field_iterator = sync_field_iterator_1; sync_field_iterator < sizeof(sync_buffer); sync_field_iterator++) {
		//Confidence Level 0
		if (confidence_level_count < confidence_level && sync_field_iterator == sync_field_iterator_1) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_0); sync_kernel_iterator++) {
				if (sync_kernel_0[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x50 "); //0xA0 and 0xA1 will cause a match with 0x50
										   //0x50 = 01010000
										   //0xA0 0xA1 = 1010000'0 1010000'1
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 256;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 1
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 8)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_1); sync_kernel_iterator++) {
				if (sync_kernel_1[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x51 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 248;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 2
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 16)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_2); sync_kernel_iterator++) {
				if (sync_kernel_2[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x52 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 240;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 3
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 24)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_3); sync_kernel_iterator++) {
				if (sync_kernel_3[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x53 ");
					//printf("MATCH Sync Kernel 3: ");
					//for (int i = 0; i < 8; i++)
					//	printf("%c", sync_kernel_3[i]);
					//printf("\n");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 232;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 4
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 32)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_4); sync_kernel_iterator++) {
				if (sync_kernel_4[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x54 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 224;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 5
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 40)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_5); sync_kernel_iterator++) {
				if (sync_kernel_5[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x55 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 216;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 6
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 48)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_6); sync_kernel_iterator++) {
				if (sync_kernel_6[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x56 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 208;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 7
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 56)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_7); sync_kernel_iterator++) {
				if (sync_kernel_7[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x57 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 200;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 8
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 64)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_8); sync_kernel_iterator++) {
				if (sync_kernel_8[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x58 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 192;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 9
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 72)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_9); sync_kernel_iterator++) {
				if (sync_kernel_9[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x59 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 184;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 10
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 80)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_10); sync_kernel_iterator++) {
				if (sync_kernel_10[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x5a ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 176;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 11
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 88)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_11); sync_kernel_iterator++) {
				if (sync_kernel_11[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x5b ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 168;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 12
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 96)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_12); sync_kernel_iterator++) {
				if (sync_kernel_12[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x5c ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 160;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 13
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 104)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_13); sync_kernel_iterator++) {
				if (sync_kernel_13[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x5d ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 152;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 14
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 112)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_14); sync_kernel_iterator++) {
				if (sync_kernel_14[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x5e ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 144;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 15
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 120)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_15); sync_kernel_iterator++) {
				if (sync_kernel_15[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0x5f ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 136;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 16
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 128)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_16); sync_kernel_iterator++) {
				if (sync_kernel_16[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xa0 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 128;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 17
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 136)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_17); sync_kernel_iterator++) {
				if (sync_kernel_17[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xa1 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 120;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 18
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 144)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_18); sync_kernel_iterator++) {
				if (sync_kernel_18[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xa2 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 112;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 19
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 152)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_19); sync_kernel_iterator++) {
				if (sync_kernel_19[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xa3 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 104;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 20
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 160)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_20); sync_kernel_iterator++) {
				if (sync_kernel_20[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xa4 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 96;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 21
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 168)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_21); sync_kernel_iterator++) {
				if (sync_kernel_21[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xa5 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 88;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 22
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 176)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_22); sync_kernel_iterator++) {
				if (sync_kernel_22[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xa6 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 80;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 23
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 184)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_23); sync_kernel_iterator++) {
				if (sync_kernel_23[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xa7 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 72;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 24
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 192)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_24); sync_kernel_iterator++) {
				if (sync_kernel_24[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xa8 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 64;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 25
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 200)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_25); sync_kernel_iterator++) {
				if (sync_kernel_25[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xa9 ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 56;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 26
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 208)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_26); sync_kernel_iterator++) {
				if (sync_kernel_26[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xaa ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 48;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 27
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 216)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_27); sync_kernel_iterator++) {
				if (sync_kernel_27[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xab ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 40;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 28
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 224)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_28); sync_kernel_iterator++) {
				if (sync_kernel_28[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xac ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 32;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 29
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 232)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_29); sync_kernel_iterator++) {
				if (sync_kernel_29[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xad ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 24;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 30
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 240)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_30); sync_kernel_iterator++) {
				if (sync_kernel_30[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xae ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 16;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
		//Confidence Level 31
		if (confidence_level_count < confidence_level && sync_field_iterator == (sync_field_iterator_1 + 248)) {
			for (int sync_kernel_iterator = 0; sync_kernel_iterator < sizeof(sync_kernel_31); sync_kernel_iterator++) {
				if (sync_kernel_31[sync_kernel_iterator] == sync_buffer[sync_field_iterator + sync_kernel_iterator]) {
					//printf("match\n");
					success_count++;
				}
				else {
					//printf("NONONONONNONON MATCH\n");
					success_count = 0;
				}
				if (success_count == 8) {
					printf("MATCH 0xaf ");
					printf("%d\n", sync_field_iterator);
					success_count = 0;
					confidence_level_count++;
					payload_start = sync_field_iterator + 8;
					printf("Payload Start: %d\n", payload_start);
					printf("Confidence Level: %d\n", confidence_level);
					printf("Confidence Level Count: %d\n", confidence_level_count);

				}
			}
		}
	}

	//Print the payload
	for (int i = payload_start; i < (sizeof(sync_field_1)); i++)
		printf("This is the payload: %c\n", sync_field_1[i]);
	
	

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
