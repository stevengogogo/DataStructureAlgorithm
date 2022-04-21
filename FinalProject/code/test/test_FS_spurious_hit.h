#ifndef TEST_FS_SPURIOUS_HIT_H
#define TEST_FS_SPURIOUS_HIT_H
#include "utils.h"
#include "FindSimilar.h"
#include <string.h>
#include <stdlib.h>
/*
https://design215.com/toolbox/wordlist.php
https://convert.town/column-to-comma-separated-list
*/

static void PrintAllToken(char message[]){
    int iStr = 0;
    int iNxt;
    int hash;
    char tokenB[10000];
    printf("\n");
    while(1){
        iNxt = popTokenHash(message, tokenB, iStr, &hash);
        if(iNxt==-1){
            break;
        }
        iStr = iNxt;
        printf("%s ", tokenB);
    }
}

void test_check_spurious(void){
    char* hashmap[Q_RABIN];
    for(int i=0;i<Q_RABIN;i++){
        hashmap[i] = (char*)malloc(1000*sizeof(char));
    }

    char token6286[10000] = "a,and,antbird,antbirds,are,backed,bird,bolivia,brazil,colombia,ecuador,family,forests,found,french,guiana,guyana,habitats,http,hylophylax,i,in,is,it,its,lowland,moist,naevia,naevius,natural,of,on,or,org,paragraph,peru,read,species,spot,subtropical,suriname,swamps,thamnophilidae,the,tropical,venezuela,wikipedia\0";
    double tk6286 = 226;

    char token676[10000] = "a,actually,adrift,after,agree,all,also,alternate,an,and,announces,appear,are,around,arrested,as,ashore,at,battling,be,beak,beak,because,been,being,black,book,buccaneers,buried,bursts,but,by,called,can,can,captain,captures,caribbean,cartoon,celebrate,century,chest,comic,contains,counterfeit,crew,dated,dead,decoy,directly,discussion,disguises,disney,donald,down,drop,duck,eating,echo,eight,end,endings,ends,england,eyes,film,find,finds,first,fish,for,found,from,game,gap,get,getting,geysers,ghost,ghosts,gloom,gold,good,goofy,got,guys,had,has,have,haven,he,heading,headline,heard,hearted,help,henry,hidden,hiding,him,himself,his,http,hunters,i,if,in,interludes,is,island,it,just,later,lease,leg,lifted,location,long,loot,losing,lost,man,map,men,mickey,morgan,morgan,mouse,named,new,newspaper,night,no,not,nutty,obtain,of,off,offers,old,on,one,org,over,overhears,owners,paragraph,parrot,passing,peg,persuades,pete,pieces,pirate,pirates,place,placed,plants,pointer,production,quicksand,raft,read,real,rear,released,remembered,rescue,returning,reveal,ride,sea,series,sets,share,ship,skunk,slapstick,small,so,stormy,story,take,taking,tales,tattoo,tattooed,tavern,tell,that,the,their,them,there,they,this,three,tiny,to,trapped,treasure,treasure,trio,tropical,true,trying,two,unreleased,version,very,village,visited,was,wash,were,what,when,where,which,who,whom,wikipedia,with,woman,would,yellow\0";
    double tk676 = 47;

    char tokenUnion[100000] = "a,actually,adrift,after,agree,all,also,alternate,an,and,announces,antbird,antbirds,appear,are,around,arrested,as,ashore,at,backed,battling,be,beak,because,been,being,bird,black,bolivia,book,brazil,buccaneers,buried,bursts,but,by,called,can,captain,captures,caribbean,cartoon,celebrate,century,chest,colombia,comic,contains,counterfeit,crew,dated,dead,decoy,directly,discussion,disguises,disney,donald,down,drop,duck,eating,echo,ecuador,eight,end,endings,ends,england,eyes,family,film,find,finds,first,fish,for,forests,found,french,from,game,gap,get,getting,geysers,ghost,ghosts,gloom,gold,good,goofy,got,guiana,guyana,guys,habitats,had,has,have,haven,he,heading,headline,heard,hearted,help,henry,hidden,hiding,him,himself,his,http,hunters,hylophylax,i,if,in,interludes,is,island,it,its,just,later,lease,leg,lifted,location,long,loot,losing,lost,lowland,man,map,men,mickey,moist,morgan,mouse,naevia,naevius,named,natural,new,newspaper,night,no,not,nutty,obtain,of,off,offers,old,on,one,or,org,over,overhears,owners,paragraph,parrot,passing,peg,persuades,peru,pete,pieces,pirate,pirates,place,placed,plants,pointer,production,quicksand,raft,read,real,rear,released,remembered,rescue,returning,reveal,ride,sea,series,sets,share,ship,skunk,slapstick,small,so,species,spot,stormy,story,subtropical,suriname,swamps,take,taking,tales,tattoo,tattooed,tavern,tell,thamnophilidae,that,the,their,them,there,they,this,three,tiny,to,trapped,treasure,trio,tropical,true,trying,two,unreleased,venezuela,version,very,village,visited,was,wash,were,what,when,where,which,who,whom,wikipedia,with,woman,would,yellow\0";
    double tkInter = 256;



    int iStr = 0;
    int iNxt;
    int hash;
    char tokenB[10000];
    while(1){
        iNxt = popTokenHash(tokenUnion, tokenB, iStr, &hash);
        if(iNxt==-1){
            break;
        }
        iStr = iNxt;
        if(strncmp(hashmap[hash], tokenB, strlen(tokenB)) != 0 && hashmap[hash][0]!='\0'){
            printf("Spurious Hit: %s / %s with ID=%d\n", hashmap[hash], tokenB, hash);
        };
        strncpy(hashmap[hash], tokenB, strlen(tokenB)+1);
    }


    //Free
    for(int i=0;i<Q_RABIN;i++){
        free(hashmap[i]);
    }
}


