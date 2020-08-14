# include <stdio.h>

void flushstdin()
{
  char cont = '\0';
  while ((cont = getchar()) != '\n' && cont != EOF)
    ;

  return;
}

void Pause()
{
  puts("\nPress ENTER to exit...");
  flushstdin();

  return;
}

void PrintHelp()
{
  puts("Scale method: delta = (intercept - sigma_iso) / (- slope)");
  puts("Usage:");
  puts("Pass only argument \"/?\" \"-h\" or \"--help\" will show this help message and exit.");
  puts("The first argument should be the file path.");
  puts("Then followed by the element to be scaled, the slope, and the intercept.");
  puts("If you do not want to use scale method, just let slope be -1 and intercept be 0.");
  puts("If only file name is provided, the arguments will use slope = -1.0157 and intercept = 32.2109,");
  puts("which are for B3LYP/6-31G*/SMD//B3LYP/6-31G*/vaccum for Hydrogen.");
  puts("If no argument is provided, you will need to input arguments interactively.");
  puts("In interactive mode, when directly press ENTER as input,");
  puts("the default value shown above will be used.");

  return;
}

