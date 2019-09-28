// cs-assignment 2-1 "Byte Manipulation - Convert to Bytes"
// @author shj

// import modules
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define STR_SIZE 10 // string size
#define TESTING_TIMES 30 // for unit-testing

// declare prototype
int testing();

// define enum type for serve dynamic types in 'generateRandomValue' function
typedef enum {
        INT,
        DOUBLE,
        CHAR,
        STRING
} TYPE; // TYPE type

/**
 * generate random alphabet
 * => ascii 65-90
 * @return random alphabet [A-Z]
 * */
char generateRandomAlphabet() {
        return rand() % 26 + 65; // [A-Z]
}

/*
 * generate random value
 * @param t specific value's type
 * @param x value (void pointer is used to serve dynamic types)
 * */
void generateRandomValue(TYPE t, void *x) {
        switch (t) { // check type
                case INT:
                        // generate a random integer type value
                        *(int *) x = rand();
                        break;
                case DOUBLE:
                        // generate a random double type value
                        *(double *) x = rand() + rand() / (double) rand();
                        break;
                case CHAR:
                        // generate a random char type value
                        *(char *) x = generateRandomAlphabet();
                        break;
                case STRING:
                        // generate random char type values
                        for (int i = 0; i < STR_SIZE; i++) {
                                // insert alphabet into the 'x'
                                ((char *)x)[i] = generateRandomAlphabet();
                        }
                        break;
        }
}

/**
 * store byte function
 * @param len length of the value
 * @param v inserted value (unsigned char => for stored by Byte type)
 * @param result store value
 * */
void storeByte(size_t len, unsigned char *v, unsigned char *result) {
        for (size_t i = 0; i < len; i++) {
                // printf("%p\t%.2x\n", v + i, v[i]); // print address and byte value
                result[i] = v[i]; // storing
        }
}

/**
 * converter function
 * @param t specific type
 * @param v random value
 * @return converted unsigned char array
 * */
unsigned char *converter(TYPE t, void *v) {
        // declare vars
        size_t len;
        unsigned char *result;

        // check type
        switch (t) {
                case INT: // value => int type
                        // calc length
                        len = sizeof(*(int *)v);
                        result = malloc(len * sizeof(char)); // define result array

                        // print msg
                        printf("int >> value: 0x%x, length: %ld\n", *(int *)v, len);

                        // store bytes into the result array
                        storeByte(len, v, result);

                        break;
                case DOUBLE: // value => double type
                        // same process
                        len = sizeof(*(double *)v);
                        result = malloc(len * sizeof(char));

                        printf("double >> value: 0x%llx, length: %ld\n", *(unsigned long long *)v, len);

                        storeByte(len, v, result);

                        break;
                case CHAR: // value => char type
                        len = sizeof(*(char *)v);
                        result = malloc(len * sizeof(char));

                        printf("char >> value: 0x%x, length: %ld\n", *(char *)v, len);

                        storeByte(len, v, result);

                        break;
                case STRING: // value => char array type
                        len = sizeof((char *)v);
                        result = malloc(len * sizeof(char));

                        // print string value
                        printf("string >> value: %s( ", (char *)v);

                        // with bytes
                        for (int ind = 0; ind < len; ind++) {
                                printf("%c%x", ind != 0 ? ' ' : '\b', ((unsigned char *)v)[ind]);
                        }

                        printf("), length: %ld\n", len);

                        storeByte(len, v, result);

                        break;
        }

        return result;
}

/**
 * print bytes
 * @param len size of value
 * @param bs char array
 * */
void printBytes(size_t len, unsigned char * bs) {
        for (int row = 0; row < len; row++) {
                printf("result: 0x%x\n", bs[row]);
        }
}

/**
 * main function
 * */
int main(void) {
        // random
        srand(time(NULL));

        // testing
        if (testing() != 0) {
                printf("in process...\n\n");

                // generate random values
                int i;
                generateRandomValue(INT, &i);

                double d;
                generateRandomValue(DOUBLE, &d);

                char c;
                generateRandomValue(CHAR, &c);

                char *s = malloc(STR_SIZE * sizeof(char));
                generateRandomValue(STRING, s);

                // convert to byte type
                unsigned char * ic = converter(INT, &i);
                unsigned char * dc = converter(DOUBLE, &d);
                unsigned char * cc = converter(CHAR, &d);
                unsigned char * sc = converter(STRING, s);

                // print bytes
                printf("\nprint int type\n==========\n");
                printBytes(sizeof(i), ic);

                printf("\nprint double type\n==========\n");
                printBytes(sizeof(d), dc);

                printf("\nprint char type\n==========\n");
                printBytes(sizeof(c), cc);

                printf("\nprint string type\n==========\n");
                printBytes(sizeof(s), sc);

                // free
                free(ic);
                free(dc);
                free(cc);
                free(sc);
        }

        return 0;
}

/**
 * unit-testing function
 * @return testing result
 * */
int testing() {
        // printf msg
        printf("=== start testing... ===\n\n");

        // init var
        int result = 1; // true

        // start testing
        for (int i = 0; i < TESTING_TIMES; i++) {
                // gen random values
                int ri;
                generateRandomValue(INT, &ri);

                double rd;
                generateRandomValue(DOUBLE, &rd);

                char rc;
                generateRandomValue(CHAR, &rc);

                char *rs = malloc(STR_SIZE * sizeof(char));
                generateRandomValue(STRING, rs);

                // print values
                printf("\n=== testing %d ===\n", i + 1);
                printf("random int: %d\n", ri);
                printf("random double: %lf\n", rd);
                printf("random char: %c\n", rc);
                printf("random string: %s\n", rs);

                // free
                free(rs);
        }

        // check test result
        if (result != 0) {
                printf("\n\n=== success testing ===\n\n");
        } else {
                printf("\n\n=== failed to testing ===\n\n");
        }

        return result;
}
