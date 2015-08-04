/*
 * rwfile.cpp
 *
 *  Created on: 04 авг. 2015 г.
 *      Author: alexey
 */

#include "rwfile.h"

rw_file::rw_file() {
	// TODO Auto-generated constructor stub

}

rw_file::~rw_file() {
	// TODO Auto-generated destructor stub
}

void rw_file::write_file(const char* filename,const char* data_buffer)
{
	FILE* fd;
	fd=fopen(filename,"a");
	fprintf(fd,data_buffer);
	fclose(fd);
}

char* rw_file::read_file(const char* filename)
{
	FILE* fd;
	fd=fopen(filename,"r");
	fseek(fd , 0 , SEEK_END);                          		// устанавливаем позицию в конец файла
	long lSize = ftell(fd);                            		// получаем размер в байтах
	rewind (fd); 											 // устанавливаем указатель в конец файла
	char * buffer = (char*) malloc(sizeof(char) * lSize);
	size_t result = fread(buffer, 1, lSize, fd); 				//читаем файл
	if (result != (size_t)lSize)
	   {
	       fputs("Err read", stderr);
	       exit (3);
	   }
	fclose(fd);
	return buffer;


}
