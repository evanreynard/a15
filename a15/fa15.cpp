#include<math.h>

double Strom(double dU, double dR1, double dR2, double dL, double dT)
{
	double dLm = -(dR1 * dR2) / ((dR1 + dR2) * dL);
	double dIo = dU / dR1;
	double dK  = - (dU * dR2) / (dR1 * (dR1 + dR2));
	return (dK * exp(dLm * dT) + dIo);
}