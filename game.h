double matrix_UGame(double, double);
int reputation_UGame(double, double);

int reputation_UGame(double s1[2], double s2[2]){
	if (s1[0] >= s2[1]) return 1;
	else return 0;
}

double matrix_UGame(double s1[2], double s2[2]){
	if (s1[0]>=s2[1] && s2[0]>=s1[1]) return 1-s1[0]+s2[0];
	else if  (s1[0]>=s2[1] && s2[0]<s1[1]) return 1-s1[0];
	else if  (s1[0]<s2[1] && s2[0]>=s1[1]) return s2[0];
	else return 0;
}