#include "api.h"
#include "ExpressionMatch.h"
#include "FindSimilar.h"
#include "GroupAnalysis.h"
#include "ExpressionMatch.h"
#include "utils.h"
#include <stdio.h>
#include <time.h>

/*
static void get_mails(char* filename, mail** mails, int* num_mail){
    FILE* fp;
    size_t len;
    ssize_t read;
    //Mail info
    int id;
    int maxnum = 1000000;
    char* line = (char *) malloc(maxnum);
    char* from= (char *) malloc(maxnum);
    char* subject= (char *) malloc(maxnum);
    char* idstr= (char *) malloc(maxnum);
    char* content= (char *) malloc(maxnum);
    char* to= (char *) malloc(maxnum);
    size_t buffer=32;
    size_t chr;
    

    fp = fopen(filename, "r");
    if (fp == NULL)
        printf("File not found");

    chr = getline(&idstr,&buffer,fp);
    sscanf(idstr, "%d", num_mail);
    *mails = (mail*)malloc(*num_mail*sizeof(mail));
    
    for(int i=0;i<*num_mail;i++){
       
        chr = getline(&line,&buffer,fp);
        chr = getline(&idstr,&buffer,fp);
        chr = getline(&from,&buffer,fp);
        chr = getline(&content,&buffer,fp);
        chr = getline(&subject,&buffer,fp);
        chr = getline(&to,&buffer,fp);

        sscanf(idstr, "%d", &id);
        //Check content
        //Copy mail information
        (*mails)[i].id = id;
        strcpy((*mails)[i].subject, subject);
        strcpy((*mails)[i].content, content);
        strcpy((*mails)[i].from, from);
        strcpy((*mails)[i].to, to);
    }

    fclose(fp);
    free(line);
    free(idstr);
    free(content);
    free(subject);
    free(from);
    free(to);
}
int main(){
    
    char* hashmap[Q_RABIN];
    for(int i=0;i<Q_RABIN;i++){
        hashmap[i] = (char*)malloc(1000*sizeof(char));
    }

    char token6286[10000] = "a,and,antbird,antbirds,are,backed,bird,bolivia,brazil,colombia,ecuador,family,forests,found,french,guiana,guyana,habitats,http,hylophylax,i,in,is,it,its,lowland,moist,naevia,naevius,natural,of,on,or,org,paragraph,peru,read,species,spot,subtropical,suriname,swamps,thamnophilidae,the,tropical,venezuela,wikipedia\0";

    char token676[10000] = "a,actually,adrift,after,agree,all,also,alternate,an,and,announces,appear,are,around,arrested,as,ashore,at,battling,be,beak,beak,because,been,being,black,book,buccaneers,buried,bursts,but,by,called,can,can,captain,captures,caribbean,cartoon,celebrate,century,chest,comic,contains,counterfeit,crew,dated,dead,decoy,directly,discussion,disguises,disney,donald,down,drop,duck,eating,echo,eight,end,endings,ends,england,eyes,film,find,finds,first,fish,for,found,from,game,gap,get,getting,geysers,ghost,ghosts,gloom,gold,good,goofy,got,guys,had,has,have,haven,he,heading,headline,heard,hearted,help,henry,hidden,hiding,him,himself,his,http,hunters,i,if,in,interludes,is,island,it,just,later,lease,leg,lifted,location,long,loot,losing,lost,man,map,men,mickey,morgan,morgan,mouse,named,new,newspaper,night,no,not,nutty,obtain,of,off,offers,old,on,one,org,over,overhears,owners,paragraph,parrot,passing,peg,persuades,pete,pieces,pirate,pirates,place,placed,plants,pointer,production,quicksand,raft,read,real,rear,released,remembered,rescue,returning,reveal,ride,sea,series,sets,share,ship,skunk,slapstick,small,so,stormy,story,take,taking,tales,tattoo,tattooed,tavern,tell,that,the,their,them,there,they,this,three,tiny,to,trapped,treasure,treasure,trio,tropical,true,trying,two,unreleased,version,very,village,visited,was,wash,were,what,when,where,which,who,whom,wikipedia,with,woman,would,yellow\0";

    char tokenInter[100000] = "a,actually,adrift,after,agree,all,also,alternate,an,and,announces,antbird,antbirds,appear,are,around,arrested,as,ashore,at,backed,battling,be,beak,because,been,being,bird,black,bolivia,book,brazil,buccaneers,buried,bursts,but,by,called,can,captain,captures,caribbean,cartoon,celebrate,century,chest,colombia,comic,contains,counterfeit,crew,dated,dead,decoy,directly,discussion,disguises,disney,donald,down,drop,duck,eating,echo,ecuador,eight,end,endings,ends,england,eyes,family,film,find,finds,first,fish,for,forests,found,french,from,game,gap,get,getting,geysers,ghost,ghosts,gloom,gold,good,goofy,got,guiana,guyana,guys,habitats,had,has,have,haven,he,heading,headline,heard,hearted,help,henry,hidden,hiding,him,himself,his,http,hunters,hylophylax,i,if,in,interludes,is,island,it,its,just,later,lease,leg,lifted,location,long,loot,losing,lost,lowland,man,map,men,mickey,moist,morgan,mouse,naevia,naevius,named,natural,new,newspaper,night,no,not,nutty,obtain,of,off,offers,old,on,one,or,org,over,overhears,owners,paragraph,parrot,passing,peg,persuades,peru,pete,pieces,pirate,pirates,place,placed,plants,pointer,production,quicksand,raft,read,real,rear,released,remembered,rescue,returning,reveal,ride,sea,series,sets,share,ship,skunk,slapstick,small,so,species,spot,stormy,story,subtropical,suriname,swamps,take,taking,tales,tattoo,tattooed,tavern,tell,thamnophilidae,that,the,their,them,there,they,this,three,tiny,to,trapped,treasure,trio,tropical,true,trying,two,unreleased,venezuela,version,very,village,visited,was,wash,were,what,when,where,which,who,whom,wikipedia,with,woman,would,yellow\0";


    int iStr = 0;
    int iNxt;
    int hash;
    char tokenB[10000];
    while(1){
        iNxt = popTokenHash(tokenInter, tokenB, iStr, &hash);
        if(iNxt==-1){
            break;
        }
        if(strncmp(hashmap[hash], tokenB, strlen(tokenB)) != 0){
            printf("Spurious Hit: %s / %s with ID=%d", hashmap[hash], tokenB, hash);
        };
        strncpy(hashmap[hash], tokenB, strlen(tokenB)+1);
    }
}
*/




