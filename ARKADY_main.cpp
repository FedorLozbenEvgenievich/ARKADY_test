#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <cstdlib>
#include <math.h>

const float pi=3.14159265;

float sq(float a) {
	return a*a;
}

__int64 fac(int a) {
	__int64 b=1;
	for (int i=1;i<=a;i++) {
		b*=i;
	}
	return b;
}

int main() {
	const int Nmax=50000;
	bool there=true,start=false,iterate=false;
	int position=1,position_=1,cond=1;
	char ch;
	int N=1000,T=100000,T_skip=1;
	float v=0.2,r=1.5,p_kill=0.001,p_heal=0,p_sick=0.1;
	float Ob_x[Nmax],Ob_y[Nmax],Ob_aim[Nmax],Ob_dx[Nmax],Ob_dy[Nmax];
	unsigned int Ob_t[Nmax];
	unsigned char Ob_cond[Nmax];
	float t_distr[100];
	
	int Ob_mx[Nmax],Ob_my[Nmax];
	
	int mas_max[70][70];//for optimisation
	int mas_is[70][70];
	int* mas[70][70];
	
	for (int i=0;i<70;i++) {
		for (int j=0;j<70;j++) {
			mas[i][j]=(int*)malloc((int)sizeof(int)*4);
			mas_max[i][j]=4;
			mas_is[i][j]=0;
		}
	}
	
	t_distr[0]=0;//making inverse of Poisson to generate noise
	float t_distr_inv[100];
	int k=7;
	t_distr_inv[0]=0;
	for (int i=1;i<100;i++) {
		if (t_distr_inv[i-1]>=1) {t_distr_inv[i]=1;} else {
			t_distr_inv[i]=t_distr_inv[i-1]+pow(k,i)/fac(i)/exp(k);
			if (t_distr_inv[i]>1) {t_distr_inv[i]=1;}
		}
	}
	for (int i=0;i<100;i++) {
		for (int j=1;j<100;j++) {
			if ((t_distr_inv[j]>=i/100.0)&&(t_distr_inv[j-1]<=i/100.0)) {t_distr[i]=j;}
		}
	}
	
	while (there==true) {
		system("cls");
		printf("|WDSA-interact by FEDOR LOZBEN|\n");//draw the menu
		
		if (position==1) {printf("|->");} else {printf("|  ");}
		printf("      START|");
		if ((cond>=2)&&(position_==1)) {printf("|->");} else {printf("|  ");}
		if (cond>=2) {printf(" 1<=[N=%5d]<=%5d   cahnge->|",N,Nmax);}
		printf("\n");
		
		if (position==2) {printf("|->");} else {printf("|  ");}
		printf(" PARAMETRES|");
		if ((cond>=2)&&(position_==2)) {printf("|->");} else {printf("|  ");}
		if (cond>=2) {printf(" dying   p=%5f    cahnge->|",p_kill);}
		printf("\n");
		
		if (position==3) {printf("|->");} else {printf("|  ");}
		printf("        OUT|");
		if ((cond>=2)&&(position_==3)) {printf("|->");} else {printf("|  ");}
		if (cond>=2) {printf(" healing p=%5f    cahnge->|",p_heal);}
		printf("\n");
		
		printf("|  ");
		printf("           |");
		if ((cond>=2)&&(position_==4)) {printf("|->");} else {printf("|  ");}
		if (cond>=2) {printf(" 1<=[T=%7d]        cahnge->|",T);}
		printf("\n");
		
		printf("|  ");
		printf("           |");
		if ((cond>=2)&&(position_==5)) {printf("|->");} else {printf("|  ");}
		if (cond>=2) {printf(" catching p=%5f   cahnge->|",p_sick);}
		printf("\n");
		
		printf("|  ");
		printf("           |");
		if ((cond>=2)&&(position_==6)) {printf("|->");} else {printf("|  ");}
		if (cond>=2) {printf(" draw each %5d       cahnge->|",T_skip);}
		printf("\n");
		
		ch=getch();//do what user asks
		if (cond==1) {
			if (ch=='w') {position--;}
			if (ch=='s') {position++;}
			if (position==0) {position=3;}
			if (position==4) {position=1;}
		}
		if (cond==2) {
			if (ch=='w') {position_--;}
			if (ch=='s') {position_++;}
			if (position_==0) {position_=6;}
			if (position_==7) {position_=1;}
		}
		if (ch=='a') {
			if (cond==2) {cond=1;}
			if ((cond==1)&&(position==1)) {
				start=true;
				iterate=true;
			}
		}
		if (ch=='d') {
			if (cond==1) {
				if (position==1) {
					start=true;
					iterate=false;
				}
				if (position==2) {cond=2;}
				if (position==3) {there=false;}
			} else {
				if (cond==2) {
					if (position_==1) {
						printf("\n\nN=");
						scanf("%d",&N);
						if (N<1) {N=1;}
						if (N>Nmax) {N=Nmax;}
					}
					if (position_==2) {
						printf("\n\ndying p=");
						scanf("%f",&p_kill);
						if (p_kill<0) {p_kill=0;}
						if (p_kill>1) {p_kill=1;}
					}
					if (position_==3) {
						printf("\n\nhealing p=");
						scanf("%f",&p_heal);
						if (p_heal<0) {p_heal=0;}
						if (p_heal>1) {p_heal=1;}
					}
					if (position_==4) {
						printf("\n\nT=");
						scanf("%d",&T);
						if (T<1) {T=1;}
						if (T>100000) {T=100000;}
					}
					if (position_==5) {
						printf("\n\nhealing p=");
						scanf("%f",&p_sick);
						if (p_sick<0) {p_sick=0;}
						if (p_sick>1) {p_sick=1;}
					}
					if (position_==6) {
						printf("\n\nskip each=");
						scanf("%d",&T_skip);
						if (T_skip<1) {T_skip=1;}
						if (T_skip>T/2) {T_skip=T/2;}
					}
				}
			}
		}
		if (start==true) {
			system("cls");
			printf("abort - [SPACE]\n");
		}
		float a_stat=0,b_stat=0,c_stat=0,d_stat=0;
		int n_stat=0,stat_D[100];
		for (int k=0;k<100;k++) {stat_D[k]=0;}
		ch=0;
		while ((start==true)||((iterate==true)&&(ch!=' '))) {//starting the simulation
			start=false;
			if (iterate==true) {
				printf("__");
			}
			int xx,yy;
			
			for (int i=0;i<N;i++) {
				float ang=(rand()%1000)*2*pi/10000.0;
				Ob_dx[i]=v*cos(ang);
				Ob_dy[i]=v*sin(ang);
				Ob_x[i]=(rand()%10001)/10000.0*80;
				Ob_y[i]=(rand()%10001)/10000.0*100;
				Ob_cond[i]=0;
				
				xx=Ob_x[i]/1.5;
				yy=Ob_y[i]/1.5;
				
				if (mas_is[xx][yy]>=mas_max[xx][yy]*3/4) {
					mas_max[xx][yy]*=2;
					mas[xx][yy]=(int*)realloc(mas[xx][yy],(int)sizeof(int)*mas_max[xx][yy]);
				}
				mas[xx][yy][mas_is[xx][yy]]=i;
				mas_is[xx][yy]++;
				
				Ob_mx[i]=xx;
				Ob_my[i]=yy;
			}
			
			Ob_cond[0]=1;
			Ob_t[0]=t_distr[(int)((rand()%1001)/1000.0 * 100)]*24;
			
			ch=0;//preparations done, can run now
			for (int t=0;(t<T)&&(ch!=' ');t++) {
				if (kbhit()) {ch=getch();}
				for (int i=0;i<N;i++) {//movement
					
					int xx,yy;
					
					xx=Ob_mx[i];
					yy=Ob_my[i];
					int j=0;
					while ((mas[xx][yy][j]!=i)&&(j<mas_is[xx][yy])) {j++;}
					if (j<mas_is[xx][yy]) {
						mas[xx][yy][j]=mas[xx][yy][mas_is[xx][yy]-1];
						mas_is[xx][yy]--;
						if ((mas_is[xx][yy]<=mas_max[xx][yy]*1/4)&&(mas_max[xx][yy]>4)) {
							mas_max[xx][yy]/=2;
							mas[xx][yy]=(int*)realloc(mas[xx][yy],(int)sizeof(int)*mas_max[xx][yy]);
						}
					}
					
					Ob_x[i]+=Ob_dx[i];
					Ob_y[i]+=Ob_dy[i];
					
					xx=Ob_x[i]/1.5;
					yy=Ob_y[i]/1.5;
					
					Ob_mx[i]=xx;
					Ob_my[i]=yy;
					
					if (mas_is[xx][yy]>=mas_max[xx][yy]*3/4) {
						mas_max[xx][yy]*=2;
						mas[xx][yy]=(int*)realloc(mas[xx][yy],(int)sizeof(int)*mas_max[xx][yy]);
					}
					mas[xx][yy][mas_is[xx][yy]]=i;
					mas_is[xx][yy]++;
					
					if ((Ob_cond[i]<2)&&(Ob_dx[i]>0)&&(Ob_x[i]>80)) {Ob_dx[i]=-Ob_dx[i];}
					if ((Ob_dx[i]>0)&&(Ob_x[i]>100)) {Ob_dx[i]=-Ob_dx[i];}
					
					if ((Ob_cond[i]>2)&&(Ob_dx[i]<0)&&(Ob_x[i]<90)) {Ob_dx[i]=-Ob_dx[i];}
					if ((Ob_dx[i]<0)&&(Ob_x[i]<0)) {Ob_dx[i]=-Ob_dx[i];}
					
					if ((Ob_dy[i]>0)&&(Ob_y[i]>100)) {Ob_dy[i]=-Ob_dy[i];}
					if ((Ob_dy[i]<0)&&(Ob_y[i]<0)) {Ob_dy[i]=-Ob_dy[i];}
				}//getting infected
				for (int i=0;i<N;i++) {
					if (Ob_cond[i]==0) {
						int xx,yy;
						xx=Ob_x[i]/1.5;
						yy=Ob_y[i]/1.5;
						for (int xxx=xx-1;xxx<=xx+1;xxx++) {//a bit of optimisation comes
							for (int yyy=yy-1;yyy<=yy+1;yyy++) {
								if ((xxx>=0)&&(xxx<=70)&&(yyy>=0)&&(yyy<=70)) {
									for (int jj=0;jj<mas_is[xxx][yyy];jj++) {
										int j=mas[xxx][yyy][jj];
										if ((Ob_cond[j]==1)||(Ob_cond[j]==2)) {
											if (sq(Ob_x[i]-Ob_x[j])+sq(Ob_y[i]-Ob_y[j])<r*r) {
												if ((rand()%1000+1)/1000.0<p_sick) {Ob_cond[i]=1;}
											}
										}
									}
								}
							}
						}
						if (Ob_cond[i]==1) {
							Ob_t[i]=t_distr[(int)((rand()%1001)/1000.0 * 100)]*24;
						}
					} else {
						if (Ob_cond[i]!=3) {//for alive only
							if ((rand()%1000+1)/1000.0<p_heal) {//setting healthy (need to deal with optimisation grid a bit)
								Ob_cond[i]=0;
								if (Ob_x[i]>88) {Ob_x[i]=88;}//moving from hospital to the common area
								
								int xx,yy;
								
								xx=Ob_mx[i];
								yy=Ob_my[i];
								int j=0;//delete from the past position
								while ((mas[xx][yy][j]!=i)&&(j<mas_is[xx][yy])) {j++;}
								if (j<mas_is[xx][yy]) {
									mas[xx][yy][j]=mas[xx][yy][mas_is[xx][yy]-1];
									mas_is[xx][yy]--;
									if ((mas_is[xx][yy]<=mas_max[xx][yy]*1/4)&&(mas_max[xx][yy]>4)) {
										mas_max[xx][yy]/=2;
										mas[xx][yy]=(int*)realloc(mas[xx][yy],(int)sizeof(int)*mas_max[xx][yy]);
									}
								}
								
								xx=Ob_x[i]/1.5;
								yy=Ob_y[i]/1.5;//add to the current position
								if (mas_is[xx][yy]>=mas_max[xx][yy]*3/4) {
									mas_max[xx][yy]*=2;
									mas[xx][yy]=(int*)realloc(mas[xx][yy],(int)sizeof(int)*mas_max[xx][yy]);
								}
								mas[xx][yy][mas_is[xx][yy]]=i;
								mas_is[xx][yy]++;
								
								Ob_mx[i]=xx;
								Ob_my[i]=yy;
							}
							
							if (Ob_cond[i]==1) {//making infection observable (and deal with optimisation)
								if (Ob_t[i]==0) {
									Ob_cond[i]=2;
									Ob_x[i]=100-(rand()%1000)*10/1000.0;//move to hospital
									
									int xx,yy;
									
									xx=Ob_mx[i];
									yy=Ob_my[i];
									int j=0;//delete from the past position
									while ((mas[xx][yy][j]!=i)&&(j<mas_is[xx][yy])) {j++;}
									if (j<mas_is[xx][yy]) {
										mas[xx][yy][j]=mas[xx][yy][mas_is[xx][yy]-1];
										mas_is[xx][yy]--;
										if ((mas_is[xx][yy]<=mas_max[xx][yy]*1/4)&&(mas_max[xx][yy]>4)) {
											mas_max[xx][yy]/=2;
											mas[xx][yy]=(int*)realloc(mas[xx][yy],(int)sizeof(int)*mas_max[xx][yy]);
										}
									}
									
									xx=Ob_x[i]/1.5;
									yy=Ob_y[i]/1.5;//add to the current position
									if (mas_is[xx][yy]>=mas_max[xx][yy]*3/4) {
										mas_max[xx][yy]*=2;
										mas[xx][yy]=(int*)realloc(mas[xx][yy],(int)sizeof(int)*mas_max[xx][yy]);
									}
									mas[xx][yy][mas_is[xx][yy]]=i;
									mas_is[xx][yy]++;
									
									Ob_mx[i]=xx;
									Ob_my[i]=yy;
								} else {
									Ob_t[i]--;
								}
							}
							
							if ((Ob_cond[i]==2)&&((rand()%1000+1)/1000.0<p_kill)) {//death
								Ob_cond[i]=3;
								int xx,yy;
								xx=Ob_mx[i];
								yy=Ob_my[i];
								int j=0;
								while ((mas[xx][yy][j]!=i)&&(j<mas_is[xx][yy])) {j++;}
								if (j<mas_is[xx][yy]) {
									mas[xx][yy][j]=mas[xx][yy][mas_is[xx][yy]-1];
									mas_is[xx][yy]--;
									if ((mas_is[xx][yy]<=mas_max[xx][yy]*1/4)&&(mas_max[xx][yy]>4)) {
										mas_max[xx][yy]/=2;
										mas[xx][yy]=(int*)realloc(mas[xx][yy],(int)sizeof(int)*mas_max[xx][yy]);
									}
								}
							}
						}
					}
				}
				
				if (((t%T_skip==0)&&(iterate==false))||((t==T-1)&&(iterate==true))) {
					int a=0,b=0,c=0,d=0;
					for (int i=0;i<N;i++) {//seeing how many of who
						if (Ob_cond[i]==0) {a++;}
						if (Ob_cond[i]==1) {b++;}
						if (Ob_cond[i]==2) {c++;}
						if (Ob_cond[i]==3) {d++;}
					}
					if (iterate==true) {
						printf("%d %d %d %d\n",a,b,c,d);
						n_stat++;
						a_stat+=a;
						b_stat+=b;
						c_stat+=c;
						d_stat+=d;
						stat_D[d*100/N]+=1;//statistics is being collected if asked
					} else {
						float aa=a*20.0/N;//drawing faces
						float bb=b*20.0/N;
						float cc=c*20.0/N;
						float dd=d*20.0/N;
						a=(int)(aa);
						b=(int)(bb);
						c=(int)(cc);
						d=(int)(dd);
						if (a+b+c+d<20) {//in case rounding made a mistakes need to correct it a bit
							while (a+b+c+d<20) {
								if ((aa-a>=bb-b)&&(aa-a>=cc-c)&&(aa-a>=dd-d)) {a++;} else {
									if ((bb-b>=aa-a)&&(bb-b>=cc-c)&&(bb-b>=dd-d)) {b++;} else {
										if ((cc-c>=aa-a)&&(cc-c>=bb-b)&&(cc-c>=dd-d)) {c++;} else {
											d++;
										}
									}
								}
							}
						}
						for (int i=0;i<a;i++) {printf(":) ");}//healthy
						for (int i=0;i<b;i++) {printf(":| ");}//sick,nonobservable
						for (int i=0;i<c;i++) {printf(":( ");}//sick,observable
						for (int i=0;i<d;i++) {printf(":X ");}//dead
						printf("\n");
					}
				}
			}
			if (iterate==false) {
				printf("press [SPACE] to return back");
				while (ch!=' ') {ch=getch();}
			}
		}
		ch=0;
		if (iterate==true) {
			iterate=false;
			if (n_stat>0) {
				printf("\n\n\n");
				printf("mean:\n");//show statistics
				printf(":) - %.5f%\n",a_stat*100.0/n_stat/N);
				printf(":| - %.5f%\n",b_stat*100.0/n_stat/N);
				printf(":( - %.5f%\n",c_stat*100.0/n_stat/N);
				printf(":X - %.5f%\n",d_stat*100.0/n_stat/N);
				printf("\n death distribution:\n");//draw a plot
				for (int i=0;i<20;i++) {
					for (int j=0;j<20;j++) {
						if (stat_D[5*j]+stat_D[5*j+1]+stat_D[5*j+2]+stat_D[5*j+3]+stat_D[5*j+4]>5*(20-i)*n_stat/100) {printf("## ");} else {printf(".. ");}
					}
					printf("\n");
				}
				for (int i=0;i<20;i++) {printf("%2d ",i*5);}
			} else {//no observations -> no output (/0 otherwise)
				printf("could not collect data \\_(*.*)_/\n");
			}
			printf("press [SPACE] to return back");
			while (ch!=' ') {ch=getch();}
		}
	}
	printf("Thanx for using");
	return 0;
}
