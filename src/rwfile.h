/*
 * rwfile.h
 *
 *  Created on: 04 авг. 2015 г.
 *      Author: alexey
 */

#ifndef RWFILE_H_
#define RWFILE_H_
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fstream>

class rw_file {
public:
	rw_file();
	~rw_file();
	void write_file(const char* filename,const char* data_buffer);
	char* read_file(const char* filename);
};

#endif /* RWFILE_H_ */