int main(void) {
    // Var: Api
    int n_mails, n_queries;
    mail *mails;
    query *queries;

    //Var: Find Similar
    int* list = (int*)malloc(MAX_N_MAIL*sizeof(int));
    int nlist;
    double threshold;

    int mid;
    infoFs infs;

    //Initiation

    //FS//
	api.init(&n_mails, &n_queries, &mails, &queries);   
    init_FS(&infs);

    //Answer
	for(int i = 0; i < n_queries; i++){

		//Find Similar
        if (queries[i].type == find_similar){
            //data
            mid = queries[i].data.find_similar_data.mid;
            threshold = queries[i].data.find_similar_data.threshold;

            //process

            answer_FS(&infs, mails, mid,n_mails, threshold, list, &nlist);


            //answer
            //if(queries[i].data.find_similar_data.threshold>=-1){
            api.answer(queries[i].id, list, nlist);
            //}
        }
        
        //Expression Match
        else if(queries[i].type == expression_match){
			//answer_ExpressionMatch(queries[i].data.expression_match_data.expression,mails,list,&nlist);
		    //api.answer(queries[i].id, list, nlist);
        }

        //Group Analysis
        else {

            answer_GroupAnalysis(queries[i].data.group_analyse_data.mids, queries[i].data.group_analyse_data.len,mails, list, &nlist);
            api.answer(queries[i].id, list, nlist);
   
        }
    }

    //Garbage Collection
    //kill_FindSimilar(smrys, n_mails);
    free(mails);
    free(queries);
    free(list);

    return 0;
}
