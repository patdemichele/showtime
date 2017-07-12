
// ingest_bmp.h.
// contains declarations of useful functions for interpreting a bitmap file as a standard array of structs in the C programming language.

// This file is in its earliest phases. Developer still does not know much about the bitmap file format.

typedef struct {
  unsigned short filetype;
  unsigned int filesize;
  unsigned short res_1; //reserved fields
  unsigned short res_2; //reserved fields
  unsigned int offset; //offset to data in bytes
} BITMAPFILEHEADER;

typedef struct {
  unsigned int structuresize;
  unsigned long width; // in pixels
  unsigned long height;
  unsigned short scratch; //?
  unsigned short bits_per_pixel;
  unsigned int compression;
  unsigned int image_size; // in bytes
  unsigned long pixels_per_metre;
  unsigned long pixels_per_metre_2; //?
  unsigned int num_color_indices_used;
  unsigned int num_color_indices_important;
} BITMAPINFOHEADER;

// populates struct given fd
int get_file_header(int fd, BITMAPFILEHEADER* bmpfh);

// populates struct given fd
int get_info_header(int fd, BITMAPINFOHEADER* bmpih);

struct {
  char unknown; // fill in details on this struct later
} pixel;

// include other paramters to specify size?
int get_image(int fd, pixel **dest);
