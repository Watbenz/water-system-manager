#ifndef CALCULATE_H
#define CALCULATE_H

double getTankRemainingPercent(int d, int tankHeight)
{
    if ((d <= 0) || (d >= tankHeight))
        return -1;
    return 100.0 - ((d / (double)tankHeight) * 100.0);
}

#endif