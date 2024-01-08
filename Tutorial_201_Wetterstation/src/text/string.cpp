#include <Arduino.h>

int getIndexOfBeforeLastString(String text, char search, int mark)
{
    if ((signed)text.length() > mark)
    {
        return text.substring(0, mark).lastIndexOf(search);
    }
    return mark;
}

String getLeftPaddingString(String text, char fillChar, int length)
{
    int lengthText = text.length();
    if (lengthText >= length)
    {
        return text;
    }
    String append = "";
    for (int i = 0; i < length - lengthText; i++)
    {
        append += fillChar;
    }
    append += text;
    return append;
}

String getRightPaddingString(String text, char fillChar, int length)
{
    int lengthText = text.length();
    if (lengthText >= length)
    {
        return text;
    }
    String append = "";
    for (int i = 0; i < length - lengthText; i++)
    {
        append += fillChar;
    }
    text += append;
    return text;
}