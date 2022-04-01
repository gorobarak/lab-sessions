#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int whatDigit(int ch){
    // printf(" ch  = %d\n", ch);
    if (ch < 48 || ch > 70){
        return 0; 
    }
    if (ch < 58){
        return ch - 48;
    }
    if (ch > 64){
        return ch - 65 + 10;
    }
    return 0;
}
void dupEnc(int enc){
    int ch = fgetc(stdin);
    int firstch = ch;
    while(1){
        if(ch == '\n')// 10 == \n
            while (enc != 0){
                fputc(firstch, stdout);
                enc--;
            }
        else{
            if (ch == EOF){
                return;
            }
            fputc(ch, stdout);
        }
        ch  = fgetc(stdin);
    }
}
void rmEnc(int enc){
    int ch  = fgetc(stdin);
    while(ch != EOF){
        for(int i  = enc; i > 0; i--){
            if(ch == '\n'){
                printf("-NONE-");
                return;
            }
            ch = fgetc(stdin);
            }
        
        while(ch != '\n'){
            fputc(ch, stdout);
            ch = fgetc(stdin);
        }
    }
}
    

int main(int argc, char* argv[]){
    // FILE* in = stdin;
    // FILE* out = stdout;
    // FILE* err = stderr;
    int debug = 0;
    int enc = 0;
    int sign;
    int i;

    for(i = 1; i < argc; i++){
        if (strcmp("-D", argv[i]) == 0){
            debug = 1;
        }
        else if(strncmp("+e", argv[i], 2) == 0 || strncmp("-e", argv[i], 2) == 0 ){
            enc = whatDigit(argv[i][2]);
            // printf(" bla - %d\n",argv[i][2]);
            // printf("%d", enc);
            sign  = (strncmp("+e", argv[i], 2) == 0) ? 1 : -1;
            if (enc == 0)
            {
            printf(" Argument of out of range - %c" , argv[i][3]);
            return 1; 
            } 
        }
        else{
            printf("Invalid Parameters - %s\n", argv[i]);
            return 1; //error
        }
    }

    if (sign == 1){
        dupEnc(enc);
    }
    else{
        rmEnc(enc);
    }
    

    
    printf("\n");
    return 0;
}
