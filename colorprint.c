#ifndef COLORPRINT
#define COLORPRINT 1

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

int const MAXLINE = 10000;

const char BLUE[] = "\e[0;34m";
const char GREEN[] = "\e[0;32m";
const char RED[] = "\e[0;31m";
const char WHITE[] = "\e[0;37m";

int ChooseColor(char* col, const char* p);
int DoColor(FILE* stream, char* col, const char* p, va_list* argn);
int ColorPrint(FILE* stream, const char* fmt, ...);

/*!
    \brief Do fprintf with color identifiers
    \param stream [in] stream directory
    \param fmt [out] output format
    \return cnt count of successfully processed arguments
    \return 0 if something goes wrong

    identifiers past '%':
        color identifier:
            -w white color
            -r red color
            -g green color
            -b blue color
        format identifier:
            -b double
            -d int
            -c char
            -t other

    Example: "%gb" print green double
*/

int ColorPrint(FILE* stream, const char* fmt, ...)
{
    va_list argn;
    va_start(argn, fmt);

    const char* p = fmt;
    int cnt = 0;

    for (p = fmt; *p; p++)
    { /*Loop begin*/
        /*Search %*/
        if (*p == '%') {
            /*Output color*/
            char col[MAXLINE] = { 0 };
            if (ChooseColor(col, ++p) != 0) {
                va_end(argn);
                return 0;
            }
            /*Output format*/
            if (DoColor(stream, col, ++p, &argn) != 0) {
                va_end(argn);
                return 0;
            }
            ++cnt;
        }
        else {
            putc(*p, stream);
            continue;
        }
        va_end(argn);
    } /*Loop end*/

    return cnt;
}

/*!
    \brief Read color identifiers and handle with
    \param p [in] raw format
    \param col [out] color
    \return 1 if something goes wrong
    \return 0 if all correct
*/

int ChooseColor(char* col, const char* p)
{
    switch (*p) {
       case 'r':
           strcpy(col, RED);
           break;
       case 'g':
           strcpy(col, GREEN);
           break;
       case 'b':
           strcpy(col, BLUE);
           break;
       case 'w':
           strcpy(col, WHITE);
           break;
       default:
           printf("\nWrong color\n");
           return 1;
    }
    return 0;
}

/*!
    \brief Read format identifiers and handle with
    \param stream [in] stream directory
    \param p [in] raw format
    \param col [in] color
    \param argn [in] ColorPrint arguments
    \return 1 if something goes wrong
    \return 0 if all correct
*/

int DoColor(FILE* stream, char* col, const char* p, va_list* argn)
{
    switch (*p) {
        case 'b':
            fputs(col, stream);
            fprintf (stream, "%lf", va_arg(*argn, double));
            fputs(WHITE, stream);
            break;
        case 'd':
            fputs(col, stream);
            fprintf (stream, "%d", va_arg(*argn, int));
            fputs(WHITE, stream);
            break;
        case 't':
            fputs(col, stream);
            break;
        case 'c':
            fputs(col, stream);
            fprintf (stream, "%c", va_arg(*argn, int));
            fputs(WHITE, stream);
            break;
        default:
            fputs(RED, stream);
            printf("\nWrong print format\n");
            va_end(*argn);
            return 1;
    }
    return 0;
}
#endif
