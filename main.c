#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define WIDTH 60
#define HEIGHT 20
#define X WIDTH/2
#define Y HEIGHT/2
#define XMAX WIDTH-X-1
#define XMIN -(WIDTH-X)
#define YMAX HEIGHT-Y
#define YMIN -(HEIGHT-Y)+1

char grid[HEIGHT][WIDTH];

int plot(int x, int y)
{
    if( x > XMAX || x < XMIN || y > YMAX || y < YMIN )
        return(-1);

    grid[Y-y][X+x] = '*';
    return(1);
}

/* Initialize grid */
void init_grid(void)
{
    int x,y;

    for(y=0;y<HEIGHT;y++)
        for(x=0;x<WIDTH;x++)
            grid[y][x] = ' ';
    /* draw the axis */
    for(y=0;y<HEIGHT;y++)
        grid[y][X] = '|';
    for(x=0;x<WIDTH;x++)
        grid[Y][x] = '-';
    grid[Y][X] = '+';
}

/* display grid */
void show_grid(void)
{
    int x,y;

    for(y=0;y<HEIGHT;y++)
    {
        for(x=0;x<WIDTH;x++)
            putchar(grid[y][x]);
        putchar('\n');
    }
}

char * strlwr(char * s)
{
        char *t = s;
 
        if (!s)
        {
                return 0;
        }
 
        int i = 0;
        while ( *t != '\0' )
        {
                if (*t >= 'A' && *t <= 'Z' )
                {
                        *t = *t + ('a' - 'A');
                }
                t++;
        }
 
        return s;
}
/*
int round(float num){
    if (num - (int) num < 0.5){
        return (int) num;
    }
    return (int) num + 1;
}*/

double eval(char str[]){
	double res = 0;
	char str1[300] = "#include<stdio.h>\n#include<stdlib.h>\n#include<math.h>\ndouble rnd(double x){double p = (x-floor(x) < 0.5)?0:1;return floor(x)+p;}\nint main(){double pi=3.14159265;double e=2.7182818;FILE *f;f=fopen(\"res.txt\", \"w\");double n=(double)";
	strcat(str1, str);
	char str2[60] = ";fprintf(f,\"%%f\",n);fclose(f);return 0;}";
	strcat(str1, str2);
	
	FILE *f;
	f = fopen("res.c", "w");
	fprintf(f, str1);
	fclose(f);
	
	system("gcc res.c -o m");
	system("./m");
	
	FILE *fres;
	fres = fopen("res.txt", "r");
	fscanf(fres, "%lf", &res);
	fclose(fres);
	
	return res;
}

