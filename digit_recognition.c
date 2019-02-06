// Brian Popeck

#include <stdlib.h>
#include <stdio.h>

#include <string.h>	// memset

// is exactly 794 bytes long (alignment of 1)
typedef struct DataItem {
	unsigned char image[784];
	unsigned char label[10];
} DataItem;

const int NUM_TRAINING_DATA = 5000;

void make_label_array(unsigned char* label_array, unsigned char label);
void get_training_labels(DataItem* training_data, char* filename);
void get_training_images(DataItem* training_data, char* filename);
FILE* open_file(char* filename, char* mode);

int main(int argc, char** argv) {
	DataItem training_data[NUM_TRAINING_DATA];
	get_training_labels(training_data, argv[1]);
	get_training_images(training_data, argv[2]);
	return 0;
}

void get_training_images(DataItem* training_data, char* filename) {
	FILE* f = open_file(filename, "rb");

	// read magic number
	int magic_number = 0;
	fread(&magic_number, sizeof(int), 1, f);
	printf("The magic number is %d\n", magic_number);

	// read number of images present in file
	int num_items = 0;
	fread(&num_items, sizeof(int), 1, f);
	printf("The number of labels is %d\n", num_items);

	// read number of rows per image
	int num_rows = 0;
	fread(&num_rows, sizeof(int), 1, f);
	printf("The number of rows per image is %d\n", num_rows);

	// read number of columns per image
	int num_columns = 0;
	fread(&num_columns, sizeof(int), 1, f);
	printf("The number of columns per image is %d\n", num_columns);

	for (int i=0; i < NUM_TRAINING_DATA; i++) {
		fread(training_data[i].image, 784, 1, f);
	}


	fclose(f);
}

void make_label_array(unsigned char* label_array, unsigned char label) {
	memset(label_array, 0, 10);
	label_array[label] = 1;
}

void get_training_labels(DataItem* training_data, char* filename) {
	FILE* f = open_file(filename, "rb");

	// read magic number
	int magic_number = 0;
	fread(&magic_number, sizeof(int), 1, f);
	printf("The magic number is %d\n", magic_number);	// should be 17301504

	// read number of items present in file
	int num_items = 0;
	fread(&num_items, sizeof(int), 1, f);
	printf("The number of labels is %d\n", num_items);


	unsigned char label_value;
	for (int i=0; i < NUM_TRAINING_DATA; i++) {
		label_value = 0;
		fread(&label_value, 1, 1, f);
		make_label_array(training_data[i].label, label_value);

		for (int j=0; j < 10; j++) {
			printf("%d ", training_data[i].label[j]);
		}
		printf("\n");
	}


	fclose(f);
}

// Returns a pointer to a file opened in the specified mode
FILE* open_file(char* filename, char* mode) {
	FILE* f = fopen(filename, mode);
	if (f == NULL) {
		printf("The program could not open the file %s\n", filename);
		exit(1);
	}

	return f;
}