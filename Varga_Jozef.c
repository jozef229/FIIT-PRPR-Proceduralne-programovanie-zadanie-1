#include <stdio.h>
#include <stdlib.h>

void V_vypis(FILE **subor){
    int x=0,y=0;
    char c;
    if ((*subor = fopen("ZAMESTNANCI.TXT", "r")) == NULL) {
        printf("Neotvoreny subor\n");
    }
    else {
        while((c=getc(*subor))!= EOF){
            if(c=='\n'){
                x++;
                printf("\n");
                if(x==6)x=0;
                y=x;
            }
            else switch(x){
                case 0:{
                    if(x==y)printf("osobne cislo zamestnanca: %c",c);
                    else printf("%c",c);
                    y++;
                }break;
                case 1:{
                    if(x==y)printf("meno priezvisko: %c",c);
                    else printf("%c",c);
                    y++;
                }break;
                case 2:{
                    if(x==y)printf("administrativa/vyrobny pracovnik: %c",c);
                    else printf("%c",c);
                    y++;
                }break;
                case 3:{
                    if(x==y)printf("plat: %c",c);
                    else printf("%c",c);
                    y++;
                }break;
                case 4:{
                    if(x==y)printf("datum: %c",c);
                    else printf("%c",c);
                    y++;
                }break;
            }
        }
    }
    if (*subor != NULL)printf("\n");
}

void P_naj_plat(FILE **subor){
	int pomoc=0,rok=0,cislo_zaznamu=0,x=0,b=0,i=0,y=0,z=0;
	char rocnik[4]={'0','0','0','0'},plat[7],c,pracovnik;
	double pomoc_plat=100000.00,cislo;
	if(*subor!=NULL){	
		rewind(*subor);
	    while((c=getc(*subor))!= EOF){
	        if(c=='\n'){
	            x++;
	            if(x==6){
	            	for(b=0;b<7;b++)if(plat[b]=='.')plat[b+3]=0;
	                sscanf(plat, "%lf", &cislo);
	                sscanf(rocnik, "%d", &rok);
	                
					if(pomoc<=rok&&pracovnik=='0'){
						if(pomoc==rok&&cislo<pomoc_plat){
							pomoc_plat=cislo;
						}
						else if(pomoc==rok&&cislo>pomoc_plat);
						else{
							pomoc=rok;
							cislo_zaznamu=i;
							pomoc_plat=cislo;
						}
					}
	            	x=0;
	            	i++;
	            }
	        	y=x;
	        	z=x;
	        }
	        else if(x==2){
		        if(y==2)pracovnik=c;
		        y++;
	        }
	        else if(x==4){
	            if(y>7){
				rocnik[y-7]=c;
				}
	            y++;
	        }
	        else if(x==3){
	            plat[z-3]=c;
	            z++;
	        }
	    }
	    for(b=0;b<7;b++)if(plat[b]=='.')plat[b+3]=0;
	    sscanf(plat, "%lf", &cislo);
	    sscanf(rocnik, "%d", &rok);
		if(pomoc<=rok&&pracovnik=='0'){
			if(pomoc==rok&&cislo<pomoc_plat){
				pomoc_plat=cislo;
			}
			else if(pomoc==rok&&cislo>pomoc_plat);
			else{
				pomoc=rok;
				cislo_zaznamu=i;
				pomoc_plat=cislo;
			}
		}
	if(pomoc_plat!=100000.00)printf("%.2lf\n",pomoc_plat);
	}
	else *subor=NULL;
}

void N_plat_zamestnancov(FILE **subor, int *pocet, double **platy){
	if(*subor!=NULL){
		if(*platy!=NULL)free(*platy);
	    *pocet=1;
		double cislo;
	  	int x=0,y=0,i=0,b=0;
	    char c, plat[7];
		rewind(*subor);
	    while((c=getc(*subor))!= EOF){
	        if(c=='\n'){
	            x++;
	            if(x==6){
				x=0;
				*pocet=*pocet+1;
				}
	        }
	    }
	    rewind(*subor);
	    if((*platy =(double *) malloc((*pocet)*(sizeof(double))))==NULL)printf("nedostatok pamate");
	    x=0; 
	    while((c=getc(*subor))!= EOF){
	    
	        if(c=='\n'){
	            x++;
	            if(x==6){
	            	for(b=0;b<7;b++)if(plat[b]=='.')plat[b+3]=0;
	                sscanf(plat, "%lf", &cislo);
					*(*platy+i)=cislo;
	                x=0;
	                i++;
	            }
	            y=x;
	        }
	        else if(x==3){
	            plat[y-3]=c;
	            y++;
	        }
	    }
	    for(b=0;b<7;b++)if(plat[b]=='.')plat[b+3]=0;
	    sscanf(plat, "%lf", &cislo);
	    *(*platy+i)=cislo;
	}
	else *subor=NULL;
}