int findFirstIns(char *string, char *key){
    
	int len_string = strlen(string);
	int len_key = strlen(key);
	char win[len_key + 1];
	int i, j;
	for (i = 0; i < len_string - len_key + 1; i++){
		for (j = 0; j < len_key; j++){
			win[j] = *(string + i + j);
		}
		//win[j + 1] = NULL;
		if (strcmp(win, key) == 0){
			return i;
		}
	}
	return -1;
}
char *str_replace(char *orig, char *rep, char *with) {
    char *result; // the return string
    char *ins;    // the next insert point
    char *tmp;    // varies
    int len_rep;  // length of rep (the string to remove)
    int len_with; // length of with (the string to replace rep with)
    int len_front; // distance between rep and end of last rep
    int count;    // number of replacements

    // sanity checks and initialization
    if (!orig || !rep)
        return NULL;
    len_rep = strlen(rep);
    if (len_rep == 0)
        return NULL; // empty rep causes infinite loop during count
    if (!with)
        with = "";
    len_with = strlen(with);

    // count the number of replacements needed
    ins = orig;
    for (count = 0; tmp = strstr(ins, rep); ++count) {
        ins = tmp + len_rep;
    }

    tmp = result = malloc(strlen(orig) + (len_with - len_rep) * count + 1);

    if (!result)
        return NULL;

    // first time through the loop, all the variable are set correctly
    // from here on,
    //    tmp points to the end of the result string
    //    ins points to the next occurrence of rep in orig
    //    orig points to the remainder of orig after "end of rep"
    while (count--) {
        ins = strstr(orig, rep);
        len_front = ins - orig;
        tmp = strncpy(tmp, orig, len_front) + len_front;
        tmp = strcpy(tmp, with) + len_with;
        orig += len_front + len_rep; // move to next "end of rep"
    }
    strcpy(tmp, orig);
    return result;
}
int isnumber(char c){
    if (48<=c && c<=57){
        return 1;
    }
    return 0;
}
int isspec(char c){
    if (33<=c && c <= 47 && c != 40 && c != 41){
        return 1;
    }
    return 0;
}
void insert(char *strA, char* strB, int x, char* strC){
    strncpy(strC, strA, x);
    *(strC + x) = '\0';
    strcat(strC, strB);
    strcat(strC, strA + x);
}
void ins_star(char *string){
    int len_string = strlen(string);
    int i;
    int k = len_string - 1;
    char *string2 = (char *) malloc(500 * sizeof("c"));
    for (i = 0; i < k; i++){
        if (isnumber(*(string + i)) + isnumber(*(string + i + 1)) == 1){
            if (*(string + i + 1)!= 41 && *(string + i)!=40 ){
                if (isspec(*(string + i)) + isspec(*(string + i + 1)) == 0){
                    insert(string, "*", i+1, string2);
                    strcpy(string, string2);
                    k++;}
            }
        }
    }
}
double evalf(char *fcontread, double val){
    FILE *fptrFunc;
    char *fname = (char *) malloc(500*sizeof("c"));
    char *fcont = (char *) malloc(500*sizeof("c"));
    char *nfcont = (char *) malloc(500*sizeof("c"));
    char *fans = (char *) malloc(500*sizeof("c"));
    fptrFunc = fopen(fcontread, "r");fscanf(fptrFunc, "%s", fcont);fclose(fptrFunc);
    sprintf(fans, "%lf", val);
    nfcont = str_replace(fcont, "z", fans);
    return eval(nfcont);
}
double derivative(char* fcontread, double val){
    double a = evalf(fcontread, val + 0.00001);
    double b = evalf(fcontread, val);
    return (double)100000 * (a - b);
}
int norm(char *string, double arr[100]){
	int i,j;
	char *nstr = (char *)malloc(500*sizeof("c"));
	char *nstr2 = (char *)malloc(500*sizeof("c"));
    char *nstr3 = (char *)malloc(500 * sizeof("c"));
	for (i = 0; i < 10; i++){
        sprintf(nstr, "%c%d", 97+i/10, i % 10+1);
        sprintf(nstr2, "%lf", arr[i]);
        nstr3 = str_replace(string, nstr, nstr2);
        strcpy(string, nstr3);
		
	}
	ins_star(string);
	return 1;
}
int printtable(double array[]){
	int i,j;
	printf("  \t");
	for (i=0; i<10; i++){
		printf("%d        \t|", i+1);
	}
	printf("\n");
	for (i=0; i<10; i++){
		printf("%c|\t", 65+i);
		for (j=0; j<10; j++){
			printf("%lf\t|", array[i*10 + j]);
		}
		printf("\n");
	}
	return 1;
}
int graph(char* string, float d1, float d2)
{
    float x,y;
    char *nfcont = (char *) calloc(20, sizeof(char));
    char *fans = (char *) calloc(20, sizeof(char));
    int *inds = (int *) calloc(500, sizeof(int));
    double* values = (double *)calloc(11, sizeof(double));
    float value;
    init_grid();
    for(x=d1;x<=d2;x+=0.1)
    {
        sprintf(fans, "%f", x);
        nfcont = str_replace(string, "z", fans);
        y = eval(nfcont);
        plot(rintf(x*10),rintf(y*8));
    }
    printf("\n");
    show_grid();

    return(0);
}

