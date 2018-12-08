#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <math.h>
#include <byteswap.h>

//TAG DEFINES
#define BYTETOBITS 8
#define HEX255 0xFF
#define IMAGEWIDTH 256
#define IMAGELENGTH 257
#define BITSPERSAMPLE 258
#define COMPRESSION 259
#define PHOTOMETRICINTERP 262
#define STRIPOFFSETS 273
#define SAMPLESPERPIXEL 277
#define ROWSPERSTRIP 278
#define STRIPBYTECOUNTS 279


//TODO: Strips offsets, multi IFDs. lseek == check.
//This struct was taken from https://www.fileformat.info/format/tiff/egff.htm this link.
typedef struct _TifTag
{
	unsigned short TagId;       /* The tag identifier  */
	unsigned short DataType;    /* The scalar type of the data items  */
	unsigned long DataCount;   /* The number of items in the tag data  */
	unsigned long DataOffset;  /* The byte offset to the data items  */
} TIFTAG;
ssize_t r_read(int fd, void *buf, size_t size);

int main(int argc, char* argv[]){
	if(argc!=2){
		fprintf(stderr, "Usage: %s tifFileName\n", argv[0]);
		exit(-1);
	}
	int byteOrder; //0 for Intel byte order, 1 for Motorola Byte Order
	unsigned char buffer;
	char* path = argv[1];
	mode_t mode = S_IRUSR | S_IRGRP | S_IROTH;
	size_t offset = 0;
	size_t bytes_read;
	unsigned short tiffFortyTwo;
	unsigned long imgFileDir;
	unsigned long newStrip;
	unsigned short tagCount = 1;
	unsigned short bitsPerSample;
	unsigned short samplesPerPixel;
	int sampleToPixel;
	unsigned short stripCount;
	unsigned long *stripOffsets;
	unsigned long imageWidth;
	unsigned long imageLength;
	unsigned long rowsPerString;
	unsigned long *stripBytes;
	int isBlackZero;
	
	TIFTAG *tags;
	char tiffID[2];
	int wordCount = 0;
	int i,j,k,m;
	
	int fd = open( path, O_RDONLY, mode);
	
	if( fd == -1){
		perror("Failed to open input file");
		exit(-1);
	}
	while(1){
		//tiff file ID II or MM.
		while((bytes_read = r_read(fd, &tiffID, 2)) == -1  && (errno == EINTR));
		++wordCount;
		if(bytes_read == 0)
			break;
		if(tiffID[0] == 'M' && tiffID[1] == 'M')
			byteOrder = 1;		
		else if(tiffID[0] == 'I' && tiffID[1] == 'I')
			byteOrder = 0;
		else{
			perror("Unkown Order Type");
			break;
		}
		
		//Reading version.
		while((bytes_read = r_read(fd, &tiffFortyTwo, sizeof(tiffFortyTwo))) == -1  && (errno == EINTR));
		if(bytes_read == 0)
			break;
		if(byteOrder == 1)
			tiffFortyTwo=__bswap_16(tiffFortyTwo);
	
		//Reading Offset of image data.
		while((bytes_read = r_read(fd, &imgFileDir, sizeof(imgFileDir))) == -1  && (errno == EINTR));
		if(bytes_read == 0)
			break;
		if(byteOrder == 1)
			imgFileDir=__bswap_32(imgFileDir);
	
		if(lseek(fd, imgFileDir, SEEK_SET) == imgFileDir-1 ){
			perror("lseek call failed.");
			close(fd);
			break;
		}	
	
		//Reading tag count of the current image data
		while((bytes_read = r_read(fd, &tagCount, sizeof(tagCount))) == -1  && (errno == EINTR));
		if(bytes_read == 0)
			break;
		if(byteOrder == 1)
			tagCount=__bswap_16(tagCount);
		tags = (TIFTAG *) malloc(tagCount * sizeof(TIFTAG));

		//Reading tags
		for(i = 0; i<tagCount; ++i){
			while((bytes_read = r_read(fd, &tags[i], sizeof(tags[i]))) == -1  && (errno == EINTR));
			if(bytes_read == 0)
				break;
			if(byteOrder == 1){
				tags[i].TagId=__bswap_16(tags[i].TagId);
				tags[i].DataType=__bswap_16(tags[i].DataType);
				tags[i].DataCount=__bswap_32(tags[i].DataCount);
				if(tags[i].DataType == 4)
					tags[i].DataOffset=__bswap_32(tags[i].DataOffset);
				else
					tags[i].DataOffset=__bswap_16(tags[i].DataOffset);
			}	
		}
		
		for(int i =0; i<tagCount; ++i){	
			//Processing tags.
			if(tags[i].TagId == IMAGEWIDTH){
				imageWidth = tags[i].DataOffset;
				printf("\nWidth: %hu pixels\n", imageWidth);
			}
			else if(tags[i].TagId == IMAGELENGTH){
				imageLength = tags[i].DataOffset;
				printf("Height: %hu pixels\n", imageLength);
			}
			else if(tags[i].TagId == BITSPERSAMPLE){
				bitsPerSample = tags[i].DataOffset;
			}

			else if(tags[i].TagId == COMPRESSION){
				if(tags[i].DataOffset == 0){
					perror("File must be uncompressed");
					break;
				}
			}
			else if(tags[i].TagId == PHOTOMETRICINTERP){
				if(tags[i].DataOffset == 0)
					isBlackZero = 0;
				else if(tags[i].DataOffset == 1)
					isBlackZero = 1;
				else{
					perror("This program doesn't support RGB color files");
					break;
				}
			}
			else if(tags[i].TagId == STRIPOFFSETS){
				stripCount = tags[i].DataCount;
				if(stripCount < 1){
					printf("Corrupted file");
					break;
				}
				stripOffsets = (unsigned long *) malloc(stripCount * sizeof(stripOffsets));
				stripOffsets[0] = tags[i].DataOffset;
			}						
			else if(tags[i].TagId == SAMPLESPERPIXEL){
				samplesPerPixel = tags[i].DataOffset;
			}
			else if(tags[i].TagId == ROWSPERSTRIP){
				rowsPerString = tags[i].DataOffset;
			}
			else if(tags[i].TagId == STRIPBYTECOUNTS){
				stripBytes = (unsigned long *) malloc(stripCount * sizeof(stripBytes));
				stripBytes[0] = tags[i].DataOffset;
			}
		}	
		
		
		if(byteOrder == 0)
			printf("Byte Order: Intel\n");
		else
			printf("Byte Order: Motorola\n");
		
		//If there are multiple strips.
		if(stripCount >1){
			if(lseek(fd, stripOffsets[0], SEEK_SET) == stripOffsets[0]-1 ){
			perror("lseek call failed.");
			close(fd);
			break;
			}
			for(i=0; i<stripCount; ++i){
				while((bytes_read = r_read(fd, &stripOffsets[i], sizeof(stripOffsets[i]))) == -1  && (errno == EINTR));
				if(bytes_read == 0)
					break;
				if(byteOrder == 1)
					stripOffsets[i]=__bswap_32(stripOffsets[i]);
			}
			//Bytes per strip.
			if(lseek(fd, stripBytes[0], SEEK_SET) == stripBytes[0]-1 ){
				perror("lseek call failed.");
				close(fd);
				break;
			}
			for(i=0; i<stripCount; ++i){
				while((bytes_read = r_read(fd, &stripBytes[i], 2)) == -1  && (errno == EINTR));
				if(bytes_read == 0)
					break;
				if(byteOrder == 1)
					stripBytes[i]=__bswap_32(stripBytes[i]);
			}
		}
		
		sampleToPixel = (bitsPerSample/BYTETOBITS)*samplesPerPixel;
		if(sampleToPixel < 1){
			printf("This program doesn't support files with less than 1 byte per pixel\n");
			break;
		}
		else{
			for(k=0; k<stripCount; ++k){
				if(lseek(fd, stripOffsets[k], SEEK_SET) == stripOffsets[k]-1 ){
					perror("lseek call failed.");
					break;
				}
				for(i=0; i<imageWidth; ++i){		
					for(j=0; j<imageLength; ++j){
						while((bytes_read = r_read(fd, &buffer, samplesPerPixel)) == -1  && (errno == EINTR));
						if(bytes_read == 0)
							break;
						if(byteOrder == 1)
							buffer=__bswap_32(buffer);					
						if(buffer == HEX255){
							if(isBlackZero)
								printf("0 ");
							else
								printf("1 ");
							}
						else
							if(isBlackZero)
								printf("1 ");
							else
								printf("0 ");
					}
					printf("\n");
				}
			}
		}
		break;
	}
	free(stripBytes);
	free(stripOffsets);
	free(tags);
	close(fd);
}

//From the last year's book.
ssize_t r_read(int fd, void *buf, size_t size) {
    ssize_t retval;
    while (retval = read(fd, buf, size), retval == -1 && errno == EINTR) ;
    return retval;
}
