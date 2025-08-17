#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int daysInMonth(int m, int y) {
    if (m == 2) {
        if ((y % 400 == 0) || (y % 4 == 0 && y % 100 != 0)) return 29;
        return 28;
    }
    if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
    return 31;
}

int main() {
    char s1[11], s2[11];
    scanf("%s %s", s1, s2);
    int d1 = (s1[0]-'0')*10 + (s1[1]-'0');
    int m1 = (s1[3]-'0')*10 + (s1[4]-'0');
    int y1 = (s1[6]-'0')*1000 + (s1[7]-'0')*100 + (s1[8]-'0')*10 + (s1[9]-'0');
    int d2 = (s2[0]-'0')*10 + (s2[1]-'0');
    int m2 = (s2[3]-'0')*10 + (s2[4]-'0');
    int y2 = (s2[6]-'0')*1000 + (s2[7]-'0')*100 + (s2[8]-'0')*10 + (s2[9]-'0');
    int count = 0;
    while (1) {
        long long val = d1;
        val = val * 100 + m1;
        val = val * 10000 + y1;
        if (val % 4 == 0 || val % 7 == 0) count++;
        if (d1 == d2 && m1 == m2 && y1 == y2) break;
        d1++;
        if (d1 > daysInMonth(m1, y1)) {
            d1 = 1;
            m1++;
            if (m1 > 12) {
                m1 = 1;
                y1++;
            }
        }
    }
    printf("%d", count);
    return 0;
}