void main(){
    int i,j;
	double array[100];
	for (i = 0; i < 100; i++){
		array[i] = 0;
	}
    system("cls");
	FILE *fptrWrite;
	FILE *fptrRead;
    FILE *fptrFunc;
    FILE *fptrDOC;
    FILE *fptrHistory;
	char *command = (char *) malloc(500*sizeof("c"));
	char *sub_command = (char *) malloc(500*sizeof("c"));
	char *sub_sub_command = (char *) malloc(500*sizeof("c"));
	char *file_cont_writ = (char *) malloc(500*sizeof("c"));
    char *file_cont_read = (char *) malloc(5000*sizeof("c"));
	char *ssc2 = (char *) malloc(500*sizeof("c"));
	char *sub_command2 = (char *) malloc(500*sizeof("c"));
    char *fname = (char *) malloc(500*sizeof("c"));
    char *fcont = (char *) malloc(500*sizeof("c"));
    char *nfcont = (char *) malloc(500*sizeof("c"));
    char *fcontread = (char *) malloc(500*sizeof("c"));
    char *fans = (char *) malloc(500*sizeof("c"));
    char *temp1 = (char *) malloc(500*sizeof("c"));
    char *docstirng = (char *) malloc(5000 * sizeof("c"));
    char *str_modified = (char *) calloc(5000 , sizeof("c"));
    char *tok;
    char *hist_str = (char *) calloc(5000 , sizeof("c"));
    long fsize;
    double temp;
	int a,b, cont = 1;
    fptrHistory = fopen("history.txt", "a");
	printf("Enter command : ");
	scanf("%s %s %s", command, sub_command, sub_sub_command);
    sprintf(str_modified, "%s %s %s\n",  command, sub_command, sub_sub_command);
    fprintf(fptrHistory, str_modified);
    fclose(fptrHistory);
	
	while (strcmp(command, "exit") != 0){
		//printf(">>> ");
		i = 0;
		cont = 1;
		if (strcmp(command, "eval") == 0){
            norm(sub_command, array);
			sub_command2 = strlwr(sub_command);
			printf("\n%lf\n", eval(sub_command2));
		}

        else if(strcmp(command, "help") == 0){
            fptrDOC = fopen("doc.txt", "r");
            fread(docstirng, 6000, 1, fptrDOC);
            fclose(fptrDOC);
            printf("\n%s\n", docstirng);

        }
        else if (strcmp(command, "let") == 0){
            /*This portion gets a function from the user and saves it.
            after that the function is able to be called and evaluated
            with different inputs. e.g. let f 2sin(z)*/
            sprintf(fname, "%s.txt", sub_command);
            norm(sub_sub_command, array);
            fptrFunc = fopen(fname, "w");fprintf(fptrFunc, "%s", sub_sub_command);fclose(fptrFunc);
            printf("done. note : this version only supports one variable functions with variable z.\n");

        }
        else if (strcmp(command, "evalf") == 0){// eval$function f 14
            //sprintf(fname, "%s.txt", sub_command);
            //sprintf(fcontread, "%s.txt", sub_command);
            strcpy(fcontread, sub_command); strcat(fcontread, ".txt");
            fptrFunc = fopen(fcontread, "r");fscanf(fptrFunc, "%s", fcont);fclose(fptrFunc);
            sprintf(fans, "%lf", eval(sub_sub_command));
            nfcont = str_replace(fcont, "z", fans);
            printf(" \n%lf\n", eval(nfcont));
    
        }
        else if (strcmp(command, "drvt") == 0){
            strcpy(fcontread, sub_command); strcat(fcontread, ".txt");
            temp = eval(sub_sub_command);
            printf("\n%lf\n", derivative(fcontread, temp));
        }
        else if (strcmp(command, "graph") == 0){
            norm(sub_command, array);
			sub_command2 = strlwr(sub_command);
            float d1, d2;
            sscanf(sub_sub_command, "%f-%f", &d1, &d2);
            printf("%f %f\n", d1, d2);
            graph(sub_command2, d1, d2);
            printf("\n");
		}
        else if (strcmp(command, "history") == 0){
            fptrHistory = fopen("history.txt", "r");
            /*
            fscanf(fptrHistory, "%s", hist_str);
            fclose(fptrHistory);
            printf("%s\n", hist_str);*/
            fseek(fptrHistory, 0, SEEK_END);
            fsize = ftell(fptrHistory);
            fseek(fptrHistory, 0, SEEK_SET);  /* same as rewind(f); */

            hist_str = malloc(fsize + 1);
            fread(hist_str, fsize, 1, fptrHistory);
            fclose(fptrFunc);

            hist_str[fsize] = 0;
            printf(hist_str);
            free(hist_str);

		}

        printf(">>> ");
        fptrHistory = fopen("history.txt", "a");
		scanf("%s %s %s", command, sub_command, sub_sub_command);
        sprintf(str_modified, "%s %s %s\n",  command, sub_command, sub_sub_command);
        fprintf(fptrHistory, str_modified);
        fclose(fptrHistory);
	}
    
}