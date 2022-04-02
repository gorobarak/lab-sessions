#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
        return 0;
    }
}

void regularEnc(int debug){
    int ch = fgetc(stdin);
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
            }
            
        }
        fputc(b,stdout);
        ch = fgetc(stdin);
    }
    
    printf("\n");
}

void dupEnc(int digit){
    //printf("hello from inside dupEnc\n");
    
    int ch;
    int firstch;
    firstch = fgetc(stdin);
    ch = firstch;
    while(firstch != EOF){
        while(ch != '\n'){
            if(ch == EOF){
                return;
            }
            fputc(ch, stdout);
            ch = fgetc(stdin);
        }
        for(int i = digit; i > 0 ; i--){
            fputc(firstch,stdout);
        }
        printf("\n");
        firstch = fgetc(stdin);
        ch = firstch;
    }

    printf("\n");
    return;
}

void rmEnc(int digit){
    int ch = fgetc(stdin);
    while(ch != EOF){
        for(int i = digit; i > 0; i--){
            if(ch == '\n'){
                printf("-NONE-\n");
                break;
            }
            ch = fgetc(stdin);
        }
        while(ch != '\n'){
            fputc(ch, stdout);
            ch = fgetc(stdin);
        }
        printf("\n");
        ch = fgetc(stdin);

    }
    return;
}

int main(int argc, char* argv[]){
    int i;
    int debug = 0;
    int digit = 0;
    for(i = 1; i < argc; i++)
    {
        if(strncmp(argv[i], "+e", 2) == 0 || strncmp(argv[i], "-e", 2) == 0)
        {
            // printf("HEllo from inside +e or -e\n");
            // printf("the value the evaluation is - %d\n", strncmp(argv[i],"+",1));
            //puting aside the fact that there can be an edge case where more than 1 digit was given.
            digit = calDigit(argv[i][2]);
            (strncmp(argv[i],"+",1) == 0) ? dupEnc(digit) : rmEnc(digit);
        }
        else if(strcmp(argv[i], "-D") == 0)
        {
            debug = 1;
            regularEnc(debug);
        }
        else
        {
            printf("Invalid Parameters - %s\n", argv[i]);
            return 1; //error
        }
    }
    if (argc == 0){
        regularEnc(debug); 
    }
    printf("\n");
    return 0;

}
