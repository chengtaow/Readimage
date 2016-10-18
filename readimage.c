/*
 * Chengtao Wang, 10/18/2016
 * ctwang28@gmail.com
*/
#include "tiffio.h"
#include <stdio.h>
#include <stdlib.h>

//#define filename "Example.tif"
#define n_max 50

//This function find the least member in the max list
uint16* Find_least(uint16* list){
	uint16* result = (uint16*)malloc(sizeof(uint16)*2);
	uint16 j, least, index;
	least = list[0];
	index = 0;
	for(j = 1; j < n_max; j++){
		if ( least > list[j]){
			least = list[j];
			index = j;
		}
	}
	result[0] = least;
	result[1] = index;
	return result;
}

//This function get the position from the index
uint32* Get_position(uint32 index, uint32 width){
	uint32* result = (uint32*)malloc(sizeof(uint32)*2);
	result[0] = index%width + 1;
	result[1] = index/width + 1;
	return result;
}


void main(int argc, char** argv)
{
	//Open the image and get all the pixel values
	TIFF *tif;
	uint16 spp, bpp, photo;
	uint32 width, height, linesize, i;
	char *buf;
	//store pixel values in buf.

	tif = TIFFOpen(argv[1], "r");
	if (!tif)
	{
		fprintf (stderr, "Can't open %s for reading\n", argv[1]);
		exit(0);
	}

	TIFFGetField(tif, TIFFTAG_IMAGELENGTH, &height);
	TIFFGetField(tif, TIFFTAG_IMAGEWIDTH, &width);
	TIFFGetField(tif, TIFFTAG_BITSPERSAMPLE, &bpp);
	TIFFGetField(tif, TIFFTAG_SAMPLESPERPIXEL, &spp);
	TIFFGetField(tif, TIFFTAG_PHOTOMETRIC, &photo);
	linesize = TIFFScanlineSize(tif);
	buf = malloc(linesize * height);
	for (i = 0; i < height; i++)
	    TIFFReadScanline(tif, &buf[i * linesize], i, 0);
	
	
	//Store the max values in the max list, and store their index, x, y positions.
	//We just put the first 50 pixels in the max list at first

	uint16 max[n_max]; // max list
	uint32 index[n_max], x[n_max], y[n_max]; // index, x, y positions
	for (i = 0; i < n_max; i++){
		max[i] = ((uint16 *)buf)[i];
		index[i] = i;
	}
	
	//We find the least values in the max list and replace it with the new pixels if the new pixles larger
	for (i; i < width*height; i++){
		uint16 *least = Find_least(max);
		if (((uint16 *)buf)[i] > least[0]){
			max[least[1]] = ((uint16 *)buf)[i];
			index[least[1]] = i;
		free(least);
		}
		
	}
	//Get the pixel position
	for (i = 0; i < n_max; i++){
		uint32 *position = Get_position(index[i],width);
		x[i] = position[0];
		y[i] = position[1];
		free(position);
		
	}
	
	//Print the 50 values and their postions.
	printf("The width, height of the image: %d, %d.\n", width, height);
	printf("Now print the %d max values.\n", n_max);
	for (i = 0; i < n_max; i++){
		printf("The position is x: %d, y: %d. The pixel value: %d.\n", x[i], y[i], max[i]);
	}
	

	TIFFClose(tif);
	
}
