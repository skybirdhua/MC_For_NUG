Agent ** agent; 

void initialAgent(); 
void initialStrategy(); 
void renewStrategy();
void renewUtility();
void renewWeight();
void renewWeight_random();
void renewReputation(int);

double max(double, double);
double min(double, double);

double max(double a, double b) {
	if (a >= b) return a;
	else return b;
}

double min(double a, double b) {
	if (a >= b) return b;
	else return a;
}

void initialAgent() {
	agent = new Agent * [2];
	int i, j, k;
	for (k = 0;k <= 1;k++) {
		int N_temp = N + 1;
		agent[k] = new Agent[N_temp];
		for (i = 1; i <= N;i++) {
			agent[k][i].no = i;
			agent[k][i].noN = neighbor[i][0];
			agent[k][i].neighbor = new Agent *[neighbor[i][0]];
			agent[k][i].W = 1;
			N_temp = neighbor[i][0] + 1;
			agent[k][i].pi = new double[N_temp];
			for (j = 1; j <= neighbor[i][0]; j++) {
				agent[k][i].neighbor[j-1] = &agent[k][neighbor[i][j]];
			}
		}
	}
	for (k = 0;k <= 1;k++) {
		for (i = 1; i <= N;i++) {
			agent[k][i].correspondent = &agent[1 - k][i];
		}
	}
}


void initialStrategy() {
	for (int k = 0;k <= 1;k++) {
		if (k == 0) {
			for (int i = 1; i <= N; i++) {
				agent[k][i].strategy[0] =  1.0*rand() / RAND_MAX;
				agent[k][i].strategy[1] =  1.0*rand() / RAND_MAX;
				agent[k][i].stretegy_pre[0] = agent[k][i].strategy[0];
				agent[k][i].stretegy_pre[1] = agent[k][i].strategy[1];
				agent[k][i].W = 1;
			}
		}
		else {
			for (int i = 1; i <= N; i++) {
				agent[k][i].strategy[0] = 1.0*rand() / RAND_MAX;
				agent[k][i].strategy[1] = 1.0*rand() / RAND_MAX;
				agent[k][i].stretegy_pre[0] = agent[k][i].strategy[0];
				agent[k][i].stretegy_pre[1] = agent[k][i].strategy[1];
				agent[k][i].W = 1;
			}
		}
	}
}

void renewUtility() {
	int i,j,k;
	for(k=0;k<=1;k++){
		for (i = 1;i <= N;i++) {
			agent[k][i].pi[0] = 0.0;
			for (j = 0;j < agent[k][i].noN;j++) {
				agent[k][i].pi[j+1]= matrix_UGame(agent[k][i].strategy,agent[k][i].neighbor[j]->strategy);
				agent[k][i].pi[0] += agent[k][i].pi[j+1];
			}
			if (agent[k][i].pi[0] > 0) {
				agent[k][i].utility = 1.0* agent[k][i].pi[0]* agent[k][i].W;
			}
		}
	}
}

void renewReputation(int t) {
	int i, j, k;
	for (k = 0; k <= 1; k++) {
		for (i = 1; i <= N; i++) {
			double R = 0;
			for (j = 0; j < agent[k][i].noN; j++) {
				R += reputation_UGame(agent[k][i].strategy, agent[k][i].neighbor[j]->strategy);
			}
			R = R / 4;
			if (t == 0) {
				agent[k][i].R = R;
			}
			else {
				agent[k][i].R = alpha*agent[k][i].R+R;
			}
		}
	}
}

void renewWeight() {
	int i, j, k;
	for (k = 0; k <= 1; k++) {
		for (i = 1; i <= N; i++) {
			double R_mean = 0;
			for (j = 0; j < agent[k][i].noN; j++) {
				R_mean += agent[k][i].neighbor[j]->R;
			}
			R_mean = R_mean / agent[k][i].noN;
			if (agent[k][i].R > R_mean) {
				agent[k][i].W = min(agent[k][i].W + delta,1+Delta);
			}
			else if (agent[k][i].R < R_mean) {
				agent[k][i].W = max(1-Delta,agent[k][i].W - delta);
			}
		}
	}
}
void renewWeight_random() {
	int i, j, k;
	for (k = 0; k <= 1; k++) {
		for (i = 1; i <= N; i++) {
			int r = rand() % 3;
			if (r == 0) {
				agent[k][i].W = min(agent[k][i].W + delta, 1 + Delta);
			}
			else if (r == 1) {
				agent[k][i].W = max(1 - Delta, agent[k][i].W - delta);
			}
		}
	}
}

void renewStrategy() {
	int k, i, j;
	double u_lunpan[2];
	for (k = 0;k <= 1;k++) {
		for (i = 1;i <= N;i++) {
			u_lunpan[0] = 0; u_lunpan[1] = 0;
			for (j = 0; j < agent[k][i].noN; j++) {
				u_lunpan[0] += agent[k][i].neighbor[j]->utility;
			}
			u_lunpan[0]+=agent[k][i].utility;
			u_lunpan[0] = u_lunpan[0] * 1.0 * rand() / RAND_MAX;
			for (j = 0; j < agent[k][i].noN; j++) {
				u_lunpan[1] +=agent[k][i].neighbor[j]->utility;
				if (u_lunpan[1] >= u_lunpan[0]) {
					agent[k][i].stretegy_pre[0] = agent[k][i].neighbor[j]->strategy[0];
					agent[k][i].stretegy_pre[1] = agent[k][i].neighbor[j]->strategy[1];
					break;
				}
			}
		}
		for (i = 1; i <= N; i++) {
			if (1.0 * rand() / RAND_MAX <= mutant) {
				agent[k][i].stretegy_pre[0] = agent[k][i].stretegy_pre[0] + (1.0 * rand() / RAND_MAX * 2 - 1) * epslon;
				agent[k][i].stretegy_pre[0] = min(max(agent[k][i].stretegy_pre[0], 0), 1);
				agent[k][i].stretegy_pre[1] = agent[k][i].stretegy_pre[1] + (1.0 * rand() / RAND_MAX * 2 - 1) * epslon;
				agent[k][i].stretegy_pre[1] = min(max(agent[k][i].stretegy_pre[1], 0), 1);
			}
			agent[k][i].strategy[0] = agent[k][i].stretegy_pre[0];
			agent[k][i].strategy[1] = agent[k][i].stretegy_pre[1];
		}
	}
}