void test_check_spurious2(void){
    char* hashmap[Q_RABIN];
    for(int i=0;i<Q_RABIN;i++){
        hashmap[i] = (char*)malloc(1000*sizeof(char));
    }
    char text6286[100000] = "Hylophylax naevia The Spot-backed Antbird (Hylophylax naevius) is a species of bird in the Thamnophilidae family, the antbirds. It is found in Bolivia, Brazil, Colombia, Ecuador, French Guiana, Guyana, Peru, Suriname, and Venezuela. Its natural habitats are subtropical or tropical moist lowland forests and subtropical or tropical swamps.  I read the paragraph on http://wikipedia.org  Spot-backed Antbird\0";

    char text1648[100000] = "The depiction of disability in the media plays a major role in forming public perception of disability. Perceptions created by the media informs the way people with disabilities are treated in society. \"The media have been cited as a key site for the reinforcement of negative images and ideas in regard to people with disabilities.\"[1] In response, there have been increasing examples worldwide of people with disabilities pursuing their own media projects, such as film series centered on disability issues, radio programs and podcasts designed around and marketed towards those with disabilities, and so on. This is seen by many disability rights activists as a way to, as some in these circles term it, \"piss on pity\". The media generally depict people with disabilities according to common stereotypes such as pity and heroism.[2] Disability advocates often call this type of societal situation the \"pity/heroism trap\" or \"pity/heroism dichotomy\"[2] and call instead for its supporters to \"Piss On Pity\" and push forward with inclusion instead.[3] When reports are about the \"plight of the disabled\" they rely on the pity or medical model of disability. Telethons are an example of this, such as the Jerry Lewis MDA Telethon which has been heavily criticised and sometimes even physically protested by disability rights advocates.[4] Negative day-to-day reporting may occur chiefly by depicting a given person or people with a disability as a burden or drain on society.[5] The \"super-crip\" model, in which subjects are portrayed as heroically overcoming their afflictions, is also often used when reporting on sport.[1] The social model tends to be used for reporting on the activities of disability rights activists if the report is positive.[6] Ouch![1] by the British Broadcasting Corporation, The Largest Minority[2] broadcast in New York City, and a show presented in sign language on SABC television in South Africa, Dtv[3], are examples of programming produced for, and usually also by, disabled people. Radio reading services are radio stations that broadcast readings from newspapers, magazines and books to mainly blind or partially sighted audiences. Many activist and charitable organisations have websites and publish their own magazines or newsletters. Various organisations and programmes have been established to try to positively influence the frequency and quality of reporting on disability issues.[7][8][9][10] I read the paragraph on http://wikipedia.org Disability in the media\0";

    char token6286[100000] = "a, and, antbird, antbirds, are, backed, bird, bolivia, brazil, colombia, ecuador, family, forests, found, french, guiana, guyana, habitats, http, hylophylax, i, in, is, it, its, lowland, moist, naevia, naevius, natural, of, on, or, org, paragraph, peru, read, species, spot, subtropical, suriname, swamps, thamnophilidae, the, tropical, venezuela, wikipedia\0";
    double tk6286 = 47;

    char token1648[100000] = "1, 10, 2, 3, 4, 5, 6, 7, 8, 9, a, about, according, activist, activists, activities, advocates, afflictions, africa, also, an, and, are, around, as, audiences, be, been, blind, books, british, broadcast, broadcasting, burden, by, call, centered, charitable, chiefly, circles, cited, city, common, corporation, created, crip, criticised, day, depict, depicting, depiction, designed, dichotomy, disabilities, disability, disabled, drain, dtv, established, even, example, examples, film, for, forming, forward, frequency, from, generally, given, has, have, heavily, heroically, heroism, http, i, ideas, if, images, in, inclusion, increasing, influence, informs, instead, is, issues, it, its, jerry, key, language, largest, lewis, magazines, mainly, major, many, marketed, may, mda, media, medical, minority, model, negative, new, newsletters, newspapers, occur, of, often, on, or, org, organisations, ouch, overcoming, own, paragraph, partially, people, perception, perceptions, person, physically, piss, pity, plays, plight, podcasts, portrayed, positive, positively, presented, produced, programmes, programming, programs, projects, protested, public, publish, pursuing, push, quality, radio, read, reading, readings, regard, reinforcement, rely, report, reporting, reports, response, rights, role, sabc, seen, series, services, show, sighted, sign, site, situation, so, social, societal, society, some, sometimes, south, sport, stations, stereotypes, subjects, such, super, supporters, telethon, telethons, television, tends, term, that, the, their, there, these, they, this, those, to, towards, trap, treated, try, type, used, usually, various, way, websites, when, which, wikipedia, with, worldwide, york\0";
    double tk1648 = 213;

    char tokenUnion[1000000] = "1, 10, 2, 3, 4, 5, 6, 7, 8, 9, a, about, according, activist, activists, activities, advocates, afflictions, africa, also, an, and, antbird, antbirds, are, around, as, audiences, backed, be, been, bird, blind, bolivia, books, brazil, british, broadcast, broadcasting, burden, by, call, centered, charitable, chiefly, circles, cited, city, colombia, common, corporation, created, crip, criticised, day, depict, depicting, depiction, designed, dichotomy, disabilities, disability, disabled, drain, dtv, ecuador, established, even, example, examples, family, film, for, forests, forming, forward, found, french, frequency, from, generally, given, guiana, guyana, habitats, has, have, heavily, heroically, heroism, http, hylophylax, i, ideas, if, images, in, inclusion, increasing, influence, informs, instead, is, issues, it, its, jerry, key, language, largest, lewis, lowland, magazines, mainly, major, many, marketed, may, mda, media, medical, minority, model, moist, naevia, naevius, natural, negative, new, newsletters, newspapers, occur, of, often, on, or, org, organisations, ouch, overcoming, own, paragraph, partially, people, perception, perceptions, person, peru, physically, piss, pity, plays, plight, podcasts, portrayed, positive, positively, presented, produced, programmes, programming, programs, projects, protested, public, publish, pursuing, push, quality, radio, read, reading, readings, regard, reinforcement, rely, report, reporting, reports, response, rights, role, sabc, seen, series, services, show, sighted, sign, site, situation, so, social, societal, society, some, sometimes, south, species, sport, spot, stations, stereotypes, subjects, subtropical, such, super, supporters, suriname, swamps, telethon, telethons, television, tends, term, thamnophilidae, that, the, their, there, these, they, this, those, to, towards, trap, treated, tropical, try, type, used, usually, various, venezuela, way, websites, when, which, wikipedia, with, worldwide, york\0";
    double tkUnion = 243;

    //PrintAllToken(text6286);
    printf("\n");

    int iStr = 0;
    int iNxt;
    int hash;
    char tokenB[10000];
    printf("\nSimilarity: %f (Threshold in PB %d: %f) Between Email: %d vs %d\n", (tk6286+tk1648 - tkUnion)/ tkUnion,91,0.070000, 1648, 1099);
    while(1){
        iNxt = popTokenHash(tokenUnion, tokenB, iStr, &hash);
        if(iNxt==-1){
            break;
        }
        iStr = iNxt;
        if(strncmp(hashmap[hash], tokenB, strlen(tokenB)) != 0 && hashmap[hash][0]!='\0'){
            printf("Spurious Hit: %s / %s with ID=%d\n", hashmap[hash], tokenB, hash);
        };
        strncpy(hashmap[hash], tokenB, strlen(tokenB)+1);
    }


    //Free
    for(int i=0;i<Q_RABIN;i++){
        free(hashmap[i]);
    }
}


#endif 