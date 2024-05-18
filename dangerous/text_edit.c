#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {

    FILE *fp = fopen("/Users/adityasaccount/Documents/big_hackMHS/hackmhs/hackmhs.ino", "w");
    if (!fp) {
        perror("Error opening file");
		puts("hello");
        return 1;
    }

    FILE *wfp = fopen("/Users/adityasaccount/Documents/big_hackMHS/dangerous/base.ino", "r");
    if (!wfp) {
        perror("Error opening file");
		puts("hello2");
        fclose(fp);
        return 1;
    }

    // Read from base.ino and write to hackmhs.ino with inserted arguments
    char line[256];
    int count = 1;
    while (fgets(line, sizeof(line), wfp)) {
        if (count == 10) fprintf(fp, "int max = %s;\n", argv[1]);
        else if (count == 12) fprintf(fp, "int f_scale = %s;\n", argv[2]);
        else if (count == 13) fprintf(fp, "int f_intercept = %s;\n", argv[3]);
        else if (count == 15) fprintf(fp, "int d_scale = %s;\n", argv[4]);
        else if (count == 16) fprintf(fp, "int d_intercept = %s;\n", argv[5]);
        else fprintf(fp, "%s", line);
        count++;
        printf("%s\n", line);
    }

    fclose(wfp);
    fclose(fp);

    return 0;
}