void R_vypis_pola(int *pocet, double **platy){
	if(*platy!=NULL){
	    int i,velkost[*pocet],pomoc=0,x=0;
	    for(i=0;i<(*pocet);i++){
	    	if(*(*platy+i)<10)velkost[i]=1;
	    	else if(*(*platy+i)<100)velkost[i]=2;
	    	else if(*(*platy+i)<1000)velkost[i]=3;
	    	else if(*(*platy+i)<10000)velkost[i]=4;
	    	else velkost[i]=5;
			}
		for(i=0;i<(*pocet);i++){
			if(pomoc<velkost[i])pomoc=velkost[i];
		}
		for(i=0;i<(*pocet);i++){
	    	for(x=0;x<pomoc-velkost[i];x++)printf(" ");
	    	printf("%.2lf\n",*(*platy+i));
			}
	}
	else printf("Pole nie je vytvorene\n");
}

void H_histogram(int *pocet, double **platy){
	if(*platy!=NULL){
	    int i,x;
	    long pomoc,sranda;
	    long cislo,histogram[10]={0,0,0,0,0,0,0,0,0,0};
	    for(i=0;i<(*pocet);i++){
	    	
	    	pomoc=(*(*platy+i));
	    	if(pomoc<=9){
	    		for(x=0;x<=9;x++)if(x==pomoc)histogram[x]++;	
			}
	    	else if(pomoc<=99){
				sranda=pomoc;
				pomoc=pomoc/10;
				for(x=0;x<=9;x++)if(x==pomoc)histogram[x]++;	
				pomoc=pomoc*10;
				pomoc=sranda-pomoc;
				for(x=0;x<=9;x++)if(x==pomoc)histogram[x]++;
			}
	    	else if(pomoc<=999){
	    		sranda=pomoc;
				pomoc=pomoc/100;
				for(x=0;x<=9;x++)if(x==pomoc)histogram[x]++;	
				pomoc=pomoc*100;
				sranda=sranda-pomoc;
				pomoc=sranda/10;
				for(x=0;x<=9;x++)if(x==pomoc)histogram[x]++;
				pomoc=pomoc*10;
				pomoc=sranda-pomoc;
				for(x=0;x<=9;x++)if(x==pomoc)histogram[x]++;
			}
	    	else if(pomoc<=9999){	
	    		sranda=pomoc;
				pomoc=pomoc/1000;
				for(x=0;x<=9;x++)if(x==pomoc)histogram[x]++;	
				pomoc=pomoc*1000;
				sranda=sranda-pomoc;
				pomoc=sranda/100;
				for(x=0;x<=9;x++)if(x==pomoc)histogram[x]++;
				pomoc=pomoc*100;
				sranda=sranda-pomoc;
				pomoc=sranda/10;
				for(x=0;x<=9;x++)if(x==pomoc)histogram[x]++;
				pomoc=pomoc*10;
				pomoc=sranda-pomoc;
				for(x=0;x<=9;x++)if(x==pomoc)histogram[x]++;
			}
			else if(pomoc<=99999){
				sranda=pomoc;
				pomoc=pomoc/10000;
				for(x=0;x<=9;x++)if(x==pomoc)histogram[x]++;	
				pomoc=pomoc*10000;
				sranda=sranda-pomoc;
				pomoc=sranda/1000;
				for(x=0;x<=9;x++)if(x==pomoc)histogram[x]++;
				pomoc=pomoc*1000;
				sranda=sranda-pomoc;
				pomoc=sranda/100;
				for(x=0;x<=9;x++)if(x==pomoc)histogram[x]++;
				pomoc=pomoc*100;
				sranda=sranda-pomoc;
				pomoc=sranda/10;
				for(x=0;x<=9;x++)if(x==pomoc)histogram[x]++;
				pomoc=pomoc*10;
				pomoc=sranda-pomoc;
				for(x=0;x<=9;x++)if(x==pomoc)histogram[x]++;
			}
		}
		for(x=0;x<=9;x++)printf("%d %d\n",x,histogram[x]);
		
	}
	else printf("Pole nie je vytvorene\n");
}

void U_zoradenie(int *pocet, double **platy){
	int x,y;
	double swap;
	for(x=0;x<(*(pocet)+1);x++){
		for(y=0;y<(*(pocet)-x-1);y++){
			if((*(*platy+y))>(*(*platy+(y+1)))){
				swap=(*(*platy+y));
        		(*(*platy+y))=(*(*platy+(y+1)));
        		(*(*platy+(y+1)))=swap;
			}
		}
	}
}

int main(){		
	FILE *subor=NULL;
    double *platy= NULL;
    int pocet;
    char vstup;
    while (1) {
    	vstup=getchar();
        switch(vstup){
            case 'V':V_vypis(&subor);break;
            case 'P':P_naj_plat(&subor);break;
            case 'N':N_plat_zamestnancov(&subor, &pocet, &platy);break;
            case 'R':R_vypis_pola(&pocet, &platy);break;
            case 'H':H_histogram(&pocet, &platy);break;
            case 'U':U_zoradenie(&pocet, &platy);break;
            case 'K':{
            	if(subor!=NULL)fclose(subor);
            	if(platy!=NULL)free(platy);
				return 0;
				}break;
        }
    }
    if(subor!=NULL)fclose(subor);
    free(platy);
    return 0;
}
