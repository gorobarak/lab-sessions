#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* substring(char* str){
    return str + 2;
}
int calDigit(int ch){
    if (47 < ch && ch < 58)
    {
        return ch - 48;
    }
    else if (64 < ch && ch < 71 )
    {
        return ch - 65 + 10 ;
    }
    else{
        return -1;
    }
}

void regularEnc(int debug, FILE* instream, FILE* outstream, char* inputName , char* outputName){
    int ch = fgetc(instream);
    int counter = 0;
    while(ch != EOF){
        int b = ch;
        if ( 64 < ch && ch <91){ //is ch uppercase?
            counter++;
            b = 46;
        }
        if(debug){ //output to err, ch before and after conversion
            if(ch != 10){
                fprintf(stderr,"%i %i\n",ch,b);
            }
            else{
                fprintf(stderr, "the number of letters converted: %i\n", counter);
                fprintf(stderr, "the input file name is  %s\nthe output filename is %s\n",inputName, outputName);
            }
            
        }
        fputc(b,outstream);
        ch = fgetc(instream);
    }
    
    printf("\n");
}

void dupEnc(int digit, FILE* instream, FILE* outstream){
    //printf("hello from inside dupEnc\n");
    
    int ch;
    int firstch;
    firstch = fgetc(instream);
    ch = firstch;
    while(ch != EOF){
        while(ch != '\n'){
            if(ch == EOF){
                return;
            }
            fputc(ch, outstream);
            ch = fgetc(instream);
        }
        for(int i = digit; i > 0 ; i--){
            fputc(firstch,outstream);
        }
        fputc('\n', outstream);
        firstch = fgetc(instream);
        ch = firstch;
    }

    fputc('\n', outstream);
    return;
}

void rmEnc(int digit, FILE* instream, FILE* outstream){
    int ch = fgetc(instream);
    while(ch != EOF){
        for(int i = digit; i > 0; i--){
            if(ch == '\n'){
                printf("-NONE-");
                break;
            }
            ch = fgetc(instream);
        }
        while(ch != '\n'){
            fputc(ch, outstream);
            ch = fgetc(instream);
        }
        printf("\n");
        ch = fgetc(instream);

    }
    return;
}

int main(int argc, char* argv[]){
    int i;
    int debug = 0;
    int digit = 0;
    //int regularEncFlag = 0;
    int dupEncFlag = 0;
    int rmEncFlag = 0;
    FILE* instream = stdin;
    FILE* outstream = stdout;
    char* inputName = "-NO INPUT GIVEN-";
    char* outputName = "-NO OUTPUT GIVEN-";
    if (argc == 0){
        regularEnc(0, instream, outstream, inputName, outputName);
        printf("\n");
        return 0; 
    }

    for(i = 1; i < argc; i++)
    {
        if(strncmp(argv[i], "+e", 2) == 0 || strncmp(argv[i], "-e", 2) == 0)
        {
            
            //puting aside the fact that there can be an edge case where more than 1 digit was given.
            digit = calDigit(argv[i][2]);
            if (digit == -1 || argv[i][3] != 0){
                printf("Invalid parameters \n");
                return 0;
            }

            (strncmp(argv[i],"+",1) == 0) ? (dupEncFlag = 1) : (rmEncFlag = 1);
        }
        else if(strcmp(argv[i], "-D") == 0) //could there be debug in non-reg encoder? 
        {
            debug = 1;
            //regularEncFlag = 1;
        }
        else if(strncmp(argv[i], "-i",2) == 0){
            //printf("filename is - %s", substring(argv[i]));
            instream = fopen(substring(argv[i]),"r");
            inputName = substring(argv[i]);
        }
        else if(strncmp(argv[i], "-o", 2) ==  0){
            outstream = fopen(substring(argv[i]),"w");
            outputName = substring(argv[i]);
        }
        else
        {
            printf("Invalid Parameters - %s\n", argv[i]);
            return 1; //error
        }
    }
    
    if (dupEncFlag)
    {
        dupEnc(digit, instream, outstream);
    }
    else if(rmEncFlag)
    {
        rmEnc(digit, instream, outstream);
    }
    else
    {
        regularEnc(debug, instream, outstream,inputName, outputName);
    }
    fclose(instream);
    fclose(outstream);
    printf("\n");
    return 0;

}
