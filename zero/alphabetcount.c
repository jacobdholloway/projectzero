/*
 * alphabetcount.c - this file implements the alphabetlettercount function.
 */

#include <stdio.h> 
#include "count.h"
#include <dirent.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/**
  The alphabetlettercount function counts the frequency of each alphabet letter (a-z, case insensitive) in all the .txt files under
  directory of the given path and write the results to a file named as filetowrite.
  
  Input: 
      path - a pointer to a char string [a character array] specifying the path of the directory; and
      filetowrite - a pointer to a char string [a character array] specifying the file where results should be written in.
      alphabetfreq - a pointer to a long array storing the frequency of each alphabet letter from a - z:
      alphabetfreq[0]: the frequency of 'a'
      alphabetfreq[1]: the frequency of 'b'
         ... ...
      alphabetfreq[25]:the frequency of 'z'

  
  Output: a new file named as filetowrite with the frequency of each alphabet letter written in
  
  Steps recommended to finish the function:
  1) Find all the files ending with .txt and store in filelist.
  2) Read all files in the filelist one by one and count the frequency of each alphabet letter only (a - z). The array 
  long alphabetfreq[] always has the up-to-date frequencies of alphabet letters counted so far. If the letter is upper case, convert
  it to lower case first. 
  3) Write the result in the output file: filetowrite in following format: 
  
     letter -> frequency
     
     example:
     a -> 200
     b -> 101
     ... ...
     
  Assumption:  
  1) You can assume there is no sub-directory under the given path so you don't have to search the files 
  recursively.    
  2) Only .txt files are counted and other types of files should be ignored.
  
*/



void alphabetlettercount(char *path, char *filetowrite, long alphabetfreq[])
{
    DIR* d;
    struct dirent * dir;
    d = opendir(path);
    
    if (d != NULL)
    {
        while ((dir = readdir(d)) != NULL)
        {
            if(strstr(dir->d_name, ".txt"))
            {
                char filePath[1024];
                sprintf(filePath, "%s/%s", path, dir->d_name);

                FILE *file = fopen(filePath, "r");
                if (file != NULL)
                {
                    char ch;
                    while((ch = fgetc(file)) != EOF)
                    {
                        ch = tolower(ch);
                        if(ch >= 'a' && ch <= 'z')
                        {
                            alphabetfreq[ch - 'a']++;
                        }
                    }
                    fclose(file);
                }
            }
        }
        closedir(d);
    }

    FILE *outputFile = fopen(filetowrite, "w");
    if (outputFile != NULL)
    {
        for (char ch = 'a'; ch <= 'z'; ++ch)
        {
            fprintf(outputFile, "%c -> %ld\n", ch, alphabetfreq[ch - 'a']);
        }
        fclose(outputFile);
        
    }
}


