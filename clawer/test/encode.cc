#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

void read_file(char *filename) {
   int n;
   long elapsed_seconds;
   char line[80];
   string context;
   FILE *fr = fopen (filename, "rt");  /* open the file for reading */

   while(fgets(line, 80, fr) != NULL)
   {
	 context += line;
	 /* get a line, up to 80 chars from fr.  done if NULL */
	 sscanf (line, "%ld", &elapsed_seconds);
	 /* convert the string to a long int */
	 printf ("%ld\n", elapsed_seconds);
   }
   cout << "context:" << endl << context << endl;
   fclose(fr);  /* close the file prior to exiting the routine */
}

int main() {
	char* str = "功能he";
	cout << strlen(str) << endl;
	cout << str << endl;
	read_file("data");
	return 0;
}



