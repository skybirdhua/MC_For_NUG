#ifndef AGENT_H
#define AGENT_H



class Agent{
    public:
 	   int no;  
	   int noN;
	   Agent** neighbor;
	   Agent* correspondent;
	   double W;
	   double R;
	   double utility;
	   double * pi;
	   double strategy[2]; 
	   double stretegy_pre[2];
};

#endif

