
#include "resources.h"

CResources CResources::m_Resources;

char *CResources::GetBufferFromResource(char *resourcefilename, char *resourcename, int *filesize)
{
	//Try to open the resource file in question
	int fd = open(resourcefilename, O_RDONLY);
	if (fd < 0)
	{
		perror("Error opening resource file");
		exit(1);
	}

	//Make sure we're at the beginning of the file
	lseek(fd, 0, SEEK_SET);

	//Read the first INT, which will tell us how many files are in this resource
	int numfiles;
	read(fd, &numfiles, sizeof(int));

	//Get the pointers to the stored files
	int *filestart = (int *) malloc(sizeof(int) * numfiles);	// this is probably wrong in the zip
	read(fd, filestart, sizeof(int) * numfiles);

	//Loop through the files, looking for the file in question
	int filenamesize;
	char *buffer;
	int i;
	for(i=0;i<numfiles;i++)
	{
		char *filename;
		//Seek to the location
		lseek(fd, filestart[i], SEEK_SET);
		//Get the filesize value
		read(fd, filesize, sizeof(int));
		//Get the size of the filename string
		read(fd, &filenamesize, sizeof(int));
		//Size the buffer and read the filename
		filename = (char *) malloc(filenamesize + 1);
		read(fd, filename, filenamesize);
		//Remember to terminate the string proComo gerar amostras de dados aleatórias para tratamentos estatísticosperly!
		filename[filenamesize] = '\0';
		//Compare to the string we're looking for
		if (strcmp(filename, resourcename) == 0)
		{
			//Get the contents of the file
			buffer = (char *) malloc(*filesize);
			read(fd, buffer, *filesize);
			free(filename);
			break;
		}
		//Free the filename buffer
		free(filename);
	}

	//Release memory
	free(filestart);

	//Close the resource file!
	close(fd);

	//Did we find the file within the resource that we were looking for?
	if (buffer == NULL)
	{
		printf("Unable to find '%s' in the resource file!\n", resourcename);
		exit(1);
	}

	//Return the buffer
	return buffer;
}

SDL_Surface *CResources::LoadBitmap(char *resourcefilename, char *bitmapfilename)
{
	//Get the bitmap's buffer and size from the resource file
	int filesize = 0;
	char *buffer = GetBufferFromResource(resourcefilename, bitmapfilename, &filesize);

	//Load the buffer into a surface using RWops
	SDL_RWops *rw = SDL_RWFromMem(buffer, filesize);
	SDL_Surface *temp = SDL_LoadBMP_RW(rw, 1);

	//Release the bitmap buffer memory
	free(buffer);

	//Were we able to load the bitmap?
	if (temp == NULL)
	{
		printf("Unable to load bitmap: %s\n", SDL_GetError());
		exit(1);
	}

	//Convert the image to optimal display format
	SDL_Surface *image;
	image = SDL_DisplayFormat(temp);

	//Free the temporary surface
	SDL_FreeSurface(temp);

	//Return our loaded image
	return image;
}

Mix_Chunk *CResources::LoadSound(char *resourcefilename, char *soundfilename)
{
	//Get the sound's buffer and size from the resource file
	int filesize = 0;
	char *buffer = GetBufferFromResource(resourcefilename, soundfilename, &filesize);

	//Load the buffer into a surface using RWops
	SDL_RWops *rw = SDL_RWFromMem(buffer, filesize);
	Mix_Chunk *sound = Mix_LoadWAV_RW(rw, 1);

	//Release the buffer memory
	free(buffer);

	//Return the sound
	return sound;
}


Mix_Music *CResources::LoadMusic(char *resourcefilename, char *soundfilename)
{
	//Get the sound's buffer and size from the resource file
	int filesize = 0;
	char *buffer = GetBufferFromResource(resourcefilename, soundfilename, &filesize);

	//Load the buffer into a surface using RWops
	SDL_RWops *rw = SDL_RWFromMem(buffer, filesize);
	Mix_Music *sound = Mix_LoadMUS_RW(rw);

	//Não se pode libertar a memória senão o programa crasha!!!
	//free(buffer);

	//Return the sound
	return sound;
}




