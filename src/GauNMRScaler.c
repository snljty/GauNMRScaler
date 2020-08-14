# include <stdio.h>
# include <stdlib.h>
# include <string.h>

# include "GauNMRScaler_sub.h"

int main(int argc, char * argv[])
{
  # define ARGUMENTS_NUMBER_ERROR 1
  # define GAU_OUT_FILE_ERROR 2

  typedef enum {False, True} Bool;
  char line[BUFSIZ] = "";
  char fname_tmp[BUFSIZ] = "";
  char * fname = NULL;
  FILE * fl = NULL;
  char * loc = NULL;
  char element[3] = "H";
  /*  can only accept 2 character(s) for element  */
  char searchstr[BUFSIZ] = "";
  /*  char tmpstr[][BUFSIZ] = {"", "", "", "", "", ""};  */
  double intercept = 32.2109;
  double slope = -1.0157;
  unsigned int search_title_length = 0;
  unsigned int index = 0;
  double sigma_iso = 0.;
  double delta = 0.;
  char c = '\0';
  Bool isinteractive = False;

  switch (argc)
  {
  case 1:
    isinteractive = True;
    puts("Input the Gaussian NMR output file path:");
    scanf("%[^\n]%c", fname_tmp, & c);
    fname = fname_tmp;
    if (fname_tmp[0] == '\"')
    {
      fname_tmp[strlen(fname_tmp) - 1] = '\0';
      fname ++;
    }
    puts("Input the symbol of element you want to load:");
    fgets(line, BUFSIZ, stdin);
    * strrchr(line, '\n') = '\0';
    if (strcmp(line, ""))
    {
      strncpy(element, line, 2);
      element[strlen(line)] = '\0';
    }
    puts("Input the slope:");
    fgets(line, BUFSIZ, stdin);
    * strrchr(line, '\n') = '\0';
    if (strcmp(line, ""))
      sscanf(line, "%lf", & slope);
    puts("Input the intercept:");
    fgets(line, BUFSIZ, stdin);
    * strrchr(line, '\n') = '\0';
    if (strcmp(line, ""))
      sscanf(line, "%lf", & intercept);
    puts("");
    break;
  case 2:
    if (! (strcmp(argv[1], "/?") && strcmp(argv[1], "-h") && strcmp(argv[1], "--help")))
    {
      PrintHelp();
      return 0;
    }
    strcpy(fname_tmp, argv[1]);
    fname = fname_tmp;
    break;
  case 5:
    strcpy(fname_tmp, argv[1]);
    fname = fname_tmp;
    strcpy(element, argv[2]);
    sscanf(argv[3], "%lf", & slope);
    sscanf(argv[4], "%lf", & intercept);
    break;
  default:
    puts("Arguments amount error! use \"--help\" for help.");
    Pause();
    exit(ARGUMENTS_NUMBER_ERROR);
    break;
  }
  if (strlen(element) == 1)
    strcat(element, " ");

  strcpy(searchstr, element);
  strcat(searchstr, "   Isotropic = ");
  search_title_length = strlen(searchstr);

  if (strlen(fname) < 4 || strcmp((fname + strlen(fname) - 4), ".log") && strcmp((fname + strlen(fname) - 4), ".out"))
  {
    puts("Unknown file name extension");
    Pause();
    exit(GAU_OUT_FILE_ERROR);
  }

  fl = fopen(fname, "r");
  if (! fl)
  {
    printf("Error! Cannot open %s!\n", fname);
    Pause();
    exit(GAU_OUT_FILE_ERROR);
  }
  printf("element: %-2s    slope: %7.4lf    intercept: %9.4lf\n", element, slope, intercept);
  while (! feof(fl))
  {
    fgets(line, BUFSIZ, fl);
    if (! strcmp(line, ""))
      break;
    loc = strstr(line, searchstr);
    if (loc)
    {
      sscanf(line, "%u", & index);
      sscanf(loc + search_title_length, "%lf", & sigma_iso);
      delta = (intercept - sigma_iso) / (- slope);
      printf("Atom index %4d    delta = %9.4lf\n", index, delta);
    }
  }

  fclose(fl);
  fl = NULL;

  if (isinteractive)
    Pause();

  return 0;
}

